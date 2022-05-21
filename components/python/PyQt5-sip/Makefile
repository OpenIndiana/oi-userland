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

COMPONENT_NAME=		PyQt5-sip
COMPONENT_VERSION=	12.10.1
COMPONENT_SUMMARY=	The sip module support for PyQt5
COMPONENT_PROJECT_URL=	https://pypi.org/project/PyQt5-sip/
COMPONENT_SRC=		PyQt5_sip-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:97e008795c453488f51a5c97dbff29cda7841afb1ca842c9e819d8e6cc0ae724
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/pyqt5-sip
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= LICENSE-GPL3

PYTHON_VERSIONS=	3.9

include $(WS_MAKE_RULES)/common.mk

	
$(MANIFEST_BASE)-%.depend:	$(MANIFEST_BASE)-%.mangled
	sed -i 's/cpython-39.so/so/g' $(BUILD_DIR)/*.mangled
	$(PKGDEPEND) generate $(PKGDEPEND_GENERATE_OPTIONS) $< >$@

	

# Build dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/pyqt5
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library

