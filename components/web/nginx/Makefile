#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2012-2013, EveryCity Ltd. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nginx
COMPONENT_VERSION=	1.13.0
COMPONENT_LICENSE=	BSD
COMPONENT_PROJECT_URL=	http://nginx.net/
COMPONENT_SUMMARY=	Nginx Webserver
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:79f52ab6550f854e14439369808105b5780079769d7b8db3856be03c683605d7
COMPONENT_ARCHIVE_URL=	http://nginx.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS =  --prefix=/etc/nginx
CONFIGURE_OPTIONS += --sbin-path=$(CONFIGURE_SBINDIR.$(BITS))/nginx
CONFIGURE_OPTIONS += --with-ld-opt=$(LD_BITS)
CONFIGURE_OPTIONS += --with-cc="$(CC) $(CC_BITS)"
CONFIGURE_OPTIONS += --conf-path=/etc/nginx/nginx.conf
CONFIGURE_OPTIONS += --http-log-path=/var/nginx/logs/access_log
CONFIGURE_OPTIONS += --error-log-path=/var/nginx/logs/error_log
CONFIGURE_OPTIONS += --pid-path=/var/run/nginx
CONFIGURE_OPTIONS += --lock-path=/var/run/nginx
CONFIGURE_OPTIONS += --user=webservd
CONFIGURE_OPTIONS += --group=webservd

CONFIGURE_OPTIONS += --with-http_ssl_module
CONFIGURE_OPTIONS += --with-ipv6

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))
COMPONENT_POST_INSTALL_ACTION+= \
	( $(MKDIR) $(PROTO_DIR)/var/nginx/logs )

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
