#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# This file was automatically generated using the following command:
#   $WS_TOOLS/python-integrate-project -d developer/mercurial mercurial
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		mercurial
HUMAN_VERSION =			6.9.1
COMPONENT_SUMMARY =		Fast scalable distributed SCM (revision control, version control) system
COMPONENT_ARCHIVE_HASH =	\
	sha256:e577577ee9a97a9f84d3c34d53ccb8b9354263d6ab96447525094f3e0a567270
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	COPYING

COMPONENT_FMRI =		developer/versioning/mercurial
COMPONENT_CLASSIFICATION =	Development/Source Code Management

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

TEST_STYLE = custom

include $(WS_MAKE_RULES)/common.mk

# Build and install documentation
COMPONENT_POST_BUILD_ACTION += cd $(@D) ; $(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) doc ;
COMPONENT_POST_INSTALL_ACTION += cd $(@D) ; $(ENV) $(COMPONENT_INSTALL_ENV) $(GMAKE) DESTDIR=$(PROTO_DIR) PREFIX=$(USRDIR) install-doc ;

# This test fails with PYTHONPATH set
TEST_BLACKLIST += test-hghave.t
# https://bz.mercurial-scm.org/show_bug.cgi?id=6402
TEST_BLACKLIST += test-stdio.py
# https://bz.mercurial-scm.org/show_bug.cgi?id=6915
TEST_BLACKLIST += test-patchbomb.t
# https://bz.mercurial-scm.org/show_bug.cgi?id=6899
TEST_BLACKLIST += test-revlog-mmapindex.t
# https://bz.mercurial-scm.org/show_bug.cgi?id=6957
TEST_BLACKLIST += test-highlight.t

# Use bash in sh mode for the tests; using /bin/sh on Solaris hasn't always
# worked, and using /bin/bash doesn't always work, either.
# Test the bits from the proto area, rather than rebuilding.
COMPONENT_PRE_TEST_ACTION += \
	(cd $(BUILD_DIR); rm -f sh; ln -s /bin/bash sh; \
	printf "%s\n" $(TEST_BLACKLIST) > blacklist);

# see tests/README
COMPONENT_TEST_DIR =	$(@D)/tests
COMPONENT_TEST_ENV +=	TERM=dumb
COMPONENT_TEST_ENV +=	HGTEST_JOBS=$(or $(HGTEST_JOBS),1)
COMPONENT_TEST_ENV +=	PATH=$(PATH.gnu)
COMPONENT_TEST_CMD =	$(PYTHON)
COMPONENT_TEST_ARGS =	./run-tests.py \
			--verbose \
			--shell $(BUILD_DIR)/sh \
			--with-hg $(PROTOUSRBINDIR)/hg \
			--blacklist $(BUILD_DIR)/blacklist
COMPONENT_TEST_TARGETS =

# Random temporary directory
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/hgtests\.[^ ]\{8\}|\$$(HGTMP)|g'"
# Sequential number of test working directory
COMPONENT_TEST_TRANSFORMS += "-e 's|\(/child\)[0-9]\{1,\}/|\1X/|g'"
# Daemon process PID
COMPONENT_TEST_TRANSFORMS += "-e 's/\([Dd]aemon process \)[0-9]\{1,\}/\1\$$(PID)/'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
