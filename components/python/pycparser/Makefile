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
# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pycparser
COMPONENT_VERSION=	2.10
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:957d98b661c0b64b580ab6f94b125e09b6714154ee51de40bca16d3f0076b86c
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/eliben/pycparser
COMPONENT_BUGDB=	python-mod/pycparser

TPNO=			16938

include $(WS_MAKE_RULES)/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_TEST_CMD =	py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =	--resultlog $(@D)/testresults
COMPONENT_TEST_ARGS +=	-p no:codechecker
COMPONENT_TEST_ENV +=	PATH=$$PATH:$(BUILD_DIR)/bin

$(SOURCE_DIR)/pycparser/ply/lex.py: $(SOURCE_DIR)/.patched

$(BUILD_DIR)/license.ply: $(SOURCE_DIR)/pycparser/ply/lex.py
	nawk '/^# Copyright / {p=1} /^# ---/ {p=0} p == 1 {print substr($$0, 3)}' $< > $@

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH) $(BUILD_DIR)/license.ply

test:		$(TEST_NO_ARCH)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
