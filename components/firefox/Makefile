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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= 	firefox
COMPONENT_VERSION= 	17.0.11esr
IPS_COMPONENT_VERSION=	17.0.11
COMPONENT_SUMMARY= 	Mozilla Firefox Web browser
COMPONENT_SRC= 		mozilla-esr17
COMPONENT_ARCHIVE= 	$(COMPONENT_NAME)-$(COMPONENT_VERSION).source.tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:1e722b25d33fa4d68d398a8f29e71e8196d2168820bef5cd3f26116ffc6aaff4
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.mozilla.org/pub/firefox/releases/$(COMPONENT_VERSION)/source/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mozilla.com/en-US/firefox/

LANG_LIST=	ar be bg ca cs da de el es-AR es-CL es-ES et fi fr he hi-IN hr hu id is it ja kk ko lt lv mk nb-NO nl nn-NO pl pt-BR pt-PT ro ru sk sl sq sr sv-SE th tr uk vi zh-CN zh-TW
LANG_FILES_LOCATION=	http://ftp.mozilla.org/pub/mozilla.org/firefox/releases/$(COMPONENT_VERSION)/linux-i686/xpi/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D) )

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

CONFIGURE_OPTIONS =	--disable-alsa
CONFIGURE_OPTIONS +=	--enable-gnomevfs
CONFIGURE_OPTIONS +=	--enable-dbus
CONFIGURE_OPTIONS +=	--enable-gnomeui
CONFIGURE_OPTIONS +=	--enable-libnotify
CONFIGURE_OPTIONS +=	--enable-libxul
CONFIGURE_OPTIONS +=	--enable-extensions=gnomevfs
CONFIGURE_OPTIONS +=	--disable-jemalloc
CONFIGURE_OPTIONS +=	--disable-debug
CONFIGURE_OPTIONS +=    --disable-tests
#CONFIGURE_OPTIONS +=	--enable-debug
CONFIGURE_OPTIONS +=	--disable-debug-symbols
#CONFIGURE_OPTIONS +=	--enable-debug-symbols
CONFIGURE_OPTIONS +=	--enable-install-strip
#CONFIGURE_OPTIONS +=	--enable-optimize=-O2
CONFIGURE_OPTIONS +=	--disable-webrtc
CONFIGURE_OPTIONS +=	--enable-dtrace
CONFIGURE_OPTIONS +=	--enable-official-branding
CONFIGURE_OPTIONS +=	--disable-updater
CONFIGURE_OPTIONS +=	--enable-ipc
CONFIGURE_OPTIONS +=	--enable-system-ffi
CONFIGURE_OPTIONS +=	--enable-system-sqlite
CONFIGURE_OPTIONS +=	--with-system-libevent
CONFIGURE_OPTIONS +=	--with-system-zlib
CONFIGURE_OPTIONS +=	--with-system-bz2
CONFIGURE_OPTIONS +=	--disable-crashreporter
CONFIGURE_OPTIONS +=	--disable-necko-wifi
CONFIGURE_OPTIONS +=	--enable-startup-notification
CONFIGURE_OPTIONS +=	--enable-application=browser
CONFIGURE_OPTIONS +=	--prefix=/usr
CONFIGURE_OPTIONS +=	--libdir=/usr/lib

ENV +=	CC=$(CC)
ENV +=	CXX=$(CXX)
ENV +=	MOZILLA_OFFICIAL=1
ENV +=	MOZ_PKG_FORMAT=BZ2
ENV +=	PKG_SKIP_STRIP=1
ENV +=	MOZILLA_PKG_NAME=firefox

CONFIGURE_ENV =	$(ENV)
COMPONENT_BUILD_ENV =	$(ENV)

LANG_FILES=$(addsuffix .xpi,$(LANG_LIST))

CLEAN_PATHS += $(LANG_FILES)

$(LANG_FILES): 
	$(FETCH) --file $@  --url $(LANG_FILES_LOCATION)/$@

download prep:: $(LANG_FILES)

build: $(BUILD_32)

COMPONENT_POST_INSTALL_ACTION  = ( \
    for file in $(PROTO_DIR)/usr/lib/firefox/browser/components/libbrowsercomps.so \
          $(PROTO_DIR)/usr/lib/firefox/sdk/bin/xpcshell ; do \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH "/usr/lib:/usr/lib/firefox:$$ORIGIN:$$ORIGIN/.."'  \
        $$file ;\
    done ; \
    for file in $(PROTO_DIR)/usr/lib/firefox/sdk/bin/*.py; do \
        $(GSED) -i -e 's:/usr/bin/env python:$(PYTHON):' $$file; \
    done )

install: $(INSTALL_32)
