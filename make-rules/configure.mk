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
# Copyright (c) 2010, 2014, Oracle and/or its affiliates. All rights reserved.
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
# Common values for USRDIR BINDIR BINDIR LIBDIR MACH64 and so on are defined
# in shared-macros.mk - so it should be included in your recipe too.
#

CONFIGURE_PREFIX =	$(USRDIR)

# Note: definitions below specifically rely on $(CONFIGURE_PREFIX) rather
# than e.g. $(USRBINDIR64) in order for certain components to be able to
# deliver their whole trees into dedicated subdirectories for each version
# (databases, compilers, etc.) by just redefining CONFIGURE_PREFIX once in
# their recipe.
CONFIGURE_EXECPREFIX =	$(CONFIGURE_PREFIX)
CONFIGURE_BINDIR.32 =	$(CONFIGURE_EXECPREFIX)$(BINDIR)
CONFIGURE_BINDIR.64 =	$(CONFIGURE_EXECPREFIX)$(BINDIR)/$(MACH64)
CONFIGURE_LIBDIR.32 =	$(CONFIGURE_EXECPREFIX)$(LIBDIR)
CONFIGURE_LIBDIR.64 =	$(CONFIGURE_EXECPREFIX)$(LIBDIR)/$(MACH64)
# Note: Some components redefine their $(CONFIGURE_LIBEXECDIR.$(BITS))=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_LIBEXECDIR.32 =	$(CONFIGURE_LIBDIR.32)
CONFIGURE_LIBEXECDIR.64 =	$(CONFIGURE_LIBDIR.64)
CONFIGURE_SBINDIR.32 =	$(CONFIGURE_EXECPREFIX)$(SBINDIR)
CONFIGURE_SBINDIR.64 =	$(CONFIGURE_EXECPREFIX)$(SBINDIR)/$(MACH64)
CONFIGURE_DATAROOTDIR=	$(CONFIGURE_PREFIX)/share
CONFIGURE_DATADIR=	$(CONFIGURE_DATAROOTDIR)
CONFIGURE_MANDIR =	$(CONFIGURE_DATAROOTDIR)/man
CONFIGURE_LOCALEDIR =	$(CONFIGURE_DATAROOTDIR)/locale

# Note: CONFIGURE_INCLUDEROOTDIR is not meant to be redefined by components -
# it is just the common base value for CONFIGURE_INCLUDEDIR which actually
# sets the argument to configure script and may be customized by components
CONFIGURE_INCLUDEROOTDIR =	$(CONFIGURE_PREFIX)/include
# This is often redefined by components to become similar to:
#   CONFIGURE_INCLUDEDIR=$(CONFIGURE_INCLUDEROOTDIR)/$(COMPONENT_NAME)
CONFIGURE_INCLUDEDIR =	$(CONFIGURE_INCLUDEROOTDIR)

# Note: Very few components have architecture-dependent configs.
# Those recipes should set them BEFORE including this file, typically to:
#   CONFIGURE_SYSCONFDIR.32 = $(ETCDIR)
#   CONFIGURE_SYSCONFDIR.64 = $(ETCDIR)/$(MACH64)
CONFIGURE_SYSCONFDIR =	$(ETCDIR)

# all texinfo documentation seems to go to /usr/share/info no matter what
CONFIGURE_INFODIR =	/usr/share/info

# A few component recipes override the doc dir as e.g. /usr/share/doc and
# install in subdir of that - or into that root directly
CONFIGURE_DOCDIR =	$(CONFIGURE_DATAROOTDIR)/doc/$(COMPONENT_NAME)
CONFIGURE_DOCDIR_HTML =	$(CONFIGURE_DOCDIR)
CONFIGURE_DOCDIR_DVI =	$(CONFIGURE_DOCDIR)
CONFIGURE_DOCDIR_PDF =	$(CONFIGURE_DOCDIR)
CONFIGURE_DOCDIR_PS  =	$(CONFIGURE_DOCDIR)

# A few components override these statedirs; a common choice then is
#   CONFIGURE_LOCALSTATEDIR=/var/lib
CONFIGURE_LOCALSTATEDIR =	$(VARDIR)
# Sometimes but not necessarily (so must be explicit) some components set
#   CONFIGURE_SHAREDSTATEDIR=$(CONFIGURE_LOCALSTATEDIR)
CONFIGURE_SHAREDSTATEDIR =	$(VARDIR)

# These optional variables enable certain blocks in this makefile
# that additionally (re-)define some values and options
CONFIGURE_PROTO_DIRS?=yes
CONFIGURE_DEFAULT_DIRS?=yes
CONFIGURE_DEFAULT_EXTRA_DIRS?=yes
CONFIGURE_DEFAULT_STATE_DIRS?=yes

ifeq ($(CONFIGURE_PROTO_DIRS),yes)
# Redefine the relevant pieces of PROTO*DIR trees to match possible
# customizations for `configure`'d components
PROTOUSRDIR =   $(PROTO_DIR)/$(CONFIGURE_PREFIX)
PROTOUSRBINDIR =    $(PROTO_DIR)/$(CONFIGURE_BINDIR.32)
PROTOUSRBINDIR32 =  $(PROTO_DIR)/$(CONFIGURE_BINDIR.32)
PROTOUSRBINDIR64 =  $(PROTO_DIR)/$(CONFIGURE_BINDIR.64)
PROTOUSRSBINDIR =   $(PROTO_DIR)/$(CONFIGURE_SBINDIR.32)
PROTOUSRSBINDIR32 = $(PROTO_DIR)/$(CONFIGURE_SBINDIR.32)
PROTOUSRSBINDIR64 = $(PROTO_DIR)/$(CONFIGURE_SBINDIR.64)
PROTOUSRLIBDIR =    $(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)
PROTOUSRLIBDIR64 =  $(PROTO_DIR)/$(CONFIGURE_LIBDIR.64)
PROTOUSRINCDIR =    $(PROTO_DIR)/$(CONFIGURE_INCLUDEDIR)
PROTOUSRSHAREDIR =      $(PROTO_DIR)/$(CONFIGURE_DATAROOTDIR)
PROTOUSRSHAREMANDIR =   $(PROTO_DIR)/$(CONFIGURE_MANDIR)
PROTOUSRSHAREMAN1DIR =  $(PROTOUSRSHAREMANDIR)/man1
PROTOUSRSHAREMAN1MDIR = $(PROTOUSRSHAREMANDIR)/man1m
PROTOUSRSHAREMAN3DIR =  $(PROTOUSRSHAREMANDIR)/man3
PROTOUSRSHAREMAN4DIR =  $(PROTOUSRSHAREMANDIR)/man4
PROTOUSRSHAREMAN5DIR =  $(PROTOUSRSHAREMANDIR)/man5
PROTOUSRSHAREDOCDIR =   $(PROTO_DIR)/$(CONFIGURE_DOCDIR)
PROTOUSRSHARELOCALEDIR =    $(PROTO_DIR)/$(CONFIGURE_LOCALEDIR)
endif

# Note: we start with = here, and so IGNORE envvars that a component
# recipe might define before including this file.
CONFIGURE_ENV = CONFIG_SHELL="$(CONFIG_SHELL)"
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


# Note: we start with += here, and so INHERIT options that a component
# recipe might define before including this file. Ordering might matter.
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

# (root of) architecture-independent files
CONFIGURE_OPTIONS += --prefix=$(CONFIGURE_PREFIX)
ifeq ($(CONFIGURE_DEFAULT_DIRS),yes)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
# user executables
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
# object code libraries
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
# system admin executables
CONFIGURE_OPTIONS += --sbindir=$(CONFIGURE_SBINDIR.$(BITS))
endif

# For legacy purposes that fenced the 4 lines defined above,
# this definition below is fenced separately, so individual
# components can easily elect to un-select these lines.
# It is assumed that generally "configure" guesses these
# values from "prefix" correctly - :
ifeq ($(CONFIGURE_DEFAULT_EXTRA_DIRS),yes)
# (root of) architecture-dependent files (for us it's usually same as PREFIX)
CONFIGURE_OPTIONS += --exec-prefix=$(CONFIGURE_EXECPREFIX)
# program executables (for us it's usually same as LIB)
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBEXECDIR.$(BITS))
# (root of) C header files
CONFIGURE_OPTIONS += --includedir=$(CONFIGURE_INCLUDEDIR)
# locale-dependent data
CONFIGURE_OPTIONS += --localedir=$(CONFIGURE_LOCALEDIR)
# read-only architecture-independent data root and actual data (usually same)
CONFIGURE_OPTIONS += --datarootdir=$(CONFIGURE_DATAROOTDIR)
CONFIGURE_OPTIONS += --datadir=$(CONFIGURE_DATADIR)
# man documentation
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
# info (and tex?) documentation
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
# other documentation types
CONFIGURE_OPTIONS += --docdir=$(CONFIGURE_DOCDIR)
CONFIGURE_OPTIONS += --htmldir=$(CONFIGURE_DOCDIR_HTML)
CONFIGURE_OPTIONS += --dvidir=$(CONFIGURE_DOCDIR_DVI)
CONFIGURE_OPTIONS += --pdfdir=$(CONFIGURE_DOCDIR_PDF)
CONFIGURE_OPTIONS += --psdir=$(CONFIGURE_DOCDIR_PS)
endif

# Components that do define custom dirs are likely to encroach
# on these two, hence the separate fencing. Alternately these
# components can upgrade to define CONFIGURE_SHAREDSTATEDIR as they need :)
ifeq ($(CONFIGURE_DEFAULT_STATE_DIRS),yes)
# read-only single-machine data, usually /etc
ifneq ($(CONFIGURE_SYSCONFDIR.$(BITS)),)
CONFIGURE_OPTIONS +=    --sysconfdir=$(CONFIGURE_SYSCONFDIR.$(BITS))
else
CONFIGURE_OPTIONS +=    --sysconfdir=$(CONFIGURE_SYSCONFDIR)
endif
# modifiable single-machine data, often /var, sometimes /var/lib
CONFIGURE_OPTIONS +=    --localstatedir=$(CONFIGURE_LOCALSTATEDIR)
# Note: Some components define --sharedstatedir=DIR individually,
# usually as "/var/$(COMPONENT_NAME)"
CONFIGURE_OPTIONS +=    --sharedstatedir=$(CONFIGURE_SHAREDSTATEDIR)
endif

# Other configure options for the current bitness
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))

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
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
	-$(PARFAIT) build
endif
	$(TOUCH) $@

# install the built source into a prototype area
$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_INSTALL_ENV) $(GMAKE) \
			$(COMPONENT_INSTALL_ARGS) $(COMPONENT_INSTALL_TARGETS))
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

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

$(BUILD_DIR)/%/.tested:    $(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_TEST_ACTION)
	(cd $(COMPONENT_TEST_DIR) ; \
		$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
		$(COMPONENT_TEST_CMD) \
		$(COMPONENT_TEST_ARGS) $(COMPONENT_TEST_TARGETS))
	$(COMPONENT_POST_TEST_ACTION)
	$(COMPONENT_TEST_CLEANUP)
	$(TOUCH) $@

ifeq   ($(strip $(PARFAIT_BUILD)),yes)
parfait: install
	-$(PARFAIT) build
else
parfait:
	$(MAKE) PARFAIT_BUILD=yes parfait
endif

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
