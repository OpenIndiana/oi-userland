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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libxml2
COMPONENT_VERSION=	2.9.4
COMPONENT_PROJECT_URL=	http://xmlsoft.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:ffb911191e509b966deb55de705387f14156e1a56b21824357cdf0053233633c
COMPONENT_ARCHIVE_URL=	ftp://xmlsoft.org/libxml2/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libxml

# W3C XML Conformance Test Suites
COMPONENT_ARCHIVE_1= xmlts20080827.tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:96151685cec997e1f9f3387e3626d61e6284d4d6e66e0e440c209286c03e9cc7
COMPONENT_ARCHIVE_URL_1= http://www.w3.org/XML/Test/$(COMPONENT_ARCHIVE_1)

TPNO=			29079

SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_32_and_64)
include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_ENABLE)

CFLAGS +=	$(CPP_LARGEFILES)
LDFLAGS +=	$(LD_Z_DEFS) $(LD_Z_TEXT) -lpthread

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-threads
CONFIGURE_OPTIONS += --with-python=$(PYTHON.$(BITS))
CONFIGURE_OPTIONS += --with-python-install-dir=$(PYTHON_VENDOR_PACKAGES)
# Cannot link to lzma since it's not in /lib and install media still has separate /usr.
CONFIGURE_OPTIONS += --without-lzma

COMPONENT_PREP_ACTION += (cd $(@D) ; cp ../mapfile libxml2.syms ; autoreconf -if)

# After we have configured, make a copy of the python bits so we can build and
# test separate python 2.7 and 3.4 support.  Note for 3.4: .py files need to
# go in .../vendor-packages (whether building 32-bit or 64-bit) whereas .so
# files need to go in .../vendor-packages for 32-bit but .../vendor-packages/64
# for 64-bit.  For 2.7, Python is built 32- and 64-bit, so .py files end
# up in both places even though only the 32-bit location is needed, but the
# superfluous files in the proto area are harmless; meanwhile, the .so files
# end up in their proper 32- and 64-bit locations.  But Python 3.4 is built
# 64-bit only, so we have an extra sed edit below to force the .py files into
# the 32-bit location and we manually specify the 32-bit path in the manifest
# to correct for the .so file being installed there instead of the 64-bit path
# where it belongs.  Further, Python 3.4 needs an extra 'm' on the link and
# include paths, plus a tweak to the binary path; see PEP 3149 for details.
COMPONENT_POST_CONFIGURE_ACTION += \
    (cd $(@D) ; cp -rp python python3.4 ; \
    $(GSED) -i -e 's|-lpython2[.]7|-lpython3.4m|' \
     -e 's|usr/bin/$(MACH64)/python2[.]7|usr/bin/python3.4m|' \
     -e 's|usr/include/python2[.]7|usr/include/python3.4m|' \
     -e 's/2[.]7/3.4/g' -e 's|vendor-packages/64|vendor-packages|' \
     `find python3.4 -name Makefile` ; \
)

# It's also nice to test python 3.4 modules.
COMPONENT_POST_TEST_ACTION += \
    ( if [ $(BITS) -eq 64 ]; then \
	cd $(@D)/python3.4 ; \
	$(GMAKE) $(COMPONENT_TEST_ARGS) test ; \
     else \
        true ; \
     fi )

# We have patched our 64 bit python so it will search for modules only in
# '64/' directories. Now we need to provide one. Otherwise python will
# end up using libxml2mod.so installed on system.
$(BUILD_DIR)/$(MACH64)/.tested: COMPONENT_PRE_TEST_ACTION = ( \
    $(MKDIR) $(@D)/python/.libs/64 \
             $(@D)/python3.4/.libs/64; \
    $(SYMLINK) ../libxml2mod.so $(@D)/python/.libs/64/libxml2mod.so; \
    $(SYMLINK) ../libxml2mod.so $(@D)/python3.4/.libs/64/libxml2mod.so);

COMPONENT_PRE_TEST_ACTION += \
    (cd $(@D) ; gtar xf $(COMPONENT_DIR)/$(COMPONENT_ARCHIVE_1));

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS = \
	'-e "s/^make\[.*$$/[EnD]/" ' \
	'-e "/^\#\# XML regression tests/,/^\[EnD\]/p" ' \
	'-e "/^\#\# running Python regression tests/,/^\[EnD\]/p" ' \
        '-e "/.*/d" '

COMPONENT_SYSTEM_TEST_TARGETS = system-test 
COMPONENT_PRE_SYSTEM_TEST_ACTION += $(COMPONENT_PRE_TEST_ACTION)

COMPONENT_POST_INSTALL_ACTION.32 += \
	$(PYTHON.2.7.32) -m compileall $(PROTOUSRLIBDIR)/python2.7/vendor-packages;

# After we have built/installed libxml2, build/install the python
# support for python 3.4
COMPONENT_POST_INSTALL_ACTION.64 += \
	cd $(@D)/python3.4 ; \
	$(GMAKE) $(COMPONENT_INSTALL_ARGS) install ; \
	$(PYTHON.3.4.64) -m compileall $(PROTOUSRLIBDIR)/python3.4/vendor-packages;

REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/math
