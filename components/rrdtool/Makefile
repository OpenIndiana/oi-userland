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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         rrdtool
COMPONENT_VERSION=      1.4.9
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:3e2826e0d60aaf85313da35b3c0d3a926748fe482b4ada766a325a83b60125cc
COMPONENT_ARCHIVE_URL=  http://oss.oetiker.ch/rrdtool/pub/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://oss.oetiker.ch/rrdtool/
COMPONENT_BUGDB=        utility/rrdtool
TPNO=                   21430 

PYTHON_VERSION=         2.7
PYTHON_VERSIONS=        2.7

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=$(dir $(CC)):/usr/bin:/usr/sbin:/usr/gnu/bin

PERL_VERSION.32 = 5.12
PERL_VERSION.64 = 5.16
PERL_VERSION = $(PERL_VERSION.$(BITS))

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PREP_ACTION = ( cd $(@D); autoconf -f)

CONFIGURE_OPTIONS  += --enable-perl 
CONFIGURE_OPTIONS  += --enable-python
CONFIGURE_OPTIONS  += --disable-ruby
CONFIGURE_OPTIONS  += --enable-tcl
CONFIGURE_OPTIONS  += --enable-static=no
CONFIGURE_OPTIONS  +=   CC="$(CC) $(CC_BITS)" 
CONFIGURE_OPTIONS  +=   CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=   LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS  +=   PERL=/usr/perl5/$(PERL_VERSION)/bin/perl
CONFIGURE_OPTIONS  +=   POD2MAN=/usr/perl5/$(PERL_VERSION)/bin/pod2man
CONFIGURE_OPTIONS  +=   POD2HTML=/usr/perl5/$(PERL_VERSION)/bin/pod2html
CONFIGURE_OPTIONS  +=   PERLCC="\"$(CC) $(CC_BITS)\""
CONFIGURE_OPTIONS  +=   PERLCCFLAGS="\"$(CFLAGS)\""
CONFIGURE_OPTIONS  +=   PERLLD="\"$(CC) $(CC_BITS)\""
CONFIGURE_OPTIONS  +=   PERLLIB=/usr/perl5/$(PERL_VERSION)/lib
CONFIGURE_OPTIONS  +=   PERLINSTALLMAN3DIR=/usr/share/man/man3
CONFIGURE_OPTIONS  +=   PERLINSTALLSITEMAN3DIR=/usr/share/man/man3
CONFIGURE_OPTIONS  +=   PERLINSTALLVENDORMAN3DIR=/usr/share/man/man3
CONFIGURE_OPTIONS +=    am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_OPTIONS +=    am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_OPTIONS  +=   PYTHON=$(PYTHON.$(PYTHON_VERSION).$(BITS))

$(CONFIGURE_64): CONFIGURE_OPTIONS  +=   LUARRDLIBDIR=64

PYTHON_ENV  =   CC="$(CC)"
PYTHON_ENV +=   CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += $(PYTHON_ENV)
COMPONENT_INSTALL_ENV += $(PYTHON_ENV)

PKG_MACROS         +=   P_ARCH=$(shell arch)

ASLR_MODE	    =   $(ASLR_ENABLE)

PKG_MACROS +=  PYVER=$(PYTHON_VERSION)
PKG_MACROS +=  PYV=$(shell echo $(PYTHON_VERSION) | tr -d .)

# common targets
configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)
		
BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += runtime/python-27
