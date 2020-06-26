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
# Copyright 2016, Aurelien Larcher.
#
BUILD_STYLE= setup.py
BUILD_BITS= NO_ARCH

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= python-certifi
COMPONENT_VERSION= 2020.06.20
IPS_COMPONENT_VERSION= 2020.6.20
COMPONENT_FMRI= library/python/certify
COMPONENT_PROJECT_URL=  http://certifi.io/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:323a62f5ddfa1a4f093246b52f451aacb725b6cc8eefe647ad6f8bcbed3c9131
COMPONENT_ARCHIVE_URL= \
    https://github.com/certifi/python-certifi/archive/$(COMPONENT_VERSION).tar.gz

TEST_TARGET= $(NO_TESTS)
PYTHON_VERSIONS=	2.7 3.5

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
