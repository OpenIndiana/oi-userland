# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Aurelien Larcher
# Copyright 2020 Michal Nowak
#

BUILD_STYLE=setup.py
BUILD_BITS=NO_ARCH

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		meson
COMPONENT_VERSION=	0.59.0
COMPONENT_SUMMARY=	The Meson Build system
COMPONENT_PROJECT_URL=	https://mesonbuild.com/
COMPONENT_FMRI=		developer/build/meson
COMPONENT_CLASSIFICATION=Development/Distribution Tools
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/mesonbuild/meson/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:e376c298df64b643dfe01eccb2d7b6f1e02e95aa38c19f19d120d129612ce476
COMPONENT_LICENSE=	APLv2

TEST_TARGET= $(TEST_64)

GCC_VERSION=		10
PYTHON_VERSION=		3.9
PYTHON_VERSIONS=	3.9

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Assumes GNU msgfmt is first in PATH
PYTHON_ENV += PATH="$(GCC_ROOT)/bin:$(PATH.gnu)"

COMPONENT_INSTALL_ARGS = --root $(PROTO_DIR) --force --prefix=/usr --install-lib=$(PYTHON_LIB)

PROTO_PY_MESONBUILD_DIR= $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/mesonbuild
COMPONENT_POST_INSTALL_ACTION= \
	( $(GSED) -i -e 's/env python3/python$(PYTHON_VERSION)/' $(PROTO_PY_MESONBUILD_DIR)/rewriter.py ; )


COMPONENT_TEST_DIR=		$(COMPONENT_SRC)
COMPONENT_TEST_CMD=		./run_tests.py
COMPONENT_TEST_ARGS=
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Test transforms retain only reproducible summaries of results output.
# -E flag enables extended regular expressions, so that | can be used
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/^Total .*time:/d" ' \
        '-e "s/[0-9][0-9\.]* *s//" ' \
        '-e "/^Total/p" ' \
        '-E -e "/(^test| \.\.\. |PASS|FAIL|ERROR)/p" '

# Manually added build dependencies
REQUIRED_PACKAGES += developer/build/ninja

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/importlib-metadata-39
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-39
