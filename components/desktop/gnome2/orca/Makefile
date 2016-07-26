##
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
# Copyright (c) 2014 Ken Mays
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         orca
COMPONENT_VERSION=      2.32.1
COMPONENT_PROJECT_URL=  http://www.gnome.org
COMPONENT_SUMMARY=      Orca screen reader/magnifier
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:44da9da70c1b47bc87fda8f3b9da4cc1df9993d92388434f5707d39b5a832629
COMPONENT_ARCHIVE_URL=  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.32/$(COMPONENT_ARCHIVE)


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

CONFIGURE_ENV+= PYTHON="$(PYTHON)"
CONFIGURE_ENV+= am_cv_python_pythondir="$(PYTHON.$(PYTHON_VERSION).VENDOR_PACKAGES.32)"
CONFIGURE_ENV+= am_cv_python_pyexecdir="$(PYTHON.$(PYTHON_VERSION).VENDOR_PACKAGES.32)"


# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += gnome/accessibility/at-spi
REQUIRED_PACKAGES += gnome/accessibility/gnome-mag
REQUIRED_PACKAGES += gnome/speech/gnome-speech
REQUIRED_PACKAGES += library/accessibility/brltty
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/liblouis
REQUIRED_PACKAGES += library/perl-5/xml-parser
REQUIRED_PACKAGES += library/python-2/python-xdg-27
REQUIRED_PACKAGES += library/python/gnome-python-27
REQUIRED_PACKAGES += library/python/pycairo-27
REQUIRED_PACKAGES += library/python/pygobject
REQUIRED_PACKAGES += library/python/pygobject-27
REQUIRED_PACKAGES += library/python/pygtk2
REQUIRED_PACKAGES += library/python/pygtk2-27
REQUIRED_PACKAGES += library/python/python-dbus-27
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/python2.7
REQUIRED_PACKAGES += text/gnu-gettext
REQUIRED_PACKAGES += text/gnu-grep
REQUIRED_PACKAGES += text/intltool
