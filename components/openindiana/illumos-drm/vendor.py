#!/usr/bin/python3.13
#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2026 Till Wegmueller
#

"""Download Cargo.lock's immutable crate archives and vendor the pinned DDI.

Called only by download. Registry archives are checked against Cargo.lock;
source archives are checked by userland-fetch before this script runs.
"""
import hashlib
import json
import re
from pathlib import Path
import shutil
import sys
import tarfile
import tomllib
import urllib.request

source, ddi, cache, dest = map(Path, sys.argv[1:])
cache = cache / 'illumos-drm-crates'
cache.mkdir(parents=True, exist_ok=True)
if dest.exists():
    shutil.rmtree(dest)
dest.mkdir()
with tarfile.open(source) as archive:
    lock = next(m for m in archive.getmembers() if m.name.endswith('/Cargo.lock'))
    packages = tomllib.loads(archive.extractfile(lock).read().decode())['package']


def checksum(directory, package=None):
    files = {str(p.relative_to(directory)): hashlib.sha256(p.read_bytes()).hexdigest()
             for p in sorted(directory.rglob('*')) if p.is_file()
             and p.name != '.cargo-checksum.json'}
    (directory / '.cargo-checksum.json').write_text(
        json.dumps({'files': files, 'package': package}, sort_keys=True))


for package in packages:
    if not package.get('source', '').startswith('registry+'):
        continue
    name, version = package['name'], package['version']
    filename = cache / f'{name}-{version}.crate'
    if not filename.exists():
        print(f'Downloading {name} {version}', flush=True)
        url = f'https://static.crates.io/crates/{name}/{name}-{version}.crate'
        with urllib.request.urlopen(url) as response:
            filename.write_bytes(response.read())
    if hashlib.sha256(filename.read_bytes()).hexdigest() != package['checksum']:
        raise SystemExit(f'Checksum mismatch: {filename}')
    with tarfile.open(filename) as archive:
        archive.extractall(dest, filter='data')
    checksum(dest / f'{name}-{version}', package['checksum'])

# The git workspace crates retain their original Cargo.toml and source.
# Cargo accepts a directory source in place of the git revision when each
# member has a checksum file, just as cargo vendor produces.
with tarfile.open(ddi) as archive:
    scratch = dest / '.ddi'
    archive.extractall(scratch, filter='data')
root = next(scratch.iterdir())
for package in packages:
    if not package.get('source', '').startswith('git+'):
        continue
    name = package['name']
    manifests = [p for p in root.rglob('Cargo.toml')
                 if tomllib.loads(p.read_text()).get('package', {}).get('name') == name]
    if len(manifests) != 1:
        raise SystemExit(f'Cannot locate pinned git crate: {name}')
    src = manifests[0].parent
    target = dest / f"{name}-{package['version']}"
    shutil.copytree(src, target)
    # cargo vendor resolves workspace.package inheritance for git members.
    manifest = tomllib.loads((src / 'Cargo.toml').read_text())
    workspace = tomllib.loads((root / 'Cargo.toml').read_text())
    text = (target / 'Cargo.toml').read_text()
    for key, value in workspace.get('workspace', {}).get('package', {}).items():
        text = re.sub(r'^' + re.escape(key) + r'\.workspace\s*=\s*true$',
                      f'{key} = {json.dumps(value)}', text, flags=re.M)
    # DDI member dependencies use workspace inheritance too.
    for key, value in workspace.get('workspace', {}).get('dependencies', {}).items():
        if isinstance(value, dict):
            value = dict(value)
            if 'path' in value:
                value['path'] = '../' + Path(value['path']).name
            inline = '{ ' + ', '.join(f'{k} = {json.dumps(v)}' for k, v in value.items()) + ' }'
        else:
            inline = json.dumps(value)
        text = re.sub(r'^' + re.escape(key) + r'\.workspace\s*=\s*true$',
                      key + ' = ' + inline, text, flags=re.M)
        # Inline member overrides (e.g. optional = true) augment the inherited
        # dependency without retaining a path into the original git workspace.
        def override(match):
            extra = match.group(1)
            if inline.startswith('{'):
                return key + ' = ' + inline[:-2] + ', ' + extra + ' }'
            return key + ' = { version = ' + inline + ', ' + extra + ' }'
        text = re.sub(r'^' + re.escape(key) + r' = \{ workspace = true, (.+) \}$',
                      override, text, flags=re.M)
    tomllib.loads(text)  # Reject malformed normalization before stamping.
    (target / 'Cargo.toml').write_text(text)
    checksum(target)
shutil.rmtree(scratch)
print('Vendored all locked registry and git dependencies', flush=True)
