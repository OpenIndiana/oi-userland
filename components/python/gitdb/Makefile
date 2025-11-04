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
#   $WS_TOOLS/python-integrate-project gitdb
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		gitdb
HUMAN_VERSION =			4.0.12
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Git Object Database
COMPONENT_PROJECT_URL =		https://github.com/gitpython-developers/gitdb
COMPONENT_ARCHIVE_HASH =	\
	sha256:5ef71f855d191a3326fcfbc0d5da835f26b13fbcba60c32c21091c349ffdb571
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# See https://github.com/gitpython-developers/gitdb/issues/70
COMPONENT_PRE_TEST_ACTION += ( \
	$(RM) -r $(COMPONENT_TEST_DIR)/.git-test-tree ; \
	$(GIT) clone https://github.com/gitpython-developers/gitdb.git $(COMPONENT_TEST_DIR)/.git-test-tree ; \
	cd $(COMPONENT_TEST_DIR)/.git-test-tree ; \
	$(GIT) reset --hard $(HUMAN_VERSION) ; \
) ;
COMPONENT_TEST_ENV += GITDB_TEST_GIT_REPO_BASE=$(COMPONENT_TEST_DIR)/.git-test-tree/.git

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/smmap
REQUIRED_PACKAGES.python += runtime/python
