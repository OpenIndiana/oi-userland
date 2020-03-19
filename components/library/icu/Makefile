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
#

BUILD_BITS=64_and_32
PREFERRED_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= icu
COMPONENT_VERSION= 66.1
COMPONENT_UVERSION= 66_1
COMPONENT_DVERSION= 66-1
COMPONENT_SUMMARY= International Components for Unicode
COMPONENT_SRC= $(COMPONENT_NAME)
COMPONENT_ARCHIVE= icu4c-$(COMPONENT_UVERSION)-src.tgz
COMPONENT_ARCHIVE_HASH= sha256:52a3f2209ab95559c1cf0a14f24338001f389615bf00e2585ef3dbc43ecf0a2e
COMPONENT_PROJECT_URL = http://icu-project.org
COMPONENT_ARCHIVE_URL = https://github.com/unicode-org/icu/releases/download/release-$(COMPONENT_DVERSION)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_SCRIPT = $(SOURCE_DIR)/source/runConfigureICU
CONFIGURE_OPTIONS = Solaris/GCC
CONFIGURE_OPTIONS+= --with-data-packaging=library
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --enable-static
CONFIGURE_OPTIONS+= --disable-samples
CONFIGURE_OPTIONS+= --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS+= --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --bindir=$(CONFIGURE_BINDIR.$(BITS))

CONFIGURE_OPTIONS.32+= --disable-64bit-libs

COMPONENT_POST_CONFIGURE_ACTION = \
(echo 'CPPFLAGS += -DICU_DATA_DIR=\"$(CONFIGURE_PREFIX)/share/icu/$(COMPONENT_VERSION)\"' >> $(@D)/icudefs.mk ) 

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_CMD+= -k

COMPONENT_TEST_TRANSFORMS += \
	" -e 's/([0-9m\.[:space:]]*s[[:space:]]*)//g' " \
	" -e 's/()//g' " \
	" -e 's/[[:space:]]*$$//g' " \
	" -n -e '/{/p' -e '/}/p' " \
	" -e '/OK/p' -e '/TEST/p' -e '/ISSUE/p' " \
	" -e '/^\#/p' -e '/^ok:/p' -e '/^\/ts/p' "

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
