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

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pymongo
HUMAN_VERSION =			4.4.1
COMPONENT_SUMMARY =		pymongo - Python driver for MongoDB <http://www.mongodb.org>
COMPONENT_PROJECT_URL =		http://github.com/mongodb/mongo-python-driver
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/bf/1c/38b956d48667745f2f083937dd31b0467fa3f537480e30c692b1fc4fef3d/pymongo-4.4.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:a4df87dbbd03ac6372d24f2a8054b4dc33de497d5227b50ec649f436ad574284
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# pymongo --> mockupdb ==> pymongo
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/dnspython
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
