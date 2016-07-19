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

COMPONENT_NAME=         rrdtool
COMPONENT_VERSION=      1.6.0
COMPONENT_ARCHIVE_HASH= sha256:cd948e89cd2d8825fab4a6fb0323f810948d934af7d92c9ee8b5e9e1350e52d7
COMPONENT_ARCHIVE_URL=  http://oss.oetiker.ch/rrdtool/pub/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://oss.oetiker.ch/rrdtool/
TPNO=                   29102 

PYTHON_VERSION=         2.7
PYTHON_VERSIONS=        2.7

TEST_TARGET= $(NO_TESTS)
include ../../make-rules/common.mk

PATH=$(dir $(CC)):$(USRBINDIR):$(USRSBINDIR):$(GNUBIN)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PREP_ACTION = ( cd $(@D); autoconf -f)
PERLVERDIR=	$(USRDIR)/perl5/$(PERL_VERSION)
PERLBINDIR=	$(PERLVERDIR)/bin
PERLLIBDIR=	$(PERLVERDIR)/lib

CONFIGURE_OPTIONS  += --enable-python
CONFIGURE_OPTIONS  += --disable-ruby
CONFIGURE_OPTIONS  += --enable-tcl
CONFIGURE_OPTIONS  += --disable-static
CONFIGURE_OPTIONS  +=   CC="$(CC) $(CC_BITS)" 
CONFIGURE_OPTIONS  +=   POD2MAN=$(PERLBINDIR)/pod2man
CONFIGURE_OPTIONS  +=   POD2HTML=$(PERLBINDIR)/pod2html
CONFIGURE_OPTIONS  +=   am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_OPTIONS  +=   am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_OPTIONS  +=   PYTHON=$(PYTHON.$(PYTHON_VERSION).$(BITS))

CONFIGURE_OPTIONS.32 += --disable-perl
CONFIGURE_OPTIONS.64 += --enable-perl
CONFIGURE_OPTIONS.64 += LUARRDLIBDIR=64
CONFIGURE_OPTIONS.64 += PERL=$(PERLBINDIR)/perl
CONFIGURE_OPTIONS.64 += PERLCC="\"$(CC) $(CC_BITS)\""
CONFIGURE_OPTIONS.64 += PERLCCFLAGS="\"$(CFLAGS)\""
CONFIGURE_OPTIONS.64 += PERLLD="\"$(CC) $(CC_BITS)\""
CONFIGURE_OPTIONS.64 += PERLLIB=$(PERLLIBDIR)
CONFIGURE_OPTIONS.64 += PERLINSTALLMAN3DIR=$(USRSHAREMAN3DIR)
CONFIGURE_OPTIONS.64 += PERLINSTALLSITEMAN3DIR=$(USRSHAREMAN3DIR)
CONFIGURE_OPTIONS.64 += PERLINSTALLVENDORMAN3DIR=$(USRSHAREMAN3DIR)

PYTHON_ENV  =   CC="$(CC)"
PYTHON_ENV +=   CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += $(PYTHON_ENV)
COMPONENT_INSTALL_ENV += $(PYTHON_ENV)

PKG_MACROS +=  PYVER=$(PYTHON_VERSION)
PKG_MACROS +=  PYV=$(shell echo $(PYTHON_VERSION) | tr -d .)

REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += runtime/python-27
