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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		compiz-plugins-extra
COMPONENT_VERSION=	0.8.10
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.northfield.ws/
COMPONENT_SUMMARY=	extra effects plugins for compiz
COMPONENT_SRC=		plugins-extra
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:31393ac6d58d12dca96b2f4b1d7c21fd118fc829aeb3117a598437c616186c80
COMPONENT_ARCHIVE_URL=	http://www.northfield.ws/projects/compiz/releases/$(COMPONENT_VERSION)/$(COMPONENT_SRC).tar.gz

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = ( cd $(@D) && \
  aclocal -I. && \
  autoheader && \
  libtoolize --automake --copy --force && \
  automake -a -f -c &&\
  autoconf &&\
  find $(@D) -name '*_options.c' -o -name '*_options.h' -exec rm -f {} \; )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--enable-schemas

CONFIGURE_ENV+=	INTLTOOL_PERL=$(PERL)
CONFIGURE_ENV+=	PYTHON=$(PYTHON)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += desktop/compiz/bcop
REQUIRED_PACKAGES += desktop/compiz/plugin/compiz-fusion-main

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/glu
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
