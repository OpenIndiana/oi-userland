#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sbcl
COMPONENT_VERSION=	1.2.7
COMPONENT_PROJECT_URL=	http://www.sbcl.org/
COMPONENT_FMRI=		runtime/sbcl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-source.tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:b27099d8c9fb5c63673e7dc4a83f82b4088dd0ed02e849a4d164aa1b12cc5283
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/sbcl/sbcl/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD-PublicDomain
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	sbcl - Steel Bank Common Lisp

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_ENV  =	PATH=/usr/bin:/usr/sbin:/bin:/sbin:/usr/gnu/bin
COMPONENT_ENV +=	GNUMAKE=$(GMAKE)
COMPONENT_BUILD_ARGS  =	--prefix=/usr
COMPONENT_BUILD_ARGS +=	--arch=x86

$(BUILD_DIR)/%/.built:	$(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(BUILD_DIR)
	$(CP) -a $(SOURCE_DIR) $(@D)
	(cd $(@D) ; chmod +x find-gnumake.sh)
	(cd $(@D) ; $(ENV) $(COMPONENT_ENV) /usr/gnu/bin/sh make.sh $(COMPONENT_BUILD_ARGS))
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
	-$(PARFAIT) build
endif
	$(TOUCH) $@

$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built
	(cd $(@D) ; $(ENV) $(COMPONENT_ENV) BUILD_ROOT=$(PROTO_DIR) /usr/gnu/bin/sh install.sh)
	$(TOUCH) $@

build:		$(BUILD_32)

install:	$(INSTALL_32)

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

REQUIRED_PACKAGES += runtime/sbcl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
