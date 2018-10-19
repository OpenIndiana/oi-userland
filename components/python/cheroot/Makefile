#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2018 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cheroot
COMPONENT_VERSION=	6.5.2
COMPONENT_SUMMARY=	'Cheroot - high-performance, pure-Python HTTP server'
COMPONENT_PROJECT_URL=	https://github.com/cherrypy/cheroot
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ba2b9b0f59fcdcd920d51f61c19c4a8d65f8469741e634c04eaf6feca5b76837
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/cheroot
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE.md

PYTHON_VERSIONS=	2.7 3.4 3.5

COMPONENT_POST_INSTALL_ACTION = \
        (cd $(PROTO_DIR)/usr/bin ; $(MV) -f cheroot cheroot-$(PYTHON_VERSION))

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV += SETUPTOOLS_SCM_PRETEND_VERSION=$(COMPONENT_VERSION)
COMPONENT_INSTALL_ENV += SETUPTOOLS_SCM_PRETEND_VERSION=$(COMPONENT_VERSION)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:           $(NO_TEST)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/setuptools-34
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
