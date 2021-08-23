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
# Copyright 2015 Alexander Pyhalov
# Copyright 2020 Andreas Wacknitz
#

BUILD_BITS= 32_and_64
BUILD_STYLE= meson
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME= atk
COMPONENT_MJR_VERSION=2.36
COMPONENT_MNR_VERSION=0
COMPONENT_VERSION= $(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_SUMMARY= GNOME accesibility toolkit libraries
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:fb76247e369402be23f1f5c65d38a9639c1164d934e40f6a9cf3c9e96b652788
COMPONENT_ARCHIVE_URL= \
	https://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.gnome.org
COMPONENT_FMRI= library/desktop/atk
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/common.mk

# gcc-7 fails to build atk:
GCC_VERSION=	10

# gobject-introspection is 64-Bit-only
CONFIGURE_OPTIONS.32 += -Dintrospection=false

# Workaround for build failures due to atk Makefiles not passing CFLAGS or
# LDFLAGS, especially the -m32/64 flag, to g-ir-scanner
COMPONENT_BUILD_ENV += CFLAGS="$(strip $(CFLAGS))"
COMPONENT_BUILD_ENV += LDFLAGS="$(strip $(LDFLAGS))"
COMPONENT_BUILD_ENV += CC="$(CC)"

COMPONENT_INSTALL_ENV += PATH="$(PATH.gnu)"

# Upstream's "gmake test" target builds tests but does not run them,
# so run them manually for now.
COMPONENT_TEST_TARGETS += ; cd tests; ./testdocument; ./testrole ; \
    ./testrelation ; ./teststateset ; ./testvalue

# get rid of the timestamps from the test results
COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9].[0-9][0-9]s//" '

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Manually added build dependencies
REQUIRED_PACKAGES+= library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES+= developer/gcc-10

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
