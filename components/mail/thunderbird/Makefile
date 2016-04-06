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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	thunderbird
COMPONENT_VERSION= 	38.6.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	Mozilla Thunderbird Email/Newsgroup Client
COMPONENT_SRC= 		comm-esr38
COMPONENT_ARCHIVE= 	$(COMPONENT_NAME)-$(COMPONENT_VERSION).source.tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:0417711325a4ba6fa61882bfcd9a7ce325fa0b903474e087f16e13a70be15a6b
COMPONENT_ARCHIVE_URL= \
  https://ftp.mozilla.org/pub/thunderbird/releases/$(COMPONENT_VERSION)/source/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mozilla.com/en-US/thunderbird/

LANG_LIST=	ar be bg ca cs da de el es-AR es-ES et fi fr he hr hu id is it ja ko lt nl nn-NO pl pt-BR pt-PT ro ru sk sl sq sr sv-SE tr uk vi zh-CN zh-TW
LANG_FILES_LOCATION=	http://ftp.mozilla.org/pub/mozilla.org/thunderbird/releases/$(COMPONENT_VERSION)/linux-i686/xpi/

LIGHTNING_VERSION=4.0.5.2
LIGHTNING_DIR="$(PROTO_DIR)/usr/lib/thunderbird-$(COMPONENT_VERSION)/extensions/{e2fda1a4-762b-4020-b5ad-a41df1933103}"
GDATA_PROVIDER_DIR="$(PROTO_DIR)/usr/lib/thunderbird/extensions/{a62ef8ec-5fdc-40c2-873c-223b8a6925cc}"

COMPONENT_ARCHIVE_1=		lightning-$(LIGHTNING_VERSION).xpi
COMPONENT_ARCHIVE_HASH_1=	sha256:8f37425b3d780d72793592cb238424d17543254f76ff4da6f42a7ed2a72a5868
COMPONENT_ARCHIVE_URL_1=	https://addons.mozilla.org/thunderbird/downloads/file/389076/lightning-4.0.5.2-sm+tb-linux.xpi

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

PATH=/usr/gnu/bin:/usr/bin:/usr/sbin

CONFIGURE_OPTIONS =	--disable-alsa
CONFIGURE_OPTIONS +=	--enable-dbus
CONFIGURE_OPTIONS +=	--enable-gnomeui
CONFIGURE_OPTIONS +=	--enable-libxul
CONFIGURE_OPTIONS +=	--disable-jemalloc
CONFIGURE_OPTIONS +=	--without-intl-api
CONFIGURE_OPTIONS +=	--disable-debug
CONFIGURE_OPTIONS +=	--disable-tests
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
CONFIGURE_OPTIONS +=	--enable-pulseaudio
CONFIGURE_OPTIONS +=	--enable-system-ffi
CONFIGURE_OPTIONS +=	--enable-gstreamer
CONFIGURE_OPTIONS +=	--enable-system-pixman
CONFIGURE_OPTIONS +=	--with-system-icu
CONFIGURE_OPTIONS +=	--enable-system-sqlite
CONFIGURE_OPTIONS +=	--enable-shared-js
CONFIGURE_OPTIONS +=	--with-system-libevent
CONFIGURE_OPTIONS +=	--with-system-zlib
CONFIGURE_OPTIONS +=	--with-system-bz2
CONFIGURE_OPTIONS +=	--disable-crashreporter
CONFIGURE_OPTIONS +=    --enable-startup-notification
CONFIGURE_OPTIONS +=	--enable-calendar
CONFIGURE_OPTIONS +=	--enable-application=mail
CONFIGURE_OPTIONS +=	--prefix=/usr
CONFIGURE_OPTIONS +=	--libdir=/usr/lib

CXXFLAGS +=	-Wno-invalid-offsetof -fpermissive

ENV +=  SHELL=/usr/bin/sh
ENV +=	CC=$(CC)
ENV +=	CXX=$(CXX)
ENV +=	MOZILLA_OFFICIAL=1
ENV +=	MOZ_PKG_FORMAT=BZ2
ENV +=	PKG_SKIP_STRIP=1
ENV +=	MOZILLA_PKG_NAME=thunderbird
ENV +=	CXXFLAGS="$(CXXFLAGS)"
# -L.../dist/bin needs to be set otherwise it will report missing libnss3.so,
# libssl3.so, etc, while linking.
ENV +=  LDFLAGS="-z ignore -z interpose -B nodirect -L$(BUILD_DIR_32)/dist/lib"
ENV +=  OS_DEFINES="-D__USE_LEGACY_PROTOTYPES__"

CONFIGURE_ENV =	$(ENV)
COMPONENT_BUILD_ENV =	$(ENV)
COMPONENT_INSTALL_ENV += HOME=/tmp

LANG_FILES=$(addsuffix .xpi,$(LANG_LIST))

CLEAN_PATHS += $(LANG_FILES)

COMPONENT_BUILD_ARGS =

$(LANG_FILES):
	$(FETCH) --file $@  --url $(LANG_FILES_LOCATION)/$@

COMPONENT_POST_INSTALL_ACTION += \
	$(RM) -r $(LIGHTNING_DIR) ; \
	$(CP) -r $(BUILD_DIR_32)/dist/bin/distribution/extensions/{e2fda1a4-762b-4020-b5ad-a41df1933103} \
	  $(LIGHTNING_DIR) ; \
	unzip -u -d $(LIGHTNING_DIR) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1); \
	for file in $(PROTO_DIR)/usr/lib/thunderbird-$(COMPONENT_VERSION)/libprldap60.so \
	  $(LIGHTNING_DIR)/components/libcalbasecomps.so  \
	  $(PROTO_DIR)/usr/lib/thunderbird-$(COMPONENT_VERSION)/distribution/extensions/{e2fda1a4-762b-4020-b5ad-a41df1933103}/components/libcalbasecomps.so; do \
	  /usr/bin/elfedit -e 'dyn:value -s  RPATH "/usr/lib:/usr/lib/thunderbird"' $$file ;\
	done ;


COMPONENT_POST_INSTALL_ACTION += \
	list1='$(LANG_LIST)' ; for f in $$list1 ; do \
	  $(CP) $$f.xpi \
	    $(PROTOUSRLIBDIR)/thunderbird-$(COMPONENT_VERSION)/extensions/langpack-$$f@thunderbird.mozilla.org.xpi ; \
	done ;

COMPONENT_TEST_DIR =    $(@D)/js/src
COMPONENT_TEST_TARGETS=check-jit-test
COMPONENT_TEST_TRANSFORMS += \
	'-e "/\(^TEST-PASS\).*/d" '

$(SOURCE_DIR)/.patched-firefox-%: GPATCH_FLAGS += -d $(@D)/mozilla

download prep:: $(LANG_FILES)

build: $(BUILD_32)

install: $(INSTALL_32)

test:	$(TEST_32)
