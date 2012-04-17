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
# Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
#

$(BUILD_DIR)/%-2.6/.built:		PYTHON_VERSION=2.6
$(BUILD_DIR)/%-2.7/.built:		PYTHON_VERSION=2.7
$(BUILD_DIR)/$(MACH32)-%/.built:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.built:	BITS=64

$(BUILD_DIR)/%-2.6/.installed:		PYTHON_VERSION=2.6
$(BUILD_DIR)/%-2.7/.installed:		PYTHON_VERSION=2.7
$(BUILD_DIR)/$(MACH32)-%/.installed:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.installed:	BITS=64

BUILD_32 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.built)
BUILD_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.built)

INSTALL_32 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.installed)
INSTALL_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.installed)

PYTHON_ENV =	CC="$(CC)"
PYTHON_ENV +=	CFLAGS="$(CFLAGS)"

# if we are building python 2.7 support, build it and install it first
# so that python 2.6 is installed last and is the canonical version.
# when we switch to 2.7 as the default, it should go last.
ifneq ($(findstring 2.7,$(PYTHON_VERSIONS)),)
$(BUILD_DIR)/%-2.6/.build:	$(BUILD_DIR)/%-2.7/.build
$(BUILD_DIR)/%-2.6/.installed:	$(BUILD_DIR)/%-2.7/.installed
endif

# build the configured source
$(BUILD_DIR)/%/.built:	$(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(SOURCE_DIR) ; $(ENV) $(PYTHON_ENV) \
		$(PYTHON.$(BITS)) ./setup.py build \
			--build-temp $(@D:$(BUILD_DIR)/%=%))
	$(COMPONENT_POST_BUILD_ACTION)
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
	-$(PARFAIT) $(SOURCE_DIR)/$(@D:$(BUILD_DIR)/%=%)
endif
	$(TOUCH) $@


COMPONENT_INSTALL_ARGS +=	--root $(PROTO_DIR) 
COMPONENT_INSTALL_ARGS +=	--install-lib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=	--install-purelib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=	--install-platlib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=	--install-data=$(PYTHON_DATA)
COMPONENT_INSTALL_ARGS +=	--force

# install the built source into a prototype area
$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(SOURCE_DIR) ; $(ENV) $(COMPONENT_INSTALL_ENV) \
		$(PYTHON.$(BITS)) ./setup.py install $(COMPONENT_INSTALL_ARGS))
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

COMPONENT_TEST_DEP =	$(BUILD_DIR)/%/.installed
COMPONENT_TEST_DIR =	$(COMPONENT_SRC)/test
COMPONENT_TEST_ENV_CMD =	$(ENV) -
COMPONENT_TEST_ENV +=	PYTHONPATH=$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES)
COMPONENT_TEST_CMD =	$(PYTHON)
COMPONENT_TEST_ARGS +=	./runtests.py

# test the built source
$(BUILD_DIR)/%/.tested:	$(COMPONENT_TEST_DEP)
	$(COMPONENT_PRE_TEST_ACTION)
	(cd $(COMPONENT_TEST_DIR); $(COMPONENT_TEST_ENV_CMD) \
		$(COMPONENT_TEST_ENV) \
		$(COMPONENT_TEST_CMD) $(COMPONENT_TEST_ARGS) )
	$(COMPONENT_POST_TEST_ACTION)
	$(TOUCH) $@

ifeq   ($(strip $(PARFAIT_BUILD)),yes)
parfait: install
	-$(PARFAIT) build
else
parfait:
	$(MAKE) PARFAIT_BUILD=yes parfait
endif

clean::
	$(RM) -r $(SOURCE_DIR) $(BUILD_DIR)
