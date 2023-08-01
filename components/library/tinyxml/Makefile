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
# Copyright 2016 phorcys@126.com.  All rights reserved.
#

BUILD_STYLE=configure
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         tinyxml
COMPONENT_VERSION=      2.6.2
COMPONENT_REVISION=     2
COMPONENT_FMRI=         library/tinyxml
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=  http://sourceforge.net/projects/tinyxml/
COMPONENT_SUMMARY=      TinyXML is a simple, small, minimal, C++ XML parser that can be easily integrating into other programs.
COMPONENT_SRC=          $(COMPONENT_NAME)
COMPONENT_SRC_VERSION= $(shell echo $(COMPONENT_VERSION) | $(GSED) -e 's/\./_/g')
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:15bdfdcec58a7da30adc87ac2b078e4417dbe5392f3afb719f9ba6d062645593
COMPONENT_ARCHIVE_URL=  \
	http://downloads.sourceforge.net/project/tinyxml/tinyxml/$(COMPONENT_VERSION)/$(COMPONENT_NAME)_$(COMPONENT_SRC_VERSION).tar.gz
COMPONENT_LICENSE=      zlib/libpng License

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= \
    ( cd  $(@D) && \
		  $(TOUCH)  INSTALL NEWS README AUTHORS ChangeLog && \
		  libtoolize && aclocal && autoconf && automake --add-missing )

CONFIGURE_OPTIONS+= --disable-static

COMPONENT_POST_INSTALL_ACTION= \
    ( $(GSED) -e "s:%LIBDIR%:$(CONFIGURE_LIBDIR.$(BITS)):g" \
              -e "s:%VERSION%:$(COMPONENT_VERSION):g" \
              $(SOURCE_DIR)/tinyxml.pc > $(BUILD_DIR)/tinyxml.pc.$(BITS) )

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
