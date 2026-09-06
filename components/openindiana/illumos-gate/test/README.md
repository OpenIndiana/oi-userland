Run on illumos against patched source:

```sh
python3 test/gettext-fallback.py illumos-gate/usr/src/lib/libc/port/i18n/gettext_real.c
```

The harness extracts the lookup function and uses native gettext to decode fixture
catalogues. It checks fallback ordering, normalization and per-domain selection.
A full libc build and public-API regression run are still required before release.
