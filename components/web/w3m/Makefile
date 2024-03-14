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
# Copyright 2023 Niklas Poslovski
#

USE_OPENSSL11 = yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= w3m
COMPONENT_VERSION=  0.5.3.20230121
HUMAN_VERSION= 0.5.3+git20230121
#COMPONENT_REVISION= 6
COMPONENT_SUMMARY= A text-based web browser
COMPONENT_SRC= $(COMPONENT_NAME)-0.5.3-git20230121
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:fdc7d55d3c0104db26aa9759db34f37e5eee03f44c868796e3bbfb8935c96e39
COMPONENT_ARCHIVE_URL= \
  https://github.com/tats/w3m/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_PROJECT_URL= https://w3m.sourceforge.net/
COMPONENT_FMRI= web/browser/w3m
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE= MIT

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --libexecdir=/usr/lib
CONFIGURE_OPTIONS+= --with-browser=/usr/bin/firefox

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/gc
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
