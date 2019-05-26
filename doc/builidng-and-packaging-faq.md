# oi-userland building and packaging FAQ

This page contains answers to the most common questions regarding building and packaging software with oi-userland.

* [How to bypass checks for \*.pyc files in p5m manifest?](#how-to-bypass-checks-for-pyc-files-in-p5m-manifest)
* [Why compiled python files are no longer automatically added to manifests?](#why-compiled-python-files-are-no-longer-automatically-added-to-manifests)
* [How can I use COMPONENT_SUMMARY with PYVER components?](#how-can-i-use-component_summary-with-pyver-components)
* [Why do I receive "mv: cannot access .deps/libsomething.Tpo" error during component build?](#why-do-i-receive-mv-cannot-access-depslibsomethingtpo-error-during-component-build)
* [Why COMPONENT_AUTOGEN_MANIFEST is dangerous?](#why-component_autogen_manifest-is-dangerous)

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

## Why compiled python files are no longer automatically added to manifests? 

After introduction of Python 3.4 autopyc transform has to distinguish compiled files for python 2.x (*.pyc) and for python 3.x (__pycache__/*.cpython-3x.pyc).
This is done on the base of file path. 
Files in usr/lib/python2.x/*.py  are processed as earlier (following Python 2.x convention).
Files in usr/lib/python3.x are processed according to Python 3.x convention.
All other *.py files are not processed automatically. 

## How can I use COMPONENT_SUMMARY with PYVER components?

There's a known oi-userland build system issue that COMPONENT_SUMMARY and other PKG macroses, containing spaces, can work incorrectly with PYVER components.
You can either specify such values in p5m file directly or use single quotation marks in Makefile, for example:

```
COMPONENT_SUMMARY= 'Cheroot - high-performance, pure-Python HTTP server'
```

## Why do I receive "mv: cannot access .deps/libsomething.Tpo" error during component build?

The most frequent reason for this error is a regeneration of `Makefile.in` files in the wrong directory (when you used $(CLONEY) to populate build directory with sources and then run automake).
Generally, libtoolize, aclocal, automake and friends should be run as COMPONENT_PREP_ACTION  when $(@D) is $(SOURCE_DIR), before  changing $(@D) to $(BUILD_DIR_$(BITS)).
$(CLONEY) should be run in COMPONENT_PRE_CONFIGURE_ACTION.
Another possible reason is missing some step in configuration - e.g. libtoolize.

## Why COMPONENT_AUTOGEN_MANIFEST is dangerous?

Setting COMPONENT_AUTOGEN_MANIFEST=yes in your component's Makefile and adding empty *.p5m manifest you can make oi-userland build system to generate *.p5m manifest automatically.
But it's not a very good idea: it hides manifest from you and so manifest can contain garbage.
Even more, if you change component or its dependencies, the files can be missing from the package without any warning.
The better alternative is to use "gmake sample-manifest", copy generated manifest to component directory and modify it as needed.
