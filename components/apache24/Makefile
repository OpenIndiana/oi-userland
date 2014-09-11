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
# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		apache2
COMPONENT_VERSION=	2.4.10
COMPONENT_PROJECT_URL=	http://httpd.apache.org/
COMPONENT_SRC_NAME=	httpd
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ab62f3283de03126fbd509866d8e4fdc9317235b6fca2734ae18827271f9c1fe
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/httpd/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/apache

TPNO=	18388
	
CONFIGURE_DEFAULT_DIRS=no

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

ASLR_MODE = $(ASLR_ENABLE)

PATCH_LEVEL=0

# Some patches need configure script re-creation.
COMPONENT_PREP_ACTION +=($(CP) mod_auth_gss/mod_auth_gss.c $(@D)/modules/aaa);
COMPONENT_PREP_ACTION +=($(CP) mod_auth_gss/mod_auth_gss.html $(@D)/docs/manual/mod);
COMPONENT_PREP_ACTION +=(cd $(@D); autoreconf);

CONFIGURE_PREFIX =	/usr/apache2/2.4

CONFIGURE_OPTIONS +=	--enable-layout=Solaris
CONFIGURE_OPTIONS +=	--enable-mpms-shared=all
CONFIGURE_OPTIONS +=	--enable-mods-shared=all
CONFIGURE_OPTIONS +=	--enable-exception-hook
CONFIGURE_OPTIONS +=	--enable-cgi
CONFIGURE_OPTIONS +=	--enable-suexec
CONFIGURE_OPTIONS +=	--with-suexec-caller=webservd
CONFIGURE_OPTIONS +=	--with-apr=/usr/apr/1.5/bin/$(MACH64)/apr-1-config
CONFIGURE_OPTIONS +=	--with-apr-util=/usr/apr-util/1.5/bin/$(MACH64)/apu-1-config
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	LTFLAGS="--silent --tag=CC"

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
PATH=$(PARFAIT_TOOLS):$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin
endif

COMPONENT_POST_INSTALL_ACTION += ($(KSH93) Solaris/customization.sh $(PROTO_DIR))

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
