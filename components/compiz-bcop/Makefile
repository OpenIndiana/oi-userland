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

COMPONENT_NAME=		compiz-bcop
COMPONENT_VERSION=	0.8.10
COMPONENT_FMRI=		desktop/compiz/bcop
COMPONENT_CLASSIFICATION=Development/Other Languages
COMPONENT_PROJECT_URL=	http://www.northfield.ws/
COMPONENT_SUMMARY=	beryl compiz XML option parser
COMPONENT_SRC_NAME=	bcop
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:76a8e8c04f1c07cb4d2c204512806f94a59f4089a00a9c344be8f62d531d6504
COMPONENT_ARCHIVE_URL=	http://www.northfield.ws/projects/compiz/releases/$(COMPONENT_VERSION)/$(COMPONENT_SRC_NAME).tar.gz
COMPONENT_LICENSE_FILE=	compiz-bcop.license
COMPONENT_LICENSE=	MIT, LGPLv2.1, GPLv2


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
					aclocal -I. && \
				        autoheader && \
			                libtoolize --automake --copy --force && \
					automake -a -f -c &&\
					autoconf )

CONFIGURE_OPTIONS+=	--with-getopt=/usr/gnu/bin/getopt

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
