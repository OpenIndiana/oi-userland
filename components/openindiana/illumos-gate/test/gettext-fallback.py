#!/usr/bin/env python3
import pathlib
import struct
import subprocess
import sys
import tempfile


def catalogue(path, text):
    entries = {b'': b'Content-Type: text/plain; charset=UTF-8\n', b'probe': text.encode()}
    if text == 'missing':
        del entries[b'probe']
    keys = sorted(entries)
    offset = 28 + 16 * len(keys)
    ids, values, data = [], [], bytearray()
    for key in keys:
        ids.append((len(key), offset + len(data)))
        data.extend(key + b'\0')
    for key in keys:
        value = entries[key]
        values.append((len(value), offset + len(data)))
        data.extend(value + b'\0')
    header = struct.pack('<7I', 0x950412de, 0, len(keys), 28, 28 + 8 * len(keys), 0, 0)
    tables = b''.join(struct.pack('<2I', *entry) for entry in ids + values)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(header + tables + data)


source = pathlib.Path(sys.argv[1]).read_text()
start = source.index('char *\nhandle_locale(')
end = source.index('\n#define\tALLFREE', start)
cases = [
    ('de_DE.UTF-8', {'de': 'base'}, 'base'),
    ('de_DE.UTF-8', {'de_DE.UTF-8': 'exact', 'de': 'base'}, 'exact'),
    ('de_DE.UTF-8', {'de_DE.UTF-8': 'missing', 'de': 'base'}, 'base'),
    ('de_DE.UTF-8', {'de_DE.utf8': 'normalized', 'de_DE': 'region'}, 'normalized'),
    ('de_DE.UTF-8', {'de_DE': 'region', 'de': 'base'}, 'region'),
    ('sr_RS.UTF-8@latin', {'sr@latin': 'modifier', 'sr_RS': 'region'}, 'modifier'),
    ('sr_RS.UTF-8@latin', {'sr_RS': 'region', 'sr': 'base'}, 'region'),
    ('zh_TW.UTF-8', {'zh_TW': 'traditional', 'zh_CN': 'simplified'}, 'traditional'),
    ('zh_TW.UTF-8', {'zh': 'base'}, 'base'),
    ('fr_CA.UTF-8', {'fr_FR': 'other-region'}, 'probe'),
    ('de_DE.8859-1', {'de_DE.iso88591': 'numeric'}, 'numeric'),
    ('C.UTF-8', {'C': 'ignored'}, 'probe'),
    ('POSIX.UTF-8', {'POSIX': 'ignored'}, 'probe'),
    ('de', {'de': 'base'}, 'base'),
    ('de_DE.UTF-8', {}, 'probe'),
]
with tempfile.TemporaryDirectory(prefix='gettext-fallback-') as tmp:
    root = pathlib.Path(tmp)
    (root / 'handle_locale.c').write_text(source[start:end])
    test = pathlib.Path(__file__).with_suffix('.c')
    binary = root / 'test'
    subprocess.run(['gcc', '-m64', '-Wall', '-Wextra', '-Werror', '-I', str(root),
                    str(test), '-o', str(binary)], check=True)
    for i, (locale, catalogues, expected) in enumerate(cases):
        domain = 'test' + str(i)
        for name, text in catalogues.items():
            catalogue(root / name / 'LC_MESSAGES' / (domain + '.mo'), text)
        subprocess.run([str(binary), str(root), locale, domain, expected], check=True)
print('PASS: 15 catalogue fallback cases')
