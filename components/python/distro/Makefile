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
# Copyright (c) 2021 Nona Hansel
#

BUILD_BITS=					NO_ARCH
BUILD_STYLE=				setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			distro
COMPONENT_VERSION=	1.5.0
COMPONENT_FMRI=			library/python/distro	
COMPONENT_CLASSIFICATION= Development/Python		
COMPONENT_SUMMARY=	'Alternative implementation for Python's platform.linux_distribution()'	
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0e58756ae38fbd8fc3020d54badb8eae17c5b9dcbed388b17bb55b8a5928df92
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://pypi.org/project/distro/
COMPONENT_LICENSE=			Apache-2.0
COMPONENT_LICENSE_FILE= LICENSE	

PYTHON_VERSIONS=			3.7 3.9	

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
