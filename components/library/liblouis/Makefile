#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Alexander Pyhalov
# Copyright 2021 Andreas Wacknitz
#

BUILD_BITS=	64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= liblouis
COMPONENT_VERSION= 3.13.0
COMPONENT_SUMMARY= Support for contracted braille
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:f9be5bd83f1de5d218f7dd2d7f0f9c4af08af3dc8f282a342f2c83cbb1799267
COMPONENT_ARCHIVE_URL=	https://github.com/liblouis/liblouis/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL = http://liblouis.org/
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_FMRI = library/liblouis
COMPONENT_LICENSE = LGPLv3,GPLv3
COMPONENT_LICENSE_FILE = liblouis.license

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

PYTHON_VERSION=	3.7

COMPONENT_BUILD_ARGS =

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i ) 

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION += ( cp -a $(SOURCE_DIR)/* $(@D)) ;

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-ucs4

# While the main library is built with configure, the python module is
# built & installed with separate invocations of setup.py
PYTHON_ENV +=   CC="$(CC)"
PYTHON_ENV +=   CFLAGS="$(CFLAGS)"
PYTHON_ENV +=   PYTHONPATH='$(@D)/python' 

COMPONENT_POST_BUILD_ACTION += \
    (cd $(@D)/python ; \
        $(ENV) $(COMPONENT_BUILD_ENV) $(PYTHON_ENV) \
        LD_LIBRARY_PATH_$(BITS)=$(@D)/liblouis/.libs/ \
            $(PYTHON) ./setup.py build );
COMPONENT_POST_INSTALL_ACTION += \
    (cd $(@D)/python ; \
        $(ENV) $(COMPONENT_INSTALL_ENV) $(PYTHON_ENV) \
        LD_LIBRARY_PATH_$(BITS)=$(PROTO_DIR)$(USRLIB.$(BITS)) \
            $(PYTHON) ./setup.py install --root $(PROTO_DIR) \
        --install-lib $(PYTHON_LIB) );

# Needed for "gmake test" to work successfully.
unexport SHELLOPTS

# Share 32- and 64-bit test results
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Standard automake test framework results transform
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL/p" ' \
        '-e "/SKIP/p" ' \
        '-e "/PASS/p" ' \
        '-e "/FAIL/p" ' \
        '-e "/ERROR/p" '

# additional transforms for brltty
COMPONENT_TEST_TRANSFORMS += \
        '-e "/^==*$$/p" ' \
        '-e "/expected/p" '

# Manually added build dependencies
REQUIRED_PACKAGES += runtime/python-37

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library
