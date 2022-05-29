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

COMPONENT_NAME=		PyQt-builder
COMPONENT_VERSION=	1.12.2
COMPONENT_SUMMARY=	The PEP 517 compliant PyQt build system
COMPONENT_PROJECT_URL=	https://pypi.org/project/PyQt-builder/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:f62bb688d70e0afd88c413a8d994bda824e6cebd12b612902d1945c5a67edcd7
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/pyqtbuilder
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= LICENSE-GPL3

PYTHON_VERSION=	3.9
PYTHON_VERSIONS=	3.9

include $(WS_MAKE_RULES)/common.mk

# Manually added dependencies
REQUIRED_PACKAGES += library/python/packaging-39
REQUIRED_PACKAGES += library/python/sip

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-39
