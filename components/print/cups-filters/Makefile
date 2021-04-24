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
# Copyright 2022 Andreas Wacknitz
#

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	cups-filters
COMPONENT_VERSION=	1.28.12
COMPONENT_SUMMARY=	Additional backends, filters and other software for CUPS
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:46e2ea3d884ad222bb863ce6511e59cf390ef8e835295be44a80e500b2a33a3a
COMPONENT_ARCHIVE_URL=	https://www.openprinting.org/download/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://openprinting.github.io/
COMPONENT_FMRI=	print/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Printing
COMPONENT_LICENSE=	GPLv2,GPLv3,LGPLv2,LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION += (cd $(@D) ; \
   PATH=$(PATH.gnu) $(CONFIG_SHELL) autogen.sh )
#COMPONENT_PREP_ACTION +=(cd $(@D); autoreconf -fiv)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION = \
   ($(CLONEY) $(SOURCE_DIR) $(@D))

CPPFLAGS = -D_POSIX_PTHREAD_SEMANTICS
CPPFLAGS += -I/usr/include/cups

# Build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)
LDFLAGS  += -lldap_r -lsocket

CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"
#CPPFLAGS += -I/usr/include/cups/private
#CPPFLAGS += -I/usr/include/cups/private/cups
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
# Ensure dynamic shared objects are linked using same LDFLAGS as executables.
CONFIGURE_ENV += DSOFLAGS="$(LDFLAGS)"

CONFIGURE_OPTIONS +=	--libdir=/usr/lib/cups/$(MACH64)
CONFIGURE_OPTIONS +=	--localedir=$(USRSHARELOCALEDIR)
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--localstatedir=$(VARDIR)
#CONFIGURE_OPTIONS +=	--with-cups-rundir=/system/volatile/cups
CONFIGURE_OPTIONS +=	--with-ldap-includes=/usr/include/openldap
CONFIGURE_OPTIONS +=	--with-fontdir=$(USRSHAREFONTSDIR)
CONFIGURE_OPTIONS +=	--disable-static
# use pdftops (poppler) renderer instead
CONFIGURE_OPTIONS +=	--with-pdftops=pdftops
CONFIGURE_OPTIONS +=	--disable-mutool
# gs has better collor management but crashes
CONFIGURE_OPTIONS +=	--enable-poppler
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	--enable-driverless=no
CONFIGURE_OPTIONS +=	ENABLE_DRIVERLESS_FALSE="Y"
CONFIGURE_OPTIONS +=	--with-php=no
CONFIGURE_OPTIONS +=	--with-test-font-path=/usr/share/fonts/TrueType/dejavu/DejaVuSans.ttf
# Makefile.am files of this component are not compatible with Solaris make.
# Use GNU make to avoid the configuration error when makefile fragments are processed.
CONFIGURE_OPTIONS +=  MAKE=$(GMAKE)

COMPONENT_BUILD_ENV  += PATH="$(PATH.gnu)"
COMPONENT_INSTALL_ENV+= PATH="$(PATH.gnu)"

COMPONENT_TEST_ENV +=   libtool_install_magic='%%%MAGIC variable%%%'
COMPONENT_TEST_ENV +=   libtool_execute_magic='%%%MAGIC variable%%%'
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/ TOTAL:/p" ' \
	'-e "/PASS:/p" ' \
	'-e "/ SKIP:/p" ' \
	'-e "/ XFAIL:/p" ' \
	'-e "/ FAIL:/p" ' \
	'-e "/ ERROR:/p" '

$(SOURCE_DIR)/cups-filters.license:
	cat	$(@D)/COPYING \
		$(COMPONENT_DIR)/GPL-2.txt \
		$(COMPONENT_DIR)/GPL-3.txt \
		$(COMPONENT_DIR)/LGPL-2.0.txt \
		$(COMPONENT_DIR)/LGPL-2.1.txt > $@

#$(INSTALL_64):	$(SOURCE_DIR)/cups-filters.license

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += print/filter/ghostscript
REQUIRED_PACKAGES += print/psutils
REQUIRED_PACKAGES += print/qpdf
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/network/avahi
