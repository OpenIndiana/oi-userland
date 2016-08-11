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
# Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
#

#
# Rules and Macros for building opens source software that uses configure /
# GNU auto* tools to configure their build for the system they are on.  This
# uses GNU Make to build the components to take advantage of the viewpath
# support and build multiple version (32/64 bit) from a shared source.
#
# To use these rules, include $(WS_MAKE_RULES)/configure.mk in your Makefile
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

CONFIGURE_PREFIX ?=	/usr

# If the component prefers 64-bit binaries, then ensure builds deliver 64-bit
# binaries to the standard directories and 32-bit binaries to the non-standard
# location.  This allows simplification of package manifests and makes it
# easier to deliver the 64-bit binaries as the default.
ifeq ($(strip $(PREFERRED_BITS)),64)
CONFIGURE_BINDIR.32 ?=	$(CONFIGURE_PREFIX)/bin/$(MACH32)
CONFIGURE_SBINDIR.32 ?=	$(CONFIGURE_PREFIX)/sbin/$(MACH32)
CONFIGURE_BINDIR.64 ?=	$(CONFIGURE_PREFIX)/bin
CONFIGURE_SBINDIR.64 ?=	$(CONFIGURE_PREFIX)/sbin
else
CONFIGURE_BINDIR.32 ?=	$(CONFIGURE_PREFIX)/bin
CONFIGURE_SBINDIR.32 ?=	$(CONFIGURE_PREFIX)/sbin
CONFIGURE_BINDIR.64 ?=	$(CONFIGURE_PREFIX)/bin/$(MACH64)
CONFIGURE_SBINDIR.64 ?=	$(CONFIGURE_PREFIX)/sbin/$(MACH64)
endif

# Regardless of PREFERRED_BITS, 64-bit libraries should always be delivered to
# the appropriate subdirectory by default.
CONFIGURE_LIBDIR.32 ?=	$(CONFIGURE_PREFIX)/lib
CONFIGURE_LIBDIR.64 ?=	$(CONFIGURE_PREFIX)/lib/$(MACH64)

CONFIGURE_MANDIR ?=	$(CONFIGURE_PREFIX)/share/man
CONFIGURE_LOCALEDIR ?=	$(CONFIGURE_PREFIX)/share/locale
# all texinfo documentation seems to go to /usr/share/info no matter what
CONFIGURE_INFODIR ?=	/usr/share/info
CONFIGURE_INCLUDEDIR ?=	/usr/include

CONFIGURE_ENV = CONFIG_SHELL="$(CONFIG_SHELL)"

CONFIGURE_DEFAULT_DIRS?=yes

CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"
CONFIGURE_ENV += CC="$(CC)"
CONFIGURE_ENV += CXX="$(CXX)"

# Ensure that 64-bit versions of *-config scripts are preferred.
CONFIGURE_ENV.64 += PATH="$(USRBIN.64):$(PATH)"

# A full build must be performed if any new options are added here as not all
# components use autoconf-based configure scripts and some have patched theirs
# to reject "unknown" options (which may be supported by newer versions of
# autoconf's configure).
CONFIGURE_OPTIONS += --prefix=$(CONFIGURE_PREFIX)
ifeq ($(CONFIGURE_DEFAULT_DIRS),yes)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --sbindir=$(CONFIGURE_SBINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
endif
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(MACH))
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(MACH).$(BITS))

COMPONENT_INSTALL_ARGS +=	DESTDIR=$(PROTO_DIR)

$(BUILD_DIR_32)/.configured:	BITS=32
$(BUILD_DIR_64)/.configured:	BITS=64

CONFIGURE_ENV += $(CONFIGURE_ENV.$(BITS))
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
# parfait creates '*.bc' files which can confuse configure's
# object/exe extension detection. which we really don't need it
# to do anyway, so we'll just tell it what they are.
CONFIGURE_ENV += ac_cv_objext=o
CONFIGURE_ENV += ac_cv_exeext=""
# this is fixed in the clang compiler but we can't use it yet
CONFIGURE_ENV += ac_cv_header_stdbool_h=yes
endif

# This MUST be set in the build environment so that if pkg-config is executed
# during the build process, the correct header files and libraries will be
# picked up.  In the Linux world, a system is generally only 32-bit or 64-bit
# at one time so this isn't an issue that various auto* files account for (they
# don't set PKG_CONFIG_PATH when executing pkg-config even if it was specified
# during ./configure).
COMPONENT_BUILD_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

# CC_FOR_BUILD and CXX_FOR_BUILD are used by autoconf to set the compiler and
# required flags for generating native executables and is typically used for
# host detection and other tests during the autoconf process.  Explicitly
# specifying the target bits ensures that autoconf reliably detects 32-bit and
# 64-bit builds.
CC_FOR_BUILD ?= "$(CC) $(CC_BITS)"
ifneq  ($(strip $(CC_FOR_BUILD)),)
CONFIGURE_ENV += CC_FOR_BUILD=$(CC_FOR_BUILD)
endif

CXX_FOR_BUILD ?= "$(CXX) $(CC_BITS)"
ifneq  ($(strip $(CXX_FOR_BUILD)),)
CONFIGURE_ENV += CXX_FOR_BUILD=$(CXX_FOR_BUILD)
endif

# Similar idea for CPP as above; there's a common macro found in lib-prefix.m4
# for autoconf that detects a 64-bit host on Solaris by using CPP.  As such, by
# default, we need to explicitly specify the target bits to ensure that
# autoconf reliably detects 32-bit and 64-bit builds.
CONFIGURE_CPPFLAGS ?= $(CC_BITS)
ifneq  ($(strip $(CONFIGURE_CPPFLAGS)),)
CONFIGURE_ENV += CPPFLAGS="$(strip $(CONFIGURE_CPPFLAGS) $(CPPFLAGS))"
endif

# temporarily work around some issues
CONFIGURE_ENV += "ac_cv_func_realloc_0_nonnull=yes"
CONFIGURE_ENV += "NM=/usr/gnu/bin/nm"
COMPONENT_BUILD_ENV += "ac_cv_func_realloc_0_nonnull=yes"

# 23200148 undo this once 23169155 Move developer/gnome/gettext to Userland
CONFIGURE_ENV += INTLTOOL_PERL="$(PERL)"
COMPONENT_BUILD_ENV += INTLTOOL_PERL="$(PERL)"

# configure the unpacked source for building 32 and 64 bit version
CONFIGURE_SCRIPT ?=	$(SOURCE_DIR)/configure
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
		$(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS))
	$(COMPONENT_POST_BUILD_ACTION)
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
	-$(PARFAIT) $(@D)
endif
	$(TOUCH) $@

# install the built source into a prototype area
$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_INSTALL_ENV) $(GMAKE) \
			$(COMPONENT_INSTALL_ARGS) $(COMPONENT_INSTALL_TARGETS))
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

# Test the built source.  If the output file shows up in the environment or
# arguments, don't redirect stdout/stderr to it.
$(BUILD_DIR)/%/.tested-and-compared:    $(BUILD_DIR)/%/.built
	$(RM) -rf $(COMPONENT_TEST_BUILD_DIR)
	$(MKDIR) $(COMPONENT_TEST_BUILD_DIR)
	$(COMPONENT_PRE_TEST_ACTION)
	-(cd $(COMPONENT_TEST_DIR) ; \
		$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
		$(COMPONENT_TEST_CMD) \
		$(COMPONENT_TEST_ARGS) $(COMPONENT_TEST_TARGETS)) \
		$(if $(findstring $(COMPONENT_TEST_OUTPUT),$(COMPONENT_TEST_ENV)$(COMPONENT_TEST_ARGS)),,&> $(COMPONENT_TEST_OUTPUT))
	$(COMPONENT_POST_TEST_ACTION)
	$(COMPONENT_TEST_CREATE_TRANSFORMS)
	$(COMPONENT_TEST_PERFORM_TRANSFORM)
	$(COMPONENT_TEST_COMPARE)
	$(COMPONENT_TEST_CLEANUP)
	$(TOUCH) $@

$(BUILD_DIR)/%/.tested:    $(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_TEST_ACTION)
	(cd $(COMPONENT_TEST_DIR) ; \
		$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
		$(COMPONENT_TEST_CMD) \
		$(COMPONENT_TEST_ARGS) $(COMPONENT_TEST_TARGETS))
	$(COMPONENT_POST_TEST_ACTION)
	$(COMPONENT_TEST_CLEANUP)
	$(TOUCH) $@

# Test the installed packages.  If the output file shows up in the environment
# or arguments, don't redirect stdout/stderr to it.
$(BUILD_DIR)/%/.system-tested-and-compared:    $(SOURCE_DIR)/.prep
	$(RM) -rf $(COMPONENT_TEST_BUILD_DIR)
	$(MKDIR) $(COMPONENT_TEST_BUILD_DIR)
	$(COMPONENT_PRE_SYSTEM_TEST_ACTION)
	-(cd $(COMPONENT_SYSTEM_TEST_DIR) ; \
		$(COMPONENT_SYSTEM_TEST_ENV_CMD) $(COMPONENT_SYSTEM_TEST_ENV) \
		$(COMPONENT_SYSTEM_TEST_CMD) \
		$(COMPONENT_SYSTEM_TEST_ARGS) $(COMPONENT_SYSTEM_TEST_TARGETS)) \
		$(if $(findstring $(COMPONENT_TEST_OUTPUT),$(COMPONENT_SYSTEM_TEST_ENV)$(COMPONENT_SYSTEM_TEST_ARGS)),,&> $(COMPONENT_TEST_OUTPUT))
	$(COMPONENT_POST_SYSTEM_TEST_ACTION)
	$(COMPONENT_TEST_CREATE_TRANSFORMS)
	$(COMPONENT_TEST_PERFORM_TRANSFORM)
	$(COMPONENT_TEST_COMPARE)
	$(COMPONENT_SYSTEM_TEST_CLEANUP)
	$(TOUCH) $@

$(BUILD_DIR)/%/.system-tested:    $(SOURCE_DIR)/.prep
	$(COMPONENT_PRE_SYSTEM_TEST_ACTION)
	(cd $(COMPONENT_SYSTEM_TEST_DIR) ; \
		$(COMPONENT_SYSTEM_TEST_ENV_CMD) $(COMPONENT_SYSTEM_TEST_ENV) \
		$(COMPONENT_SYSTEM_TEST_CMD) \
		$(COMPONENT_SYSTEM_TEST_ARGS) $(COMPONENT_SYSTEM_TEST_TARGETS))
	$(COMPONENT_POST_SYSTEM_TEST_ACTION)
	$(COMPONENT_SYSTEM_TEST_CLEANUP)
	$(TOUCH) $@

# If BUILD_STYLE is set, provide a default configure target.
ifeq   ($(strip $(BUILD_STYLE)),configure)
configure:	$(CONFIGURE_$(MK_BITS))
endif

ifeq   ($(strip $(PARFAIT_BUILD)),yes)
parfait: build
else
parfait:
	$(MAKE) PARFAIT_BUILD=yes parfait
endif

REQUIRED_PACKAGES += developer/build/autoconf
REQUIRED_PACKAGES += developer/build/automake
REQUIRED_PACKAGES += developer/build/gnu-make
REQUIRED_PACKAGES += developer/build/libtool
REQUIRED_PACKAGES += developer/build/pkg-config
REQUIRED_PACKAGES += developer/macro/gnu-m4
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += library/libtool/libltdl
