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
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gexif
COMPONENT_VERSION=	0.5
COMPONENT_PROJECT_URL=	http://libexif.sourceforge.net/
COMPONENT_SUMMARY=	gexif is the GTK+ based GUI interface to libexif-gtk
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:beed223c55fc32ba7bf2f91e69e6daf2087c8b44ccfd9191c34058bacd776c24
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/libexif/files/gexif/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
					aclocal -I. && \
				        autoheader && \
			                libtoolize --automake --copy --force && \
					intltoolize --copy --force --automake && \
					automake -a -f -c &&\
					autoconf )

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libexif-gtk
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
