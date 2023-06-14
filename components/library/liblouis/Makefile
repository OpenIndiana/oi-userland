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
# Copyright 2022-2023 Niklas Poslovski
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= liblouis
COMPONENT_VERSION= 3.26.0
COMPONENT_SUMMARY= The Liblouis software suite provides an open-source braille translator, back-translator and formatter for a large number of languages and braille codes
COMPONENT_SRC= $(COMPONENT_NAME)-5d876c6e7fcef9f0840f1bc4fd045cd8eb2aacff
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:2a5f1afe4705b4bb3d1c25e83ef0aae3bdb91c0eb4b654536e01a01344c655ec
COMPONENT_ARCHIVE_URL=	https://github.com/liblouis/liblouis/archive/5d876c6e7fcef9f0840f1bc4fd045cd8eb2aacff.tar.gz
# They tagged the version before increasing it in configure.ac - Remove the line above and uncomment the line below with the next update.
#COMPONENT_ARCHIVE_URL=	https://github.com/liblouis/liblouis/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL = https://liblouis.io/
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_FMRI = library/liblouis
COMPONENT_LICENSE = LGPLv3,GPLv3
COMPONENT_LICENSE_FILE = liblouis.license

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

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

# additional transforms for brltty
COMPONENT_TEST_TRANSFORMS += \
        '-e "/^==*$$/p" ' \
        '-e "/expected/p" '

# Manually added build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
