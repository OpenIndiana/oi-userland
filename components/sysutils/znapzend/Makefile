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
COMPONENT_VERSION=	0.19.1
COMPONENT_SUMMARY=	zfs backup with remote capabilities and mbuffer integration
COMPONENT_DESCRIPTION=	ZnapZend is a ZFS centric backup tool. It relies on snapshot,\
 send and receive to do its work. It has the built-in ability to manage both local\
 snapshots as well as remote copies by thining them out as time progresses.\
 The ZnapZend configuration is stored as properties in the ZFS filesystem itself,\
 see znapzendzetup to get started.
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:93e3ec3c6f5cdf6973f72a6b764c49dc6545f2a0a2e0267a1382d471b930efea
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

COMPONENT_PREP_ACTION =	( cd $(SOURCE_DIR) && autoreconf --force --install --verbose --make )

COMPONENT_PRE_CONFIGURE_ACTION =	( $(CLONEY) $(SOURCE_DIR) $(@D) )

# Preferred (build) version of gcc
GCCLIBDIR  =	$(GCC_ROOT)/lib
PKG_OPTIONS +=	-D GCC_RUNTIME_PKG="$(GCC_RUNTIME_PKG)"

# Note: Building and installing for one bitness, so for PATH to have
# the binaries, it should be linked straight in bin/ (no $BITS magic)
# In the second loop we help runtime linker find libssp.so that ListUtil's
# library refers to. Note: for us, suffices if it is 32-bit.
ELFEDIT = /usr/bin/elfedit
COMPONENT_POST_INSTALL_ACTION =	( $(MKDIR) $(PROTO_DIR)/$(CONFIGURE_PREFIX)/bin \
        && ORIGDIR="../share/$(COMPONENT_NAME)/bin" \
        && for BINFILE in znapzend znapzendzetup znapzendztatz ; do \
            rm -f "$(PROTO_DIR)/$(CONFIGURE_PREFIX)/bin/$$BINFILE" || true ; \
            ln -sf "$$ORIGDIR/$$BINFILE" "$(PROTO_DIR)/$(CONFIGURE_PREFIX)/bin/" || exit ; \
        done \
        && find $(PROTO_DIR)/$(CONFIGURE_PREFIX)/share/$(COMPONENT_NAME)/lib/ -type f -name '*.so*' \
            | while read LIBFILE ; do \
                $(CHMOD) +w "$$LIBFILE" \
                && $(ELFEDIT) -e "dyn:rpath $(GCCLIBDIR)" "$$LIBFILE" \
                && $(CHMOD) -w "$$LIBFILE" \
                || exit ; \
            done \
        )

CONFIGURE_ENV += PERL=$(PERL)

# NOTE: znapzend is a script, but it can pull some PERL modules and some may be
# ARCHed, and/or these may (package-)conflict with dependencies of other pkgs.
# TODO: package dependency modules as separate IPS requirements, and build only
# a 32-bit znapzend? For now we work around the mess by having it all in a
# dedicated directory per ARCH, including the perl modules.
CONFIGURE_OPTIONS  =	--prefix=$(CONFIGURE_PREFIX)/share/$(COMPONENT_NAME)
# Install man pages to /usr/share
CONFIGURE_OPTIONS  =	--datarootdir=$(CONFIGURE_PREFIX)/share
CONFIGURE_OPTIONS +=	--exec-prefix=$(CONFIGURE_PREFIX)/share/$(COMPONENT_NAME)
CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--enable-svcinstall=/lib/svc/manifest/system
CONFIGURE_OPTIONS +=	--with-svcname-smf=system/filesystem/zfs/znapzend

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(TEST_32)

REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
