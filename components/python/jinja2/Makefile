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
# Copyright (c) 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2015, PALO Richard.
# Copyright 2017 Gary Mills
# Copyright 2021 Nona Hansel
# Copyright 2021 Andreas Wacknitz
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Jinja2
COMPONENT_VERSION=	3.0.2
COMPONENT_CLASSIFICATION= Development/Python
COMPONENT_FMRI=		library/python/jinja2
COMPONENT_SUMMARY=	Fast and easy to use stand-alone template engine
COMPONENT_PROJECT_URL=	https://jinja.pocoo.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:827a0e32839ab1600d4eb1c4c33ec5a8edfbc5cb42dafa13b81f182f97784b45
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_LICENSE=	BSD

PYTHON_VERSIONS=	3.7 3.9

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR =	$(SOURCE_DIR)/tests
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =

# Manually added test dependencies
REQUIRED_PACKAGES += library/python/flaky
REQUIRED_PACKAGES += library/python/hypothesis
REQUIRED_PACKAGES += library/python/pluggy
REQUIRED_PACKAGES += library/python/py 
REQUIRED_PACKAGES += library/python/pytest
REQUIRED_PACKAGES += library/python/pytest-benchmark
REQUIRED_PACKAGES += library/python/pytest-reporter

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
