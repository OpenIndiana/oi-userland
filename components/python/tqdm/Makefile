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
# Copyright 2019 Nona Hansel
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tqdm
COMPONENT_VERSION=	4.34.0
COMPONENT_SUMMARY=	'Fast, extensible progress bar for Python and CLI'
COMPONENT_PROJECT_URL=	https://github.com/tqdm/tqdm
COMPONENT_FMRI=		library/python/tqdm		
COMPONENT_CLASSIFICATION= Development/Python 
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_ARCHIVE_HASH= \
	sha256:ebc205051d79b49989140f5f6c73ec23fce5f590cbc4d9cd6e4c47f168fa0f10
COMPONENT_LICENSE=	MPLv2.0,MIT
COMPONENT_LICENSE_FILE=	LICENCE

PYTHON_VERSIONS=	3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:          $(BUILD_NO_ARCH)

install:        $(INSTALL_NO_ARCH)

test:           $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-35
