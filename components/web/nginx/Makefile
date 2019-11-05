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

BUILD_BITS = 64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nginx
COMPONENT_VERSION=	1.16.1
COMPONENT_LICENSE=	BSD
COMPONENT_PROJECT_URL=	http://nginx.net/
COMPONENT_SUMMARY=	Nginx Webserver
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:f11c2a6dd1d3515736f0324857957db2de98be862461b5a542a3ac6188dbe32b
COMPONENT_ARCHIVE_URL=	http://nginx.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_FMRI=	web/server/nginx
COMPONENT_CLASSIFICATION=	Web Services/Application and Web Servers

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS =  --prefix=/etc/nginx
CONFIGURE_OPTIONS += --sbin-path=/usr/sbin/nginx
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
CONFIGURE_OPTIONS += --with-http_addition_module
CONFIGURE_OPTIONS += --with-http_sub_module
CONFIGURE_OPTIONS += --with-http_dav_module
CONFIGURE_OPTIONS += --with-http_flv_module
CONFIGURE_OPTIONS += --with-http_mp4_module
CONFIGURE_OPTIONS += --with-http_gzip_static_module
CONFIGURE_OPTIONS += --with-http_gunzip_module
CONFIGURE_OPTIONS += --with-http_geoip_module
CONFIGURE_OPTIONS += --with-http_realip_module
CONFIGURE_OPTIONS += --with-http_secure_link_module
CONFIGURE_OPTIONS += --with-http_v2_module
CONFIGURE_OPTIONS += --with-http_stub_status_module
CONFIGURE_OPTIONS += --with-http_xslt_module
CONFIGURE_OPTIONS += --with-stream
CONFIGURE_OPTIONS += --with-stream_ssl_module
CONFIGURE_OPTIONS += --with-mail
CONFIGURE_OPTIONS += --with-mail_ssl_module
CONFIGURE_OPTIONS += --with-ipv6
CONFIGURE_OPTIONS += --with-threads

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))
COMPONENT_POST_INSTALL_ACTION+= \
	( $(MKDIR) $(PROTO_DIR)/var/nginx/logs )

REQUIRED_PACKAGES += database/geoip
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
