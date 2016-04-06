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
# Copyright 2016 Jim Klimov
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME= zeromq

# See configure.ac for ABI version mapping to software version
COMPONENT_VERSION_ABI= 3
COMPONENT_VERSION= 3.2.5
COMPONENT_SUMMARY= Open source message queue optimised for performance
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:09653e56a466683edb2f87ee025c4de55b8740df69481b9d7da98748f0c92124
COMPONENT_ARCHIVE_URL= \
  http://download.zeromq.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= http://zeromq.org/
# Two licenses in tarball, LGPLv3+ is referenced in their spec-file
COMPONENT_LICENSE_FILE= COPYING.LESSER
COMPONENT_LICENSE= LGPLv3+
COMPONENT_CLASSIFICATION= System/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PKG_OPTIONS +=	-D COMPONENT_VERSION_ABI="$(COMPONENT_VERSION_ABI)"

COMPONENT_PREP_ACTION =	\
	( cd $(@D) && \
	  libtoolize --copy --force && \
	  aclocal -I m4 && \
	  autoheader && \
	  automake -c -f -a && \
	  autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS +=	--with-documentation
CONFIGURE_OPTIONS +=	--enable-static=no

COMPONENT_POST_INSTALL_ACTION=	( cd $(PROTO_DIR)/usr && \
    for D in lib include share/man/* ; do \
        $(MKDIR) "./share/zeromq$(COMPONENT_VERSION_ABI)/$$D" && \
        $(CLONEY) "$(PROTO_DIR)/usr/$$D" "$(PROTO_DIR)/usr/share/zeromq$(COMPONENT_VERSION_ABI)/$$D" || exit ; \
    done \
)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# test_shutdown_stress fails
test: $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
