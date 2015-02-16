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

COMPONENT_NAME=		TwistedWeb2
COMPONENT_VERSION=	8.1.0
COMPONENT_PROJECT_URL=	http://twistedmatrix.com/trac/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:0f016d498b1db0216861e9b8fbf8ad49b5b587fa64a18f1640095c1e4f93e391
COMPONENT_ARCHIVE_URL=	http://tmrc.mit.edu/mirror/twisted/Web2/8.1/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/twisted-web2

TPNO=			9693

# Depends on twisted, which is not Python 3 ready.
PYTHON_VERSIONS=	2.7 2.6

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# Master test results are the same for all versions of Python, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Use nawk to just extract lines:
# containing "[OK]" or "[ERROR]"
# starting with "Ran . tests in"
# starting with "FAILED" or "PASSED"
# and stripping out the random portions (like time to complete the tests).
COMPONENT_TEST_TRANSFORMER =    $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/\[ERROR\]/ { print }; /\[OK\]/ { print }; /^Ran / { sub(\" tests in .+s\", \" tests in\"); print }; /^FAILED / { print }; /^PASSED / { print };'"

COMPONENT_TEST_DIR =	$(COMPONENT_SRC)
COMPONENT_TEST_CMD =	/usr/demo/twisted-python$(PYTHON_VERSION)/trial
COMPONENT_TEST_ARGS =	twisted/web2/test/test_xmlrpc.py

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build:          $(BUILD_NO_ARCH)

install:        $(INSTALL_NO_ARCH)

test:           $(TEST_NO_ARCH)
