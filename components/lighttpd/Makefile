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
# Copyright (c) 2011, 2014, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		lighttpd
COMPONENT_VERSION=	1.4.35
COMPONENT_PROJECT_URL=	http://www.lighttpd.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:62c23de053fd82e1bf64f204cb6c6e44ba3c16c01ff1e09da680d982802ef1cc
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/lighttpd

TPNO=			17006

LIGHTTPD_INSTALLDIR=/usr/lighttpd/1.4

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL=0

# We need to run autogen because we patch configure.ac file
COMPONENT_PREP_ACTION = ( cd $(@D) ; $(CONFIG_SHELL) autogen.sh )

# lighttpd is logging using __FILE__ macro. Cloning will make this happen
# using just source file names (without full absolute paths).
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_PREFIX= /usr/lighttpd/1.4
CONFIGURE_MANDIR= $(CONFIGURE_PREFIX)/man

# Force lighttpd binaries and private modules to standard path
CONFIGURE_SBINDIR.64 = $(CONFIGURE_PREFIX)/sbin
CONFIGURE_LIBDIR.64 = $(CONFIGURE_PREFIX)/lib

CONFIGURE_OPTIONS +=	--with-pic
CONFIGURE_OPTIONS +=	--with-lua
CONFIGURE_OPTIONS +=	--with-openssl
CONFIGURE_OPTIONS +=	--with-pcre
CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--with-mysql=/usr/mysql/5.5/bin/mysql_config
CONFIGURE_OPTIONS +=    CFLAGS="$(CFLAGS) -I/usr/include/openldap -lldap_r-2.4"
CONFIGURE_OPTIONS +=    PCRECONFIG="/usr/bin/$(MACH64)/pcre-config"

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
