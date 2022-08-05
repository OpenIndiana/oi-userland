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
# Copyright (c) 2014 Alexander Pyhalov. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		intltool
COMPONENT_VERSION=	0.51.0
COMPONENT_REVISION =	1
COMPONENT_FMRI=		text/intltool
COMPONENT_PROJECT_URL=	https://freedesktop.org/wiki/Software/intltool/
COMPONENT_SUMMARY=	Set of tools to centralize translation of many different file formats using GNU gettext-compatible PO files
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:67c74d94196b153b774ab9f89b2fa6c6ba79352407037c8c14d5aeb334e959cd
COMPONENT_ARCHIVE_URL=\
  https://launchpad.net/intltool/trunk/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2

USE_DEFAULT_TEST_TRANSFORMS = yes

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += developer/gnome/gettext
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
