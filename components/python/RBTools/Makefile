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
#   $WS_TOOLS/python-integrate-project -d python/RBTools rbtools
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		rbtools
HUMAN_VERSION =			5.2.1
COMPONENT_SUMMARY =		Command line tools and API for working with code and document reviews on Review Board
COMPONENT_ARCHIVE_HASH =	\
	sha256:f2863515ef6ff1cfcd3905d5f409ab8c4d12878b364d6f805ba848dcaecb97f2
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

# https://hellosplat.com/s/beanbag/tickets/4993/
# https://hellosplat.com/s/beanbag/tickets/4995/
COMPONENT_SRC_1 =		rbtools-release-$(HUMAN_VERSION)
COMPONENT_ARCHIVE_1 =		release-$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_URL_1 =	\
	https://github.com/reviewboard/rbtools/archive/refs/tags/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1 =	\
	sha256:ccad1c11175be50572200bef2a4ccbb8eb8e4ceab94cf57be642e712ea05827b
CLEAN_PATHS += $(COMPONENT_SRC_1)
# https://hellosplat.com/s/beanbag/tickets/4993/
COMPONENT_POST_UNPACK_ACTION_1 += \
	$(RM) -r $(COMPONENT_SRC)/rbtools/clients/tests/testdata ; \
	$(CP) -a $(COMPONENT_SRC_1)/rbtools/clients/tests/testdata $(COMPONENT_SRC)/rbtools/clients/tests/testdata ;
# https://hellosplat.com/s/beanbag/tickets/4995/
COMPONENT_POST_UNPACK_ACTION_1 += \
	$(RM) -r $(COMPONENT_SRC)/rbtools/testing/scripts ; \
	$(CP) -a $(COMPONENT_SRC_1)/rbtools/testing/scripts $(COMPONENT_SRC)/rbtools/testing/scripts ;

include $(WS_MAKE_RULES)/common.mk

# Tests needs GNU tools
COMPONENT_TEST_ENV += PATH=$(PATH.gnu)

# Testing needs HOME environment variable (the directory does not need to
# exist)
COMPONENT_TEST_ENV += HOME="$(@D)/.test_home"

# Manually added dependencies
TEST_REQUIRED_PACKAGES += developer/versioning/cvs
TEST_REQUIRED_PACKAGES += developer/versioning/mercurial
TEST_REQUIRED_PACKAGES += developer/versioning/subversion
TEST_REQUIRED_PACKAGES += developer/versioning/git
# see setup.cfg
TEST_REQUIRED_PACKAGES.python += library/python/pytest-env

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/certifi
PYTHON_REQUIRED_PACKAGES += library/python/colorama
PYTHON_REQUIRED_PACKAGES += library/python/housekeeping
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/importlib-resources
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/puremagic
PYTHON_REQUIRED_PACKAGES += library/python/pydiffx
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/texttable
PYTHON_REQUIRED_PACKAGES += library/python/tqdm
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
