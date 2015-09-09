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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pylint
COMPONENT_VERSION=	1.4.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=		\
	sha256:1dce8c143a5aa15e0638887c2b395e2e823223c63ebaf8d5f432a99e44b29f60
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=  https://bitbucket.org/logilab/pylint
COMPONENT_BUGDB=	utility/pylint

TPNO=			22903

# Since Pylint 1.4, it only supports Python 2.7+ and Python 3.3+.
PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/setup.py.mk

# There are several pylint documentation files that setup.py isn't installing
# but are present in the pylint package on other distributions. Copy them into
# the proto area "manually", so they can be included in the package.
PDOC =			$(PROTO_DIR)/usr/share/doc
PDOC_PYLINT =		$(PDOC)/pylint
PDOC_PYLINT_EXAMPLES =	$(PDOC_PYLINT)/examples

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/README $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/README.Python3 $(PDOC_PYLINT) ;

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/examples/custom.py $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/examples/custom_raw.py $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/elisp/pylint.el $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/examples/pylintrc_camelcase $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/examples/pylintrc $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTO_DIR)/usr/bin; $(MV) epylint epylint-$(PYTHON_VERSION)) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTO_DIR)/usr/bin; $(MV) pylint pylint-$(PYTHON_VERSION)) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTO_DIR)/usr/bin; $(MV) pylint-gui pylint-gui-$(PYTHON_VERSION)) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTO_DIR)/usr/bin; $(MV) pyreverse pyreverse-$(PYTHON_VERSION)) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTO_DIR)/usr/bin; $(MV) symilar symilar-$(PYTHON_VERSION)) ;

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets

build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)
	$(PYTHON.2.7.32) -m py_compile $(PROTO_DIR)/usr/lib/python2.7/vendor-packages/pylint/testutils.py

# The tests are run using python 2.7 only and require that
# the python-27 package is installed (does not have to be the default python). 

# Use the python 2.7 libraries for testing.
test: PYTHON_VERSION=2.7

# logilab-common and astroid are runtime dependencies of pylint,
# and we need to use their latest versions from this workspace.
# We can't just add their install targets as dependencies here,
# so just "gmake install" in the logilab-common and astroid
# component directories before running the pylint tests.
COMPONENT_PRE_TEST_ACTION = ($(GMAKE) -C \
	$(COMPONENT_DIR)/../logilab-common install; \
	$(GMAKE) -C $(COMPONENT_DIR)/../astroid install )

COMPONENT_TEST_ENV = PYTHONPATH=$(COMPONENT_DIR)/../logilab-common/build/prototype/$(MACH)$(PYTHON_VENDOR_PACKAGES):$(COMPONENT_DIR)/../astroid/build/prototype/$(MACH)$(PYTHON_VENDOR_PACKAGES):$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES)

# The test output contains details from each test, in whatever order they
# complete. Use nawk to extract just the sections that summarizes the test result.
COMPONENT_TEST_CMD = /usr/bin/pytest-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMER =	$(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/Ran (.+) test cases/{ sub(/in(.+)\)/, \"\"); print }/All (.+) modules OK/'"

# Expected failures for test target:
# 437 test cases, 19 skipped
# All 23 modules OK

test:		$(TEST_NO_ARCH)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += library/python/logilab-common-27
REQUIRED_PACKAGES += library/python/astroid-27
REQUIRED_PACKAGES += library/python/six-27
