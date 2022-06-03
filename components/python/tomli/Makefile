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

BUILD_BITS=			64
BUILD_STYLE=		setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tomli
COMPONENT_VERSION=	2.0.1
COMPONENT_SUMMARY=	A lil' TOML parser
COMPONENT_PROJECT_URL=	https://pypi.org/project/tomli/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:de526c12914f0c550d15924c62d72abc48d6fe7364aa87328337a31007fe8a4f
COMPONENT_ARCHIVE_URL=	https://files.pythonhosted.org/packages/c0/3f/d7af728f075fb08564c5949a9c95e44352e23dee646869fa104a3b2060a3/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/python/tomli
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE

PYTHON_VERSIONS=	3.7 3.9

include $(WS_MAKE_RULES)/common.mk

#COMPONENT_BUILD_ACTION=mkdir -p $(PROTO_DIR)/usr/lib/python3.9/vendor-packages
$(BUILD_DIR)/%/.built:	$(SOURCE_DIR)/.prep $(BUILD_DIR)/config-%/$(CFG)
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	mkdir -p $(PROTO_DIR)$(PYTHON_LIB)/
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
	-$(PARFAIT) $(SOURCE_DIR)/$(@D:$(BUILD_DIR)/%=%)
endif
	$(TOUCH) $@

#COMPONENT_INSTALL_ACTION=cp -r $(SOURCE_DIR)/src/tomli $(PROTO_DIR)/usr/lib/python3.9/vendor-packages/
$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built $(BUILD_DIR)/config-%/$(CFG)
	cp -r $(SOURCE_DIR)/src/tomli $(PROTO_DIR)$(PYTHON_LIB)/
	$(TOUCH) $@


	
$(MANIFEST_BASE)-%.depend:	$(MANIFEST_BASE)-%.mangled
	sed -i 's/__pycache__//g' $(BUILD_DIR)/*.mangled
	sed -i 's/.cpython-37.pyc/.py/g' $(BUILD_DIR)/*.mangled
	sed -i 's/.cpython-39.pyc/.py/g' $(BUILD_DIR)/*.mangled
	$(PKGDEPEND) generate $(PKGDEPEND_GENERATE_OPTIONS) $< >$@

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/installer-37
REQUIRED_PACKAGES += library/python/installer-39
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
