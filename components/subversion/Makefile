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

BUILD_BITS=64_and_32
include ../../make-rules/shared-macros.mk

PATH=$(dir $(CC)):$(SPRO_VROOT)/bin:$(USRBINDIR):$(GNUBIN)

COMPONENT_NAME=		subversion
COMPONENT_VERSION=	1.9.4
COMPONENT_PROJECT_URL=	http://subversion.apache.org/
COMPONENT_ARCHIVE_HASH=	\
	sha256:11f738063f322b06f8c81e42bc26c33e0cb1e465539647109e534274d4a8540c
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/subversion/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/svn

TPNO=			30345

include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL := 0
JAVA_ROOT = $(JAVA_HOME)
GNUCP = $(GNUBIN)/cp

# Because we can't seem to get -norunpath to the java bindings build any
# other way.
CXX += $(studio_NORUNPATH) -std=sun03
CFLAGS += -features=extensions
CFLAGS += -D_REENTRANT -DNDEBUG -DSOLARIS
CXXFLAGS += -features=nestedaccess,tmplife,tmplrefstatic
CXXFLAGS += -template=geninlinefuncs
CXXFLAGS += $(CC_PIC)
CXXFLAGS += -D_REENTRANT -DNDEBUG -DSOLARIS
CXXFLAGS += $(CPP_LARGEFILES)
CFLAGS += `pkg-config --cflags serf-1`
CFLAGS += $(CPP_LARGEFILES)

PYMODS := client core delta fs ra repos wc
PLMODS :=

ifneq (,$(findstring m64,$(CXXFLAGS)))
  PLMODS = Fs Core Wc Client Repos Ra Delta
endif

COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-subversion.master

COMPONENT_TEST_TRANSFORMS += \
     '-e "/libtool/d"' \
     '-e "/-m32/d"' \
     '-e "/-m64/d"' \
     '-e "/Entering/d"' \
     '-e "/Leaving/d"' \
     '-e "/At least/d"' \
     '-e "s^lib/$(MACH64)^lib/MACH64^g"'  \
     '-e "s/^make\[[0-9]\{1,\}\]/make/g"' \
     '-e "/ld: warning/d"' \
     '-e "/warning/d"' \
     '-e "/exists from a previous run/d"'

PERL_VERSION.32 = none
PERL_VERSION.64 = 5.22
PERL_VERSION=$(PERL_VERSION.$(BITS))
PERL.32 = none
PERL.64 = $(USRDIR)/perl5/$(PERL_VERSION)/bin/perl
PERL=$(PERL.$(BITS))

PERL_VERSION_22 = 5.22
PERL_ARCH_22_i386 = i86pc-solaris-thread-multi-64
PERL_ARCH_22_sparc = sun4-solaris-thread-multi-64
PERL_ARCH_22 = $(PERL_ARCH_22_$(MACH))

APR_VERSION = 1.5
APR_UTIL_VERSION = 1.5

# Use the libraries just built plus the svn test harness library.
LD_TEST_PATH_32 := \
  $(PROTOUSRLIBDIR)/svn:$(BUILD_DIR_32)/subversion/tests/.libs
LD_TEST_PATH_64 := \
  $(PROTOUSRLIBDIR)/svn/$(MACH64):$(BUILD_DIR_64)/subversion/tests/.libs

# we need the proto area for the tests
test: install

# Let's write some post-configure hacks
COMPONENT_POST_CONFIGURE_ACTION = \
    ( $(CLONEY) $(SOURCE_DIR) $(@D) ; \
    cd $(SOURCE_DIR) ; \
    $(PYTHON.$(BITS)) ./build/transform_sql.py ./subversion/libsvn_fs_fs/rep-cache-db.sql < ./subversion/libsvn_fs_fs/rep-cache-db.sql > $(BUILD_DIR_$(BITS))/subversion/libsvn_fs_fs/rep-cache-db.h 2>&1 ; \
    cd $(BUILD_DIR_$(BITS)) ; \
    find . -type f -name "*.class" -exec rm -f {} \; > /dev/null 2>&1 ; \
    cd $(BUILD_DIR_$(BITS)) ; \
    $(GSED) -i 's/-mt//g' Makefile )

COMPONENT_BUILD_TARGETS = all swig-py swig-pl javahl
COMPONENT_INSTALL_TARGETS = install install-lib \
			    install-swig-pl install-swig-py \
			    install-javahl install-javahl-lib \
			    install-bin install-docs

$(BUILD_DIR)/$(MACH64)/.installed: COMPONENT_INSTALL_TARGETS += install-mods-shared

CONFIGURE_LIBDIR.32 = $(CONFIGURE_PREFIX)/lib/svn
CONFIGURE_LIBDIR.64 = $(CONFIGURE_PREFIX)/lib/svn/$(MACH64)

APR-CONFIG.32 = $(USRDIR)/apr/$(APR_VERSION)/bin/apr-1-config
APR-CONFIG.64 = $(USRDIR)/apr/$(APR_VERSION)/bin/$(MACH64)/apr-1-config
APU-CONFIG.32 = $(USRDIR)/apr-util/$(APR_UTIL_VERSION)/bin/apu-1-config
APU-CONFIG.64 = $(USRDIR)/apr-util/$(APR_UTIL_VERSION)/bin/$(MACH64)/apu-1-config
APXS.32 = no
APXS.64 = $(USRDIR)/apache2/2.4/bin/apxs
APR-CONFIG-RPATH.32 = $(USRDIR)/apr/$(APR_VERSION)/lib
APR-CONFIG-RPATH.64 = $(USRDIR)/apr/$(APR_VERSION)/lib/$(MACH64)
APU-CONFIG-RPATH.32 = $(USRDIR)/apr-util/$(APR_VERSION)/lib
APU-CONFIG-RPATH.64 = $(USRDIR)/apr-util/$(APR_VERSION)/lib/$(MACH64)

EXPAT_INCLUDE = $(USRINCDIR)
EXPAT_LIBDIR = $(USRLIB.$(BITS))
EXPAT_LIB = -lexpat

APACHE_LIBEXECDIR=$(USRDIR)/apache2/2.4/libexec

LDFLAGS += -R$(CONFIGURE_LIBDIR.$(BITS)) -R$(APR-CONFIG-RPATH.$(BITS)) \
	   -R$(APU-CONFIG-RPATH.$(BITS))

LD_OPTIONS += -R$(CONFIGURE_LIBDIR.$(BITS)) -R$(APR-CONFIG-RPATH.$(BITS)) \
	      -R$(APU-CONFIG-RPATH.$(BITS))

CONFIGURE_ENV += PYTHON="$(PYTHON.$(BITS))"
CONFIGURE_ENV += PYMODS="$(PYMODS)"
CONFIGURE_ENV += PYTHONPATH="$(PYTHON_VENDOR_PACKAGES.$(BITS))"
CONFIGURE_ENV += JAVA_ROOT="$(JAVA_ROOT)"
CONFIGURE_ENV += PERL="$(PERL)"
CONFIGURE_ENV += ac_cv_path_PERL="$(PERL)"
CONFIGURE_ENV += PLMODS="$(PLMODS)"
CONFIGURE_ENV += LD_OPTIONS="$(LD_OPTIONS)"

CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-libtool-lock
CONFIGURE_OPTIONS += --disable-experimental-libtool
CONFIGURE_OPTIONS += --with-apxs=$(APXS.$(BITS))
CONFIGURE_OPTIONS += --with-zlib=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-jdk=$(JAVA_ROOT)
CONFIGURE_OPTIONS += --with-apr=$(USRDIR)/apr/$(APR_VERSION)
CONFIGURE_OPTIONS += --with-apr-util=$(USRDIR)/apr-util/$(APR_UTIL_VERSION)
CONFIGURE_OPTIONS += --enable-nls
CONFIGURE_OPTIONS += --disable-mod-activation
CONFIGURE_OPTIONS += --enable-javahl
CONFIGURE_OPTIONS += --with-swig
CONFIGURE_OPTIONS += --with-expat=$(EXPAT_INCLUDE):$(EXPAT_LIBDIR):$(EXPAT_LIB)
CONFIGURE_OPTIONS += --with-serf=$(CONFIGURE_PREFIIX)
CONFIGURE_OPTIONS += --with-apr=$(APR-CONFIG.$(BITS))
CONFIGURE_OPTIONS += --with-apr-util=$(APU-CONFIG.$(BITS))
CONFIGURE_OPTIONS += --with-apache-libexecdir=$(APACHE_LIBEXECDIR)
# libgnome-keyring was obsoleted upstream, disable support for storing svn
# passwords in gnome-keyring until svn is updated to use libsecret instead
CONFIGURE_OPTIONS += --without-gnome-keyring

COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_BUILD_ENV += PYTHON="$(PYTHON.$(BITS))"
COMPONENT_BUILD_ENV += PYMODS="$(PYMODS)"
COMPONENT_BUILD_ENV += PYTHONPATH="$(PYTHON_VENDOR_PACKAGES.$(BITS))"
COMPONENT_BUILD_ENV += JAVA_ROOT="$(JAVA_ROOT)"
COMPONENT_BUILD_ENV += PERL="$(PERL)"
COMPONENT_BUILD_ENV += ac_cv_path_PERL="$(PERL)"
COMPONENT_BUILD_ENV += PLMODS="$(PLMODS)"

COMPONENT_BUILD_ENV += LD_OPTIONS="$(LD_OPTIONS)"
COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_TEST_ENV += LD_LIBRARY_PATH_32="$(LD_TEST_PATH_32)"
COMPONENT_TEST_ENV += LD_LIBRARY_PATH_64="$(LD_TEST_PATH_64)"

PKG_MACROS += PERL_ARCH_22="$(PERL_ARCH_22)"
PKG_MACROS += PYVER=$(PYTHON_VERSION)

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

REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/versioning/subversion
REQUIRED_PACKAGES += developer/build/scons
REQUIRED_PACKAGES += library/apr-15
REQUIRED_PACKAGES += library/apr-util-15
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libserf
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += security/kerberos-5
REQUIRED_PACKAGES += system/library/c++-runtime
$(SOLARIS_11_ONLY)REQUIRED_PACKAGES += system/library/security/libsasl
REQUIRED_PACKAGES += system/library/security/libsasl2

