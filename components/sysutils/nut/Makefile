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
# Copyright 2016-2023 Jim Klimov
#

# NUT 2.8.0+ is diligently tested to benefit from parallel builds and succeed
USE_PARALLEL_BUILD=	yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	nut
COMPONENT_VERSION=	2.8.1
COMPONENT_REVISION=	3
COMPONENT_SUMMARY=	Network UPS Tools (NUT)
COMPONENT_DESCRIPTION=	Network UPS Tools (NUT) is a versatile power-device monitoring toolkit to facilitate safe shutdowns
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:7da48ee23b1f0d8d72560bb0af84f5c5ae4dbe35452b84cb49840132e47f099c
COMPONENT_ARCHIVE_URL=	\
  https://github.com/networkupstools/$(COMPONENT_NAME)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://networkupstools.org
COMPONENT_FMRI=	system/management/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_LICENSE=	GPLv2+
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CXXFLAGS += $(CXXFLAGS.$(BITS))
CFLAGS   += $(CFLAGS.$(BITS))

# Drop *.8 man pages (we patch to regenerate them into *.1m - see patches/07-man.patch)
# Fix up upsmon.txt encoding that might have gone wrong into the 2.8.1 release tarball
COMPONENT_PREP_ACTION =	( cd $(SOURCE_DIR) && PATH="$(PATH)" ./autogen.sh && cd docs/man && rm -f *.8 && { dos2unix upsmon.txt > upsmon.txt.tmp && mv -f upsmon.txt.tmp upsmon.txt; }  )

COMPONENT_PRE_CONFIGURE_ACTION =	( $(CLONEY) $(SOURCE_DIR) $(@D) )

# We deliver only 64-bit binaries
CONFIGURE_BINDIR.64 =	$(USRBINDIR)
CONFIGURE_SBINDIR.64 =	$(USRSBINDIR)

CONFIGURE_ENV     +=	LDFLAGS="$(LDFLAGS.64)"

CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS.64)"

CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-shared

CONFIGURE_OPTIONS +=	--with-solaris-smf=yes
CONFIGURE_OPTIONS +=	--with-solaris-init=no
CONFIGURE_OPTIONS +=	--with-solaris-pkg-svr4=no
CONFIGURE_OPTIONS +=	--with-solaris-pkg-ips=no

CONFIGURE_OPTIONS +=	--with-systemdsystemunitdir=no
CONFIGURE_OPTIONS +=	--with-systemdshutdowndir=no
CONFIGURE_OPTIONS +=	--with-systemdtmpfilesdir=no

CONFIGURE_OPTIONS +=	--with-user=nut
CONFIGURE_OPTIONS +=	--with-group=nut
CONFIGURE_OPTIONS +=	--sysconfdir=/etc/nut
CONFIGURE_OPTIONS +=	--sharedstatedir=/usr/share/nut
CONFIGURE_OPTIONS +=	--datarootdir=/usr/share/nut
CONFIGURE_OPTIONS +=	--with-hotplug-dir=no
CONFIGURE_OPTIONS +=	--with-udev-dir=no

#  --with-statepath=PATH   path for ups state files (${STATEPATH}, typically
#                          /var/state/ups)
#  --with-altpidpath=PATH  path for NUT driver/upsd .pid files not running as
#                          root (<statepath>)
#  --with-pidpath=PATH     Path for root-owned .pid files (${PIDPATH},
#                          typically /var/run)
#  --with-powerdownflag=PATH
#                          default path for upsmon POWERDOWNFLAG file
#                          (${POWERDOWNFLAG}, typically /etc/killpower)
CONFIGURE_OPTIONS +=	--with-pidpath=/var/run/nut
CONFIGURE_OPTIONS +=	--with-altpidpath=/var/run/nut
CONFIGURE_OPTIONS +=	--with-powerdownflag=/var/run/nut/killpower
CONFIGURE_OPTIONS +=	--with-statepath=/var/db/nut

CONFIGURE_OPTIONS +=	--with-dev
CONFIGURE_OPTIONS +=	--with-libltdl
CONFIGURE_OPTIONS +=	--with-ssl
CONFIGURE_OPTIONS +=	--with-openssl
CONFIGURE_OPTIONS +=	--with-gd-includes=-I/usr/include/gd2

CONFIGURE_OPTIONS +=	--libexecdir=/usr/lib/nut/bin
CONFIGURE_OPTIONS +=	--with-drvpath=/usr/lib/nut/bin
CONFIGURE_OPTIONS +=	--with-cgipath=/usr/lib/nut/cgi-bin
CONFIGURE_OPTIONS +=	--with-gd-libs=-L/usr/lib/$(MACH64)

CONFIGURE_OPTIONS +=	--with-nut-scanner=yes

# Minimize guesswork: these are features we can and do build and deliver in
# package manifest, so the build host must have relevant packages installed
CONFIGURE_OPTIONS +=	--with-serial=yes
#CONFIGURE_OPTIONS +=	--with-usb=yes
CONFIGURE_OPTIONS +=	--with-usb=libusb-1.0
CONFIGURE_OPTIONS +=	--with-modbus=yes
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

# Note: building the numerous documents of this projects is time-consuming
# and we only need one copy. Also, we don't ship "dblatex" (needed here for
# compiling PDFs) and probably don't require "html-chunked" chapters.
CONFIGURE_OPTIONS +=	--with-doc="man=yes"

# NUT-Monitor GUI client
CONFIGURE_OPTIONS +=	--with-nut-monitor=yes
CONFIGURE_OPTIONS +=	--with-pynut=no		# we use PyNUTClient from PyPI
CONFIGURE_OPTIONS +=	--with-python2=no
CONFIGURE_OPTIONS +=	--with-python=python$(PYTHON_VERSION)

# Be sure package is squeaky clean
CONFIGURE_OPTIONS +=	--enable-Werror --enable-warnings --enable-Wcolor
CONFIGURE_OPTIONS +=	--enable-keep_nut_report_feature
CONFIGURE_OPTIONS +=	--enable-silent-rules

# What do we run in case of `make check`?
CONFIGURE_OPTIONS +=	--enable-spellcheck
# NUT Integration Test suite, can take time and might fail due
# to environment (busy ports, congested hsots and timeouts):
#CONFIGURE_OPTIONS +=	--enable-check-NIT
# No CPPCHECK here yet:
CONFIGURE_OPTIONS +=	--disable-cppcheck

CONFIGURE_OPTIONS +=	$(CONFIGURE_OPTIONS.$(BITS))

# Fiddle with packaging:
# * move man1m pages to target directory (see also patches/07-man.patch)
COMPONENT_POST_INSTALL_ACTION += \
    $(MKDIR) $(PROTOUSRSHAREMANDIR)/man1m \
        && $(MV) $(PROTOUSRSHAREMANDIR)/man1/*.1m $(PROTOUSRSHAREMANDIR)/man1m/ \
        || { echo "FAILED to fix up man1m" >&2 ; exit 1; } ; \

# Manually added dependencies:
REQUIRED_PACKAGES += text/asciidoc
REQUIRED_PACKAGES += library/augeas-tools

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pynutclient
PYTHON_REQUIRED_PACKAGES += library/python/pyqt5
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/libmodbus
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += library/neon
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/freeipmi
REQUIRED_PACKAGES += system/management/powerman
REQUIRED_PACKAGES += system/management/snmp/net-snmp
