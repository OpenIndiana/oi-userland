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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ipython
COMPONENT_VERSION=	0.10
COMPONENT_PROJECT_URL=	http://ipython.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:60d602637dc5f078b083a4ca5ab64364ba816bd72439844012ed11a30f88228c
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_BUGDB=	python-mod/ipython
COMPONENT_ANITYA_ID=	1399

TPNO=			9640

# Syntax issues: not Python 3 ready.
PYTHON_VERSIONS = $(PYTHON2_VERSIONS)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# Unpack the ipython man pages.
COMPONENT_POST_UNPACK_ACTION = \
	(cd $(SOURCE_DIR)/docs/man; /usr/bin/gunzip * )

# Replace "#!/usr/bin/env ..." shebang lines with properly versioned ones.
COMPONENT_POST_INSTALL_ACTION = \
	/usr/bin/find $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION) -name *.py \
		-exec $(GSED) -i -e 's|env python|python$(PYTHON_VERSION)|' "{}" \; ;

COMPONENT_TEST_ARGS= ../scripts/iptest

# We don't want anything created in the home directory.
COMPONENT_TEST_ENV+= IPYTHONDIR=$(BUILD_DIR)

# Different amount of tests are run for sparc and x86
COMPONENT_TEST_MASTER = \
        $(COMPONENT_TEST_RESULTS_DIR)/results-$(PYTHON_VERSION)-$(MACH)-$(BITS).master

# Touching up test results
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|\(^Ran [0-9][0-9]* tests* \).*|\1|" ' \
	'-e "/tmp.*/d" ' \
	'-e "/fakemodule.*/d" ' \
	'-e "/builds.*/d" ' \
	'-e "/home.*/d" '

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(TEST_NO_ARCH)

system-test:    $(NO_TESTS)

REQUIRED_PACKAGES += library/python/python-twisted-27
REQUIRED_PACKAGES += library/python/setuptools-27

