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
# Copyright 2016 Alexander Pyhalov
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-menus
COMPONENT_VERSION=	2.30.5
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Implementation of Desktop Menu Specification for GNOME
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:6dcc565006d6e8c2025ae83ab1f82edf6bd04d61c804c0dc9bf5ea50629c4caa
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.30/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_POST_UNPACK_ACTION = ( cd $(SOURCE_DIR) && cp -r python python-2.6)

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					libtoolize --copy --force &&\
					glib-gettextize -f &&\
					intltoolize --force --copy &&\
					aclocal -I m4 &&\
					automake -c -f -a &&\
					autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =        (chmod -R u+r $(SOURCE_DIR) && cp -rp $(SOURCE_DIR)/* $(@D) && \
                                        cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
                                        cd $(@D)/po-sun && $(MAKE) all )

LDFLAGS += -lsecdb -lsocket -lnsl -ltsol

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-static

CONFIGURE_ENV+= PYTHON=$(PYTHON)
CONFIGURE_ENV+= am_cv_python_pythondir="$(PYTHON.$(PYTHON_VERSION).VENDOR_PACKAGES.32)"
CONFIGURE_ENV+= am_cv_python_pyexecdir="$(PYTHON.$(PYTHON_VERSION).VENDOR_PACKAGES.32)"

COMPONENT_BUILD_ENV+= CC="$(CC)"
COMPONENT_BUILD_ENV+= CFLAGS="$(CFLAGS)"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += runtime/python-26
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
