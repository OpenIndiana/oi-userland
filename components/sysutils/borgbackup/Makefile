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
#   $WS_TOOLS/python-integrate-project -d sysutils/borgbackup borgbackup
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		borgbackup
HUMAN_VERSION =			1.4.2
COMPONENT_SUMMARY =		Deduplicated, encrypted, authenticated and compressed backups
COMPONENT_PROJECT_URL =		https://borgbackup.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:8923f5e953205d81138d1d7276c8a1c864215e230994d620c397635568ed376f
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_FMRI =		backup/borg
COMPONENT_CLASSIFICATION =	Applications/System Utilities

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

# To fully utilize pytest-xdist
COMPONENT_TEST_ENV += XDISTN=auto

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/libxxhash
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/cython
REQUIRED_PACKAGES.python += library/python/msgpack
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += library/python/pkgconfig
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/cython
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pkgconfig
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-benchmark
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/setuptools-scm
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
TEST_REQUIRED_PACKAGES.python += library/python/wheel
