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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS =		32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pyatspi
COMPONENT_VERSION=	2.18.0
COMPONENT_PROJECT_URL=	http://www.linuxfoundation.org/en/AT-SPI_on_D-Bus
COMPONENT_ARCHIVE_HASH= \
	sha256:f86f03ad05d0502cd60fe8b98f746f74ce3bc208e9f3798f6a2130b3c5f4ab46
COMPONENT_BUGDB=	gnome/a11y-libs-core
COMPONENT_ANITYA_ID=	13157

TPNO=			30736

# replicated from $(WS_MAKE_RULES)/setup.py.mk since this uses configure.mk
CONFIGURE_64 += $(PYTHON3_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.configured)
$(BUILD_DIR)/%-3.4/.configured:		PYTHON_VERSION=3.4
$(BUILD_DIR)/%-3.5/.configured:		PYTHON_VERSION=3.5
$(BUILD_DIR)/$(MACH64)-%/.configured:	BITS=64

BUILD_64 += $(PYTHON3_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.built)
$(BUILD_DIR)/%-3.4/.built:		PYTHON_VERSION=3.4
$(BUILD_DIR)/%-3.5/.built:		PYTHON_VERSION=3.5
$(BUILD_DIR)/$(MACH64)-%/.built:	BITS=64

INSTALL_64 += $(PYTHON3_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.installed)
$(BUILD_DIR)/%-3.4/.installed:		PYTHON_VERSION=3.4
$(BUILD_DIR)/%-3.5/.installed:		PYTHON_VERSION=3.5
$(BUILD_DIR)/$(MACH64)-%/.installed:	BITS=64

# Tests require dbus python module, which we don't have for python3 yet
TEST_TARGET= $(SKIP_TEST)

# Requires pygobject3, not available in S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

CONFIGURE_OPTIONS += --disable-static
# Tests require dbus python module, which we don't have for python3 yet
CONFIGURE_OPTIONS += --disable-tests
CONFIGURE_OPTIONS += --with-python=$(PYTHON)

# Ensure Python modules are installed into vendor package directories.
CONFIGURE_ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)

# Make install path match what autopyc transforms look for
COMPONENT_POST_INSTALL_ACTION += \
     case "$(PYTHON_VERSION)" in \
	3.*) $(SYMLINK) 64/pyatspi $(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES.32)/pyatspi ;; \
     esac ;

REQUIRED_PACKAGES += library/python/pygobject-3
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35

# These are needed to build & run tests, but not for distributed packages
# REQUIRED_PACKAGES += library/desktop/atk
# REQUIRED_PACKAGES += library/desktop/gtk2
# REQUIRED_PACKAGES += library/glib2
# REQUIRED_PACKAGES += library/libxml2
# REQUIRED_PACKAGES += library/python/python-dbus
# REQUIRED_PACKAGES += system/library/libdbus
# REQUIRED_PACKAGES += system/library/libdbus-glib
