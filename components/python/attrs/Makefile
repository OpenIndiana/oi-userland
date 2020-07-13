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
# Copyright (c) 2019, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		attrs
COMPONENT_VERSION=	18.2.0
COMPONENT_REVISION=	2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:10cbf6e27dbce8c30807caf056c8eb50917e0eaafe86347671b57254006c3e69
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://www.attrs.org/en/stable/

PYTHON_VERSIONS = 2.7 3.5

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR =	$(SOURCE_DIR)/tests
COMPONENT_TEST_CMD =	$(PYTHON)
COMPONENT_TEST_ARGS =	main_runner.py

# Testing related components
REQUIRED_PACKAGES += library/python/coverage
#REQUIRED_PACKAGES += library/python/hypothesis
REQUIRED_PACKAGES += library/python/python-zope-interface
REQUIRED_PACKAGES += library/python/six

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
