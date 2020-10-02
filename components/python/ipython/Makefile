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

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ipython
COMPONENT_VERSION=	5.10.0
COMPONENT_PROJECT_URL=	http://ipython.org/
COMPONENT_SUMMARY=	Enhanced interactive Python shell
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:d1f9e2d02bb0900ddef7b6af114aca3a5cf3dc43b9de1f19d37c4aedbc724fee
COMPONENT_ARCHIVE_URL=	http://archive.ipython.org/release/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/python/ipython
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	BSD

PYTHON_VERSIONS= 3.5

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Replace "#!/usr/bin/env ..." shebang lines with properly versioned ones.
COMPONENT_PRE_BUILD_ACTION = \
	/usr/bin/find $(SOURCE_DIR) -name *.py \
		-exec $(GSED) -i -e 's/env python/python$(PYTHON_VERSION)/' "{}" \; ;

COMPONENT_POST_INSTALL_ACTION = \
        (cd $(PROTO_DIR)/usr/bin ; \
                $(MV) ipython ipython-$(PYTHON_VERSION);\
		$(MV) iptest iptest-$(PYTHON_VERSION); )


# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-35
