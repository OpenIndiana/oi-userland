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

### A lot of paths are defined and exported to pkg(5) tools below,
### so we can flexibly set up location of certain NUT components.
NUTUSER  =	nut
PKG_OPTIONS +=	-D NUTUSER="$(NUTUSER)"
NUTGROUP  =	nut
PKG_OPTIONS +=	-D NUTGROUP="$(NUTGROUP)"

# This is where config files are expected, INCLUDING (per convention from other
# distros) example config files - e.g. not lost under /usr/shared/... locations
# Also note we must not include the leading slash...
NUTETCDIR  =	$(strip .../,,...$(ETCDIR)/nut)
PKG_OPTIONS +=	-D NUTETCDIR="$(NUTETCDIR)"

# Extra programs for NUT, not intended for direct user access (drivers, CGIs)
NUTUSRDIR  =	$(strip .../,,...$(USRDIR)/nut)
PKG_OPTIONS +=	-D NUTUSRDIR="$(NUTUSRDIR)"
# Note that binaries reside in base or $(MACH64) subdirectories of these:
NUTDRVDIR  =	$(NUTUSRDIR)/bin
NUTCGIDIR  =	$(NUTUSRDIR)/cgi-bin
PKG_OPTIONS +=	-D NUTDRVDIR="$(NUTDRVDIR)"
PKG_OPTIONS +=	-D NUTCGIDIR="$(NUTCGIDIR)"

_NUTVARDIR  =	$(strip .../,,...$(VARDIR))
NUTSTATEDIR  =	$(_NUTVARDIR)/state/ups
PKG_OPTIONS +=	-D NUTSTATEDIR="$(NUTSTATEDIR)"

# So far I am not certain where we should deliver this one, so parametrize ;)
NUT_AVAHI_SERVICE_FILE =	$(NUTETCDIR)/avahi-nut.service.sample
PKG_OPTIONS +=	-D NUT_AVAHI_SERVICE_FILE="$(NUT_AVAHI_SERVICE_FILE)"

# Leading slashes must also be stripped here
NUTHOTPLUGDIR  =	$(strip .../,,...$(ETCDIR)/hotplug)
PKG_OPTIONS +=	-D NUTHOTPLUGDIR="$(NUTHOTPLUGDIR)"
NUTUDEVDIR  =	$(strip .../,,...$(USRLIBDIR)/udev)
PKG_OPTIONS +=	-D NUTUDEVDIR="$(NUTUDEVDIR)"

### Recipe bits follow...
COMPONENT_PREP_ACTION =	( cd $(SOURCE_DIR) && ./autogen.sh )

COMPONENT_PRE_CONFIGURE_ACTION =	( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_ENV.32+=	LDFLAGS="$(LDFLAGS.32)"
CONFIGURE_ENV.64+=	LDFLAGS="$(LDFLAGS.64)"

CONFIGURE_OPTIONS.32+=	LDFLAGS="$(LDFLAGS.32)"
CONFIGURE_OPTIONS.64+=	LDFLAGS="$(LDFLAGS.64)"

CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-shared

CONFIGURE_OPTIONS +=	--with-user=$(NUTUSER)
CONFIGURE_OPTIONS +=	--with-group=$(NUTGROUP)
CONFIGURE_OPTIONS +=	--sysconfdir=/$(NUTETCDIR)
CONFIGURE_OPTIONS +=	--with-hotplug-dir=/$(NUTHOTPLUGDIR)
CONFIGURE_OPTIONS +=	--with-udev-dir=/$(NUTUDEVDIR)
CONFIGURE_OPTIONS +=	--with-statepath=/$(NUTSTATEDIR)
CONFIGURE_OPTIONS +=	--with-systemdsystemunitdir=no
CONFIGURE_OPTIONS +=	--with-dev
CONFIGURE_OPTIONS +=	--with-libltdl
CONFIGURE_OPTIONS +=	--with-ssl
CONFIGURE_OPTIONS +=	--with-openssl

CONFIGURE_OPTIONS.32 +=	--with-drvpath=/$(NUTDRVDIR)
CONFIGURE_OPTIONS.32 +=	--with-cgipath=/$(NUTCGIDIR)
CONFIGURE_OPTIONS.64 +=	--with-drvpath=/$(NUTDRVDIR)/$(MACH64)
CONFIGURE_OPTIONS.64 +=	--with-cgipath=/$(NUTCGIDIR)/$(MACH64)

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

# TODO: Revise NUT package when this gate provides (GNU) freeipmi >= 1.0.1
# Note: we already have a p5m manifest for these products, just uncomment them
CONFIGURE_OPTIONS +=	--with-ipmi=no
CONFIGURE_OPTIONS +=	--with-freeipmi=no

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
CONFIGURE_OPTIONS.32 +=	--with-doc="man=yes"
CONFIGURE_OPTIONS.64 +=	--with-doc="no"

### Avoid occasionally possible hangs with chunked HTML doc, if we build it
#CONFIGURE_OPTIONS +=	--with-doc="auto"

CONFIGURE_OPTIONS +=	ASCIIDOC_VERBOSE="-v"
CONFIGURE_ENV     +=	ASCIIDOC_VERBOSE="-v"

CONFIGURE_OPTIONS +=	$(CONFIGURE_OPTIONS.$(BITS))


build: $(BUILD_32_and_64)

# Ensure installed configs etc. match 32-bit paths
$(INSTALL_32): $(INSTALL_64)

install: $(INSTALL_32_and_64)
	$(INSTALL) -m 644 $(BUILD_DIR_32)/scripts/avahi/nut.service $(PROTO_DIR)/$(NUT_AVAHI_SERVICE_FILE)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/neon
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-4-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/usb/libusb
REQUIRED_PACKAGES += system/management/powerman
REQUIRED_PACKAGES += system/management/snmp/net-snmp
