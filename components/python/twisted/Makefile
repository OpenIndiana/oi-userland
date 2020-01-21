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

BUILD_STYLE=setup.py
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Twisted
COMPONENT_VERSION=	19.10.0
COMPONENT_SUMMARY=	'Event-based framework for internet applications'
COMPONENT_PROJECT_URL=	http://twistedmatrix.com/trac/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:7394ba7f272ae722a74f3d969dcf599bc4ef093bc392038748a490f1724a515d
COMPONENT_ARCHIVE_URL=	http://twistedmatrix.com/Releases/$(COMPONENT_NAME)/19.10/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION= Development/Python
COMPONENT_FMRI=	library/python/python-twisted
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= twisted.license

PYTHON_VERSIONS=	2.7 3.5

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR =	$(SOURCE_DIR)/src/twisted/test
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =	--verbose

COMPONENT_TEST_TRANSFORMS += \
	'-n -e "s/in .* seconds //p"' \
	'-e "/::.*FAILED/p"' \
	'-e "/::.*ERROR/p"'

COMPONENT_POST_INSTALL_ACTION += ( cd $(PROTO_DIR)/usr/bin && \
	for file in cftp ckeygen conch mailmail pyhtmlizer tkconch trial twist twistd; \
	do mv $$file $$file-$(PYTHON_VERSION); done)

# Test dependency
REQUIRED_PACKAGES += library/python/incremental-27
REQUIRED_PACKAGES += library/python/incremental-35

# Tests do not finish. Results are 
# 2.7 32bit - 19 failed, 2053 passed, 901 skipped
# 2.7 64bit - 19 failed, 2053 passed, 906 skipped
# 3.5       - 18 failed, 2052 passed, 915 skipped

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
