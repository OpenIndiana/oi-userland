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

COMPONENT_NAME=		pep517
COMPONENT_VERSION=	0.12.0
COMPONENT_SUMMARY=	Wrappers to build Python packages using PEP 517 hooks
COMPONENT_PROJECT_URL=	https://pypi.org/project/pep517/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:931378d93d11b298cf511dd634cf5ea4cb249a28ef84160b3247ee9afb4e8ab0
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/pep517
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE

PYTHON_VERSIONS=	3.7 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
