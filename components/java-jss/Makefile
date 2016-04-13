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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		jss
COMPONENT_VERSION=	4.3.1
COMPONENT_PROJECT_URL=	https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS/JSS
COMPONENT_SRC=		mozilla
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:8d3e848f018fca1a2e5b75f3231546b17923df10002091f7dfa2e53cf6f7a183
COMPONENT_ARCHIVE_URL=	https://ftp.mozilla.org/pub/mozilla.org/security/jss/releases/JSS_4_3_1_RTM/src/$(COMPONENT_ARCHIVE)

# Enable compiler optimizations and disable debugging code
COMPONENT_BUILD_ENV += BUILD_OPT=1

# Generate symbolic info for debuggers
COMPONENT_BUILD_ENV += XCFLAGS="-g"
COMPONENT_BUILD_ENV += NS_USE_GCC=1

COMPONENT_BUILD_ENV += PATH=$(GCC_ROOT)/bin:$(PATH)
COMPONENT_BUILD_ENV += PKG_CONFIG_ALLOW_SYSTEM_LIBS=1
COMPONENT_BUILD_ENV += PKG_CONFIG_ALLOW_SYSTEM_CFLAGS=1

MPS.32=/usr/lib/mps
MPS.64=/usr/lib/mps/$(MACH64)
COMPONENT_BUILD_ENV += NSPR_INCLUDE_DIR=/usr/include/mps
COMPONENT_BUILD_ENV += NSPR_LIB_DIR=$(MPS.$(BITS))
COMPONENT_BUILD_ENV += NSS_INCLUDE_DIR=/usr/include/mps
COMPONENT_BUILD_ENV += NSS_LIB_DIR=$(MPS.$(BITS))
COMPONENT_BUILD_ENV += JAVA_HOME=/usr/java

COMPONENT_BUILD_ENV.64 += USE_64=1
COMPONENT_BUILD_ENV += $(COMPONENT_BUILD_ENV.$(BITS))

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

$(BUILD_DIR)/%/.built:	$(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(CLONEY) $(SOURCE_DIR) $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D); $(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) -C security/coreconf)
	(cd $(@D); $(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) -C security/jss)
	(cd $(@D); $(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) -C security/jss javadoc)
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

build: $(BUILD_32_and_64)

install: build
	$(MKDIR) -p $(PROTO_DIR)/usr/lib/mps
	$(MKDIR) -p $(PROTO_DIR)/usr/lib/mps/$(MACH64)
	$(MKDIR) -p $(PROTO_DIR)/usr/share/lib/mps
	$(MKDIR) -p $(PROTO_DIR)/usr/share/lib/mps/$(MACH64)
	$(INSTALL) $(BUILD_DIR_32)/security/jss/lib/SunOS5.11_*_OPT.OBJ/libjss4.so $(PROTO_DIR)/usr/lib/mps
	$(INSTALL) $(BUILD_DIR_64)/security/jss/lib/SunOS5.11_*_OPT.OBJ/libjss4.so $(PROTO_DIR)/usr/lib/mps/$(MACH64)
	$(INSTALL) $(BUILD_DIR_32)/dist/xpclass.jar $(PROTO_DIR)/usr/share/lib/mps
	$(INSTALL) $(BUILD_DIR_64)/dist/xpclass.jar $(PROTO_DIR)/usr/share/lib/mps/$(MACH64)
	/usr/bin/elfedit -e 'dyn:value -s  RPATH "/usr/lib/mps"' $(PROTO_DIR)/usr/lib/mps/libjss4.so
	/usr/bin/elfedit -e 'dyn:value -s  RUNPATH "/usr/lib/mps"' $(PROTO_DIR)/usr/lib/mps/libjss4.so
	/usr/bin/elfedit -e 'dyn:value -s  RPATH "/usr/lib/mps/$(MACH64)"' $(PROTO_DIR)/usr/lib/mps/$(MACH64)/libjss4.so
	/usr/bin/elfedit -e 'dyn:value -s  RUNPATH "/usr/lib/mps/$(MACH64)"' $(PROTO_DIR)/usr/lib/mps/$(MACH64)/libjss4.so
