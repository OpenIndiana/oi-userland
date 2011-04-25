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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		subversion
COMPONENT_VERSION=	1.6.16
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:e957da04252d4d7e0fff72fdcf72c715bfbaa393
COMPONENT_ARCHIVE_URL=	http://subversion.tigris.org/downloads/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL = 0

# We need to remove these environment files when
# apache2, apr and apr-util move to Userland
include $(COMPONENT_DIR)/apache.build.env
include $(COMPONENT_DIR)/apr.build.env
include $(COMPONENT_DIR)/apr-util.build.env

PYMODS = client core delta fs ra repos wc

ARCH = $(shell arch)
PERL = /usr/perl5/bin/perl
PLVER = 5.8.4
PLARCH = $(ARCH)-solaris-64int
PLDIR = /usr/perl5/$(PLVER)
PLVENDORDIR = /usr/perl5/vendor_perl/$(PLVER)
PLVENDORARCHDIR = $(PLVENDORDIR)/$(PLARCH)
PLMODS= Fs Core Wc Client Repos Ra Delta
SWIGPROG = /usr/bin/swig
ELFEDIT = /usr/bin/elfedit
JAVA_ROOT = $(JAVA_HOME)
PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig
PROTOUSRSHAREJAVADIR = $(PROTOUSRSHAREDIR)/lib/java
SVN_LDFLAGS = -R/usr/lib/svn:$(APR_USR_PREFIX)/lib:$(APR_UTIL_USR_PREFIX)/lib \
		-L$(APR_USR_PREFIX)/lib \
		-L$(APR_UTIL_USR_PREFIX)/lib \
		-lc -lm -lsocket -lresolv -lnsl -lgen

CFLAGS += -Xc -xnorunpath $(CC_BITS)
CFLAGS += -features=extinl,extensions
CFLAGS += -xustr=ascii_utf16_ushort -xcsi
CFLAGS += $(studio_C99_ENABLE)
CFLAGS += $(CPP_XPG6MODE)
CXXFLAGS += $(CC_BITS)
CXXFLAGS += -features=except,rtti,export,extensions,nestedaccess,tmplife,tmplrefstatic
CXXFLAGS += -instances=global
CXXFLAGS += -template=geninlinefuncs
CXXFLAGS += -verbose=template
CXXFLAGS += -xustr=ascii_utf16_ushort
CXXFLAGS += -norunpath
CXXFLAGS += $(PICFLAG)
CXXFLAGS += -mt -D_REENTRANT -DNDEBUG -DSOLARIS
CXXFLAGS += $(studio_cplusplus_C99_ENABLE)
CXXFLAGS += $(CPP_XPG5MODE)
CPPFLAGS += `pkg-config --cflags neon`
CPPFLAGS += $(CPP_LARGEFILES) $(CPP_POSIX)
CPPFLAGS += -DNDEBUG -DSOLARIS

# Let's write some post-configure hacks
COMPONENT_POST_CONFIGURE_ACTION = \
    ( $(CLONEY) $(SOURCE_DIR) $(@D) ; \
    cd $(SOURCE_DIR) ; \
	$(CONFIG_SHELL) ./build/transform_sql.sh ./subversion/libsvn_fs_fs/rep-cache-db.sql < ./subversion/libsvn_fs_fs/rep-cache-db.sql > $(BUILD_DIR_32)/subversion/libsvn_fs_fs/rep-cache-db.h 2>&1 )

COMPONENT_BUILD_TARGETS = all swig-py swig-pl javahl
COMPONENT_INSTALL_TARGETS = install install-lib \
			    install-swig-pl-lib install-swig-py \
			    install-javahl install-javahl-lib \
			    install-mods-shared \
			    install-bin install-docs

CONFIGURE_ENV += CC="$(CC)"
CONFIGURE_ENV += CXX="$(CCC)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += CPP="$(CC) $(CPPFLAGS) $(CFLAGS) -E"
CONFIGURE_ENV += CXXCPP="$(CCC) $(CPPFLAGS) $(CXXFLAGS) -E"
CONFIGURE_ENV += LDFLAGS="$(SVN_LDFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += LD="$(CC) $(CFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += CCLD="$(CC) $(CFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += CXXLD="$(CCC) $(CXXFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH_$(BITS))"
CONFIGURE_ENV += SWIG_LDFLAGS="$(LDFLAGS) $(SWIG_LDFLAGS)"
CONFIGURE_ENV += NEON_LIBS="`pkg-config --libs neon`"
CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += PYMODS="$(PYMODS)"
CONFIGURE_ENV += PYTHONPATH="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += JAVA_ROOT="$(JAVA_ROOT)"
CONFIGURE_ENV += PERL="$(PERL)"
CONFIGURE_ENV += PLARCH="$(PLARCH)"
CONFIGURE_ENV += PLVER="$(PLVER)"
CONFIGURE_ENV += PLDIR="$(PLDIR)"
CONFIGURE_ENV += PLVENDORDIR="$(PLVENDORDIR)"
CONFIGURE_ENV += PLVENDORARCHDIR="$(PLVENDORARCHDIR)"
CONFIGURE_ENV += PLMODS="$(PLMODS)"

LD_OPTIONS += $(SVN_LDFLAGS) $(SWIG_LDFLAGS)

# Let's make noise just because we have to override --libdir
CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --sbindir=$(CONFIGURE_SBINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_PREFIX)/lib/svn
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --enable-shared 
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-libtool-lock 
CONFIGURE_OPTIONS += --disable-neon-version-check
CONFIGURE_OPTIONS += --disable-experimental-libtool
CONFIGURE_OPTIONS += --with-apxs=$(APACHE_USR_PREFIX)/bin/apxs
CONFIGURE_OPTIONS += --with-ssl 
CONFIGURE_OPTIONS += --with-zlib=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-jdk=$(JAVA_ROOT)
CONFIGURE_OPTIONS += --with-apr=$(APR_USR_PREFIX)
CONFIGURE_OPTIONS += --with-apr-util=$(APR_UTIL_USR_PREFIX)
CONFIGURE_OPTIONS += --enable-nls
CONFIGURE_OPTIONS += --disable-mod-activation
CONFIGURE_OPTIONS += --enable-javahl
CONFIGURE_OPTIONS += --with-swig
CONFIGURE_OPTIONS += --with-neon=$(CONFIGURE_PREFIX)

# elfedit to remove the wrong RUNPATH/RPATH from the C++ library
COMPONENT_POST_INSTALL_ACTION = \
	( cd $(PROTO_DIR)/$(CONFIGURE_INCLUDEDIR) ; \
	    $(MV) subversion-1 svn ; \
	    cd $(PROTOUSRLIBDIR)/svn ; \
	    $(ELFEDIT) -e 'dyn:runpath /usr/lib/svn:/usr/apr/1.3/lib:/usr/apr-util/1.3/lib' libsvnjavahl-1.so.0.0.0 ; \
	    $(ELFEDIT) -e 'dyn:rpath /usr/lib/svn:/usr/apr/1.3/lib:/usr/apr-util/1.3/lib' libsvnjavahl-1.so.0.0.0 )

# Perl target
install_perl:
	$(PERL) -MExtUtils::Install -e \
	    'install({@ARGV}, '\''0'\'', 0, '\''0'\'');' \
	    $(BUILD_DIR_32)/subversion/bindings/swig/perl/native/blib/lib $(PROTO_DIR)/$(PLVENDORDIR) \
	    $(BUILD_DIR_32)/subversion/bindings/swig/perl/native/blib/arch $(PROTO_DIR)/$(PLVENDORDIR)/$(PLARCH) \
	    $(BUILD_DIR_32)/subversion/bindings/swig/perl/native/blib/man3 $(PROTO_DIR)/$(PLDIR)/man/man3

# common targets - we only build 32-bit subversion
build:		$(BUILD_32)

install:	$(INSTALL_32) install_perl
	$(MKDIR) $(PROTOUSRSHAREJAVADIR) ; \
	$(INSTALL) -m 0644 $(PROTOUSRLIBDIR)/svn/svn-javahl/svn-javahl.jar \
	    $(PROTOUSRSHAREJAVADIR)/

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk

