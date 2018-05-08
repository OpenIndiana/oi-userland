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
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=			  xmessage
COMPONENT_VERSION=		  1.0.5
COMPONENT_SUMMARY=		  xmessage - display a message or query in a window
COMPONENT_PROJECT_URL=	  $(XORG_BASE_URL)
COMPONENT_FMRI=			  x11/xmessage
COMPONENT_CLASSIFICATION= Applications/Accessories
COMPONENT_SRC=			  $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
  sha256:373dfb81e7a6f06d3d22485a12fcde6e255d58c6dee1bbaeb00c7d0caa9b2029
COMPONENT_ARCHIVE_URL=	  $(XORG_APP_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		  MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
