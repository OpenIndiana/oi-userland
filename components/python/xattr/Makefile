#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2020 Nona Hansel
#

# Component uses ABI3 naming.
PYTHON3_SOABI=abi3

BUILD_BITS=		64
BUILD_STYLE=		setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xattr
COMPONENT_VERSION=	0.9.7
COMPONENT_SUMMARY=	'Extended attributes library wrapper for Python'
COMPONENT_PROJECT_URL=	https://pyxattr.k1024.org/
COMPONENT_FMRI=		library/python/xattr
COMPONENT_CLASSIFICATION= Development/Python 
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(call pypi_url)	
COMPONENT_ARCHIVE_HASH= \
	sha256:b0bbca828e04ef2d484a6522ae7b3a7ccad5e43fa1c6f54d78e24bb870f49d44
COMPONENT_LICENSE=	LGPLv2+
COMPONENT_LICENSE_FILE=	LICENSE.txt

PYTHON_VERSIONS=	3.5

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
