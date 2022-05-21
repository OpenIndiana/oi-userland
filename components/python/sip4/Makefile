#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright 2022 Daniel Chan
#

BUILD_BITS=		64
BUILD_STYLE=	setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sip4
COMPONENT_VERSION=	4.19.25
COMPONENT_PROJECT_URL=	https://www.riverbankcomputing.com
COMPONENT_SRC=		sip-$(COMPONENT_VERSION)
COMPONENT_SUMMARY=	Python extension module generator for C/C++ libraries
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:b39d93e937647807bac23579edbff25fe46d16213f708370072574ab1f1b4211
COMPONENT_ARCHIVE_URL=	https://www.riverbankcomputing.com/static/Downloads/sip/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_FMRI=		developer/sip4
COMPONENT_LICENSE=  GPLv3
COMPONENT_LICENSE_FILE=	LICENSE-GPL3

PYTHON_VERSION=	3.9
PYTHON_VERSIONS=	3.9

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += CC=$(CC)
CONFIGURE_OPTIONS += AR=$(AR)
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += CXX=$(CXX)
CONFIGURE_OPTIONS += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS += LFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS += LINK="$(CC)"
CONFIGURE_OPTIONS += LINK_SHLIB="$(CXX)"
CONFIGURE_OPTIONS += CFLAGS_SHLIB=-fPIC
CONFIGURE_OPTIONS += CXXFLAGS_SHLIB=-fPIC
COMPONENT_INSTALL_ARGS = DESTDIR=$(PROTO_DIR)

COMPONENT_PRE_BUILD_ACTION = \
	cp -r $(SOURCE_DIR)/* $(@D)/;\
	cd $(@D) && python$(PYTHON_VERSION) configure.py $(CONFIGURE_OPTIONS); \
	cd $(BUILD_DIR)/.. && PatchMakefile.sh $(@D)/siplib/Makefile
	
COMPONENT_POST_BUILD_ACTION = \
	cd $(@D) && python$(PYTHON_VERSION) -m compileall sipdistutils.py; \
	mkdir -p $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/sip/__pycache__/; \
	cp $(@D)/__pycache__/* $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/sip/__pycache__/

$(BUILD_DIR)/%/.built:	$(SOURCE_DIR)/.prep $(BUILD_DIR)/config-%/$(CFG)
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(COMPONENT_COPY_ACTION)
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_BUILD_ENV) \
	$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS))
	$(COMPONENT_POST_BUILD_ACTION)
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
	-$(PARFAIT) $(SOURCE_DIR)/$(@D:$(BUILD_DIR)/%=%)
endif
	$(TOUCH) $@

$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built $(BUILD_DIR)/config-%/$(CFG)
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_INSTALL_ENV) \
	$(GMAKE) $(COMPONENT_INSTALL_ARGS) $(COMPONENT_INSTALL_TARGETS))
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

# Build dependencies
REQUIRED_PACKAGES += runtime/python-39
# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
