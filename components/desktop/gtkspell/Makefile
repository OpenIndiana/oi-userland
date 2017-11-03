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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtkspell
COMPONENT_VERSION=	2.0.16
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://gtkspell.sourceforge.net/
COMPONENT_SUMMARY=	Gtkspell provides word-processor-style highlighting and replacement of misspelled words in a GtkTextView widget
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8fc7dc560167b2cb7193e76aca625a152dc19b0ebf49816b78539cbb90d80d02
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/gtkspell/files/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_FMRI= 	library/desktop/gtkspell

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION =	( cd $(@D)  && \
	libtoolize --copy --force &&\
	aclocal -I . &&\
	automake -c -f -a &&\
	autoconf )


CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+=	--disable-static

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += system/library
