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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= icu
COMPONENT_VERSION= 55.1
COMPONENT_UVERSION= 55_1
COMPONENT_REVISION= 4
COMPONENT_SUMMARY= International Components for Unicode
COMPONENT_SRC= $(COMPONENT_NAME)
COMPONENT_ARCHIVE= icu4c-$(COMPONENT_UVERSION)-src.tgz
COMPONENT_ARCHIVE_HASH= \
    sha256:e16b22cbefdd354bec114541f7849a12f8fc2015320ca5282ee4fd787571457b
COMPONENT_PROJECT_URL = http://icu-project.org
COMPONENT_ARCHIVE_URL = http://download.icu-project.org/files/icu4c/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

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

COMPONENT_POST_CONFIGURE_ACTION =        (echo 'CPPFLAGS += -DICU_DATA_DIR=\"$(CONFIGURE_PREFIX)/share/icu/$(COMPONENT_VERSION)\"' >> $(@D)/icudefs.mk ) 

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/library/math
