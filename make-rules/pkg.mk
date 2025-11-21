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
# Copyright 2025 Marcel Telka
#

# Configure
CLONEY_MODE = none
COMPONENT_CONFIGURE_ACTION = true

# Build
COMPONENT_BUILD_ACTION = true

# Install
# The sample-manifest target needs the proto dir and so we need to create it
# during the install.  Even it will stay empty.
COMPONENT_INSTALL_ACTION = $(MKDIR) $(PROTO_DIR)

# Test
TEST_TARGET = $(NO_TESTS)

clean::
	$(RM) -r $(SOURCE_DIR)/.prep $(BUILD_DIR)

# Use common rules
USE_COMMON_RULES = yes
