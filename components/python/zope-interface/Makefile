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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS = 32_and_64
BUILD_STYLE= setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zope.interface
COMPONENT_VERSION=	5.2.0
COMPONENT_FMRI=         library/python/python-zope-interface
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_PROJECT_URL=	https://zope.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:2abe865ee27fd1faadaf4a292d2cbd126cb7d3bc0d3ac275f4dff7bb9bf73539
COMPONENT_ARCHIVE_URL= \
  https://github.com/zopefoundation/$(COMPONENT_NAME)/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=      ZPL

PYTHON_VERSIONS=	2.7 3.5 3.7 3.9

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR =    $(SOURCE_DIR)/src
COMPONENT_TEST_CMD =    $(PYTHON) -m pytest
COMPONENT_TEST_ARGS =

COMPONENT_SYSTEM_TEST_DIR =     $(SOURCE_DIR)/src
COMPONENT_SYSTEM_TEST_CMD =     $(PYTHON) -m pytest
COMPONENT_SYSTEM_TEST_ARGS =

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
