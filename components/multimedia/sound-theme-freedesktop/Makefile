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
# Copyright (c) 2014 Alexander Pyhalov. All rights reserved
# Copyright (c) 2019 Nona Hansel
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sound-theme-freedesktop
COMPONENT_VERSION=	0.8
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	XDG FreeDesktop Sound Theme
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Specifications/sound-theme-spec/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:cb518b20eef05ec2e82dda1fa89a292c1760dc023aba91b8aa69bafac85e8a14
COMPONENT_ARCHIVE_URL=	https://people.freedesktop.org/~mccann/dist/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			gnome/theme/sound/xdg-sound-theme
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Theming
COMPONENT_LICENSE=		cc sa 2.0, cc sa 3.0 Unported, cc by-sa 2.0 Generic, cc by 3.0 Unported, GPLv2, LGPLv2, Artistic

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_ENV += PERL=$(PERL)

# Auto-generated dependencies
