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
# Copyright 2023 Andreas Wacknitz
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	libppd
COMPONENT_VERSION= 2.1.1
COMPONENT_SUMMARY= libppd is the legacy support library for PPD files
COMPONENT_DESCRIPTION= LIBPPD is only for legacy PPD file support! It should not be a motivation to create new PPD files or new PPD extensions!
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:3fa341cc03964046d2bf6b161d80c1b4b2e20609f38d860bcaa11cb70c1285e4
COMPONENT_PROJECT_URL= https://openprinting.github.io/
COMPONENT_ARCHIVE_URL= https://github.com/OpenPrinting/$(COMPONENT_NAME)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	print/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Printing
COMPONENT_LICENSE= Apache-2.0-with-GPL2-LGPL2-Exception
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION += ( cd $(@D); PATH=$(PATH) $(CONFIG_SHELL) autogen.sh )

CPPFLAGS = -D_POSIX_PTHREAD_SEMANTICS
CPPFLAGS += -I/usr/include/cups

CFLAGS += $(XPG6MODE)

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
COMPONENT_BUILD_ENV   += PATH="$(PATH.gnu)"
COMPONENT_INSTALL_ENV += PATH="$(PATH.gnu)"

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --localedir=$(USRSHARELOCALEDIR)
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
# We don't have mutool (https://mupdf.readthedocs.io/en/latest/mupdf-command-line.html).
CONFIGURE_OPTIONS += --disable-mutool
# We don't have acroread.
CONFIGURE_OPTIONS += --disable-acroread

COMPONENT_BUILD_ENV   += PATH="$(PATH.gnu)"
COMPONENT_INSTALL_ENV += PATH="$(PATH.gnu)"
COMPONENT_TEST_ENV    += libtool_install_magic='%%%MAGIC variable%%%'
COMPONENT_TEST_ENV    += libtool_execute_magic='%%%MAGIC variable%%%'

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += print/libcupsfilters
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
