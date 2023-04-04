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
# Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
# Copyright 2011 EveryCity Ltd. All rights reserved.
#

#
# Rules and Macros for building opens source software that uses configure /
# GNU auto* tools to configure their build for the system they are on.  This
# uses GNU Make to build the components to take advantage of the viewpath
# support and build multiple version (32/64 bit) from a shared source.
#
# To use these rules, include ../make-rules/configure.mk in your Makefile
# and define "build", "install", and "test" targets appropriate to building
# your component.
# Ex:
#
# 	build:		$(SOURCE_DIR)/build/$(MACH32)/.built \
#	 		$(SOURCE_DIR)/build/$(MACH64)/.built
#
#	install:	$(SOURCE_DIR)/build/$(MACH32)/.installed \
#	 		$(SOURCE_DIR)/build/$(MACH64)/.installed
#
#	test:		$(SOURCE_DIR)/build/$(MACH32)/.tested \
#	 		$(SOURCE_DIR)/build/$(MACH64)/.tested
#
# Any additional pre/post configure, build, or install actions can be specified
# in your make file by setting them in on of the following macros:
#	COMPONENT_PRE_CONFIGURE_ACTION, COMPONENT_POST_CONFIGURE_ACTION
#	COMPONENT_PRE_BUILD_ACTION, COMPONENT_POST_BUILD_ACTION
#	COMPONENT_PRE_INSTALL_ACTION, COMPONENT_POST_INSTALL_ACTION
#	COMPONENT_PRE_TEST_ACTION, COMPONENT_POST_TEST_ACTION
#
# If component specific make targets need to be used for build or install, they
# can be specified in
#	COMPONENT_BUILD_TARGETS, COMPONENT_INSTALL_TARGETS
#	COMPONENT_TEST_TARGETS
#

CONFIGURE_PREFIX =	/usr

# If the component prefers 64-bit binaries, then ensure builds deliver 64-bit
# binaries to the standard directories and 32-bit binaries to the non-standard
# location.  This allows simplification of package manifests and makes it
# easier to deliver the 64-bit binaries as the default.
ifeq ($(strip $(PREFERRED_BITS)),64)
CONFIGURE_BINDIR.32  = $(CONFIGURE_PREFIX)/bin/$(MACH32)
CONFIGURE_BINDIR.64  = $(CONFIGURE_PREFIX)/bin
CONFIGURE_SBINDIR.32 = $(CONFIGURE_PREFIX)/sbin/$(MACH32)
CONFIGURE_SBINDIR.64 = $(CONFIGURE_PREFIX)/sbin
else
CONFIGURE_BINDIR.32  = $(CONFIGURE_PREFIX)/bin
CONFIGURE_BINDIR.64  = $(CONFIGURE_PREFIX)/bin/$(MACH64)
CONFIGURE_SBINDIR.32 = $(CONFIGURE_PREFIX)/sbin
CONFIGURE_SBINDIR.64 = $(CONFIGURE_PREFIX)/sbin/$(MACH64)
endif

# Regardless of PREFERRED_BITS, 64-bit libraries should always be delivered to
# the appropriate subdirectory by default.
CONFIGURE_LIBDIR.32  = $(CONFIGURE_PREFIX)/lib
CONFIGURE_LIBDIR.64  = $(CONFIGURE_PREFIX)/lib/$(MACH64)

CONFIGURE_MANDIR =	$(CONFIGURE_PREFIX)/share/man
CONFIGURE_LOCALEDIR =	$(CONFIGURE_PREFIX)/share/locale
# all texinfo documentation seems to go to /usr/share/info no matter what
CONFIGURE_INFODIR =	/usr/share/info
CONFIGURE_INCLUDEDIR =	/usr/include

CONFIGURE_ENV = CONFIG_SHELL="$(CONFIG_SHELL)"
CONFIGURE_ENV += PATH="$(PATH)"
CONFIGURE_ENV += CC="$(CC)"
CONFIGURE_ENV += CXX="$(CXX)"
CONFIGURE_ENV += F77="$(F77)"
CONFIGURE_ENV += FC="$(FC)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_ENV += FFLAGS="$(F77FLAGS)"
CONFIGURE_ENV += FCFLAGS="$(FCFLAGS)"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

# Rewrite absolute source-code paths into relative for ccache, so that any
# workspace with a shared CCACHE_DIR can benefit when compiling a component
ifneq ($(strip $(CCACHE)),)
CONFIGURE_ENV += CCACHE="$(CCACHE)"
CONFIGURE_OPTIONS += CCACHE="$(CCACHE)"
CONFIGURE_ENV += CC_gcc_32="$(CC_gcc_32)"
CONFIGURE_ENV += CC_gcc_64="$(CC_gcc_32)"
CONFIGURE_ENV += CXX_gcc_32="$(CXX_gcc_64)"
CONFIGURE_ENV += CXX_gcc_64="$(CXX_gcc_64)"
CONFIGURE_OPTIONS += CC_gcc_32="$(CC_gcc_32)"
CONFIGURE_OPTIONS += CC_gcc_64="$(CC_gcc_32)"
CONFIGURE_OPTIONS += CXX_gcc_32="$(CXX_gcc_64)"
CONFIGURE_OPTIONS += CXX_gcc_64="$(CXX_gcc_64)"
CONFIGURE_ENV.$(BITS) += CCACHE_BASEDIR="$(BUILD_DIR_$(BITS))"
CONFIGURE_OPTIONS.$(BITS) += CCACHE_BASEDIR="$(BUILD_DIR_$(BITS))"

ifneq ($(strip $(CCACHE_DIR)),)
CONFIGURE_ENV += CCACHE_DIR="$(CCACHE_DIR)"
CONFIGURE_OPTIONS += CCACHE_DIR="$(CCACHE_DIR)"
endif

ifneq ($(strip $(CCACHE_LOGFILE)),)
CONFIGURE_ENV += CCACHE_LOGFILE="$(CCACHE_LOGFILE)"
CONFIGURE_OPTIONS += CCACHE_LOGFILE="$(CCACHE_LOGFILE)"
endif

endif

CONFIGURE_DEFAULT_DIRS?=yes

CONFIGURE_OPTIONS += CC="$(CC)"
CONFIGURE_OPTIONS += CXX="$(CXX)"
CONFIGURE_OPTIONS += F77="$(F77)"
CONFIGURE_OPTIONS += FC="$(FC)"
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS += FFLAGS="$(F77FLAGS)"
CONFIGURE_OPTIONS += FCFLAGS="$(FCFLAGS)"
CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

CONFIGURE_OPTIONS += --prefix=$(CONFIGURE_PREFIX)
ifeq ($(CONFIGURE_DEFAULT_DIRS),yes)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --sbindir=$(CONFIGURE_SBINDIR.$(BITS))
endif
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))

COMPONENT_INSTALL_ARGS +=	DESTDIR=$(PROTO_DIR)

$(BUILD_DIR_32)/.configured:	BITS=32
$(BUILD_DIR_64)/.configured:	BITS=64

CONFIGURE_ENV += $(CONFIGURE_ENV.$(BITS))


# temporarily work around some issues
CONFIGURE_ENV += "ac_cv_func_realloc_0_nonnull=yes"
COMPONENT_BUILD_ENV += "ac_cv_func_realloc_0_nonnull=yes"

# configure the unpacked source for building 32 and 64 bit version
CONFIGURE_SCRIPT =	$(SOURCE_DIR)/configure
$(BUILD_DIR)/%/.configured:	$(SOURCE_DIR)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(COMPONENT_PRE_CONFIGURE_ACTION)
	(cd $(@D) ; $(ENV) $(CONFIGURE_ENV) $(CONFIG_SHELL) \
		$(CONFIGURE_SCRIPT) $(CONFIGURE_OPTIONS))
	$(COMPONENT_POST_CONFIGURE_ACTION)
	$(TOUCH) $@

# build the configured source
$(BUILD_DIR)/%/.built:	$(BUILD_DIR)/%/.configured
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) $(COMPONENT_BUILD_ARGS) \
		$(COMPONENT_BUILD_TARGETS))
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

# install the built source into a prototype area
$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_INSTALL_ENV) $(GMAKE) \
			$(COMPONENT_INSTALL_ARGS) $(COMPONENT_INSTALL_TARGETS))
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

CONFIGURE_TEST_TRANSFORMS = \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

USE_DEFAULT_TEST_TRANSFORMS?=no
ifeq ($(strip $(USE_DEFAULT_TEST_TRANSFORMS)),yes)
COMPONENT_TEST_TRANSFORMS+= $(CONFIGURE_TEST_TRANSFORMS)
endif

# test the built source
$(BUILD_DIR)/%/.tested-and-compared:    $(BUILD_DIR)/%/.built
	$(RM) -rf $(COMPONENT_TEST_BUILD_DIR)
	$(MKDIR) $(COMPONENT_TEST_BUILD_DIR)
	$(COMPONENT_PRE_TEST_ACTION)
	-(cd $(COMPONENT_TEST_DIR) ; \
		$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
		$(COMPONENT_TEST_CMD) \
		$(COMPONENT_TEST_ARGS) $(COMPONENT_TEST_TARGETS)) \
		&> $(COMPONENT_TEST_OUTPUT)
	$(COMPONENT_POST_TEST_ACTION)
	$(COMPONENT_TEST_CREATE_TRANSFORMS)
	$(COMPONENT_TEST_PERFORM_TRANSFORM)
	$(COMPONENT_TEST_COMPARE)
	$(COMPONENT_TEST_CLEANUP)
	$(TOUCH) $@

$(BUILD_DIR)/%/.tested:    SHELLOPTS=pipefail
$(BUILD_DIR)/%/.tested:    $(BUILD_DIR)/%/.built
	$(RM) -rf $(COMPONENT_TEST_BUILD_DIR)
	$(MKDIR) $(COMPONENT_TEST_BUILD_DIR)
	$(COMPONENT_PRE_TEST_ACTION)
	(cd $(COMPONENT_TEST_DIR) ; \
		$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
		$(COMPONENT_TEST_CMD) \
		$(COMPONENT_TEST_ARGS) $(COMPONENT_TEST_TARGETS)) \
		|& $(TEE) $(COMPONENT_TEST_OUTPUT)
	$(COMPONENT_POST_TEST_ACTION)
	$(COMPONENT_TEST_CREATE_TRANSFORMS)
	$(COMPONENT_TEST_PERFORM_TRANSFORM)
	$(COMPONENT_TEST_CLEANUP)
	$(TOUCH) $@

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
