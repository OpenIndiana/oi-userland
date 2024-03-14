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
# Copyright (c) 2019 Michal Nowak
#

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=	   libpciaccess
COMPONENT_VERSION= 0.17
COMPONENT_FMRI=	   diagnostic/scanpci
COMPONENT_SUMMARY= scanpci and libpciaccess - generic PCI access software
COMPONENT_CLASSIFICATION=System/Hardware
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:74283ba3c974913029e7a547496a29145b07ec51732bbb5b5c58d5025ad95b73
COMPONENT_LICENSE_FILE=	COPYING

DROP_STATIC_LIBRARIES = yes

include $(WS_MAKE_RULES)/common.mk

# Missing files in build dir for common without this.
COMPONENT_PREP_ACTION = (cd $(@D) && \
			PATH="$(PATH)" libtoolize --automake --copy --force && \
                         aclocal -Im4 && \
                         autoheader && \
                         automake -a -f -c && \
                         autoconf )

# Drop 32-bit binaries
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRBINDIR32) ;

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
