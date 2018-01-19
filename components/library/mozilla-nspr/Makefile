#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2011, Andrzej Szeszo
# Copyright 2013, Jon Tibble
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nspr
COMPONENT_VERSION=	4.12
COMPONENT_PROJECT_URL=	https://developer.mozilla.org/ru/docs/NSPR
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:e0b10a1e569153668ff8bdea6c7e491b389fab69c2f18285a1ebf7c2ea4269de
COMPONENT_ARCHIVE_URL=	http://ftp.mozilla.org/pub/mozilla.org/nspr/releases/v$(COMPONENT_VERSION)/src/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_SCRIPT = $(SOURCE_DIR)/nspr/configure

CONFIGURE_ENV += CC="$(CC)"

CONFIGURE_LIBDIR.32 = /usr/lib/mps
CONFIGURE_LIBDIR.64 = /usr/lib/mps/$(MACH64)

CONFIGURE_OPTIONS.64 += --enable-64bit

CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --includedir=/usr/include/mps
#CONFIGURE_OPTIONS += --disable-debug
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
	$(MKDIR) -p $(PROTO_DIR)/usr/lib/pkgconfig
	cat $(COMPONENT_DIR)/nspr.pc | sed s/^Version:/Version:\ $(COMPONENT_VERSION)/ \
		> $(PROTO_DIR)/usr/lib/pkgconfig/nspr.pc
	for i in $(PROTO_DIR)/usr/lib/mps/*.so; do \
		/usr/bin/elfedit -e 'dyn:value -s  RPATH "/usr/lib/mps"' $$i ;\
		done ;
	for i in $(PROTO_DIR)/usr/lib/mps/*.so; do \
		/usr/bin/elfedit -e 'dyn:value -s  RUNPATH "/usr/lib/mps"' $$i ;\
		done
	for i in $(PROTO_DIR)/usr/lib/mps/$(MACH64)/*.so; do \
		/usr/bin/elfedit -e 'dyn:value -s  RPATH "/usr/lib/mps/$(MACH64)"' $$i ;\
		done ;
	for i in $(PROTO_DIR)/usr/lib/mps/$(MACH64)/*.so; do \
		/usr/bin/elfedit -e 'dyn:value -s  RUNPATH "/usr/lib/mps/$(MACH64)"' $$i ;\
		done
	$(TOUCH) $(BUILD_DIR_32)/.installed $(BUILD_DIR_64)/.installed

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
