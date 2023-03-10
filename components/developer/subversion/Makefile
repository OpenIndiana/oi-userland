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
# Copyright (c) 2023 Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

PATH=$(dir $(CC)):/usr/bin:/usr/gnu/bin

COMPONENT_NAME=		subversion
COMPONENT_VERSION=	1.14.2
COMPONENT_REVISION =	2
COMPONENT_PROJECT_URL=	https://subversion.apache.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:c9130e8d0b75728a66f0e7038fc77052e671830d785b5616aad53b4810d3cc28
COMPONENT_ARCHIVE_URL=	https://apache.org/dist/subversion/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	Apache v2.0

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION += $(GSED) -i -e 's|@PYTHON_LIB@|'"$(PYTHON_LIB)"'|' $(@D)/Makefile.in ;

PYMODS = client core delta fs ra repos wc
PLMODS= Fs Core Wc Client Repos Ra Delta

CXXFLAGS += $(CC_PIC)
CXXFLAGS += $(CPP_LARGEFILES)
CFLAGS += -D__EXTENSIONS__
CFLAGS += `pkg-config --cflags neon`
CFLAGS += $(CPP_LARGEFILES)

# Let's write some post-configure hacks
COMPONENT_POST_CONFIGURE_ACTION = \
    ( $(CLONEY) $(SOURCE_DIR) $(@D) ; \
    cd $(SOURCE_DIR) ; \
	$(PYTHON) ./build/transform_sql.py ./subversion/libsvn_fs_fs/rep-cache-db.sql < ./subversion/libsvn_fs_fs/rep-cache-db.sql > $(BUILD_DIR_$(BITS))/subversion/libsvn_fs_fs/rep-cache-db.h 2>&1 )

COMPONENT_BUILD_TARGETS = all swig-pl swig-py javahl
COMPONENT_INSTALL_TARGETS = install install-lib \
			    install-swig-pl install-swig-py \
			    install-javahl install-javahl-lib \
			    install-mods-shared \
			    install-bin install-docs

CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += PYMODS="$(PYMODS)"
CONFIGURE_ENV += PYTHONPATH="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += JAVA_ROOT="$(JAVA_HOME)"
CONFIGURE_ENV += PERL="$(PERL)"
CONFIGURE_ENV += PLMODS="$(PLMODS)"
CONFIGURE_ENV += LD_OPTIONS="$(LD_OPTIONS)"

LIBSVNDIR = $(CONFIGURE_PREFIX)/lib/$(MACH64)

APR-CONFIG = /usr/apr/bin/apr-1-config
APU-CONFIG = /usr/apr-util/bin/apu-1-config
APXS = /usr/apache2/2.4/bin/apxs
APR-CONFIG-RPATH = /usr/apr/lib/$(MACH64)
APU-CONFIG-RPATH = /usr/apr-util/lib/$(MACH64)
APACHE_LIBEXECDIR = `$(APXS) -q libexecdir`

LDFLAGS += -R$(LIBSVNDIR) -R$(APR-CONFIG-RPATH) \
	   -R$(APU-CONFIG-RPATH)

CONFIGURE_ENV += RUBY="$(RUBY.1.9)"

# Let's make noise just because we have to override --libdir
CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --libdir=$(LIBSVNDIR)
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --enable-shared 
CONFIGURE_OPTIONS += --disable-libtool-lock 
CONFIGURE_OPTIONS += --disable-experimental-libtool
CONFIGURE_OPTIONS += --with-zlib=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-jdk=$(JAVA_HOME)
CONFIGURE_OPTIONS += --with-apr=/usr/apr
CONFIGURE_OPTIONS += --with-apr-util=/usr/apr-util
CONFIGURE_OPTIONS += --enable-nls
CONFIGURE_OPTIONS += --disable-mod-activation
CONFIGURE_OPTIONS += --enable-javahl
CONFIGURE_OPTIONS += --with-swig
CONFIGURE_OPTIONS += --with-utf8proc=internal
CONFIGURE_OPTIONS += --with-apr=$(APR-CONFIG)
CONFIGURE_OPTIONS += --with-apr-util=$(APU-CONFIG)
CONFIGURE_OPTIONS += --with-apxs=$(APXS)
CONFIGURE_OPTIONS += --with-apache-libexecdir=$(APACHE_LIBEXECDIR)
# libgnome-keyring was obsoleted upstream, disable support for storing svn
# passwords in gnome-keyring until svn is updated to use libsecret instead
CONFIGURE_OPTIONS += --without-gnome-keyring

# Build and install should be able to find tools like chmod, touch, or true
COMPONENT_BUILD_ENV += PATH=$(PATH)
COMPONENT_INSTALL_ENV += PATH=$(PATH)

# Rename Python libraries to follow Python SOABI naming scheme
COMPONENT_POST_INSTALL_ACTION += \
	EXT_SUFFIX=$(shell $(PYTHON) -c "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))") ; \
	for i in $(PROTO_DIR)$(PYTHON_LIB)/libsvn/*.so ; do \
		[[ -f $$i ]] || continue ; \
		[[ $${i%%$$EXT_SUFFIX} == $$i ]] || continue ; \
		t=$${i%%.so}$$EXT_SUFFIX ; \
		$(MV) $$i $$t ; \
	done ;
# Make sure built perl libraries are writable so we can modify them later
COMPONENT_POST_INSTALL_ACTION += \
	find $(PROTOUSRDIR)/perl5/vendor_perl/$(PERL_VERSION)/$(PERL_ARCH) \
		-name *.so -exec chmod +w {} \; -print ;

COMPONENT_TEST_TRANSFORMS += \
'-e "/libtool/d"' \
'-e "/-m64/d"' \
'-e "/Entering/d"' \
'-e "/Leaving/d"' \
'-e "/At least/d"' \
'-e "s^lib/$(MACH64)^lib/MACH64^g"'  \
'-e "s/^make\[[0-9]\{1,\}\]/make/g"' \
'-e "/ld: warning/d"' \
'-e "/warning/d"' \
'-e "/exists from a previous run/d"' \
'-e "s/\.//g"' \
'-e "/^Python version.*/d"' \
'-e "/^make:/d"'

# Master test results are different between amd64 and SPARCV9.
COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH64).master

# Build dependencies
PYTHON_REQUIRED_PACKAGES += library/python/py3c

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/apr
REQUIRED_PACKAGES += library/apr-util
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libserf
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += library/magic
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
