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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

# ocaml configure system checks for gcc as gcc*,
# so we can't set -cc option to $(CC).
# Instead we set PATH to $(GCC_ROOT)/bin:$(PATH) and -cc to gcc
PATH=$(GCC_ROOT)/bin:$(USRBINDIR):$(GNUBIN):$(USRSBINDIR)

COMPONENT_NAME=		ocaml
COMPONENT_VERSION=	3.11.2
COMPONENT_PROJECT_URL=	http://www.ocaml.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:86f3387a0d7e7c8be2a3c53af083a5a726e333686208d5ea0dd6bb5ac3f58143
COMPONENT_ARCHIVE_URL=	http://caml.inria.fr/distrib/ocaml-3.11/$(COMPONENT_ARCHIVE)

# Documentation sources
#
COMPONENT_ARCHIVE_1= ocaml-3.11-refman.html.tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:1c65b334ccb155aefa1e5e930a91f816d843d37e26b27d3a0351c57149005a5c
COMPONENT_ARCHIVE_URL_1= http://caml.inria.fr/distrib/ocaml-3.11/$(COMPONENT_ARCHIVE_1)

COMPONENT_ARCHIVE_2= ocaml-3.11-refman.pdf
COMPONENT_ARCHIVE_HASH_2= \
    sha256:35f5adfeb92817f7e3ef66dec6b4ca910f48a3a2cf0bfa34bd155fe6866de405
COMPONENT_ARCHIVE_URL_2= http://caml.inria.fr/distrib/ocaml-3.11/$(COMPONENT_ARCHIVE_2)

COMPONENT_ARCHIVE_3= ocaml-3.11-refman.info.tar.gz
COMPONENT_ARCHIVE_HASH_3= \
    sha256:48eedc6a870bef84562b2d0ed25d9c3b15ab646f72ecfb4c6c2cbaccc6b4081d
COMPONENT_ARCHIVE_URL_3= http://caml.inria.fr/distrib/ocaml-3.11/$(COMPONENT_ARCHIVE_3)

TPNO=			9233

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ARGS=

# Ocaml does not use a standard configure script, but has its own handwritten
# one.  So we must specify the arguments it accepts by hand.
#
CONFIGURE_OPTIONS = --bindir $(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir $(CONFIGURE_LIBDIR.$(BITS))/ocaml
CONFIGURE_OPTIONS += --x11lib $(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --x11include $(CONFIGURE_INCLUDEDIR)
CONFIGURE_OPTIONS += --mandir $(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += -cc gcc
CONFIGURE_OPTIONS += -aspp "/usr/bin/as -P"
CONFIGURE_OPTIONS += -as "/usr/bin/as"

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_BUILD_TARGETS = world opt opt.opt

# Set up some environment variables to make things look nicer.
#
UL_OCAML_PDFDOC     = $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_2)
UL_OCAML_INCLUDES = -nostdlib -I stdlib -I utils -I parsing -I typing -I bytecomp -I asmcomp -I driver
UL_OCAML_ALLINCLUDES = $(UL_OCAML_INCLUDES) -I otherlibs/unix -I otherlibs/str -I otherlibs/dynlink
UL_PROTO_BINDIR     = $(PROTO_DIR)/$(CONFIGURE_BINDIR.$(BITS))
UL_PROTO_LIBDIR     = $(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS))
UL_PROTO_INFODIR    = $(PROTO_DIR)/$(CONFIGURE_INFODIR)
UL_PROTO_DATADIR    = $(PROTO_DIR)/$(CONFIGURE_PREFIX)/share
COMPONENT_INSTALL_ARGS += EMACSDIR="$(UL_PROTO_DATADIR)/emacs/site-lisp"
UL_PROTO_DOCDIR     = $(UL_PROTO_DATADIR)/doc/ocaml
UL_PROTO_EXAM       = $(UL_PROTO_DOCDIR)/otherlibs/labltk

# This action unpacks the additional tarballs and builds some additional
# useful programs.  For example, the ocamlbyteinfo and ocamlplugininfo
# utilities are useful additions from Debian, and also included in RHEL.
# http://git.debian.org/?p=pkg-ocaml-maint/packages/ocaml.git;a=tree;f=debian/ocamlbyteinfo;hb=HEAD
#

COMPONENT_POST_BUILD_ACTION = (cd $(@D); \
                $(GTAR) xf $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1); \
                $(GTAR) xf $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_3); \
                $(CP) $(COMPONENT_DIR)/files/ocamlbyteinfo.ml $(@D); \
                $(CP) $(COMPONENT_DIR)/files/ocamlplugininfo.ml $(@D); \
                $(CP) ./otherlibs/dynlink/natdynlink.ml .; \
                ($(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) \
                 $(COMPONENT_BUILD_ARGS) -C emacs ocamltags); \
                ($(ENV) $(COMPONENT_BUILD_ENV) \
                 boot/ocamlrun ./ocamlc $(UL_OCAML_ALLINCLUDES) \
                 dynlinkaux.cmo ocamlbyteinfo.ml -o ocamlbyteinfo); \
                ($(ENV) $(COMPONENT_BUILD_ENV) \
                 boot/ocamlrun ./ocamlopt $(UL_OCAML_ALLINCLUDES) \
                 unix.cmxa str.cmxa natdynlink.ml ocamlplugininfo.ml \
                 -o ocamlplugininfo); \
                ($(ENV) $(COMPONENT_BUILD_ENV) \
                 boot/ocamlrun ./ocamlopt $(UL_OCAML_INCLUDES) \
                 -o objinfo config.cmx tools/objinfo.ml))

COMPONENT_INSTALL_ARGS += BINDIR="$(UL_PROTO_BINDIR)"
COMPONENT_INSTALL_ARGS += LIBDIR="$(UL_PROTO_LIBDIR)/ocaml"
COMPONENT_INSTALL_ARGS += MANDIR="$(PROTOUSRSHAREMANDIR)"
COMPONENT_INSTALL_ARGS += EMACSDIR="$(UL_PROTO_DATADIR)/emacs/site-lisp"

# This action moves additional files we want to install into the proto area.
# I prefer using "cp -R" for copying the documentation tarball and example
# contents since it will make it easier to see new files need to be packaged
# when Ocaml is updated.
#
COMPONENT_POST_INSTALL_ACTION = (cd $(@D)/emacs ; \
                $(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) install install-ocamltags $(COMPONENT_INSTALL_ARGS); \
                cd $(@D); \
                $(MKDIR) -p $(UL_PROTO_INFODIR); \
                $(CP) $(@D)/infoman/ocaml*.gz $(UL_PROTO_INFODIR); \
                $(MKDIR) -p $(UL_PROTO_EXAM); \
                $(CP) $(UL_OCAML_PDFDOC) $(UL_PROTO_DOCDIR)/refman.pdf; \
                $(CP) -R $(@D)/htmlman $(UL_PROTO_DOCDIR); \
                $(CP) -R $(@D)/otherlibs/labltk/examples_* $(UL_PROTO_EXAM); \
                $(RM) $(UL_PROTO_EXAM)/examples_*/.cvsignore)

# ASLR should be enabled when 64-bit support is enabled, which is planned as
# a follow-on step.
#
# ASLR_MODE = $(ASLR_DISABLE)

# Files built in the COMPONENT_POST_INSTALL_ACTION are found by setting
# PKG_PROTO_DIRS as follows:
#
PKG_PROTO_DIRS +=       $(BUILD_DIR_$(BITS))

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
