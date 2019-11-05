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
# Copyright 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	nut
COMPONENT_VERSION=	2.7.4
COMPONENT_REVISION=	3
COMPONENT_SUMMARY=	Network UPS Tools (NUT)
COMPONENT_DESCRIPTION=	Network UPS Tools (NUT) is a versatile power-device monitoring toolkit to facilitate safe shutdowns
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:d580915fdf7090655c1c7c98eb116b61952553f06f0039b1f93c9f5a13e2d36b
COMPONENT_ARCHIVE_URL=	\
  https://github.com/networkupstools/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=	http://networkupstools.org
COMPONENT_FMRI=	system/management/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_LICENSE=	GPLv2+
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CXXFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE
CFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE

CXXFLAGS+=$(CXXFLAGS.$(BITS))
CFLAGS+=$(CFLAGS.$(BITS))

# Document generation can fail with -jN
COMPONENT_BUILD_ARGS=

COMPONENT_PREP_ACTION =	( cd $(SOURCE_DIR) && ./autogen.sh )

COMPONENT_PRE_CONFIGURE_ACTION =	( $(CLONEY) $(SOURCE_DIR) $(@D) )

# We deliver only 64-bit binaries
CONFIGURE_BINDIR.32 = $(USRBINDIR32)
CONFIGURE_SBINDIR.32 = $(USRSBINDIR32)
CONFIGURE_BINDIR.64 = $(USRBINDIR)
CONFIGURE_SBINDIR.64 = $(USRSBINDIR)

CONFIGURE_ENV.32+=	LDFLAGS="$(LDFLAGS.32)"
CONFIGURE_ENV.64+=	LDFLAGS="$(LDFLAGS.64)"

CONFIGURE_OPTIONS.32+=	LDFLAGS="$(LDFLAGS.32)"
CONFIGURE_OPTIONS.64+=	LDFLAGS="$(LDFLAGS.64)"

CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-shared

CONFIGURE_OPTIONS +=	--with-user=nut
CONFIGURE_OPTIONS +=	--with-group=nut
CONFIGURE_OPTIONS +=	--sysconfdir=/etc/nut
CONFIGURE_OPTIONS +=	--sharedstatedir=/usr/share/nut
CONFIGURE_OPTIONS +=	--datarootdir=/usr/share/nut
CONFIGURE_OPTIONS +=	--with-hotplug-dir=no
CONFIGURE_OPTIONS +=	--with-udev-dir=no
CONFIGURE_OPTIONS +=	--with-altpidpath=/var/run/nut
CONFIGURE_OPTIONS +=	--with-statepath=/var/db/nut
CONFIGURE_OPTIONS +=	--with-systemdsystemunitdir=no
CONFIGURE_OPTIONS +=	--with-dev
CONFIGURE_OPTIONS +=	--with-libltdl
CONFIGURE_OPTIONS +=	--with-ssl
CONFIGURE_OPTIONS +=	--with-openssl

CONFIGURE_OPTIONS.32 +=	--with-drvpath=/usr/lib/nut/bin/$(MACH32)
CONFIGURE_OPTIONS.32 +=	--with-cgipath=/usr/lib/nut/cgi-bin/$(MACH32)
CONFIGURE_OPTIONS.64 +=	--with-drvpath=/usr/lib/nut/bin
CONFIGURE_OPTIONS.64 +=	--with-cgipath=/usr/lib/nut/cgi-bin

# No separate toggle for this yet
#CONFIGURE_OPTIONS +=	--with-nut-scanner=yes

# Minimize guesswork: these are features we can and do build and deliver in
# package manifest, so the build host must have relevant packages installed
CONFIGURE_OPTIONS +=	--with-serial=yes
CONFIGURE_OPTIONS +=	--with-usb=yes
CONFIGURE_OPTIONS +=	--with-neon=yes
CONFIGURE_OPTIONS +=	--with-avahi=yes
CONFIGURE_OPTIONS +=	--with-powerman=yes
CONFIGURE_OPTIONS +=	--with-cgi=yes
CONFIGURE_OPTIONS +=	--with-ipmi=yes
CONFIGURE_OPTIONS +=	--with-freeipmi=yes

# Likely we'll not have this backend working any time soon
CONFIGURE_OPTIONS +=	--with-linux_i2c=no
CONFIGURE_OPTIONS +=	--with-macosx_ups=no

# Note: Link with the correct ISA of net-snmp (for drivers) and gdlib (for cgi)
CONFIGURE_OPTIONS +=	--with-snmp
CONFIGURE_OPTIONS +=	--with-net-snmp-config=$(USRBINDIR)/net-snmp-config-$(BITS)

CONFIGURE_OPTIONS.32 +=	--with-gdlib-config=$(USRBINDIR)/gdlib-config
CONFIGURE_OPTIONS.64 +=	--with-gdlib-config=$(USRBINDIR64)/gdlib-config

# Note: building the numerous documents of this projects is time-consuming
# and we only need one copy. Also, we don't ship "dblatex" (needed here for
# compiling PDFs) and probably don't require "html-chunked" chapters.
CONFIGURE_OPTIONS.32 +=        --with-doc="no"
CONFIGURE_OPTIONS.64 +=        --with-doc="man=yes"

CONFIGURE_OPTIONS +=	$(CONFIGURE_OPTIONS.$(BITS))

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/neon
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/usb/libusb
REQUIRED_PACKAGES += system/management/freeipmi
REQUIRED_PACKAGES += system/management/powerman
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += text/asciidoc
