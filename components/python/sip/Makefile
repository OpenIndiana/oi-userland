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

COMPONENT_NAME=		sip
COMPONENT_VERSION=	6.6.1
COMPONENT_SUMMARY=	A Python bindings generator for C/C++ libraries
COMPONENT_PROJECT_URL=	https://pypi.org/project/sip/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:696c575c72144122701171f2cc767fe6cc87050ea755a04909152a8508ae10c3
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/sip
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= LICENSE-GPL3

PYTHON_VERSION= 3.9
PYTHON_VERSIONS= 3.9

include $(WS_MAKE_RULES)/common.mk

	
$(MANIFEST_BASE)-%.depend:	$(MANIFEST_BASE)-%.mangled
	sed -i 's/cpython-39.so/so/g' $(BUILD_DIR)/*.mangled
	$(PKGDEPEND) generate $(PKGDEPEND_GENERATE_OPTIONS) $< >$@

# Build dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/packaging-39
REQUIRED_PACKAGES += library/python/ply-39
REQUIRED_PACKAGES += library/python/pyparsing-39
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += library/python/toml-39
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
