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

COMPONENT_NAME=		alacarte
COMPONENT_VERSION=	0.13.2
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Simple menu editor for GNOME
COMPONENT_FMRI=		desktop/xdg/menu-editor/alacarte
COMPONENT_CLASSIFICATION=	Applications/Configuration and Preferences
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:9fa36e5181b1eea947b184cb0f79d796b25cc5a5f122819a1ac2ff01bc7ee4ed
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/0.13/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	LGPLv2

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					intltoolize --force --copy --automake &&\
					libtoolize --copy --force &&\
					aclocal -I . &&\
					autoconf &&\
					autoheader &&\
					automake -c -f -a )

COMPONENT_PRE_CONFIGURE_ACTION =        (chmod -R u+r $(SOURCE_DIR) && cp -rp $(SOURCE_DIR)/* $(@D) && \
                                        cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
                                        cd $(@D)/po-sun && $(MAKE) all )

CONFIGURE_ENV+=	PYTHON=$(PYTHON)
CONFIGURE_ENV+= am_cv_python_pythondir="$(PYTHON.$(PYTHON_VERSION).VENDOR_PACKAGES.32)"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += runtime/python-27
