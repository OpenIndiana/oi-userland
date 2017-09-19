#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2013  Erol Zavidic. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libxml2
COMPONENT_VERSION=	2.9.5
COMPONENT_PROJECT_URL=	http://xmlsoft.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:4031c1ecee9ce7ba4f313e91ef6284164885cdb69937a123f6a83bb6a72dcd38
COMPONENT_ARCHIVE_URL=	ftp://xmlsoft.org/libxml2/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libxml

# W3C XML Conformance Test Suites
COMPONENT_ARCHIVE_1= xmlts20130923.tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:9b61db9f5dbffa545f4b8d78422167083a8568c59bd1129f94138f936cf6fc1f
COMPONENT_ARCHIVE_URL_1= http://www.w3.org/XML/Test/$(COMPONENT_ARCHIVE_1)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/lint-libraries.mk

CFLAGS +=	$(CPP_LARGEFILES)
LDFLAGS +=	$(CC_BITS) $(LD_Z_DEFS) $(LD_Z_TEXT) -lpthread

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-threads
CONFIGURE_OPTIONS += --with-python=$(PYTHON.$(BITS))
CONFIGURE_OPTIONS += --with-python-install-dir=$(PYTHON_VENDOR_PACKAGES)

#COMPONENT_PREP_ACTION += (cd $(@D) ; cp ../mapfile libxml2.syms )
# autoreconf breaking libtool
COMPONENT_PREP_ACTION += (cd $(@D) ; cp ../mapfile libxml2.syms ; autoreconf -if)

# After we have configured, make a copy of the python bits so we
# can build and test separate python 3.4 support.
COMPONENT_POST_CONFIGURE_ACTION = (cd $(@D) ; cp -rp python python3.4 ; \
    $(GSED) -i -e 's|-lpython2[.]7|-lpython3.4m|' \
     -e 's|usr/bin/$(MACH64)/python2[.]7|usr/bin/python3.4m|' \
     -e 's|usr/include/python2[.]7|usr/include/python3.4m|' \
     -e 's/2[.]7/3.4/g' `find python3.4 -name Makefile`)

# After we have built/installed libxml2, build/install the python
# support for python 3.4
COMPONENT_POST_INSTALL_ACTION = \
    (cd $(@D)/python3.4 ; $(GMAKE) $(COMPONENT_INSTALL_ARGS) install)

# It's nice to test also python 3.4 module.
COMPONENT_POST_TEST_ACTION = \
    (cd $(@D)/python3.4 ; $(GMAKE) $(COMPONENT_TEST_ARGS) test)

# We have patched our 64 bit python so it will search for modules only in
# '64/' directories. Now we need to provide one. Otherwise python will
# end up using libxml2mod.so installed on system.
$(BUILD_DIR)/$(MACH64)/.tested: COMPONENT_PRE_TEST_ACTION = ( \
  $(MKDIR) $(@D)/python/.libs/64; \
  $(SYMLINK) ../libxml2mod.so $(@D)/python/.libs/64/libxml2mod.so; \
  $(MKDIR) $(@D)/python/.libs/64 $(@D)/python3.4/.libs/64; \
  $(SYMLINK) ../libxml2mod.so $(@D)/python3.4/.libs/64/libxml2mod.so);

COMPONENT_PRE_TEST_ACTION += \
    (cd $(@D) ; gtar xf $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE_1));

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^\#\#/p" ' \
	'-e "/^Making/p" ' \
	'-e "/^Ran/p" ' \
	'-e "/^Test/p" ' \
	'-e "/^Total/p" ' \
	'-e "/errors were expected/p" '

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)
	$(PYTHON.2.7.32) -m compileall $(PROTO_DIR)/usr/lib/python2.7/vendor-packages
	$(PYTHON.3.4.32) -m compileall $(PROTO_DIR)/usr/lib/python3.4/vendor-packages

test:		$(TEST_32_and_64)
