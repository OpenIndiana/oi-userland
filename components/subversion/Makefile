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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

PATH=$(dir $(CC)):$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin

COMPONENT_NAME=		subversion
COMPONENT_VERSION=	1.6.16
COMPONENT_PROJECT_URL=	http://subversion.apache.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:54046728853cd33985101471c068df93cf742f16313642113622a5dfd8bff90c
COMPONENT_ARCHIVE_URL=	http://subversion.tigris.org/downloads/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL = 0

PYMODS = client core delta fs ra repos wc

PLMODS= Fs Core Wc Client Repos Ra Delta

JAVA_ROOT = $(JAVA_HOME)

# because we can't seem to get -norunpath to the java bindings build any
# other way.
CXX += $(studio_NORUNPATH)

CFLAGS += -features=extensions
CFLAGS += -xustr=ascii_utf16_ushort -xcsi
CXXFLAGS += -features=nestedaccess,tmplife,tmplrefstatic
CXXFLAGS += -template=geninlinefuncs
CXXFLAGS += -verbose=template
CXXFLAGS += -xustr=ascii_utf16_ushort
CXXFLAGS += $(CC_PIC)
CXXFLAGS += -mt -D_REENTRANT -DNDEBUG -DSOLARIS
CFLAGS += `pkg-config --cflags neon`
CFLAGS += $(CPP_LARGEFILES)

# Let's write some post-configure hacks
COMPONENT_POST_CONFIGURE_ACTION = \
    ( $(CLONEY) $(SOURCE_DIR) $(@D) ; \
    cd $(SOURCE_DIR) ; \
	$(CONFIG_SHELL) ./build/transform_sql.sh ./subversion/libsvn_fs_fs/rep-cache-db.sql < ./subversion/libsvn_fs_fs/rep-cache-db.sql > $(BUILD_DIR_32)/subversion/libsvn_fs_fs/rep-cache-db.h 2>&1 )

COMPONENT_BUILD_TARGETS = all swig-py swig-pl javahl
COMPONENT_INSTALL_TARGETS = install install-lib \
			    install-swig-pl install-swig-py \
			    install-javahl install-javahl-lib \
			    install-mods-shared \
			    install-bin install-docs

CONFIGURE_ENV += CC="$(CC)"
CONFIGURE_ENV += CXX="$(CXX)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"
CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += PYMODS="$(PYMODS)"
CONFIGURE_ENV += PYTHONPATH="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += JAVA_ROOT="$(JAVA_ROOT)"
CONFIGURE_ENV += PERL="$(PERL)"
CONFIGURE_ENV += PLMODS="$(PLMODS)"

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
CONFIGURE_OPTIONS += --with-apxs=/usr/apache2/2.2/bin/apxs
CONFIGURE_OPTIONS += --with-ssl 
CONFIGURE_OPTIONS += --with-zlib=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-jdk=$(JAVA_ROOT)
CONFIGURE_OPTIONS += --with-apr=/usr/apr/1.3
CONFIGURE_OPTIONS += --with-apr-util=/usr/apr-util/1.3
CONFIGURE_OPTIONS += --enable-nls
CONFIGURE_OPTIONS += --disable-mod-activation
CONFIGURE_OPTIONS += --enable-javahl
CONFIGURE_OPTIONS += --with-swig
CONFIGURE_OPTIONS += --with-neon=$(CONFIGURE_PREFIX)

# common targets - we only build 32-bit subversion
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk

