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
#   $WS_TOOLS/python-integrate-project RBTools
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		RBTools
HUMAN_VERSION =			4.1
COMPONENT_SUMMARY =		RBTools - Command line tools and API for working with code and document reviews on Review Board
COMPONENT_PROJECT_URL =		https://www.reviewboard.org/downloads/rbtools/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/19/ef/8900501b1af41d2485ee1eabb9f3e309f80fdae911c97927d8917ae99f9f/RBTools-4.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:24efb20346b905c9be0464e747ee1bdee7967d1b94175697ea0c830d929475ff
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
	sha256:c840655f46b3cbded1803e77b53a4f8df74dcd2d7bfa1391b15646345f08ac99
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

# Manually added dependencies
TEST_REQUIRED_PACKAGES += developer/versioning/cvs
TEST_REQUIRED_PACKAGES += developer/versioning/mercurial
TEST_REQUIRED_PACKAGES += developer/versioning/subversion
TEST_REQUIRED_PACKAGES += developer/versioning/git

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/certifi
PYTHON_REQUIRED_PACKAGES += library/python/colorama
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/pydiffx
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/texttable
PYTHON_REQUIRED_PACKAGES += library/python/tqdm
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
