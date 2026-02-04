#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2026 Geoff Weiss
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         heimdal
COMPONENT_VERSION=      7.8.0
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=      Kerberos 5 implementation
COMPONENT_PROJECT_URL=  https://heimdal.software/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:fd87a207846fa650fd377219adc4b8a8193e55904d8a752c2c3715b4155d8d38
COMPONENT_ARCHIVE_URL=  https://github.com/heimdal/heimdal/releases/download/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         system/library/heimdal
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      BSD-2-Clause AND BSD-3-Clause AND HPND-export-US AND HPND-export2-US
COMPONENT_LICENSE_FILE= heimdal.license

DROP_STATIC_LIBRARIES = yes
include $(WS_MAKE_RULES)/common.mk

# heimdal-7.8.0/lib/roken/getifaddrs.c:1003:5: error: implicit declaration of function 'rk_freeifaddrs'; did you mean 'freeifaddrs'? [-Wimplicit-function-declaration]
CFLAGS += -Wno-error=implicit-function-declaration

CONFIGURE_OPTIONS += --bindir=/usr/heimdal/bin
CONFIGURE_OPTIONS += --includedir=/usr/heimdal/include
CONFIGURE_OPTIONS += --infodir=/usr/heimdal/share/info
CONFIGURE_OPTIONS += --libdir=/usr/heimdal/lib/$(MACH64)
CONFIGURE_OPTIONS += --libexecdir=/usr/heimdal/libexec
CONFIGURE_OPTIONS += --mandir=/usr/heimdal/share/man
CONFIGURE_OPTIONS += --sbindir=/usr/heimdal/sbin
CONFIGURE_OPTIONS += --sysconfdir=/etc/hemidal
CONFIGURE_OPTIONS += --disable-afs-support
CONFIGURE_OPTIONS += --disable-silent-rules
CONFIGURE_OPTIONS += --disable-otp
CONFIGURE_OPTIONS += --with-openssl
CONFIGURE_OPTIONS += --with-readline=/usr
CONFIGURE_OPTIONS += --with-sqlite3=/usr
CONFIGURE_OPTIONS += --without-krb4

COMPONENT_INSTALL_ENV += INSTALL_CATPAGES=no

# Fix gmake publish error "Error: packaged texinfo directory file (%<action.path>)"

COMPONENT_POST_INSTALL_ACTION += ( \
	$(RM) $(PROTO_DIR)/usr/heimdal/share/info/dir ; \
	)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += database/lmdb
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += sysutils/e2fsprogs
