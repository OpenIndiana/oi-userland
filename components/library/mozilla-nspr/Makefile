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
# Copyright 2019, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nspr
COMPONENT_VERSION=	4.21
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSPR
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:15ea32c7b100217b6e3193bc03e77f485d9bf7504051443ba9ce86d1c17c6b5a
COMPONENT_ARCHIVE_URL=	http://ftp.mozilla.org/pub/mozilla.org/nspr/releases/v$(COMPONENT_VERSION)/src/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

# Test suite needs cloney
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT = $(SOURCE_DIR)/nspr/configure

CONFIGURE_ENV += CC="$(CC)"

CONFIGURE_LIBDIR.32 = /usr/lib/mps
CONFIGURE_LIBDIR.64 = /usr/lib/mps/$(MACH64)

CONFIGURE_OPTIONS.64 += --enable-64bit
CONFIGURE_OPTIONS.64 += --bindir=$(USRBINDIR)/$(MACH64)

CONFIGURE_OPTIONS  =	--prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	--libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS +=	--includedir=/usr/include/mps
CONFIGURE_OPTIONS +=	--bindir=$(USRBINDIR)
CONFIGURE_OPTIONS +=	$(CONFIGURE_OPTIONS.$(BITS))

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)
	for i in $(PROTO_DIR)/usr/lib/mps/*.so; do \
		/usr/bin/elfedit -e 'dyn:value -s  RPATH "/usr/lib/mps"' $$i ;\
		/usr/bin/elfedit -e 'dyn:value -s  RUNPATH "/usr/lib/mps"' $$i ;\
	done ;
	for i in $(PROTO_DIR)/usr/lib/mps/$(MACH64)/*.so; do \
		/usr/bin/elfedit -e 'dyn:value -s  RPATH "/usr/lib/mps/$(MACH64)"' $$i ;\
		/usr/bin/elfedit -e 'dyn:value -s  RUNPATH "/usr/lib/mps/$(MACH64)"' $$i ;\
	done ;
	$(MKDIR) $(PROTO_DIR)/$(USRSHAREMAN1DIR) ;\
	$(GSED) -e "s/@date@/`date +'%e %B %Y' | tr -d '\n'`/" -e "s/@version@/$(COMPONENT_VERSION)/" $(COMPONENT_DIR)/files/nspr-config.xml > nspr-config.xml ;\
	xmlto man nspr-config.xml ;\
	$(RM) nspr-config.xml ;\
	$(MV) nspr-config.1 $(PROTO_DIR)/$(USRSHAREMAN1DIR) ;\
	$(TOUCH) $(BUILD_DIR_32)/.installed $(BUILD_DIR_64)/.installed

# Test suite is just this script
COMPONENT_TEST_CMD=	perl nspr/pr/tests/runtests.pl
COMPONENT_TEST_ENV_CMD=
COMPONENT_TEST_ARGS=
COMPONENT_TEST_TARGETS=

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += text/xmlto

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
