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
#   $WS_TOOLS/python-integrate-project pymongo
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pymongo
HUMAN_VERSION =			4.7.2
COMPONENT_SUMMARY =		Python driver for MongoDB <http://www.mongodb.org>
COMPONENT_PROJECT_URL =		https://www.mongodb.org
COMPONENT_ARCHIVE_URL =		\
	https://github.com/mongodb/mongo-python-driver/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:e92a44e27ba003e7e53d82113aaafb3c38db96c1bc96f26a8236a367796873d1
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# Github tarball use different source directory than sdist
COMPONENT_SRC =		mongo-python-driver-$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Normalize pointer
COMPONENT_TEST_TRANSFORMS += "-e 's/\(traceback object at \)0x[a-f0-9]\{12\}>/\1\$$(POINTER)>/g'"
# The order of items in the list is random
COMPONENT_TEST_TRANSFORMS += "-e 's/\(Must be one of (\)[^)]\{1,\})/\1LIST)/g'"

# For testing the svc:/application/database/mongodb-44:default service must be
# online.

# Manually added test dependencies
TEST_REQUIRED_PACKAGES += service/database/mongodb-44

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/dnspython
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/pytest
