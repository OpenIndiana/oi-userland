#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Aurelien Larcher
#

BUILD_BITS= 64_and_32
BUILD_STYLE = cmake
USE_COMMON_TEST_MASTER= no
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libjpeg-turbo
COMPONENT_VERSION= 3.0.4
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= libjpeg -JPEG Turbo libraries
COMPONENT_PROJECT_URL= https://www.libjpeg-turbo.org/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:99130559e7d62e8d695f2c0eaeef912c5828d5b84a0537dcb24c9678c9d5b76b
COMPONENT_ARCHIVE_URL=	https://github.com/libjpeg-turbo/libjpeg-turbo/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= image/library/libjpeg-turbo
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE= IJG,BSD,zlib
COMPONENT_LICENSE_FILE= LICENSE.md

COMPONENT_FMRI.libjpeg6-turbo =		image/library/libjpeg6-turbo

COMPONENT_FMRI.libjpeg6-turbo-32 =	$(COMPONENT_FMRI.libjpeg6-turbo)/32
COMPONENT_SUMMARY.libjpeg6-turbo-32 =	$(COMPONENT_SUMMARY) (32-bit)

COMPONENT_FMRI.libjpeg7-turbo =		image/library/libjpeg7-turbo

COMPONENT_FMRI.libjpeg7-turbo-32 =	$(COMPONENT_FMRI.libjpeg7-turbo)/32
COMPONENT_SUMMARY.libjpeg7-turbo-32 =	$(COMPONENT_SUMMARY) (32-bit)

COMPONENT_FMRI.libjpeg8-turbo =		image/library/libjpeg8-turbo

COMPONENT_FMRI.libjpeg8-turbo-32 =	$(COMPONENT_FMRI.libjpeg8-turbo)/32
COMPONENT_SUMMARY.libjpeg8-turbo-32 =	$(COMPONENT_SUMMARY) (32-bit)

JPEG_API_VERSIONS = 6 7 8

# Custom BUILD_*, INSTALL_*, and TEST_* variables needs to be defined before
# the common.mk include.
$(foreach b,32 64, \
	$(eval BUILD_$(b) = $(foreach v,$(JPEG_API_VERSIONS),$(BUILD_DIR)/$(MACH$(b))/$(v)/.built)) \
	$(eval INSTALL_$(b) = $(foreach v,$(JPEG_API_VERSIONS),$(BUILD_DIR)/$(MACH$(b))/$(v)/.installed)) \
	$(if $(strip $(wildcard $(COMPONENT_TEST_RESULTS_DIR)/results-*.master)), \
		$(eval TEST_$(b) = $(foreach v,$(JPEG_API_VERSIONS),$(BUILD_DIR)/$(MACH$(b))/$(v)/.tested-and-compared)) \
		, \
		$(eval TEST_$(b) = $(foreach v,$(JPEG_API_VERSIONS),$(BUILD_DIR)/$(MACH$(b))/$(v)/.tested)) \
	) \
)

include $(WS_MAKE_RULES)/common.mk

# Set BITS and JPEG_API_VERSION for all targets
$(foreach t,configured built installed tested tested-and-compared, \
	$(foreach b,32 64, \
		$(eval $(BUILD_DIR_$(b))/%/.$(t): BITS=$(b)) \
	) \
	$(foreach v,$(JPEG_API_VERSIONS), \
		$(eval $(BUILD_DIR)/%/$(v)/.$(t): JPEG_API_VERSION=$(v)) \
	) \
)

# Settings to build the desired libjpeg API
CMAKE_OPTIONS.JPEG6= 
CMAKE_OPTIONS.JPEG7= -DWITH_JPEG7=ON
CMAKE_OPTIONS.JPEG8= -DWITH_JPEG8=ON

# TurboAPI does not depend on libjpeg API version so it is enough to build it
# once only.
CMAKE_OPTIONS.JPEG6 += -DWITH_TURBOJPEG=FALSE
CMAKE_OPTIONS.JPEG7 += -DWITH_TURBOJPEG=FALSE

# Include files for old libjpeg API versions goes to separate directory
CMAKE_OPTIONS.JPEG6 += -DCMAKE_INSTALL_INCLUDEDIR=$(USRINCDIR)/libjpeg$(JPEG_API_VERSION)-turbo
CMAKE_OPTIONS.JPEG7 += -DCMAKE_INSTALL_INCLUDEDIR=$(USRINCDIR)/libjpeg$(JPEG_API_VERSION)-turbo

# Libraries for old libjpeg API versions goes to separate directory
CMAKE_OPTIONS.JPEG6 += -DCMAKE_INSTALL_LIBDIR=$(USRLIBDIR)/libjpeg$(JPEG_API_VERSION)-turbo/$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS.JPEG7 += -DCMAKE_INSTALL_LIBDIR=$(USRLIBDIR)/libjpeg$(JPEG_API_VERSION)-turbo/$(CMAKE_LIBDIR.$(BITS))

# Disable static libs
CMAKE_OPTIONS+=	-DENABLE_STATIC=FALSE

# Allow for build with different API compliance
CMAKE_OPTIONS+=	$(CMAKE_OPTIONS.JPEG$(JPEG_API_VERSION))

# We need to install just a subset of files for various combinations of libjpeg
# API version and bitness
CMAKE_COMPONENTS.JPEG6 +=	lib
CMAKE_COMPONENTS.JPEG6.64 +=	include
CMAKE_COMPONENTS.JPEG7 +=	lib
CMAKE_COMPONENTS.JPEG7.64 +=	include
CMAKE_COMPONENTS.JPEG8.32 +=	lib
CMAKE_COMPONENTS +=		$(CMAKE_COMPONENTS.JPEG$(JPEG_API_VERSION))
CMAKE_COMPONENTS +=		$(CMAKE_COMPONENTS.JPEG$(JPEG_API_VERSION).$(BITS))

# Create library symlinks at standard locations
COMPONENT_POST_INSTALL_ACTION += \
	for f in $(PROTOUSRLIBDIR)/libjpeg$(JPEG_API_VERSION)-turbo/$(CMAKE_LIBDIR.$(BITS))/*.so.* ; do \
		[ -e "$$f" ] || continue ; \
		t=$(PROTOUSRLIBDIR.$(BITS)) ; \
		while true ; do \
			while [ "$${f\#/}" != "$$f" ] ; do f=$${f\#/} ; done ; \
			while [ "$${t\#/}" != "$$t" ] ; do t=$${t\#/} ; done ; \
			[ "$${f%%/*}" == "$${t%%/*}" ] || break ; \
			f=$${f\#$${f%%/*}} ; \
			t=$${t\#$${t%%/*}} ; \
		done ; \
		[ "$$t" ] && t=$$t/ ; \
		f=$$(echo $$t | $(GSED) -e 's|[^/]\{1,\}|..|g')$$f ; \
		$(MKDIR) $(PROTOUSRLIBDIR.$(BITS)) ; \
		$(SYMLINK) $$f $(PROTOUSRLIBDIR.$(BITS))/$$(basename $$f) ; \
	done ;

# Per libjpeg API version test directory
COMPONENT_TEST_BUILD_DIR = $(BUILD_DIR)/test/$(MACH$(BITS))/$(JPEG_API_VERSION)
# Per libjpeg API version master test results file
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(BITS)-$(JPEG_API_VERSION).master

# Normalize test results
COMPONENT_TEST_TRANSFORMS += "-e 's/ *[0-9]\{1,\}\.[0-9]\{1,\} sec\$$//'"			# timing
COMPONENT_TEST_TRANSFORMS += "-e '/^Total Test time/d'"						# timing
COMPONENT_TEST_TRANSFORMS += "-e '/^ *Start/d'"							# drop Start lines
COMPONENT_TEST_TRANSFORMS += "-e 's/^ *[0-9]\{1,\}\/[0-9]\{1,\} Test *\#[0-9]\{1,\}:/Test/'"	# drop test numbers

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
