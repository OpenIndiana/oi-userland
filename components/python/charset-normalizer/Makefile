#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright 2022 Andreas Wacknitz
#

BUILD_BITS= NO_ARCH
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		charset-normalizer
COMPONENT_VERSION=	2.0.10
COMPONENT_SUMMARY=	The Real First Universal Charset Detector
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:876d180e9d7432c5d1dfd4c5d26b72f099d503e8fcc0feb7532c9289be60fcbd
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/ousret/charset_normalizer
COMPONENT_CLASSIFICATION= Development/Python
COMPONENT_FMRI=	library/python/$(COMPONENT_NAME)
COMPONENT_LICENSE= MIT

PYTHON_VERSIONS= $(PYTHON3_VERSIONS)
# iFor tests use the following as they don't work for python-3.5:
#PYTHON_VERSIONS= 3.7 3.9

include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_POST_INSTALL_ACTION = ( \
	cd $(PROTO_DIR)/usr/bin ; \
	$(MV) -f normalizer normalizer-$(PYTHON_VERSION) )

# Without copying the data folder into the tests folder many tests fail:
COMPONENT_PRE_TEST_ACTION = $(CP) -r $(COMPONENT_SRC)/data $(COMPONENT_SRC)/tests/data

COMPONENT_TEST_DIR =    $(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD =    $(PYTHON) /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
