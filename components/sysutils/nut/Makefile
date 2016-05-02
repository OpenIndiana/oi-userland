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

LDFLAGS.32= -L$(USRLIBDIR) -R $(USRLIBDIR) $(LDFLAGS) -L$(GNULIB) -R $(GNULIB)
LDFLAGS.64= -L$(USRLIBDIR64) -R $(USRLIBDIR64) $(LDFLAGS) -L$(GNULIB64) -R $(GNULIB64)

COMPONENT_PREP_ACTION =	( cd $(SOURCE_DIR) && ./autogen.sh )

COMPONENT_PRE_CONFIGURE_ACTION =	( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_ENV.32+=	LDFLAGS="$(LDFLAGS.32)"
CONFIGURE_ENV.64+=	LDFLAGS="$(LDFLAGS.64)"

CONFIGURE_OPTIONS.32+=	LDFLAGS="$(LDFLAGS.32)"
CONFIGURE_OPTIONS.64+=	LDFLAGS="$(LDFLAGS.64)"

CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-shared

CONFIGURE_OPTIONS +=	--sysconfdir=/etc/nut
CONFIGURE_OPTIONS +=	--with-hotplug-dir=/etc/hotplug
CONFIGURE_OPTIONS +=	--with-udev-dir=/usr/lib/udev
CONFIGURE_OPTIONS +=	--with-statepath=/var/state/ups
CONFIGURE_OPTIONS +=	--with-systemdsystemunitdir=no
CONFIGURE_OPTIONS +=	--with-dev
CONFIGURE_OPTIONS +=	--with-libltdl
CONFIGURE_OPTIONS +=	--with-ssl
CONFIGURE_OPTIONS +=	--with-openssl

CONFIGURE_OPTIONS.32 +=	--with-drvpath=$(USRDIR)/nut/bin
CONFIGURE_OPTIONS.32 +=	--with-cgipath=$(USRDIR)/nut/cgi-bin
CONFIGURE_OPTIONS.64 +=	--with-drvpath=$(USRDIR)/nut/bin/$(MACH64)
CONFIGURE_OPTIONS.64 +=	--with-cgipath=$(USRDIR)/nut/cgi-bin/$(MACH64)

# No separate toggle for this yet
#CONFIGURE_OPTIONS +=	--with-nut-scanner

# Minimize guesswork: these are features we can and do build and deliver in
# package manifest, so the build host must have relevant packages installed
CONFIGURE_OPTIONS +=	--with-serial
CONFIGURE_OPTIONS +=	--with-usb
CONFIGURE_OPTIONS +=	--with-neon
CONFIGURE_OPTIONS +=	--with-avahi
CONFIGURE_OPTIONS +=	--with-powerman=yes

# TODO: Revise NUT package when this gate provides (GNU) freeipmi >= 1.0.1
CONFIGURE_OPTIONS +=	--with-ipmi=no
CONFIGURE_OPTIONS +=	--with-freeipmi=no

# Likely we'll not have this backend working any time soon
CONFIGURE_OPTIONS +=	--with-linux_i2c=no
CONFIGURE_OPTIONS +=	--with-macosx_ups=no

# Note: Link with the correct ISA of net-snmp (for drivers) and gdlib (for cgi)
CONFIGURE_OPTIONS +=	--with-snmp
CONFIGURE_OPTIONS +=	--with-net-snmp-config=net-snmp-config-$(BITS)

CONFIGURE_OPTIONS.32 +=	--with-gdlib-config=$(USRBINDIR)/gdlib-config
CONFIGURE_OPTIONS.64 +=	--with-gdlib-config=$(USRBINDIR64)/gdlib-config

# Note: the CGI binary has some linking problems (picks 32-bit GDlib since we
# only deliver one config program) and we don't need both versions anyway.
CONFIGURE_OPTIONS +=	--with-cgi
#CONFIGURE_OPTIONS.32 +=	--with-cgi
#CONFIGURE_OPTIONS.64 +=	--without-cgi

# Note: building the numerous documents of this projects is time-consuming
# and we only need one copy. Also, we don't ship "dblatex" (needed here for
# compiling PDFs) and probably don't require "html-chunked" chapters.
CONFIGURE_OPTIONS.32 +=	--with-doc="man"
CONFIGURE_OPTIONS.64 +=	--with-doc="no"

#CONFIGURE_OPTIONS +=	--with-doc="auto"
### Avoid occasionally possible hangs with chunked HTML doc
CONFIGURE_OPTIONS +=	ASCIIDOC_VERBOSE="-v"
CONFIGURE_ENV     +=	ASCIIDOC_VERBOSE="-v"

CONFIGURE_OPTIONS +=	$(CONFIGURE_OPTIONS.$(BITS))

# Temporary for tests
$(BUILD_32): $(BUILD_64)

build: $(BUILD_32_and_64)

# Ensure configs etc. match 32-bit
$(INSTALL_32): $(INSTALL_64)

install: $(INSTALL_32_and_64)
	cd $(BUILD_DIR_32)/scripts/augeas && make install DESTDIR=$(PROTO_DIR)

test: $(TEST_32_and_64)
