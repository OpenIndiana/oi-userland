# oi-userland building and packaging FAQ

This page contains answers to the most common questions regarding building and packaging software with oi-userland.

* [How to bypass checks for \*.pyc files in p5m manifest?](#how-to-bypass-checks-for-pyc-files-in-p5m-manifest)
* [Why compiled python files are no longer automatically added to manifests?](#why-compiled-python-files-are-no-longer-automatically-added-to-manifests)
* [How can I use COMPONENT_SUMMARY with PYVER components?](#how-can-i-use-component_summary-with-pyver-components)
* [Why do I receive "mv: cannot access .deps/libsomething.Tpo" error during component build?](#why-do-i-receive-mv-cannot-access-depslibsomethingtpo-error-during-component-build)

## How to bypass checks for \*.pyc files in p5m manifest?

Generally there might be cases when we don't want to deliver .pyc in manifest.
In that case you should append pkg.tmp.autopyc=false, e.g:

```
file path=usr/lib/python$(PYVER)/vendor-packages/pygst.py pkg.tmp.autopyc=false
```

If this needs to be achieved for the whole IPS manifest, it's better to use a transform, e.g

```
<transform file path=.*\.py$ -> default pkg.tmp.autopyc false>
```

## Why do I receive "mv: cannot access .deps/libsomething.Tpo" error during component build?

The most frequent reason for this error is a regeneration of `Makefile.in` files in the wrong directory (when you used $(CLONEY) to populate build directory with sources and then run automake).
Generally, libtoolize, aclocal, automake and friends should be run as COMPONENT_PREP_ACTION  when $(@D) is $(SOURCE_DIR), before  changing $(@D) to $(BUILD_DIR_$(BITS)).
$(CLONEY) should be run in COMPONENT_PRE_CONFIGURE_ACTION.
Another possible reason is missing some step in configuration - e.g. libtoolize.
