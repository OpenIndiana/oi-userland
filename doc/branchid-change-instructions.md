# BRANCHID change instructions

BRANCHID is set in [make-rules/ips-buildinfo.mk](../make-rules/ips-buildinfo.mk) as

```
BRANCHID ?= $(RELEASE_MAJOR).$(RELEASE_MINOR).$(UPDATENUM).$(COMPONENT_REVISION)
```

RELEASE_MAJOR is usually set to current year, RELEASE_MINOR and UPDATENUM are bumped when necessary and COMPONENT_REVISION is set by components individually to represent component modification.

BUILD_VERSION is set in the same file as

```
BUILD_VERSION ?=  $(PKG_SOLARIS_VERSION)-$(BRANCHID)
```

Published packages version is set to ``$(IPS_COMPONENT_VERSION),$(BUILD_VERSION)``, where ``IPS_COMPONENT_VERSION`` is set to ``COMPONENT_VERSION`` if not explicitly defined in component's Makefile.

Sometimes, on major packages updates, on changing repository, on releasing new snapshot we have to change BRANCHID.

The main issue during this process is to ensure that components, using auto-generated PLV, RUBYV and PYV manifests are republished after BRANCHID change.

This is necessary, because their publishing logic is broken in some way, and they can be published twice. On the first publish everything goes OK, but on the second only meta-package,
dependent on individual packages versions,  is republished. As it includes dependency on $(IPS_COMPONENT_VERSION),$(BUILD_VERSION) subcomponents and BUILD_VERSION is changed,
we receive non-installable package.

To find components, which should be republished, use

```
git ls-files '*VER.p5m'   | xargs -n 1 dirname
```

As of May 2019 these are the following components:

```
developer/mercurial
developer/pkgtree
perl/*, excluding perl interpreters
python/*, excluding python interpreters
sysutils/rdiff-backup
```
