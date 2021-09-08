#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2021 Klaus Ziegler
#

BUILD_STYLE = setup.py
BUILD_BITS=NO_ARCH
PYTHON3_ONLY=yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           py3c
COMPONENT_VERSION=        1.3.1
COMPONENT_SUMMARY=	  port C extensions to Python 3
COMPONENT_PROJECT_URL=    https://py3c.readthedocs.io/en/latest/
COMPONENT_SRC=		  $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	  $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	  https://github.com/encukou/py3c/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:f3e138623a87cde2cd7d8e98b51447e033d43a3f639c5054185c859fa1888727
COMPONENT_FMRI=           library/python/py3c
COMPONENT_CLASSIFICATION= Development/Python
COMPONENT_LICENSE=        MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/setup.py.mk

build: $(BUILD_NO_ARCH)

install: $(INSTALL_NO_ARCH)

#
# if upgrading py3c package, please double
# check the contents of both:
#
# build/prototype/<uname -p>/usr/lib/python3.x/*
# build/prototype/<uname -p>/usr/include/python3.x/*
#
# by hashing out the next 2(4) COMPONENT_POST_INSTALL_ACTION lines,
# as of version 1.3.1 there isn't much usefull python stuff in there.
# The main purpose for which the py3c package is needed for, is to be
# able to compile subversion 1.14.1 and newer, that's why we need
# the include files from py3c in the standard location, so they
# can be used by compilers and or all versions of python.

COMPONENT_POST_INSTALL_ACTION += \
	$(RM) -r $(PROTO_DIR)$(USRINCDIR)/python* ;
COMPONENT_POST_INSTALL_ACTION += \
	$(RM) -r $(PROTO_DIR)$(USRLIBDIR)/python* ;

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) -p $(PROTO_DIR)$(USRINCDIR)/py3c ;
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) -p $(PROTO_DIR)$(USRLIBDIR)/pkgconfig ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/include/py3c.h $(PROTO_DIR)$(USRINCDIR) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) -rp $(COMPONENT_SRC)/include/py3c/* $(PROTO_DIR)$(USRINCDIR)/py3c ;
COMPONENT_POST_INSTALL_ACTION += \
	sed \
		-e '/^\# Template/d' \
		-e '/^\# Requires/d' \
		-e '/^\#Requires/d' \
		-e 's\#@includedir@\#/usr/include\#g' $(COMPONENT_SRC)/py3c.pc.in > \
	$(PROTO_DIR)$(USRLIBDIR)/pkgconfig/py3c.pc ;

# Build requirements.
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
