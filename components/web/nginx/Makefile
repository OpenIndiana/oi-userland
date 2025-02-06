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

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= nginx
COMPONENT_VERSION= 1.26.3
COMPONENT_SUMMARY= Nginx Webserver
COMPONENT_PROJECT_URL= https://nginx.org/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:69ee2b237744036e61d24b836668aad3040dda461fe6f570f1787eab570c75aa
COMPONENT_ARCHIVE_URL= https://nginx.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL= $(COMPONENT_ARCHIVE_URL).asc
COMPONENT_FMRI=	web/server/nginx
COMPONENT_CLASSIFICATION= Web Services/Application and Web Servers
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_REVISION= 1

NGX_FANCYINDEX_VERSION= 0.5.2

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CPPFLAGS += -I$(OPENSSL_INCDIR)
LDFLAGS  += -L$(OPENSSL_LIBDIR)

CONFIGURE_OPTIONS = --prefix=$(ETCDIR)/nginx
CONFIGURE_OPTIONS += --add-module=$(@D)/ngx-fancyindex
CONFIGURE_OPTIONS += --conf-path=$(ETCDIR)/nginx/nginx.conf
CONFIGURE_OPTIONS += --error-log-path=$(VARDIR)/nginx/logs/error_log
CONFIGURE_OPTIONS += --group=webservd
CONFIGURE_OPTIONS += --http-log-path=$(VARDIR)/nginx/logs/access_log
CONFIGURE_OPTIONS += --lock-path=$(VARDIR)/run/nginx
CONFIGURE_OPTIONS += --pid-path=$(VARDIR)/run/nginx
CONFIGURE_OPTIONS += --sbin-path=$(USRDIR)/sbin/nginx
CONFIGURE_OPTIONS += --user=webservd
CONFIGURE_OPTIONS += --with-cc-opt="-I$(OPENSSL_INCDIR)"
CONFIGURE_OPTIONS += --with-cc="$(CC) $(CC_BITS)"
CONFIGURE_OPTIONS += --with-http_addition_module
CONFIGURE_OPTIONS += --with-http_dav_module
CONFIGURE_OPTIONS += --with-http_flv_module
CONFIGURE_OPTIONS += --with-http_geoip_module
CONFIGURE_OPTIONS += --with-http_gunzip_module
CONFIGURE_OPTIONS += --with-http_gzip_static_module
CONFIGURE_OPTIONS += --with-http_mp4_module
CONFIGURE_OPTIONS += --with-http_realip_module
CONFIGURE_OPTIONS += --with-http_secure_link_module
CONFIGURE_OPTIONS += --with-http_ssl_module
CONFIGURE_OPTIONS += --with-http_stub_status_module
CONFIGURE_OPTIONS += --with-http_sub_module
CONFIGURE_OPTIONS += --with-http_v2_module
CONFIGURE_OPTIONS += --with-http_xslt_module
CONFIGURE_OPTIONS += --with-ld-opt="$(LD_BITS) -L$(OPENSSL_LIBDIR)"
CONFIGURE_OPTIONS += --with-mail
CONFIGURE_OPTIONS += --with-mail_ssl_module
CONFIGURE_OPTIONS += --with-stream
CONFIGURE_OPTIONS += --with-stream_ssl_module
CONFIGURE_OPTIONS += --with-threads

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D) && \
   git clone https://github.com/aperezdc/ngx-fancyindex.git $(@D)/ngx-fancyindex && \
   cd $(@D)/ngx-fancyindex && \
   git checkout v$(NGX_FANCYINDEX_VERSION))

COMPONENT_POST_INSTALL_ACTION+= \
	( $(MKDIR) $(PROTO_DIR)/var/nginx/logs )

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/geoip
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
