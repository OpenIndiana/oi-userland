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
# Copyright 2016 Alexander Pyhalov
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	python-dateutil
COMPONENT_VERSION= 	2.8.1
COMPONENT_REVISION=	2
COMPONENT_SUMMARY= 	Extensions to standard Python datetime module
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:73ebfe9dbf22e832286dafa60473e4cd239f8592f699aa5adaf10050e6e1823c
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL = https://pypi.python.org/python-dateutil/
COMPONENT_FMRI=		library/python/python-dateutil
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_SUMMARY=	powerful extensions to the standard datetime module
COMPONENT_LICENSE=	Apache 2.0, BSD 3-clause

PYTHON_VERSIONS=	$(PYTHON_ALL_VERSIONS)

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
