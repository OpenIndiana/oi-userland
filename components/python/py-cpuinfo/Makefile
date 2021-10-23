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
# Copyright 2021 Aurelien Larcher
#

BUILD_BITS= NO_ARCH
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		py-cpuinfo
COMPONENT_VERSION=	7.0.0
COMPONENT_REVISION=	1
COMPONENT_FMRI=		library/python/py-cpuinfo
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SUMMARY=	Get CPU info with pure Python
COMPONENT_PROJECT_URL=	https://github.com/workhorsy/py-cpuinfo
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:9aa2e49675114959697d25cf57fec41c29b55887bff3bc4809b44ac6f5730097
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS= $(PYTHON3_VERSIONS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_INSTALL_ACTION += \
        $(MV) $(PROTOUSRBINDIR)/cpuinfo $(PROTOUSRBINDIR)/cpuinfo-$(PYTHON_VERSION);

COMPONENT_TEST_DIR =	$(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =	test_solaris_11_x86_32.py

COMPONENT_TEST_TRANSFORMS += '-n -e "/\.\.\./p"'

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
