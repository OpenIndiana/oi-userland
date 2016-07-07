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

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hamster-applet
COMPONENT_VERSION=	2.32.1
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Time tracking for masses
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:98302221efd4ccd4a2446d2cda15b795a0b23850f562935a3dd61afe3e2cd0aa
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.32/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Applications/Panels and Applets
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_FMRI=		desktop/time-tracking/hamster

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin


# This is not autoconf based component
# It uses waf, so we have to add some magic to make it work with configure.mk

# Missing files in build dir for waf without this
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIG_SHELL = $(PYTHON)
CONFIGURE_SCRIPT=  $(SOURCE_DIR)/waf
CONFIGURE_OPTIONS= --prefix=/usr configure build

GMAKE= $(PYTHON) $(SOURCE_DIR)/waf
COMPONENT_BUILD_GMAKE_ARGS =
COMPONENT_BUILD_ARGS = build
COMPONENT_INSTALL_ARGS =
COMPONENT_INSTALL_ENV += DESTDIR=$(PROTO_DIR)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/python-2/python-notify
REQUIRED_PACKAGES += library/python-2/python-notify-27
REQUIRED_PACKAGES += library/python-2/python-xdg-27
REQUIRED_PACKAGES += library/python/gnome-python
REQUIRED_PACKAGES += library/python/gnome-python-27
REQUIRED_PACKAGES += library/python/pygobject
REQUIRED_PACKAGES += library/python/pygobject-27
REQUIRED_PACKAGES += library/python/pygtk2
REQUIRED_PACKAGES += library/python/pygtk2-27
REQUIRED_PACKAGES += library/python/pyorbit-27
REQUIRED_PACKAGES += library/python/python-dbus
REQUIRED_PACKAGES += library/python/python-dbus-27
REQUIRED_PACKAGES += library/python/python-gnome-desktop
REQUIRED_PACKAGES += library/python/python-gnome-desktop-27
REQUIRED_PACKAGES += runtime/python-27
