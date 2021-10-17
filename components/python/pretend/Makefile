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
# Copyright 2021, Andreas Wacknitz
#

BUILD_BITS= NO_ARCH
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pretend
COMPONENT_VERSION=	1.0.9
COMPONENT_SUMMARY=	Pretend is a library to make stubbing with Python easier.
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_FMRI=		library/python/pretend
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://github.com/alex/pretend
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:c90eb810cde8ebb06dafcb8796f9a95228ce796531bc806e794c2f4649aa1b10
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_LICENSE=	Apache2

PYTHON_VERSIONS=	$(PYTHON3_VERSIONS)

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Auto-generated dependencies
