#
#*
#* CDDL HEADER START
#*
#* The contents of this file are subject to the terms of the
#* Common Development and Distribution License, Version 1.0 only
#* (the "License").  You may not use this file except in compliance
#* with the License.
#*
#* You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
#* or http://www.opensolaris.org/os/licensing.
#* See the License for the specific language governing permissions
#* and limitations under the License.
#*
#* When distributing Covered Code, include this CDDL HEADER in each
#* file and include the License file at usr/src/OPENSOLARIS.LICENSE.
#* If applicable, add the following below this CDDL HEADER, with the
#* fields enclosed by brackets "[]" replaced with your own identifying
#* information: Portions Copyright [yyyy] [name of copyright owner]
#*
#* CDDL HEADER END
#*
#*
#* Copyright 2015 OpenSXCE.org Martin Bochnig <opensxce@mail.ru>
#* FireFox 20/30/40++ gcc4.x port with Flash support for OpenSolaris++ x86/x64
#* (depends also on my kernel hack for flash-plugin follows next week)
#* https://github.com/orgs/OpenSXCE-org/people/MartinBochnig
#* https://github.com/OpenSXCE-org
#*

#
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= 	firefox
COMPONENT_VERSION= 	43.0b3
COMPONENT_REVISION=	4
IPS_COMPONENT_VERSION=	43.0b3
COMPONENT_SUMMARY= 	Mozilla Firefox Web browser
COMPONENT_SRC= 		firefox-43.0b3
COMPONENT_ARCHIVE= 	$(COMPONENT_NAME)-$(COMPONENT_VERSION).source.tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:4cef62437d4b7517fa4717fcdd2116b017621e6f5a7a9bc0ad9dfa89602b1f51
COMPONENT_ARCHIVE_URL= \
  https://ftp.mozilla.org/pub/firefox/releases/$(COMPONENT_VERSION)/source/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mozilla.com/en-US/firefox/

LANG_LIST=	ar be bg ca cs da de el es-AR es-CL es-ES et fi fr he hi-IN hr hu id is it ja kk ko lt lv mk nb-NO nl nn-NO pl pt-BR pt-PT ro ru sk sl sq sr sv-SE th tr uk vi zh-CN zh-TW
LANG_FILES_LOCATION=	http://ftp.mozilla.org/pub/mozilla.org/firefox/releases/$(COMPONENT_VERSION)/linux-i686/xpi/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D) )

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
ENV +=	CXX=$(CXX)
ENV +=	MOZILLA_OFFICIAL=1
ENV +=	MOZ_PKG_FORMAT=XZ
ENV +=	PKG_SKIP_STRIP=1
ENV +=	MOZILLA_PKG_NAME=firefox
ENV +=	SHELL="/bin/bash"

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
