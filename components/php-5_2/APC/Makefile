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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		APC
COMPONENT_VERSION=	3.0.19
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a02677a7884361d64fbf3745c402f2a6ff313e817b0d0a2010acb64cd05247b0
COMPONENT_ARCHIVE_URL=	http://pecl.php.net/get/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://pecl.php.net/package/APC/

include ../extensions.mk

CONFIGURE_OPTIONS += \
	--enable-apc \
	--enable-apc-mmap

COMPONENT_POST_INSTALL_ACTION = ( \
	$(MKDIR) $(PROTO_DIR)/$(APACHE2_SAMPLES_CONFDIR); \
	$(INSTALL) -m 0644 $(COMPONENT_DIR)/../Solaris/php-apc-stats.conf \
		$(PROTO_DIR)/$(APACHE2_SAMPLES_CONFDIR); \
	$(MKDIR) $(PROTO_DIR)/usr/php/5.2/samples/apc; \
	$(INSTALL) -m 0555 $(SOURCE_DIR)/apc.php \
		$(PROTO_DIR)/usr/php/5.2/samples/apc/apc.php; \
	) ; \
	$(FIX_CONFIG_FILES)

PKG_PROTO_DIRS += $(COMPONENT_DIR)/../APC-zts/build/prototype/$(MACH)

# Manual dependency - need APC-zts installed before APC publish
##../APC-zts/build/$(MACH32)/.installed:
##	(cd ../APC-zts ; $(MAKE) install)

##$(INSTALL_32):	../APC-zts/build/$(MACH32)/.installed
