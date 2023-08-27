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
# Copyright 2017 Till Wegmueller
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			putty
COMPONENT_VERSION=		0.79
COMPONENT_SUMMARY=		A terminal integrated SSH/Telnet client commandline tools
COMPONENT_PROJECT_URL=	https://www.chiark.greenend.org.uk/~sgtatham/putty/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://the.earth.li/~sgtatham/putty/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:428cc8666fbb938ebf4ac9276341980dcd70de395b33164496cf7995ef0ef0d8
COMPONENT_FMRI=			network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_LICENSE=		MIT
COMPONENT_LICENSE_FILE=	LICENCE

include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lnsl -lsocket

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
