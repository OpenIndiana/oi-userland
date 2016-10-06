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
# Copyright 2016 EveryCity Ltd. All rights reserved.
# Copyright 2016 Adam Stevko. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		haproxy
COMPONENT_FMRI=		web/loadbalancer/haproxy
COMPONENT_VERSION_MJR=	1.6
COMPONENT_VERSION_MNR=  9
COMPONENT_VERSION=	$(COMPONENT_VERSION_MJR).$(COMPONENT_VERSION_MNR)
COMPONENT_PROJECT_URL=	http://www.haproxy.org/
COMPONENT_SUMMARY=	A reliable, high performance TCP/HTTP load balancer
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:cf7d2fa891d2ae4aa6489fc43a9cadf68c42f9cb0de4801afad45d32e7dda133
COMPONENT_ARCHIVE_URL=	http://haproxy.1wt.eu/download/$(COMPONENT_VERSION_MJR)/src/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	HAPROXY
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_BUILD_ACTION+= \
	$(CLONEY) $(SOURCE_DIR) $(@D)

CFLAGS+= -I/usr/include/lua5.3

COMPONENT_BUILD_ARGS+=	CC=$(CC)
COMPONENT_BUILD_ARGS+=	CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS+=	LDFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_ARGS+=	PREFIX=$(USRDIR)
COMPONENT_BUILD_ARGS+=	SBINDIR=$(USRSBINDIR)
COMPONENT_BUILD_ARGS+=	DOCDIR=$(USRDIR)/share/doc/haproxy
COMPONENT_BUILD_ARGS+=	TARGET=solaris
COMPONENT_BUILD_ARGS+=	USE_OPENSSL=1
COMPONENT_BUILD_ARGS+=	USE_ZLIB=1
COMPONENT_BUILD_ARGS+=	USE_PCRE=1
COMPONENT_BUILD_ARGS+=	USE_REGPARM=1
COMPONENT_BUILD_ARGS+=	USE_PCRE_JIT=1
COMPONENT_BUILD_ARGS+=	PCRE_INC=$(USRINCDIR)/pcre
COMPONENT_BUILD_ARGS+=	USE_LUA=1
COMPONENT_BUILD_ARGS+=	LUA_LIB_NAME=lua5.3
COMPONENT_BUILD_ARGS+=	ARCH=32
COMPONENT_BUILD_ARGS+= 	CPU=i686

COMPONENT_INSTALL_ARGS+=	$(COMPONENT_BUILD_ARGS)

COMPONENT_POST_INSTALL_ACTION+= \
	( cd $(@D)/contrib/halog && \
	$(GMAKE) $(COMPONENT_BUILD_ARGS) && \
	$(CP) halog $(PROTOUSRSBINDIR) )

build:		$(BUILD_32)

install:	$(INSTALL_32)

REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua-53
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
