#!/usr/bin/bash
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

set -euo pipefail
export PATH=/usr/gnu/bin:/usr/bin:/usr/sbin
source=$1 linux=$2 out=$3 archives=$4 vendor=$5 rust_src=$6
mkdir -p "$out/sysinc/drm" "$out/tmp" "$source/.cargo"
export TMPDIR=$out/tmp
for f in /usr/include/*; do
    [ "$(basename "$f")" = drm ] || ln -sfn "$f" "$out/sysinc/"
done
cp "${archives}gfx-drm-e95220c-drm.h" "$out/sysinc/drm/drm.h"
cp "${archives}gfx-drm-e95220c-drm_mode.h" "$out/sysinc/drm/drm_mode.h"
cp "${archives}illumos-ddi-cda5b9a49f.mapfile" "$out/ddi.mapfile"
# OI rust-src ships its own vendored sysroot dependencies. Include them in
# the same directory source, so -Zbuild-std also works with an empty cache.
for d in "$rust_src"/vendor/*; do
    [ -d "$d" ] || continue
    name=$(basename "$d")
    [ -e "$vendor/$name" ] || ln -s "$d" "$vendor/$name"
done
cat > "$source/.cargo/config.toml" <<CONFIG
[source.crates-io]
replace-with = "oi-vendor"
[source.illumos-ddi]
git = "https://code.aopc.cloud/illumos/illumos-ddi.git"
rev = "e82e75d406275cb4a0bf5c23e294d87c37a9a96c"
replace-with = "oi-vendor"
[source.oi-vendor]
directory = "$vendor"
[net]
offline = true
CONFIG
cd "$source"
drivers/i915/fetch-and-patch.sh "$linux"
