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
# Copyright 2023 Andreas Wacknitz
#

BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libesmtp
COMPONENT_VERSION=      1.1.0
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=      libESMTP is a brary for posting electronic mail
COMPONENT_PROJECT_URL=  https://libesmtp.github.io/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:32bc3614ca12d21c7d933f32d43410e8744b6f91fdca7732da9877a385e4e6c3
COMPONENT_ARCHIVE_URL=  https://github.com/libesmtp/libESMTP/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Development/C
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(XPG6MODE)
CFLAGS += -D_POSIX_PTHREAD_SEMANTICS
CFLAGS += -DNAME_MAX=255 -DHOST_NAME_MAX=255
LDFLAGS += -lnsl -lsocket

COMPONENT_POST_UNPACK_ACTION= ( $(MV) libESMTP-$(COMPONENT_VERSION) $(COMPONENT_SRC) )

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += system/library
