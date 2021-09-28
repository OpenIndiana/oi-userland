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
# Copyright (c) 2021 Klaus Ziegler
#

BUILD_BITS=	64

include ../../../make-rules/shared-macros.mk

PATH=$(dir $(CC)):/usr/bin:/usr/gnu/bin

COMPONENT_NAME=		subversion
COMPONENT_VERSION=	1.14.1
COMPONENT_PROJECT_URL=	https://subversion.apache.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:2c5da93c255d2e5569fa91d92457fdb65396b0666fad4fd59b22e154d986e1a9
COMPONENT_ARCHIVE_URL=	https://apache.org/dist/subversion/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	Apache v2.0

include $(WS_MAKE_RULES)/common.mk

GCC_VERSION=	10

PYTHON= /usr/bin/python3.9
PYMODS = client core delta fs ra repos wc
PLMODS= Fs Core Wc Client Repos Ra Delta
JAVA_ROOT = $(JAVA_HOME)

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

COMPONENT_BUILD_TARGETS = $(COMPONENT_BUILD_TARGETS.$(BITS))

PERL_VERSION=5.24
PYTHON_VERSION=3.9
PERL = /usr/perl5/5.24/bin/perl
ifeq	($(strip $(MACH)),i386)
PERL_ARCH = i86pc-solaris-thread-multi-64
else
PERL_ARCH = sun4-solaris-thread-multi-64
endif

CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += PYMODS="$(PYMODS)"
CONFIGURE_ENV += PYTHONPATH="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += JAVA_ROOT="$(JAVA_ROOT)"
CONFIGURE_ENV += PERL="$(PERL)"
CONFIGURE_ENV += PLMODS="$(PLMODS)"
CONFIGURE_ENV += LD_OPTIONS="$(LD_OPTIONS)"

LIBSVNDIR.64 = $(CONFIGURE_PREFIX)/lib/$(MACH64)

APR-CONFIG.64 = /usr/apr/bin/$(MACH64)/apr-1-config
APU-CONFIG.64 = /usr/apr-util/bin/$(MACH64)/apu-1-config
APXS.64 = /usr/apache2/2.4/bin/apxs
APR-CONFIG-RPATH.64 = /usr/apr/lib/$(MACH64)
APU-CONFIG-RPATH.64 = /usr/apr-util/lib/$(MACH64)
APACHE_LIBEXECDIR.64 = `$(APXS.64) -q libexecdir`

LDFLAGS += -R$(LIBSVNDIR.$(BITS)) -R$(APR-CONFIG-RPATH.$(BITS)) \
	   -R$(APU-CONFIG-RPATH.$(BITS))

CONFIGURE_ENV += RUBY="$(RUBY.1.9)"

# Let's make noise just because we have to override --libdir
CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --libdir=$(LIBSVNDIR.$(BITS))
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --enable-shared 
CONFIGURE_OPTIONS += --disable-libtool-lock 
CONFIGURE_OPTIONS += --disable-experimental-libtool
CONFIGURE_OPTIONS += --with-zlib=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-jdk=$(JAVA_ROOT)
CONFIGURE_OPTIONS += --with-apr=/usr/apr
CONFIGURE_OPTIONS += --with-apr-util=/usr/apr-util
CONFIGURE_OPTIONS += --enable-nls
CONFIGURE_OPTIONS += --disable-mod-activation
CONFIGURE_OPTIONS += --enable-javahl
CONFIGURE_OPTIONS += --with-swig
CONFIGURE_OPTIONS += --with-utf8proc=internal
CONFIGURE_OPTIONS += --with-apr=$(APR-CONFIG.$(BITS))
CONFIGURE_OPTIONS += --with-apr-util=$(APU-CONFIG.$(BITS))
CONFIGURE_OPTIONS.64 += --with-apxs=$(APXS.$(BITS))
CONFIGURE_OPTIONS.64 += --with-apache-libexecdir=$(APACHE_LIBEXECDIR.$(BITS))
# libgnome-keyring was obsoleted upstream, disable support for storing svn
# passwords in gnome-keyring until svn is updated to use libsecret instead
CONFIGURE_OPTIONS += --without-gnome-keyring

CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))

COMPONENT_POST_BUILD_ACTION.64 += \
        ( cd $(BUILD_DIR_$(BITS)) && \
            $(GMAKE) -j1 swig-pl )
COMPONENT_POST_BUILD_ACTION = $(COMPONENT_POST_BUILD_ACTION.$(BITS))

COMPONENT_POST_INSTALL_ACTION += \
	( cd $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/libsvn ; \
		for i in *.so  ; \
		do \
		  t=`echo $$i | sed -e "s@.so@.cpython-39.so@g"` ; \
		  ln -s $$i $$t ; \
		done ) ; \
	( cd $(PROTOUSRDIR)/perl5/vendor_perl/$(PERL_VERSION)/$(PERL_ARCH) ; \
		find . -name *.so -exec chmod 755 {} \; -print )

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
REQUIRED_PACKAGES += library/py3c
REQUIRED_PACKAGES += runtime/python-39

# Auto-generated dependencies
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
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
