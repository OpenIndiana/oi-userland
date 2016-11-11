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

COMPONENT_NAME=		graphviz
COMPONENT_VERSION=	2.28.0
COMPONENT_PROJECT_URL=	http://www.graphviz.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:d3aa7973c578cae4cc26d9d6498c57ed06680cab9a4e940d0357a3c6527afc76
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)pub/graphviz/stable/SOURCES/$(COMPONENT_ARCHIVE)

TPNO=			17707

# publish for only one version of perl
PERL_VERSIONS = $(PERL_VERSION)

# There are tests, but they fail consistently because the test samples are out
# of date and not generated with a known configuration.  See
# http://graphviz.org/bugs/b2063.html
TEST_TARGET= $(SKIP_TEST)

ifneq ($(BUILD_TYPE), evaluation)
# We want to build a couple of extra things after the installs are done, so set
# the install targets appropriately.
INSTALL_TARGET = $(INSTALL_$(MK_BITS))
INSTALL_TARGET += $(PROTOUSRLIBDIR)/graphviz/config6
INSTALL_TARGET += $(PROTO_DIR)/$(PYTHON.2.7.VENDOR_PACKAGES)/gv.pyc
endif

# Depends on newer cairo, which cannot be updated in S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk

PATH =		/usr/php/5.6/bin:/usr/bin:/usr/gnu/bin

# GMP header files for the guile extension (no --with- flag)
# The guile build is broken with studio (15732452), so we disable this for now.
# CPPFLAGS +=	-I/usr/include/gmp
# Java header files (--with-javaincludedir allows for only one directory)
CPPFLAGS +=	-I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/solaris
# PHP header files (no --with- flag)
CPPFLAGS +=	$(shell PATH=$(PATH) php-config --includes)
CXX +=		$(studio_NORUNPATH)
CXX +=		-std=sun03

# Make sure to use the right python, depending on the 32/64-bit build.
CONFIGURE_ENV +=	PYTHON27=$(PYTHON.2.7)
CONFIGURE_OPTIONS +=	--without-included-ltdl
CONFIGURE_OPTIONS +=	--enable-python=no
CONFIGURE_OPTIONS +=	--enable-python27=yes
CONFIGURE_OPTIONS +=	--x-libraries=$(CONFIGURE_LIBDIR.$(BITS))

COMPONENT_BUILD_ARGS += 	GREP=$(USRBINDIR)/ggrep

ifneq ($(BUILD_TYPE), evaluation)
# perl, ruby, php ship 64-bit only.
$(CONFIGURE_32): CONFIGURE_OPTIONS +=	--enable-perl=no
$(CONFIGURE_32): CONFIGURE_OPTIONS +=	--enable-ruby=no
$(CONFIGURE_32): CONFIGURE_OPTIONS +=	--enable-php=no
$(CONFIGURE_64): CONFIGURE_ENV +=	PERL=$(PERL)
$(CONFIGURE_64): CONFIGURE_ENV +=	RUBY=$(RUBY.2.1)
$(INSTALL_64): COMPONENT_INSTALL_ARGS += PHP_INSTALL_DIR=$(shell PATH=$(PATH) php-config --extension-dir)
# tcl ships both 32 and 64 bit, but even though /usr/bin/tclsh is 64-bit, there
# is no place to stick 64-bit modules, so skip it.  On the other hand, make
# sure to find the right tcl bits when building 32-bit.
$(CONFIGURE_64): CONFIGURE_OPTIONS +=	--enable-tcl=no
$(CONFIGURE_32): CONFIGURE_OPTIONS +=	--with-tclsh=$(USRBINDIR)/$(MACH32)/tclsh
$(CONFIGURE_32): CONFIGURE_ENV += 	TCLCONFIG=$(USRLIBDIR)/tclConfig.sh
# Put the 64-bit lua module in a 64-bit directory.
$(INSTALL_32): COMPONENT_INSTALL_ARGS += LUA_INSTALL_DIR=$(USRLIBDIR)/lua/5.2
$(INSTALL_64): COMPONENT_INSTALL_ARGS += LUA_INSTALL_DIR=$(USRLIBDIR)/lua/5.2/64
# Use GNU ln, which supports the -r (--relative) option.
COMPONENT_INSTALL_ARGS += LN_S="gln -s"
endif

# Create the config file once the 32-bit build is complete.  This runs the bits
# we just built, so we have to set a handful of variables to the right place.
# The 32-bit executables are in their own directory, so we have to point to
# that version of dot explicitly.
$(PROTOUSRLIBDIR)/graphviz/config6: $(INSTALL_32)
	env LD_LIBRARY_PATH=$(PROTOUSRLIBDIR) GVBINDIR=$(PROTOUSRLIBDIR)/graphviz \
		$(PROTOUSRBINDIR)/$(MACH32)/dot -c

# Once the build is complete, compile the .py file.  There's no need to compile
# the one in the "64" directory, so don't recurse.  And make sure that the
# build path doesn't get embedded in the .pyc file.
$(PROTO_DIR)/$(PYTHON.2.7.VENDOR_PACKAGES)/gv.pyc: $(INSTALL_32)
	$(PYTHON.2.7.32) -m compileall -l -d $(PYTHON.2.7.VENDOR_PACKAGES) \
		$(PROTO_DIR)/$(PYTHON.2.7.VENDOR_PACKAGES)

PKG_MACROS += PERL_PKG=$(PERL_PKG)
PKG_MACROS += PERL_VERSION_NODOT=$(PERL_VERSION_NODOT)

# The test infrastructure doesn't run in a VPATHed environment.
COMPONENT_PRE_TEST_ACTION = \
	(cd $(@D)/rtest; ln -s $(SOURCE_DIR)/rtest/* .)

REQUIRED_PACKAGES += image/graphviz
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += print/filter/ghostscript
REQUIRED_PACKAGES += print/filter/ghostscript-core
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/ocaml
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += runtime/ruby-21
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/php-56
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
