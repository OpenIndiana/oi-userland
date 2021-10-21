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
# Copyright 2021 Andreas Wacknitz
#

BUILD_BITS= NO_ARCH
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		typing_extensions
COMPONENT_VERSION=	3.10.0.2
COMPONENT_SUMMARY=	Backported and Experimental Type Hints for Python 3.5+
COMPONENT_PROJECT_URL=	https://github.com/python/typing/blob/master/typing_extensions/README.rst
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:49f75d16ff11f1cd258e1b988ccff82a3ca5570217d7ad8c5f48205dd99a677e
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_FMRI=		library/python/typing_extensions
COMPONENT_LICENSE=	BSD

PYTHON_VERSIONS=	$(PYTHON3_VERSIONS)

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
