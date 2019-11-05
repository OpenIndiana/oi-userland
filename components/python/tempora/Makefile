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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tempora
COMPONENT_VERSION=	1.13
COMPONENT_SUMMARY=	'Objects and routines pertaining to date and time'
COMPONENT_PROJECT_URL=	https://pypi.org/project/tempora/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:4848df474c9d7ad9515fbeaadc88e48843176b4b90393652156ccff613bcaeb1
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/tempora
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV += SETUPTOOLS_SCM_PRETEND_VERSION=$(COMPONENT_VERSION)
COMPONENT_INSTALL_ENV += SETUPTOOLS_SCM_PRETEND_VERSION=$(COMPONENT_VERSION)

COMPONENT_POST_INSTALL_ACTION += \
        (cd $(PROTO_DIR)/usr/bin && \
          $(MV) -f calc-prorate calc-prorate-$(PYTHON_VERSION))

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:           $(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += library/python/setuptools_scm-27
REQUIRED_PACKAGES += library/python/setuptools_scm-34
REQUIRED_PACKAGES += library/python/setuptools_scm-35

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/setuptools-34
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
