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
COMPONENT_VERSION=	0.54.2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	The Meson Build system
COMPONENT_PROJECT_URL=	http://mesonbuild.com/
COMPONENT_FMRI=		developer/build/meson
COMPONENT_CLASSIFICATION=Development/Distribution Tools
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
	https://github.com/mesonbuild/meson/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
	sha256:a7716eeae8f8dff002e4147642589ab6496ff839e4376a5aed761f83c1fa0455
COMPONENT_LICENSE=	APLv2

PATCH_LEVEL= 0

TEST_TARGET = $(TEST_64)

PYTHON_VERSION =3.5
PYTHON_VERSIONS=3.5

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_INSTALL_ARGS = --root $(PROTO_DIR) --force --prefix=/usr --install-lib=$(PYTHON_LIB)

PROTO_PY_MESONBUILD_DIR= $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/mesonbuild
COMPONENT_POST_INSTALL_ACTION= \
	( $(GSED) -i -e 's/env python3/python$(PYTHON_VERSION)/' $(PROTO_PY_MESONBUILD_DIR)/rewriter.py ; )

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_ENV +=  CFLAGS="$(CFLAGS) $(XPG6MODE)" CPPFLAGS="$(CPPFLAGS) $(CPP_XPG6MODE)"

COMPONENT_TEST_DIR =    $(COMPONENT_SRC)

COMPONENT_TEST_ENV += \
		LANG=C.UTF-8 \
		PYTHON=$(PYTHON) \
		MESON_EXE=$(PROTO_DIR)/usr/bin/meson \
		MESON_PRINT_TEST_OUTPUT=1

COMPONENT_TEST_ARGS = run_tests.py

REQUIRED_PACKAGES += developer/build/ninja

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-35
