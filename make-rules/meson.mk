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
# Copyright (c) 2019, Oracle and/or its affiliates. All rights reserved.
#

#
# Rules and Macros for building open source software that uses meson
# to configure their build for the system they are on.   It then includes
# ninja.mk to handle the build/install/test macros
#
# To use these rules in your component Makefile, set BUILD_STYLE=meson and
# then include $(WS_MAKE_RULES)/common.mk. 
#
# Any additional pre/post configure actions can be specified
# in your make file by setting them in one of the following macros:
#	COMPONENT_PRE_CONFIGURE_ACTION, COMPONENT_POST_CONFIGURE_ACTION
#

CONFIGURE_PREFIX ?=	/usr

# When debugging a component, override this to be debug or debugoptimized
MESON_BUILDTYPE ?=	plain

ifeq ($(strip $(MESON_BUILDTYPE)), debug)
MESON_OPTIMIZATION ?=	g
else
MESON_OPTIMIZATION ?=	3
endif

MESON_BUILDPIE ?=	false

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

# Some components require an architecture-specific directory for their
# configuration, so these are specified per-bits.
CONFIGURE_ETCDIR.32 ?= $(ETCDIR)
CONFIGURE_ETCDIR.64 ?= $(ETCDIR)

CONFIGURE_DEFAULT_DIRS?=yes

CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"
CONFIGURE_ENV += CC="$(CC)"
CONFIGURE_ENV += CXX="$(CXX)"
CONFIGURE_ENV += F77="$(F77)"
CONFIGURE_ENV += FC="$(FC)"
ifneq ($(strip $(CFLAGS)),)
CONFIGURE_ENV += CFLAGS="$(strip $(CFLAGS))"
endif
ifneq ($(strip $(CXXFLAGS)),)
CONFIGURE_ENV += CXXFLAGS="$(strip $(CXXFLAGS))"
endif
CONFIGURE_CPPFLAGS ?= $(CC_BITS)
ifneq  ($(strip $(CONFIGURE_CPPFLAGS) $(CPPFLAGS)),)
CONFIGURE_ENV += CPPFLAGS="$(strip $(CONFIGURE_CPPFLAGS) $(CPPFLAGS))"
endif
CONFIGURE_ENV += LDFLAGS="$(strip $(LDFLAGS))"
ifneq ($(strip $(F77FLAGS)),)
CONFIGURE_ENV += FFLAGS="$(strip $(F77FLAGS))"
endif
ifneq ($(strip $(FCFLAGS)),)
CONFIGURE_ENV += FCFLAGS="$(strip $(FCFLAGS))"
endif

# Options here should be limited to the built-in options listed on
# https://mesonbuild.com/Builtin-options.html
CONFIGURE_OPTIONS += --buildtype=$(MESON_BUILDTYPE)
CONFIGURE_OPTIONS += --optimization=$(MESON_OPTIMIZATION)
CONFIGURE_OPTIONS += -Ddefault_library=shared
CONFIGURE_OPTIONS += -Db_pie=$(MESON_BUILDPIE)

# Install paths
CONFIGURE_OPTIONS += --prefix=$(CONFIGURE_PREFIX)
ifeq ($(CONFIGURE_DEFAULT_DIRS),yes)
CONFIGURE_OPTIONS += --bindir="$(CONFIGURE_BINDIR.$(BITS))"
CONFIGURE_OPTIONS += --sbindir="$(CONFIGURE_SBINDIR.$(BITS))"
CONFIGURE_OPTIONS += --libdir="$(CONFIGURE_LIBDIR.$(BITS))"
CONFIGURE_OPTIONS += --libexecdir="$(CONFIGURE_LIBDIR.32)"
CONFIGURE_OPTIONS += --localstatedir="$(VARDIR)"
CONFIGURE_OPTIONS += --mandir="$(CONFIGURE_MANDIR)"
CONFIGURE_OPTIONS += --sysconfdir="$(CONFIGURE_ETCDIR.$(BITS))"
endif
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(MACH))
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(MACH).$(BITS))

$(BUILD_DIR_32)/.configured:	BITS=32
$(BUILD_DIR_64)/.configured:	BITS=64

CONFIGURE_ENV += $(CONFIGURE_ENV.$(BITS))

# This MUST be set in the build environment so that if pkg-config is executed
# during the build process, the correct header files and libraries will be
# picked up.  In the Linux world, a system is generally only 32-bit or 64-bit
# at one time so this isn't an issue that various auto* files account for (they
# don't set PKG_CONFIG_PATH when executing pkg-config even if it was specified
# during ./configure).
COMPONENT_BUILD_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

MESON = 	/usr/bin/meson

# configure the unpacked source for building 32 and 64 bit version
# meson insists on separate source & build directories, so no cloney here.
$(BUILD_DIR)/%/.configured:	$(SOURCE_DIR)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(COMPONENT_PRE_CONFIGURE_ACTION)
	(cd $(SOURCE_DIR) ; $(ENV) $(CONFIGURE_ENV) $(MESON) setup $(@D) \
		$(CONFIGURE_OPTIONS))
	$(COMPONENT_POST_CONFIGURE_ACTION)
	$(TOUCH) $@

# If BUILD_STYLE is set, provide a default configure target.
ifeq   ($(strip $(BUILD_STYLE)),meson)
configure:	$(CONFIGURE_$(MK_BITS))
endif

USERLAND_REQUIRED_PACKAGES += developer/build/meson

# Meson generates build.ninja files for the ninja build tool to run,
# so we include ninja.mk for the build/install/test rules

include $(WS_MAKE_RULES)/ninja.mk
