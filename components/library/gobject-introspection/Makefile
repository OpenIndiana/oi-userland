#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Marcel Telka <marcel@telka.sk>
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gobject-introspection

COMPONENT_VERSION_MAJOR=1
COMPONENT_VERSION_MINOR=60
COMPONENT_VERSION_MICRO=1
COMPONENT_VERSION_DL=	$(COMPONENT_VERSION_MAJOR).$(COMPONENT_VERSION_MINOR)
COMPONENT_VERSION=	$(COMPONENT_VERSION_DL).$(COMPONENT_VERSION_MICRO)
COMPONENT_SUMMARY=	Introspection for GObject libraries
COMPONENT_FMRI=		library/desktop/gobject/gobject-introspection
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:d844d1499ecd36f3ec8a3573616186d36626ec0c9a7981939e99aa02e9c824b3
COMPONENT_ARCHIVE_URL= \
	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/$(COMPONENT_VERSION_DL)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://live.gnome.org/GObjectIntrospection
COMPONENT_LICENSE_FILE=	gobject-introspection.license
COMPONENT_LICENSE=	GPLv2, LGPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PYTHON_VERSION = 3.4

COMPONENT_POST_UNPACK_ACTION = \
        /usr/bin/find $(SOURCE_DIR) -name *.py \
                -exec $(GSED) -i -e 's:/usr/bin/env python:$(PYTHON):' "{}" \; ;

COMPONENT_PREP_ACTION += \
	( cd $(@D) && \
	aclocal -I ./m4 && \
	autoheader && \
	automake -a -f -c --gnu && \
	autoconf )

CONFIGURE_OPTIONS += --sysconfdir=/etc

CONFIGURE_ENV += PYTHON=$(PYTHON.$(PYTHON_VERSION).$(BITS))

COMPONENT_BUILD_ENV += CC="$(CC)"

unexport SHELLOPTS

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += library/python/markdown-34
REQUIRED_PACKAGES += developer/build/autoconf-archive
# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
