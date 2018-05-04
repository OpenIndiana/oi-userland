#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016-2018 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	znapzend
COMPONENT_VERSION=	0.18.0
COMPONENT_SUMMARY=	zfs backup with remote capabilities and mbuffer integration
COMPONENT_DESCRIPTION=	ZnapZend is a ZFS centric backup tool. It relies on snapshot,\
 send and receive to do its work. It has the built-in ability to manage both local\
 snapshots as well as remote copies by thining them out as time progresses.\
 The ZnapZend configuration is stored as properties in the ZFS filesystem itself,\
 see znapzendzetup to get started.
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:7ef999106a6dd7120787f87ed6a2775b32b2c84af6284d573a71e2a5a4c63296
COMPONENT_ARCHIVE_URL=	\
  https://github.com/oetiker/$(COMPONENT_NAME)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://github.com/oetiker/$(COMPONENT_NAME)
COMPONENT_FMRI=	backup/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = ( cd $(SOURCE_DIR) && autoreconf --force --install --verbose --make )

COMPONENT_PRE_CONFIGURE_ACTION =	( $(CLONEY) $(SOURCE_DIR) $(@D) )

PKG_OPTIONS += -D GCC_RUNTIME_PKG="$(GCC_RUNTIME_PKG)"

# NOTE: Code below assumes that BINDIR64 is one layer under BINDIR32
# Othewise might use GNU ln -rsf ...
COMPONENT_POST_INSTALL_ACTION =	( $(MKDIR) $(PROTO_DIR)/$(CONFIGURE_BINDIR.$(BITS)) \
        && case "$(BITS)" in \
            32) ORIGDIR="../share/$(COMPONENT_NAME)/$(MACH32)/bin" ;; \
            64) ORIGDIR="../../share/$(COMPONENT_NAME)/$(MACH64)/bin" ;; \
            *) echo "Unsupported BITS value: $(BITS)" >&2 ; exit 1 ;; \
        esac \
        && for BINFILE in znapzend znapzendzetup znapzendztats ; do \
            ln -sf "$$ORIGDIR/$$BINFILE" "$(PROTO_DIR)/$(CONFIGURE_BINDIR.$(BITS))/" || exit ; \
        done )

# NOTE: znapzend is a script, but it can pull some PERL modules and some may be
# ARCHed, and/or these may (package-)conflict with dependencies of other pkgs.
# TODO: package dependency modules as separate IPS requirements, and build only
# a 32-bit znapzend? For now we work around the mess by having it all in a
# dedicated directory per ARCH, including the perl modules.
CONFIGURE_OPTIONS  =	--prefix=$(CONFIGURE_PREFIX)/share/$(COMPONENT_NAME)/$(MACH$(BITS))
CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--enable-svcinstall=/lib/svc/manifest/system
CONFIGURE_OPTIONS +=	--with-svcname-smf=system/filesystem/zfs/znapzend

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
