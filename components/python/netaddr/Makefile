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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#

BUILD_STYLE= setup.py
BUILD_BITS= NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		netaddr
COMPONENT_VERSION=	0.7.18
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a1f5c9fcf75ac2579b9995c843dade33009543c04f218ff7c007b3c81695bd19
COMPONENT_PROJECT_URL=  http://github.com/drkjam/netaddr/
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/n/netaddr/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/netaddr

PYTHON_VERSIONS=3.5

include $(WS_MAKE_RULES)/common.mk

# Replace "#!/usr/bin/env ..." shebang lines with properly versioned ones.
COMPONENT_PRE_BUILD_ACTION = \
        /usr/bin/find $(SOURCE_DIR) -name *.py \
                -exec $(GSED) -i -e 's/env python/python$(PYTHON_VERSION)/' "{}" \; ;


COMPONENT_POST_INSTALL_ACTION = \
	(cd $(PROTOUSRBINDIR) ; $(MV) netaddr netaddr-$(PYTHON_VERSION))

COMPONENT_TEST_DIR =    $(SOURCE_DIR)
COMPONENT_TEST_CMD =    $(PYTHON) -m pytest
COMPONENT_TEST_ARGS =
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-e "/^plugins:/d" ' \
	'-e "s|in [0-9\.]* seconds ||g" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/ipython-35
REQUIRED_PACKAGES += runtime/python-35
