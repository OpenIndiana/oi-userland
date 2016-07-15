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
# Copyright (c) 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		distcc
COMPONENT_VERSION=	3.1
# Versioning is complicated: samba.org/ftp has 2.x versions as newest,
# while newest github release is 3.1 from 2008, and there is recent HEAD
# So we take a randomly newest Git snapshot as of package review:
COMPONENT_GIT_DATE=	20160427
COMPONENT_GIT_REV=	544904c
IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).0.$(COMPONENT_GIT_DATE)
COMPONENT_PROJECT_URL=	http://distcc.samba.org/

COMPONENT_DOCUMENTATION_URL =	https://github.com/distcc/distcc/blob/master/INSTALL

COMPONENT_SRC= distcc-distcc-$(COMPONENT_GIT_REV)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz

COMPONENT_ARCHIVE_HASH=	\
  sha256:6f0ae295e2652b44af91086125ca6df254c72bf5283dc5a10a5bf273c45ed05e
COMPONENT_ARCHIVE_URL= \
  https://codeload.github.com/distcc/distcc/legacy.tar.gz/$(COMPONENT_GIT_REV)

COMPONENT_SUMMARY=	distcc - distributor of preprocessed C/C++/ObjC files across nodes to crowd-build code (bleeding edge, Git $(COMPONENT_GIT_REV) at $(COMPONENT_GIT_DATE))
COMPONENT_FMRI=		developer/distcc
COMPONENT_CLASSIFICATION=	Development/C
COMPONENT_LICENSE=	"GPLv2"
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# distcc (pump) requires python3...
PYTHON_VERSION=3.4

COMPONENT_PREP_ACTION = \
    ( cd $(@D) && ./autogen.sh )

COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_POST_INSTALL_ACTION =	( \
    cd $(PROTOUSRSHAREMAN1DIR) && \
    for F in *.gz ; do \
        [ -s "$$F" ] && gzip -cd < "$$F" > `basename "$$F" .gz` ; \
    done )

# Find the <config.h> as included by some sources - must be before GCC plugin dir
CFLAGS += -I$(BUILD_DIR_$(BITS))/src
CXXFLAGS += -I$(BUILD_DIR_$(BITS))/src
CPPFLAGS += -I$(BUILD_DIR_$(BITS))/src

# Where to look for libiberty header and .a file: the GCC p5m manifest
# is explicit about the paths - down to i386'iness of them. Cool :\
# NOTE: Match this with GCC_ROOT, currently referring to "4.9"
CFLAGS += -I$(GCC_ROOT)/lib/gcc/i386-pc-solaris2.11/4.9.3/plugin/include -L$(GCC_ROOT)/lib

CXXFLAGS+=	$(CPP_LARGEFILE)
CFLAGS +=	$(CPP_LARGEFILE)

CFLAGS +=	-D_GNU_SOURCE -D__EXTENSIONS__
CXXFLAGS +=	-D_GNU_SOURCE -D__EXTENSIONS__

CXXFLAGS +=	-D_POSIX_PTHREAD_SEMANTICS
CFLAGS +=	-D_POSIX_PTHREAD_SEMANTICS

COMPONENT_INSTALL_ARGS +=	DESTDIR="$(PROTO_DIR)"
COMPONENT_INSTALL_ARGS +=	PYTHON="$(PYTHON)"

CONFIGURE_ENV +=	PYTHON="$(PYTHON)"
INSTALL_ENV   +=	PYTHON="$(PYTHON)"

CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)

# use getaddrinfo, getnameinfo, etc :
CONFIGURE_OPTIONS +=	--enable-rfc2553

# GSS-API mutual auth
### Are these needed? Or just seemed relevant because they are *gss*?
###REQUIRED_PACKAGES +=	system/kernel/security/gss service/security/gss
REQUIRED_PACKAGES +=	system/library/security/gss
CFLAGS += -Wno-error=unused-but-set-variable
CONFIGURE_OPTIONS +=	--with-auth

# Support mDNS "zeroconf" peer discovery/announcement
# NOTE: May require some source chizeling, skip in first recipe iterations
#CONFIGURE_OPTIONS +=	--with-avahi
CONFIGURE_OPTIONS +=	--without-avahi

# GUIs for monitoring
CONFIGURE_OPTIONS +=	--with-gnome
CONFIGURE_OPTIONS +=	--with-gtk

# common targets
# NOTE: Currently GCC libiberty is only published as a 32-bit .a file
# so we can only build a 32-bit distcc
build:          $(BUILD_32)

install:        $(INSTALL_32)
	$(GSED) -e 's:\#!/usr/bin/env python:\#!/usr/bin/python$(PYTHON_VERSION):' \
	    < $(COMPONENT_DIR)/files/distcc-top.py \
	    > $(PROTOUSRBINDIR)/distcc-top && $(CHMOD) +x $(PROTOUSRBINDIR)/distcc-top

test:           $(NO_TESTS)

# The python version required for distcc-top.py seems to be "any 2.x"
# so we do not add one to REQUIRED_PACKAGES (a system with IPS will
# likely have a suitable Python anyway) and so we just specify the
# special one needed for distcc-pump.
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libgnome
REQUIRED_PACKAGES += library/desktop/libgnomeui
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/popt
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
