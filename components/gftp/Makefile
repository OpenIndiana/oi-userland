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
# Copyright (c) 2015 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gftp
COMPONENT_VERSION=	2.0.19
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://gftp.seul.org/
COMPONENT_SUMMARY=	Multithreaded FTP client for *NIX based machines
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:5306a46be96d6f4d23906cb1836fb3d732039621a6c7fcfa921acc21ac110bfd
COMPONENT_ARCHIVE_URL=	http://gftp.seul.org//$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		desktop/gftp
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2
COMPONENT_CLASSIFICATION=	Applications/System Utilities

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
