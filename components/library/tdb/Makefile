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
# Copyright 2017 Alexander Pyhalov
# Copyright (c) 2022, Friedrich Kink
#

BUILD_BITS= 32_and_64
BUILD_STYLE= waf
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= tdb
COMPONENT_VERSION= 1.4.9
COMPONENT_SUMMARY= Trivial Database Library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:0ac226073e3a2db8648da7af744cb95f50766a52feeb001d558b2b321b74a765
COMPONENT_ARCHIVE_URL= https://download.samba.org/pub/tdb/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://wiki.samba.org/index.php/TDB
COMPONENT_FMRI = library/tdb
COMPONENT_CLASSIFICATION = Development/Databases
# Binaries are GPLv3, but we don't ship them
COMPONENT_LICENSE = LGPLv3

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION += ( \
	$(CLONEY) $(SOURCE_DIR) $(@D); \
	cd $(@D); \
	);

CFLAGS +=       $(CC_PIC) -D_POSIX_PTHREAD_SEMANTICS
CPPFLAGS +=     $(CPP_LARGEFILES) $(CPP_XPG6MODE)
# Flag is not picked up for lib/replace
LDFLAGS +=      $(LD_SSP)

WAF = PYTHONHASHSEED=1 $(PYTHON) ./buildtools/bin/waf

# Waf doesn't like variables passing via args, so we rewrite CONFIGURE_OPTIONS
CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --sbindir=$(CONFIGURE_SBINDIR.$(BITS))
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --without-gettext
CONFIGURE_OPTIONS += --disable-python
CONFIGURE_OPTIONS += --disable-rpath

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "s/(.*s)//" ' \
	'-e "s/Testing with.*//" '\
	'-e "/finished/p" ' \
	'-e "/returned/p" ' \
	'-e "/tdb1-run/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
