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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		netaddr
COMPONENT_VERSION=	0.7.13
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ca42c260b49e5fd74ba9104efa6a4fca6b55316ca42714d20d2b9b8e751e0412
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://github.com/drkjam/netaddr/
COMPONENT_BUGDB=	python-mod/netaddr

TPNO=			21724

# Depends on iPython which is not Python 3 ready.
PYTHON_VERSIONS=	$(PYTHON2_VERSIONS)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_INSTALL_ACTION = \
	(cd $(PROTO_DIR)/usr/bin ; $(MV) netaddr netaddr-$(PYTHON_VERSION))

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

COMPONENT_TEST_DIR=	$(@D)/lib/netaddr
COMPONENT_TEST_ARGS=	tests/__init__.py
COMPONENT_PRE_TEST_ACTION= \
	(cd $(COMPONENT_TEST_DIR)/tests ; \
	 ln -s $(SOURCE_DIR)/netaddr/tests/2.x ; \
	 ln -s $(SOURCE_DIR)/netaddr/tests/3.x )

# Master test results are the same for all Python versions, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# The additional netaddr specific set of transforms to be applied to the test
# results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|\(Ran 28 tests in\).*|\1|" '

test:		$(TEST_NO_ARCH)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += library/python/ipython-27
