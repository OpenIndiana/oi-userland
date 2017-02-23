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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		croniter
COMPONENT_VERSION=	0.3.12
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:445cb26bc2f3cff25a7b06575caf98312b552affffeee0437f26d416c6e3c895
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://github.com/kiorky/croniter
COMPONENT_BUGDB=	python-mod/croniter
COMPONENT_ANITYA_ID=	13188

TPNO=			28601

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# Run the tests in the build directory so as not to touch the source directory.
# The tests are copied over during the build, so we don't have to do that now.
COMPONENT_TEST_DIR = $(@D)
COMPONENT_TEST_CMD = py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS = --result-log=$(COMPONENT_TEST_OUTPUT)
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

test:		$(TEST_NO_ARCH)

system-test:	$(NO_TESTS)


REQUIRED_PKGS_PYVER += library/python/dateutil-PYVER
REQUIRED_PACKAGES += $(foreach v,$(subst .,,$(PYTHON_VERSIONS)),$(subst -PYVER,-$(v),$(REQUIRED_PKGS_PYVER)))
