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
# Copyright 2017 Alexander Pyhalov
# Copyright 2018 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	thunderbird
COMPONENT_VERSION= 	52.9.1
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	Mozilla Thunderbird Email/Newsgroup Client
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).source.tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:286fa71504e7184f3a41bcbdebf591bebe8e04dccbad1c93a47c6e72a7125c4d
COMPONENT_ARCHIVE_URL= \
  https://ftp.mozilla.org/pub/thunderbird/releases/$(COMPONENT_VERSION)/source/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mozilla.com/en-US/thunderbird/

LANG_LIST=	ar bg ca cs da de el es-AR es-ES et fi fr he hr hu id is it ja ko lt nl nn-NO pl pt-BR pt-PT ro ru sk sl sq sr sv-SE tr uk vi zh-CN zh-TW
LANG_FILES_LOCATION=	http://ftp.mozilla.org/pub/mozilla.org/thunderbird/releases/$(COMPONENT_VERSION)/linux-i686/xpi/

LIGHTNING_VERSION=5.4
LIGHTNING_DIR="$(PROTO_DIR)/usr/lib/thunderbird-$(COMPONENT_VERSION)/extensions/{e2fda1a4-762b-4020-b5ad-a41df1933103}"
GDATA_PROVIDER_DIR="$(PROTO_DIR)/usr/lib/thunderbird/extensions/{a62ef8ec-5fdc-40c2-873c-223b8a6925cc}"

COMPONENT_ARCHIVE_1=		lightning-$(LIGHTNING_VERSION)-sm+tb-linux.xpi
COMPONENT_ARCHIVE_HASH_1=	sha256:1dba9da346bf0a4755eb3466b754f3a0acb22f2ff8195d0c907c2afeb23115e8
COMPONENT_ARCHIVE_URL_1=	https://addons.cdn.mozilla.net/user-media/addons/_attachments/2313/$(COMPONENT_ARCHIVE_1)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && autoconf-2.13 &&\
			  cd $(@D)/mozilla && autoconf-2.13 &&\
                          cd $(@D)/mozilla/js/src && autoconf-2.13 )

COMPONENT_PRE_CONFIGURE_ACTION =        (cp $(COMPONENT_DIR)/files/gld-wrapper  $(BUILD_DIR) && chmod +x $(BUILD_DIR)/gld-wrapper )

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS =	--disable-alsa
CONFIGURE_OPTIONS +=	--enable-dbus
CONFIGURE_OPTIONS +=	--enable-gnomeui
CONFIGURE_OPTIONS +=	--enable-jemalloc
CONFIGURE_OPTIONS +=	--disable-debug
CONFIGURE_OPTIONS +=	--disable-tests
CONFIGURE_OPTIONS +=	--disable-debug-symbols
CONFIGURE_OPTIONS +=	--enable-install-strip
CONFIGURE_OPTIONS +=	--enable-optimize=-O2
CONFIGURE_OPTIONS +=	--disable-webrtc
CONFIGURE_OPTIONS +=	--enable-official-branding
CONFIGURE_OPTIONS +=	--disable-updater
CONFIGURE_OPTIONS +=	--enable-pulseaudio
CONFIGURE_OPTIONS +=	--enable-system-ffi
CONFIGURE_OPTIONS +=	--enable-system-pixman
CONFIGURE_OPTIONS +=	--with-system-zlib
CONFIGURE_OPTIONS +=	--with-system-bz2
CONFIGURE_OPTIONS +=	--disable-crashreporter
CONFIGURE_OPTIONS +=    --enable-startup-notification
CONFIGURE_OPTIONS +=	--enable-calendar
CONFIGURE_OPTIONS +=	--enable-application=mail
CONFIGURE_OPTIONS +=    --enable-default-toolkit=cairo-gtk2
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
ENV +=  OS_DEFINES="-D__USE_LEGACY_PROTOTYPES__"
ENV +=  GLD_WRAPPER=$(BUILD_DIR)/gld-wrapper
ENV +=  LDFLAGS="-L$(BUILD_DIR_32)/dist/lib -L$(BUILD_DIR_32)/dist/bin"

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
	for file in $(PROTO_DIR)/usr/lib/thunderbird-$(COMPONENT_VERSION)/*.so \
          $(PROTO_DIR)/usr/lib/thunderbird-$(COMPONENT_VERSION)/plugin-container; do \
	  /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(GCC_ROOT)/lib:/usr/lib/thunderbird"' $$file ;\
	  /usr/bin/elfedit -e 'dyn:value -s  RPATH "$(GCC_ROOT)/lib:/usr/lib/thunderbird"' $$file ;\
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

# Auto-generated dependencies
REQUIRED_PACKAGES += developer/build/autoconf-213
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/toolkit/libxt
