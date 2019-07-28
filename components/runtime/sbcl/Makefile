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
COMPONENT_VERSION=	1.5.5
COMPONENT_PROJECT_URL=	http://www.sbcl.org/
COMPONENT_FMRI=		runtime/sbcl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-source.tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:cb47fae6a86f0c5c57431604fb4e5f11c8a823f94ce128d568b8770fc5bcaae2
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/sbcl/sbcl/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD-PublicDomain
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	sbcl - Steel Bank Common Lisp
COMPONENT_CLASSIFICATION=	Development/Other Languages

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_ENV  =	PATH=/usr/bin:/usr/sbin:/bin:/sbin:/usr/gnu/bin
COMPONENT_ENV +=	GNUMAKE=$(GMAKE)
COMPONENT_ENV +=	CC="$(CC)"
COMPONENT_BUILD_ARGS  =	--prefix=/usr
COMPONENT_BUILD_ARGS +=	--arch=x86
# This is currently --with-sb-thread --with-sb-core-compression
# --with-sb-xref-internals and :sb-after-xc-core as a build feature.
COMPONENT_BUILD_ARGS +=	--fancy

$(BUILD_DIR)/%/.built:	$(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(BUILD_DIR)
	$(CP) -a $(SOURCE_DIR) $(@D)
	(cd $(@D) ; $(ENV) $(COMPONENT_ENV) /usr/gnu/bin/sh make.sh $(COMPONENT_BUILD_ARGS))
	(cd $(@D)/doc/manual ; $(ENV) $(COMPONENT_ENV) BUILD_ROOT=$(PROTO_DIR) $(GMAKE) html info)
	$(TOUCH) $@

$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built
	(cd $(@D) ; $(ENV) $(COMPONENT_ENV) BUILD_ROOT=$(PROTO_DIR) /usr/gnu/bin/sh install.sh)
	$(TOUCH) $@

$(BUILD_DIR)/%/.tested:		$(BUILD_DIR)/%/.installed
	(cd $(@D)/tests; $(ENV) $(COMPONENT_ENV) BUILD_ROOT=$(PROTO_DIR) /usr/gnu/bin/sh run-tests.sh)

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
