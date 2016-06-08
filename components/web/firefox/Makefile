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
# Copyright 2015 OpenSXCE.org Martin Bochnig <opensxce@mail.ru>
# Copyright 2013-2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	firefox
COMPONENT_VERSION= 	45.2.0esr
IPS_COMPONENT_VERSION= 	45.2.0
COMPONENT_SUMMARY= 	Mozilla Firefox Web browser
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_NAME)-$(COMPONENT_VERSION).source.tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:1a729774034231c919dc5a556e17d3342792d5347c755d8d0a4f67a07374804b
COMPONENT_ARCHIVE_URL= \
  https://ftp.mozilla.org/pub/firefox/releases/$(COMPONENT_VERSION)/source/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mozilla.com/en-US/firefox/

LANG_LIST=	ar be bg ca cs da de el es-AR es-CL es-ES et fi fr he hi-IN hr hu id is it ja kk ko lt lv mk nb-NO nl nn-NO pl pt-BR pt-PT ro ru sk sl sq sr sv-SE th tr uk vi zh-CN zh-TW
LANG_FILES_LOCATION=	http://ftp.mozilla.org/pub/mozilla.org/firefox/releases/$(COMPONENT_VERSION)/linux-i686/xpi/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = (cp $(COMPONENT_DIR)/files/gld-wrapper  $(BUILD_DIR); chmod +x $(BUILD_DIR)/gld-wrapper )

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

CONFIGURE_OPTIONS =	--enable-application=browser
CONFIGURE_OPTIONS +=	--enable-official-branding
CONFIGURE_OPTIONS +=	--disable-updater
CONFIGURE_OPTIONS +=	--enable-debug-symbols=no
CONFIGURE_OPTIONS +=	--enable-update-channel=esr
CONFIGURE_OPTIONS +=	--disable-tests
CONFIGURE_OPTIONS +=	--enable-jemalloc
CONFIGURE_OPTIONS +=	--disable-dtrace
CONFIGURE_OPTIONS +=    --disable-xinerama
CONFIGURE_OPTIONS +=	--disable-crashreporter
CONFIGURE_OPTIONS +=	--disable-pulseaudio
CONFIGURE_OPTIONS +=	--disable-gstreamer
CONFIGURE_OPTIONS +=	--with-intl-api
CONFIGURE_OPTIONS +=	--disable-debug
CONFIGURE_OPTIONS +=	--enable-ipc
CONFIGURE_OPTIONS +=	--enable-default-toolkit=cairo-gtk2
CONFIGURE_OPTIONS +=	--prefix=/usr
CONFIGURE_OPTIONS +=	--libdir=/usr/lib

ENV +=	CC=$(CC)
ENV +=	GLD_WRAPPER=$(BUILD_DIR)/gld-wrapper
ENV +=	CXX=$(CXX)
ENV +=	MOZILLA_OFFICIAL=1
ENV +=	MOZ_PKG_FORMAT=XZ
ENV +=	PKG_SKIP_STRIP=1
ENV +=	MOZILLA_PKG_NAME=firefox
ENV +=	SHELL="/bin/bash"

CONFIGURE_ENV =	$(ENV)
COMPONENT_BUILD_ENV =	$(ENV)
COMPONENT_INSTALL_ENV += HOME=/tmp

LANG_FILES=$(addsuffix .xpi,$(LANG_LIST))

CLEAN_PATHS += $(LANG_FILES)

$(LANG_FILES): 
	$(FETCH) --file $@  --url $(LANG_FILES_LOCATION)/$@

download prep:: $(LANG_FILES)

build: $(BUILD_32)

COMPONENT_POST_INSTALL_ACTION  = ( \
    for file in $(PROTO_DIR)/usr/lib/firefox/browser/components/libbrowsercomps.so \
          $(PROTO_DIR)/usr/lib/firefox/sdk/lib/libxul.so \
          $(PROTO_DIR)/usr/lib/firefox/sdk/bin/xpcshell ; do \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH "/usr/lib:/usr/lib/firefox:$$ORIGIN:$$ORIGIN/.."'  \
        $$file ;\
    done ; \
    for file in $(PROTO_DIR)/usr/lib/firefox/sdk/bin/*.py; do \
        $(GSED) -i -e 's:/usr/bin/env python:$(PYTHON):' $$file; \
    done )

install: $(INSTALL_32)
