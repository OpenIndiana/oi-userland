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
# Copyright (c) 2013, 2019, Oracle and/or its affiliates. All rights reserved.
# Copyright 2022 Daniel Chan
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pyparsing
COMPONENT_VERSION=	3.0.9
COMPONENT_FMRI=		library/python/pyparsing
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SUMMARY=	Python parsing module
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:2b020ecf7d21b687f219b71ecad3631f644a47f01403fa1d1036b0c6416d70fb
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/pyparsing/
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE= LICENSE

PYTHON_VERSIONS= 3.7 3.9
#$(PYTHON3_VERSIONS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_INSTALL_ACTION= \
	$(MV) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages

$(BUILD_DIR)/%/.built:	$(SOURCE_DIR)/.prep $(BUILD_DIR)/config-%/$(CFG)
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(COMPONENT_COPY_ACTION)
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(SOURCE_DIR) ; $(ENV) HOME=$(BUILD_DIR)/config-$* $(COMPONENT_BUILD_ENV) \
		$(PYTHON.$(BITS)) -m build)
	$(COMPONENT_POST_BUILD_ACTION)
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
	-$(PARFAIT) $(SOURCE_DIR)/$(@D:$(BUILD_DIR)/%=%)
endif
	$(TOUCH) $@

$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built $(BUILD_DIR)/config-%/$(CFG)
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(SOURCE_DIR) ; $(ENV) HOME=$(BUILD_DIR)/config-$* $(COMPONENT_INSTALL_ENV) \
		$(PYTHON.$(BITS)) -m installer --destdir="$(PROTO_DIR)" $(SOURCE_DIR)/dist/*.whl)
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@



COMPONENT_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_TEST_CMD =	$(PYTHON) unitTests.py
COMPONENT_TEST_ARGS =
COMPONENT_TEST_TRANSFORMS += \
	'-e "s/[0-9]*\.[0-9]*s//"' \
	'-re "s|(Ran [0-9]+ tests).*|\1|"' \
	'-re "s|(\.+).*|\1|"' \
	'-n' \
	'-e "/\.\.\./p"' \
	'-e "/Ran [0-9]+ tests/p"'

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Manually added dependencies
REQUIRED_PACKAGES += library/python/build-37
REQUIRED_PACKAGES += library/python/build-39
REQUIRED_PACKAGES += library/python/pep517-37
REQUIRED_PACKAGES += library/python/pep517-39
REQUIRED_PACKAGES += library/python/tomli-37
REQUIRED_PACKAGES += library/python/tomli-39
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
