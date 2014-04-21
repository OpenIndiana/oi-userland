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
#

include ../../make-rules/shared-macros.mk

PATH=$(dir $(CC)):$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin

COMPONENT_NAME=		subversion
COMPONENT_VERSION=	1.7.5
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://subversion.apache.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:cb102a437335a8921f00cef9bf730d84527713f1a5091e3e1eb2f16402f85dc1
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/subversion/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/svn

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL = 0
PYMODS = client core delta fs ra repos wc
PLMODS= Fs Core Wc Client Repos Ra Delta
JAVA_ROOT = $(JAVA6_HOME)
#PERL_VERSION.32 = 5.12
#PERL_VERSION.64 = 5.16
#PERL_VERSION = $(PERL_VERSION.$(BITS))
#PERL = $(PERL.$(PERL_VERSION))
GNUCP = /usr/gnu/bin/cp

# because we can't seem to get -norunpath to the java bindings build any
# other way.
#CXX += $(studio_NORUNPATH)
#CFLAGS += -features=extensions
#CFLAGS += -xustr=ascii_utf16_ushort -xcsi
#CXXFLAGS += -features=nestedaccess,tmplife,tmplrefstatic
#CXXFLAGS += -template=geninlinefuncs
#CXXFLAGS += -verbose=template
#CXXFLAGS += -xustr=ascii_utf16_ushort
CXXFLAGS += $(CC_PIC)
#CXXFLAGS += -mt -D_REENTRANT -DNDEBUG -DSOLARIS
CXXFLAGS += $(CPP_LARGEFILES)
CFLAGS += `pkg-config --cflags neon`
CFLAGS += $(CPP_LARGEFILES)

#PERL_VERSION_12 = 5.12
#PERL_VERSION_16 = 5.16
#PERL_ARCH_12_i386 = i86pc-solaris-64int
#PERL_ARCH_16_i386 = i86pc-solaris-64
#PERL_ARCH_12_sparc = sun4-solaris-64int
#PERL_ARCH_16_sparc = sun4-solaris-64
#PERL_ARCH_12 = $(PERL_ARCH_12_$(MACH))
#PERL_ARCH_16 = $(PERL_ARCH_16_$(MACH))

# Let's write some post-configure hacks
COMPONENT_POST_CONFIGURE_ACTION = \
    ( $(CLONEY) $(SOURCE_DIR) $(@D) ; \
    cd $(SOURCE_DIR) ; \
	$(PYTHON.$(BITS)) ./build/transform_sql.py ./subversion/libsvn_fs_fs/rep-cache-db.sql < ./subversion/libsvn_fs_fs/rep-cache-db.sql > $(BUILD_DIR_$(BITS))/subversion/libsvn_fs_fs/rep-cache-db.h 2>&1 )

COMPONENT_BUILD_TARGETS.32 = all swig-py swig-pl javahl
COMPONENT_BUILD_TARGETS.64 = all swig-py javahl
COMPONENT_INSTALL_TARGETS.32 = install install-lib \
			    install-swig-pl install-swig-py \
			    install-javahl install-javahl-lib \
			    install-mods-shared \
			    install-bin install-docs
COMPONENT_INSTALL_TARGETS.64 = install install-lib \
			    install-swig-py \
			    install-javahl install-javahl-lib \
			    install-mods-shared \
			    install-bin install-docs


COMPONENT_BUILD_TARGETS = $(COMPONENT_BUILD_TARGETS.$(BITS))
COMPONENT_INSTALL_TARGETS = $(COMPONENT_INSTALL_TARGETS.$(BITS))

CONFIGURE_ENV += PYTHON="$(PYTHON.$(BITS))"
CONFIGURE_ENV += PYMODS="$(PYMODS)"
CONFIGURE_ENV += PYTHONPATH="$(PYTHON_VENDOR_PACKAGES.$(BITS))"
CONFIGURE_ENV += JAVA_ROOT="$(JAVA_ROOT)"
CONFIGURE_ENV += PERL="$(PERL)"
CONFIGURE_ENV += PLMODS="$(PLMODS)"
CONFIGURE_ENV += LD_OPTIONS="$(LD_OPTIONS)"

LIBSVNDIR.32 = $(CONFIGURE_PREFIX)/lib/svn
LIBSVNDIR.64 = $(CONFIGURE_PREFIX)/lib/svn/$(MACH64)

APR-CONFIG.32 = /usr/apr/bin/apr-1-config
APR-CONFIG.64 = /usr/apr/bin/$(MACH64)/apr-1-config
APU-CONFIG.32 = /usr/apr-util/bin/apu-1-config
APU-CONFIG.64 = /usr/apr-util/bin/$(MACH64)/apu-1-config
APXS.32 = /usr/apache2/2.2/bin/apxs
APXS.64 = /usr/apache2/2.2/bin/$(MACH64)/apxs

# Let's make noise just because we have to override --libdir
CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --sbindir=$(CONFIGURE_SBINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir=$(LIBSVNDIR.$(BITS))
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --enable-shared 
#CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-libtool-lock 
CONFIGURE_OPTIONS += --disable-neon-version-check
CONFIGURE_OPTIONS += --disable-experimental-libtool
CONFIGURE_OPTIONS += --with-apxs=/usr/apache2/2.2/bin/apxs
CONFIGURE_OPTIONS += --with-ssl 
CONFIGURE_OPTIONS += --with-zlib=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-jdk=$(JAVA_ROOT)
CONFIGURE_OPTIONS += --with-apr=/usr/apr
CONFIGURE_OPTIONS += --with-apr-util=/usr/apr-util
CONFIGURE_OPTIONS += --enable-nls
CONFIGURE_OPTIONS += --disable-mod-activation
CONFIGURE_OPTIONS += --enable-javahl
CONFIGURE_OPTIONS += --with-swig
CONFIGURE_OPTIONS += --with-neon=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-apr=$(APR-CONFIG.$(BITS))
CONFIGURE_OPTIONS += --with-apr-util=$(APU-CONFIG.$(BITS))
CONFIGURE_OPTIONS += --with-apxs=$(APXS.$(BITS))

# Swig overwrites the 32-bit directory with 64-bit objects.
# So we work around that.
COMPONENT_POST_INSTALL_ACTION += \
    ( cd $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION) ; \
	$(RM) -rf vendor-packages-$(BITS) ; \
	$(MV) vendor-packages vendor-packages-$(BITS) ; \
	$(MKDIR) -p vendor-packages ; \
	$(MKDIR) -p vendor-packages/64 ; \
	if test -d vendor-packages-64 ; then \
	    $(GNUCP) -rpd vendor-packages-64/libsvn vendor-packages/64/ ; \
	    $(GNUCP) -rpd vendor-packages-64/svn vendor-packages/64/ ; \
	    $(GNUCP) -rpd vendor-packages-32/libsvn vendor-packages/ ; \
	    $(GNUCP) -rpd vendor-packages-32/svn vendor-packages/ ; \
	fi ; )

#ASLR_MODE=$(ASLR_ENABLE)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk

