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
# Copyright 2015 Alexander Pyhalov
# Copyright 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libvpx
COMPONENT_SUMMARY=	The VP8/VP9 royalty-free Codec SDK
COMPONENT_PROJECT_URL=	http://www.webmproject.org/
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_FMRI=	library/video/$(COMPONENT_NAME)

# The current version is always _1; the older delivered versions (_2+)
# are in order of growing numbers starting from the oldest we support
COMPONENT_VERSION_1=	1.6.0
COMPONENT_SRC_1=		$(COMPONENT_NAME)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
	sha256:e2fc00c9f60c76f91a1cde16a2356e33a45b76a5a5a1370df65fd57052a4994a
COMPONENT_ARCHIVE_URL_1= \
	https://github.com/webmproject/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION).tar.gz
SOURCE_DIR_1=			$(COMPONENT_DIR)/$(COMPONENT_SRC_1)

# Base variables are needed for packaging automagic
COMPONENT_ARCHIVE_URL=	$(COMPONENT_ARCHIVE_URL_1)
COMPONENT_SRC=			$(COMPONENT_SRC_1)
COMPONENT_VERSION=		$(COMPONENT_VERSION_1)
SOURCE_DIR=				$(SOURCE_DIR_1)

# Older version for legacy compatibility
COMPONENT_VERSION_2	= 1.4.0
COMPONENT_ARCHIVE_HASH_2= \
	sha256:eca30ea7fae954286c9fe9de9d377128f36b56ea6b8691427783b20c67bcfc13
COMPONENT_ARCHIVE_URL_2= \
	https://github.com/webmproject/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION_2).tar.gz
COMPONENT_SRC_2=		$(COMPONENT_NAME)-$(COMPONENT_VERSION_2)
COMPONENT_ARCHIVE_2=	$(COMPONENT_SRC_2).tar.gz
SOURCE_DIR_2=			$(COMPONENT_DIR)/$(COMPONENT_SRC_2)

# Another intermediate version
COMPONENT_VERSION_3=	1.5.0
COMPONENT_ARCHIVE_HASH_3= \
	sha256:f199b03b67042e8d94a3ae8bc841fb82b6a8430bdf3965aeeaafe8245bcfa699
COMPONENT_ARCHIVE_URL_3= \
	https://github.com/webmproject/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION_3).tar.gz
COMPONENT_SRC_3=		$(COMPONENT_NAME)-$(COMPONENT_VERSION_3)
COMPONENT_ARCHIVE_3=	$(COMPONENT_SRC_3).tar.gz
SOURCE_DIR_3=			$(COMPONENT_DIR)/$(COMPONENT_SRC_3)

# Base variables are needed for packaging automagic
COMPONENT_ARCHIVE_URL=	$(COMPONENT_ARCHIVE_URL_1)
COMPONENT_SRC=			$(COMPONENT_SRC_1)
COMPONENT_VERSION=		$(COMPONENT_VERSION_1)
SOURCE_DIR=				$(SOURCE_DIR_1)


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH.32=/usr/gnu/bin:/usr/bin
PATH.64=/usr/gnu/bin/$(MACH64):/usr/gnu/bin:/usr/bin/$(MACH64):/usr/bin
PATH=$(PATH.$(BITS))

CFLAGS +=	$(CPP_LARGEFILES)
CPPFLAGS +=	$(CPP_LARGEFILES)

TARGET.32 = x86-solaris-gcc
TARGET.64 = x86_64-solaris-gcc

CONFIGURE_OPTIONS = --prefix=$(USRDIR)
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --enable-vp8
CONFIGURE_OPTIONS += --enable-vp9
CONFIGURE_OPTIONS += --enable-postproc
CONFIGURE_OPTIONS += --enable-runtime-cpu-detect
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-examples
CONFIGURE_OPTIONS += --disable-unit-tests
CONFIGURE_OPTIONS += --target=$(TARGET.$(BITS))

COMPONENT_PRE_CONFIGURE_ACTION_1 = \
    ($(CLONEY) $(SOURCE_DIR_1) $(@D))

COMPONENT_PRE_CONFIGURE_ACTION_2 = \
    ($(CLONEY) $(SOURCE_DIR_2) $(@D))

COMPONENT_PRE_CONFIGURE_ACTION_3 = \
    ($(CLONEY) $(SOURCE_DIR_3) $(@D))

# Unique stuff for the newer version
BUILD_DIR_32_1 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH32)
BUILD_DIR_64_1 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH64)
BUILD_DIR_32 = $(BUILD_DIR_32_1)
BUILD_DIR_64 = $(BUILD_DIR_64_1)

BUILD_32 +=     $(BUILD_DIR_32_1)/.built
BUILD_64 +=     $(BUILD_DIR_64_1)/.built

INSTALL_32 +=   $(BUILD_DIR_32_1)/.installed
INSTALL_64 +=   $(BUILD_DIR_64_1)/.installed

$(SOURCE_DIR_1)/.prep:
	$(COMPONENT_PREP_ACTION)
	$(TOUCH) $@

$(BUILD_DIR_32_1)/.configured:  CONFIGURE_SCRIPT=$(SOURCE_DIR_1)/configure
$(BUILD_DIR_32_1)/.configured:  COMPONENT_PRE_CONFIGURE_ACTION=$(COMPONENT_PRE_CONFIGURE_ACTION_1)
$(BUILD_DIR_32_1)/.configured:  BITS=32

$(BUILD_DIR_64_1)/.configured:  CONFIGURE_SCRIPT=$(SOURCE_DIR_1)/configure
$(BUILD_DIR_64_1)/.configured:  COMPONENT_PRE_CONFIGURE_ACTION=$(COMPONENT_PRE_CONFIGURE_ACTION_1)
$(BUILD_DIR_64_1)/.configured:  BITS=64



# Unique stuff for the intermediate version (1.5.0 should be similar to current 1.6.0)
BUILD_DIR_32_3 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_3)-$(MACH32)
BUILD_DIR_64_3 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_3)-$(MACH64)

BUILD_32 +=     $(BUILD_DIR_32_3)/.built
BUILD_64 +=     $(BUILD_DIR_64_3)/.built

INSTALL_32 +=   $(BUILD_DIR_32_3)/.installed
INSTALL_64 +=   $(BUILD_DIR_64_3)/.installed

$(SOURCE_DIR_3)/.prep:
	$(COMPONENT_PREP_ACTION)
	$(TOUCH) $@

$(BUILD_DIR_32_3)/.configured:  CONFIGURE_SCRIPT=$(SOURCE_DIR_3)/configure
$(BUILD_DIR_32_3)/.configured:  COMPONENT_PRE_CONFIGURE_ACTION=$(COMPONENT_PRE_CONFIGURE_ACTION_3)
$(BUILD_DIR_32_3)/.configured:  BITS=32

$(BUILD_DIR_64_3)/.configured:  CONFIGURE_SCRIPT=$(SOURCE_DIR_3)/configure
$(BUILD_DIR_64_3)/.configured:  COMPONENT_PRE_CONFIGURE_ACTION=$(COMPONENT_PRE_CONFIGURE_ACTION_3)
$(BUILD_DIR_64_3)/.configured:  BITS=64



# Macros to configure, build, and install the old version for the time being.
BUILD_DIR_32_2 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_2)-$(MACH32)
BUILD_DIR_64_2 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_2)-$(MACH64)

BUILD_32 +=     $(BUILD_DIR_32_2)/.built
BUILD_64 +=     $(BUILD_DIR_64_2)/.built

INSTALL_32 +=   $(BUILD_DIR_32_2)/.installed
INSTALL_64 +=   $(BUILD_DIR_64_2)/.installed

$(SOURCE_DIR_2)/.prep:
	$(COMPONENT_PREP_ACTION)
	$(TOUCH) $@

$(BUILD_DIR_32_2)/.configured:  CONFIGURE_SCRIPT=$(SOURCE_DIR_2)/configure
$(BUILD_DIR_32_2)/.configured:  COMPONENT_PRE_CONFIGURE_ACTION=$(COMPONENT_PRE_CONFIGURE_ACTION_2)
$(BUILD_DIR_32_2)/.configured:  BITS=32

$(BUILD_DIR_64_2)/.configured:  CONFIGURE_SCRIPT=$(SOURCE_DIR_2)/configure
$(BUILD_DIR_64_2)/.configured:  COMPONENT_PRE_CONFIGURE_ACTION=$(COMPONENT_PRE_CONFIGURE_ACTION_2)
$(BUILD_DIR_64_2)/.configured:  BITS=64



# Cause the old versions to be prepped at all
$(SOURCE_DIR_1)/.prep: $(SOURCE_DIR_2)/.prep $(SOURCE_DIR_3)/.prep

# install the old versions (_2, _3) first
$(BUILD_DIR_32_1)/.installed:     $(BUILD_DIR_32_2)/.installed $(BUILD_DIR_32_3)/.installed
$(BUILD_DIR_64_1)/.installed:     $(BUILD_DIR_64_2)/.installed $(BUILD_DIR_64_3)/.installed

# common targets
build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
