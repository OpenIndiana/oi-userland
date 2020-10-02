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

BUILD_BITS=32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libxml2
COMPONENT_VERSION=	2.9.9
COMPONENT_REVISION=	4
COMPONENT_PROJECT_URL=	http://xmlsoft.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:94fb70890143e3c6549f265cee93ec064c80a84c42ad0f23e85ee1fd6540a871
COMPONENT_ARCHIVE_URL=	ftp://xmlsoft.org/libxml2/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libxml

# W3C XML Conformance Test Suites
COMPONENT_ARCHIVE_1= xmlts20080827.tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:96151685cec997e1f9f3387e3626d61e6284d4d6e66e0e440c209286c03e9cc7
COMPONENT_ARCHIVE_URL_1= http://www.w3.org/XML/Test/$(COMPONENT_ARCHIVE_1)

include $(WS_MAKE_RULES)/common.mk

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
# can build and test separate python 3.5 support.
COMPONENT_POST_CONFIGURE_ACTION = ( \
    cd $(@D) ; cp -rp python python3.5 ; \
    $(GSED) -i -e 's|-lpython2[.]7|-lpython3.5m|' \
     -e 's|usr/bin/$(MACH64)/python2[.]7|usr/bin/python3.5m|' \
     -e 's|usr/include/python2[.]7|usr/include/python3.5m|' \
     -e 's/2[.]7/3.5/g' -e 's|vendor-packages/64|vendor-packages|' \
     `find python3.5 -name Makefile`;)

# After we have built/installed libxml2, build/install the python
# support for python 3.5 
COMPONENT_POST_INSTALL_ACTION.64 = \
    cd $(@D)/python3.5 ; $(GMAKE) $(COMPONENT_INSTALL_ARGS) install ;

# It's nice to test also python 3.5 modules (LC_ALL is set to avoid test failure).
COMPONENT_POST_TEST_ACTION.64 = \
    cd $(@D)/python3.5; \
    LC_ALL=en_US.UTF-8 $(GMAKE) $(COMPONENT_TEST_ARGS) test

# We have patched our 64 bit python so it will search for modules only in
# '64/' directories. Now we need to provide one. Otherwise python will
# end up using libxml2mod.so installed on system.
$(BUILD_DIR)/$(MACH64)/.tested: COMPONENT_PRE_TEST_ACTION = ( \
    $(MKDIR) $(@D)/python/.libs/64 \
             $(@D)/python3.5/.libs/64; \
    $(SYMLINK) ../libxml2mod.so $(@D)/python/.libs/64/libxml2mod.so; \
    $(SYMLINK) ../libxml2mod.so $(@D)/python3.4/.libs/64/libxml2mod.so; \
    $(SYMLINK) ../libxml2mod.so $(@D)/python3.5/.libs/64/libxml2mod.so );

COMPONENT_PRE_TEST_ACTION += \
    (cd $(@D) ; gtar xf $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE_1));

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS = \
	'-e "s/^make\[.*$$/[EnD]/" ' \
	'-e "/^\#\# XML regression tests/,/^\[EnD\]/p" ' \
	'-e "/^\#\# running Python regression tests/,/^\[EnD\]/p" ' \
	'-e "/.*/d" '

COMPONENT_POST_INSTALL_ACTION.32 += \
        $(PYTHON.2.7.32) -m compileall $(PROTOUSRLIBDIR)/python2.7/vendor-packages; \

COMPONENT_POST_INSTALL_ACTION.64 += \
        $(PYTHON.3.5.64) -m compileall $(PROTOUSRLIBDIR)/python3.5/vendor-packages;

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
