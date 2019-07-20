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
# Copyright 2014, Alexander Pyhalov 
# Copyright 2019, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nss
COMPONENT_VERSION=	3.44
COMPONENT_PROJECT_URL=	https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:a5620e59b6eeedfd5a12c9298b50ad92e9898b223e214eb675e36f4ffb5b6aff
COMPONENT_ARCHIVE_URL=	https://ftp.mozilla.org/pub/mozilla.org/security/nss/releases/NSS_3_44_RTM/src/$(COMPONENT_ARCHIVE)

# Enable compiler optimizations and disable debugging code
COMPONENT_BUILD_ENV += BUILD_OPT=1

# Generate symbolic info for debuggers and use c99 by default
COMPONENT_BUILD_ENV += XCFLAGS="-g -std=c99 -D__EXTENSIONS__"

COMPONENT_BUILD_ENV += PATH=$(GCC_ROOT)/bin:$(PATH)
COMPONENT_BUILD_ENV += PKG_CONFIG_ALLOW_SYSTEM_LIBS=1
COMPONENT_BUILD_ENV += PKG_CONFIG_ALLOW_SYSTEM_CFLAGS=1
COMPONENT_BUILD_ENV += NSS_USE_SYSTEM_SQLITE=1
COMPONENT_BUILD_ENV += NS_USE_GCC=1

MPS.32=/usr/lib/mps
MPS.64=/usr/lib/mps/$(MACH64)
COMPONENT_BUILD_ENV += NSPR_INCLUDE_DIR=/usr/include/mps
COMPONENT_BUILD_ENV += NSPR_LIB_DIR=$(MPS.$(BITS))
COMPONENT_BUILD_ENV += NSS_INCLUDE_DIR=/usr/include/mps
COMPONENT_BUILD_ENV += NSS_LIB_DIR=$(MPS.$(BITS))

COMPONENT_BUILD_ENV.64 += USE_64=1
COMPONENT_BUILD_ENV += $(COMPONENT_BUILD_ENV.$(BITS))

COMPONENT_TEST_ENV += $(COMPONENT_BUILD_ENV)
COMPONENT_TEST_ENV += HOST=127.0.0.1
COMPONENT_TEST_DIR = $(BUILD_DIR_$(BITS))/nss/tests

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

$(BUILD_DIR)/%/.built:	$(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(CLONEY) $(SOURCE_DIR) $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D); $(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) -C nss/coreconf)
	(cd $(@D); $(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) -C nss/lib)
	(cd $(@D); $(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) -C nss/cmd)
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

build: $(BUILD_32_and_64)

install: build
	$(MKDIR) -p $(PROTO_DIR)/usr/sfw/bin
	$(MKDIR) -p $(PROTO_DIR)/usr/sfw/bin/$(MACH64)
	$(MKDIR) -p $(PROTO_DIR)/usr/lib/mps
	$(MKDIR) -p $(PROTO_DIR)/usr/lib/mps/$(MACH64)
	$(MKDIR) -p $(PROTO_DIR)/usr/include/mps
	$(MKDIR) -p $(PROTO_DIR)/usr/lib/pkgconfig
	$(MKDIR) -p $(PROTO_DIR)/usr/lib/$(MACH64)/pkgconfig
	cp $(BUILD_DIR_32)/dist/public/nss/*.h $(PROTO_DIR)/usr/include/mps
	cp $(BUILD_DIR_32)/dist/public/dbm/*.h $(PROTO_DIR)/usr/include/mps
	cp $(BUILD_DIR_32)/dist/SunOS5.11_*_OPT.OBJ/lib/*.so $(PROTO_DIR)/usr/lib/mps
	cp $(BUILD_DIR_32)/dist/SunOS5.11_*_OPT.OBJ/lib/*.chk $(PROTO_DIR)/usr/lib/mps
	cp $(BUILD_DIR_64)/dist/SunOS5.11_*_OPT.OBJ/lib/*.so $(PROTO_DIR)/usr/lib/mps/$(MACH64)
	cp $(BUILD_DIR_64)/dist/SunOS5.11_*_OPT.OBJ/lib/*.chk $(PROTO_DIR)/usr/lib/mps/$(MACH64)
	for i in addbuiltin certutil cmsutil crlutil modutil pk12util signtool signver ssltap; do \
		cp $(BUILD_DIR_32)/dist/SunOS5.11_*_OPT.OBJ/bin/$$i $(PROTO_DIR)/usr/sfw/bin; \
		cp $(BUILD_DIR_64)/dist/SunOS5.11_*_OPT.OBJ/bin/$$i $(PROTO_DIR)/usr/sfw/bin/$(MACH64); \
		done
	cat $(COMPONENT_DIR)/files/nss.pc | sed s/^Version:/Version:\ $(COMPONENT_VERSION)/ \
		> $(PROTO_DIR)/usr/lib/pkgconfig/nss.pc 
	cat $(COMPONENT_DIR)/files/nss.pc | sed -e "s/^Version:/Version:\ $(COMPONENT_VERSION)/" \
			-e "s:/usr/lib/mps:/usr/lib/mps/$(MACH64):g" > $(PROTO_DIR)/usr/lib/$(MACH64)/pkgconfig/nss.pc
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
		done ;
	$(MKDIR) $(PROTO_DIR)/$(USRBINDIR)/ ;\
	$(MKDIR) $(PROTO_DIR)/$(USRBINDIR)/$(MACH64) ;\
	NSS_VMAJOR=`cat $(PROTO_DIR)/usr/include/mps/nss.h | grep "#define.*NSS_VMAJOR" | gawk '{print $$3}'` ;\
	NSS_VMINOR=`cat $(PROTO_DIR)/usr/include/mps/nss.h | grep "#define.*NSS_VMINOR" | gawk '{print $$3}'` ;\
	NSS_VPATCH=`cat $(PROTO_DIR)/usr/include/mps/nss.h | grep "#define.*NSS_VPATCH" | gawk '{print $$3}'` ;\
	cat $(SOURCE_DIR)/nss/pkg/pkg-config/nss-config.in | $(GSED) \
		-e "s,@prefix@,/usr,g" \
		-e "s,pkg-config,/usr/bin/pkg-config,g" \
		-e "s,@MOD_MAJOR_VERSION@,$$NSS_VMAJOR,g" \
		-e "s,@MOD_MINOR_VERSION@,$$NSS_VMINOR,g" \
		-e "s,@MOD_PATCH_VERSION@,$$NSS_VPATCH,g" \
		> $(PROTO_DIR)$(USRBINDIR)/nss-config ;\
	cat $(SOURCE_DIR)/nss/pkg/pkg-config/nss-config.in | $(GSED) \
		-e "s,@prefix@,/usr,g" \
		-e "s,pkg-config,/usr/bin/$(MACH64)/pkg-config,g" \
		-e "s,@MOD_MAJOR_VERSION@,$$NSS_VMAJOR,g" \
		-e "s,@MOD_MINOR_VERSION@,$$NSS_VMINOR,g" \
		-e "s,@MOD_PATCH_VERSION@,$$NSS_VPATCH,g" \
		> $(PROTO_DIR)$(USRBINDIR)/$(MACH64)/nss-config ;\
	$(MKDIR) $(PROTO_DIR)/$(USRSHAREMAN1DIR) ;\
	$(GSED) -e "s/@date@/`date +'%e %B %Y' | tr -d '\n'`/" -e "s/@version@/$(COMPONENT_VERSION)/" $(COMPONENT_DIR)/files/nss-config.xml > nss-config.xml ;\
	xmlto man nss-config.xml ;\
	$(RM) nss-config.xml ;\
	$(MV) nss-config.1 $(PROTO_DIR)/$(USRSHAREMAN1DIR) ;\
	$(TOUCH) $(BUILD_DIR_32)/.installed $(BUILD_DIR_64)/.installed ;

test:	$(TEST_32_and_64)

$(TEST_32):  $(BUILD_32)
	cd $(COMPONENT_TEST_DIR) && \
	$(ENV) $(COMPONENT_TEST_ENV) $(CONFIG_SHELL) all.sh &&\
	$(TOUCH) $(BUILD_DIR_$(BITS))/.tested

$(TEST_64):  $(BUILD_64) 
	cd $(COMPONENT_TEST_DIR) && \
	$(ENV) $(COMPONENT_TEST_ENV) $(CONFIG_SHELL) all.sh &&\
	$(TOUCH) $(BUILD_DIR_$(BITS))/.tested

REQUIRED_PACKAGES += text/xmlto

# Auto-generated dependencies
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += system/library
