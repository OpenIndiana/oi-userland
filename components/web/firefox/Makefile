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
# Copyright 2013-2017 Alexander Pyhalov
# Copyright 2018 Michal Nowak
#
PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	firefox
COMPONENT_VERSION= 	60.2.0esr
IPS_COMPONENT_VERSION= 	60.2.0
COMPONENT_SUMMARY= 	Mozilla Firefox Web browser
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(IPS_COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_NAME)-$(COMPONENT_VERSION).source.tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:795bdc8b5648234ce74322e3e9b219947d984ce3a1e4e09ce1061fafbbe77717
COMPONENT_ARCHIVE_URL= \
  https://ftp.mozilla.org/pub/firefox/releases/$(COMPONENT_VERSION)/source/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mozilla.com/en-US/firefox/

LANG_LIST=	ar bg ca cs da de el es-AR es-CL es-ES et fi fr he hi-IN hr hu id is it ja kk ko lt lv mk nb-NO nl nn-NO pl pt-BR pt-PT ro ru sk sl sq sr sv-SE th tr uk vi zh-CN zh-TW
LANG_FILES_LOCATION=	http://ftp.mozilla.org/pub/mozilla.org/firefox/releases/$(COMPONENT_VERSION)/linux-i686/xpi/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(USRBINDIR.64):$(PATH.illumos)

COMPONENT_PREP_ACTION = ( cd $(@D) && autoconf-2.13 &&\
                          cd $(@D)/js/src && autoconf-2.13 )


FIREFOX_LIBDIR=	$(CONFIGURE_LIBDIR.$(BITS)
GNU_ARCH=x86_64-sun-solaris

CONFIGURE_OPTIONS =	--enable-application=browser
CONFIGURE_OPTIONS +=	--enable-official-branding
CONFIGURE_OPTIONS +=	--disable-updater
CONFIGURE_OPTIONS +=	--disable-debug-symbols
CONFIGURE_OPTIONS +=	--enable-update-channel=esr
CONFIGURE_OPTIONS +=	--disable-tests
CONFIGURE_OPTIONS +=	--disable-jemalloc
CONFIGURE_OPTIONS +=	--enable-optimize="-O2 -fno-schedule-insns2 -fno-lifetime-dse -fno-delete-null-pointer-checks"
CONFIGURE_OPTIONS +=	--disable-dtrace
CONFIGURE_OPTIONS +=	--disable-crashreporter
CONFIGURE_OPTIONS +=	--enable-pulseaudio
CONFIGURE_OPTIONS +=	--disable-webrtc
CONFIGURE_OPTIONS +=	--with-intl-api
CONFIGURE_OPTIONS +=	--disable-debug
CONFIGURE_OPTIONS +=	--enable-default-toolkit=cairo-gtk3
CONFIGURE_OPTIONS +=	--prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	--libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS +=	--host=$(GNU_ARCH)
CONFIGURE_OPTIONS +=	--target=$(GNU_ARCH)


ENV +=  PATH=$(PATH)
ENV +=	CC=$(CC)
ENV +=	CFLAGS="$(CFLAGS)"
ENV +=	CXX=$(CXX)
ENV +=	CXXFLAGS="$(CXXFLAGS)"
ENV +=	LDFLAGS="$(LDFLAGS) -lm"
ENV +=	MOZILLA_OFFICIAL=1
ENV +=	MOZ_TELEMETRY_REPORTING=1
ENV +=	MOZ_PACKAGE_JSSHELL=1
ENV +=	MOZ_PKG_FORMAT=XZ
ENV +=	PKG_SKIP_STRIP=1
ENV +=	MOZILLA_PKG_NAME=firefox
ENV +=	SHELL="/bin/bash"
ENV +=  LDFLAGS="-L$(BUILD_DIR_64)/dist/lib -L$(BUILD_DIR_64)/dist/bin"
ENV +=  PYTHON="$(PYTHON)"

CONFIGURE_ENV =	$(ENV)
COMPONENT_BUILD_ENV =	$(ENV)
COMPONENT_INSTALL_ENV += HOME=/tmp

LANG_FILES=$(addsuffix .xpi,$(LANG_LIST))

CLEAN_PATHS += $(LANG_FILES)

$(LANG_FILES): 
	$(FETCH) --file $@  --url $(LANG_FILES_LOCATION)/$@

download prep:: $(LANG_FILES)

build: $(BUILD_64)

COMPONENT_POST_INSTALL_ACTION  = ( \
    for file in $(PROTO_DIR)$(FIREFOXLIBDIR)/firefox/sdk/lib/*.so \
          $(PROTO_DIR)$(FIREFOXLIBDIR)/firefox/*.so \
          $(PROTO_DIR)$(FIREFOXLIBDIR)/firefox/sdk/bin/xpcshell \
          $(PROTO_DIR)$(FIREFOXLIBDIR)/firefox/plugin-container; do \
        /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(GCC_ROOT)/lib/$(LIBSUBDIR):$(FIREFOXLIBDIR)/firefox:$$ORIGIN:$$ORIGIN/.."' $$file ; \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH "$(GCC_ROOT)/lib/$(LIBSUBDIR):$(FIREFOXLIBDIR)/firefox:$$ORIGIN:$$ORIGIN/.."'  $$file ; \
    done ; \
    for file in $(PROTO_DIR)$(FIREFOXLIBDIR)/firefox/sdk/bin/*.py; do \
        $(GSED) -i -e 's:/usr/bin/env python:$(PYTHON):' $$file; \
    done )

install: $(INSTALL_64)

# Build dependencies
REQUIRED_PACKAGES += developer/build/autoconf-213
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += system/header/header-audio

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
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
