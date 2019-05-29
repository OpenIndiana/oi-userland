#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lighttpd
COMPONENT_VERSION=	1.4.54
COMPONENT_PROJECT_URL=	http://www.lighttpd.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:5151d38cb7c4c40effa13710e77ebdbef899f945b062cf32befc02d128ac424c
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/lighttpd

LIGHTTPD_INSTALLDIR=/usr/lighttpd/1.4

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL=0

CFLAGS += -I/usr/include/openldap
LDFLAGS += -lldap_r-2.4
LDFLAGS += -lnsl -lsocket

# libtool linking will fail unless we re-create configure.
COMPONENT_PREP_ACTION = ( cd $(@D) ; $(CONFIG_SHELL) autogen.sh )

# lighttpd is logging using __FILE__ macro. Cloning will make this happen
# using just source file names (without full absolute paths).
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_PREFIX= /usr/lighttpd/1.4
CONFIGURE_MANDIR= $(CONFIGURE_PREFIX)/man
CONFIGURE_SBINDIR.64 = $(CONFIGURE_PREFIX)/sbin
CONFIGURE_BINDIR.64 = $(CONFIGURE_PREFIX)/bin

CONFIGURE_OPTIONS +=	--with-pic
CONFIGURE_OPTIONS +=	--without-lua
CONFIGURE_OPTIONS +=	--with-openssl
CONFIGURE_OPTIONS +=	--with-pcre
CONFIGURE_OPTIONS +=	--with-mysql=$(MYSQL_CONFIG)
CONFIGURE_OPTIONS +=	--with-ldap

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += database/mariadb-101/library
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/fastcgi/spawn-fcgi
