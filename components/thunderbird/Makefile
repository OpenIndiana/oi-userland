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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= 	thunderbird
COMPONENT_VERSION= 	24.2.0
IPS_COMPONENT_VERSION=	24.2.0
COMPONENT_SUMMARY= 	Mozilla Thunderbird Email/Newsgroup Client
COMPONENT_SRC= 		comm-esr24
COMPONENT_ARCHIVE= 	$(COMPONENT_NAME)-$(COMPONENT_VERSION).source.tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:66474132bd6ebbb8a913c3f4acd4ecc9bec011e4c7ee49475f29558801a905cf
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.mozilla.org/pub/thunderbird/releases/$(COMPONENT_VERSION)/source/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mozilla.com/en-US/thunderbird/

LANG_LIST=	ar be bg ca cs da de el es-AR es-ES et fi fr he hr hu id is it ja ko lt nl nn-NO pl pt-BR pt-PT ro ru sk sl sq sr sv-SE tr uk vi zh-CN zh-TW
LANG_FILES_LOCATION=	http://ftp.mozilla.org/pub/mozilla.org/thunderbird/releases/$(COMPONENT_VERSION)/linux-i686/xpi/

LIGHTNING_DIR="$(PROTO_DIR)/usr/lib/thunderbird/extensions/{e2fda1a4-762b-4020-b5ad-a41df1933103}"
GDATA_PROVIDER_DIR="$(PROTO_DIR)/usr/lib/thunderbird/extensions/{a62ef8ec-5fdc-40c2-873c-223b8a6925cc}"

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATCH_LEVEL=0

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D) )

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

CONFIGURE_OPTIONS =	--disable-alsa
CONFIGURE_OPTIONS +=	--enable-gnomevfs
CONFIGURE_OPTIONS +=	--enable-dbus
CONFIGURE_OPTIONS +=	--enable-gnomeui
CONFIGURE_OPTIONS +=	--enable-libxul
CONFIGURE_OPTIONS +=	--disable-jemalloc
CONFIGURE_OPTIONS +=	--disable-debug
#CONFIGURE_OPTIONS +=	--enable-debug
CONFIGURE_OPTIONS +=	--disable-debug-symbols
#CONFIGURE_OPTIONS +=	--enable-debug-symbols
CONFIGURE_OPTIONS +=	--enable-install-strip
#CONFIGURE_OPTIONS +=	--disable-install-strip
CONFIGURE_OPTIONS +=	--enable-optimize=-O2
CONFIGURE_OPTIONS +=	--disable-webrtc
CONFIGURE_OPTIONS +=	--enable-official-branding
CONFIGURE_OPTIONS +=	--disable-updater
CONFIGURE_OPTIONS +=	--enable-ipc
CONFIGURE_OPTIONS +=	--enable-system-ffi
CONFIGURE_OPTIONS +=	--enable-system-sqlite
CONFIGURE_OPTIONS +=	--with-system-libevent
CONFIGURE_OPTIONS +=	--with-system-zlib
CONFIGURE_OPTIONS +=	--with-system-bz2
CONFIGURE_OPTIONS +=	--disable-crashreporter
CONFIGURE_OPTIONS +=    --enable-startup-notification
CONFIGURE_OPTIONS +=	--enable-calendar
CONFIGURE_OPTIONS +=	--enable-application=mail
CONFIGURE_OPTIONS +=	--prefix=/usr
CONFIGURE_OPTIONS +=	--libdir=/usr/lib

ENV +=  SHELL=/usr/bin/sh
ENV +=	CC=$(CC)
ENV +=	CXX=$(CXX)
ENV +=	MOZILLA_OFFICIAL=1
ENV +=	MOZ_PKG_FORMAT=BZ2
ENV +=	PKG_SKIP_STRIP=1
ENV +=	MOZILLA_PKG_NAME=thunderbird

CONFIGURE_ENV =	$(ENV)
COMPONENT_BUILD_ENV =	$(ENV)

LANG_FILES=$(addsuffix .xpi,$(LANG_LIST))

CLEAN_PATHS += $(LANG_FILES)

$(LANG_FILES): 
	$(FETCH) --file $@  --url $(LANG_FILES_LOCATION)/$@

download prep:: $(LANG_FILES)

build: $(BUILD_32)

COMPONENT_POST_INSTALL_ACTION  = ( \
     $(MKDIR) $(LIGHTNING_DIR) ; \
     unzip -u -d $(LIGHTNING_DIR) $(BUILD_DIR_32)/mozilla/dist/xpi-stage/lightning.xpi ; \
     $(MKDIR) $(GDATA_PROVIDER_DIR) ; \
     unzip -u -d $(GDATA_PROVIDER_DIR) $(BUILD_DIR_32)/mozilla/dist/xpi-stage/gdata-provider.xpi ; \
     for file in $(PROTO_DIR)/usr/lib/thunderbird/libprldap60.so \
          $(PROTO_DIR)/usr/lib/thunderbird/sdk/bin/xpcshell \
          $(LIGHTNING_DIR)/components/libcalbasecomps.so ; do \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH "/usr/lib:/usr/lib/thunderbird"'  \
        $$file ;\
     done ; \
     for file in $(PROTO_DIR)/usr/lib/thunderbird/sdk/bin/*.py; do \
        $(GSED) -i -e 's:/usr/bin/env python:$(PYTHON):' $$file; \
     done )

install: $(INSTALL_32)
	
