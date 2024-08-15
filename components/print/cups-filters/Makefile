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
# Copyright 2022, 2023 Andreas Wacknitz
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	cups-filters
COMPONENT_VERSION=	2.0.1
COMPONENT_SUMMARY=	Additional backends, filters and other software for CUPS
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:39e71de3ce06762b342749f1dc7cba6817738f7bf4d322c1bb9ab10b8569ab80
COMPONENT_PROJECT_URL=	https://openprinting.github.io/
COMPONENT_ARCHIVE_URL=	https://github.com/OpenPrinting/$(COMPONENT_NAME)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	print/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Printing
COMPONENT_LICENSE=	GPLv2,GPLv3,LGPLv2,LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION += ( cd $(@D) ; PATH=$(PATH.gnu) $(CONFIG_SHELL) autogen.sh )

CPPFLAGS = -D_POSIX_PTHREAD_SEMANTICS
CPPFLAGS += -I/usr/include/cups

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
COMPONENT_BUILD_ENV   += PATH="$(PATH.gnu)"
COMPONENT_INSTALL_ENV += PATH="$(PATH.gnu)"

CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS += --libdir=/usr/lib/cups/$(MACH64)
CONFIGURE_OPTIONS += --localedir=$(USRSHARELOCALEDIR)
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-mutool
CONFIGURE_OPTIONS += --enable-poppler
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += --enable-driverless=no
CONFIGURE_OPTIONS += ENABLE_DRIVERLESS_FALSE="Y"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += print/filter/ghostscript
REQUIRED_PACKAGES += print/libcupsfilters
REQUIRED_PACKAGES += print/libppd
REQUIRED_PACKAGES += print/psutils
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
