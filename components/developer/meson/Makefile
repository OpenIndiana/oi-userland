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
# Copyright 2022 Andreas Wacknitz
#

BUILD_STYLE= setup.py
SINGLE_PYTHON_VERSION= yes
TEST_STYLE = run_tests.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         meson
COMPONENT_VERSION=      1.2.0
COMPONENT_SUMMARY=      The Meson Build system
COMPONENT_PROJECT_URL=  https://mesonbuild.com/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://github.com/mesonbuild/meson/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:603489f0aaa6305f806c6cc4a4455a965f22290fc74f65871f589b002110c790
COMPONENT_FMRI=         developer/build/meson
COMPONENT_CLASSIFICATION=Development/Distribution Tools
COMPONENT_LICENSE=      APLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

PKG_MACROS += PYVER=$(PYTHON_VERSION)

# Assumes GNU msgfmt is first in PATH
PYTHON_ENV += PATH="$(GCC_ROOT)/bin:$(PATH.gnu)"

COMPONENT_INSTALL_ARGS= --root $(PROTO_DIR) --force --prefix=/usr --install-lib=$(PYTHON_LIB)

PROTO_PY_MESONBUILD_DIR= $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/mesonbuild

COMPONENT_POST_INSTALL_ACTION= \
	( $(GSED) -i -e 's/env python3/python$(PYTHON_VERSION)/' $(PROTO_PY_MESONBUILD_DIR)/rewriter.py ; )

COMPONENT_TEST_CMD= ./run_tests.py
COMPONENT_TEST_ARGS= 
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/ok/p" ' \
	'-e "/PASS/p" ' \
	'-e "/SKIPPED/p" ' \
	'-e "/-----/p" ' \
	'-e "/=====/p" ' \

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += developer/build/ninja
