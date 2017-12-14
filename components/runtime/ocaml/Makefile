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
# Copyright 2017 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

include ../../../make-rules/shared-macros.mk

PATH= $(PATH.gnu)

COMPONENT_NAME=		       ocaml
COMPONENT_FMRI=          runtime/ocaml
COMPONENT_VERSION_MAJOR= 4.06
COMPONENT_VERSION=       $(COMPONENT_VERSION_MAJOR).0
IPS_COMPONENT_VERSION=   4.0.6
COMPONENT_PROJECT_URL=	 http://www.ocaml.org
COMPONENT_SRC=		       $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	     $(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=  sha256:011879c913e8f988ecdac020b205e2baa4023052efed25013bdb9a6b0d5c6a80
COMPONENT_ARCHIVE_URL=   https://github.com/$(COMPONENT_NAME)/$(COMPONENT_NAME)/archive/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY=       Objective Caml compiler and programming environment
COMPONENT_LICENSE=       QPLv1, GPLv2
COMPONENT_LICENSE_FILE=  $(COMPONENT_NAME).license
COMPONENT_CLASSIFICATION= Development/System
COMPONENT_DESCRIPTION= Objective Caml is a high-level, strongly-typed, functional and \
object-oriented programming language from the ML family of languages. This package comprises \
two batch compilers (a fast bytecode compiler and an optimizing native-code compiler), \
an interactive toplevel system, parsing tools (Lex,Yacc,Camlp4), a replay debugger, \
a documentation generator, and a comprehensive library.

# Documentation sources
#
COMPONENT_ARCHIVE_1= ocaml-$(COMPONENT_VERSION_MAJOR)-refman-html.tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:a9a0b94eaead064c525a62de6520b5092a0ea0467c2f03584d6fa462c9afaa7e
COMPONENT_ARCHIVE_URL_1= https://caml.inria.fr/distrib/ocaml-$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_ARCHIVE_1)

COMPONENT_ARCHIVE_2= ocaml-$(COMPONENT_VERSION_MAJOR)-refman.pdf
COMPONENT_ARCHIVE_HASH_2= sha256:e6c13808ea06ef3de3e7708073fafa338e0354c5662a2bbc5847356cd354af71
COMPONENT_ARCHIVE_URL_2= https://caml.inria.fr/distrib/ocaml-$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_ARCHIVE_2)

COMPONENT_ARCHIVE_3= ocaml-$(COMPONENT_VERSION_MAJOR)-refman.info.tar.gz
COMPONENT_ARCHIVE_HASH_3= sha256:28581838c61492ee20f5380a9cf240a692d430dfb32cbc75f611f6a29b55ccac
COMPONENT_ARCHIVE_URL_3= https://caml.inria.fr/distrib/ocaml-$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_ARCHIVE_3)


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk


COMPONENT_BUILD_ARGS += -j1

# Set up some environment variables to make things look nicer.
# We make an 64 build and use /usr/bin/ for the commands
UL_OCAML_PDFDOC     = $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_2)
UL_OCAML_INCLUDES = -nostdlib -I stdlib -I utils -I parsing -I typing -I bytecomp -I asmcomp -I driver
UL_OCAML_ALLINCLUDES = $(UL_OCAML_INCLUDES) -I otherlibs/unix -I otherlibs/str -I otherlibs/dynlink
UL_PROTO_BINDIR     = $(PROTO_DIR)/$(CONFIGURE_BINDIR.32)
UL_PROTO_LIBDIR     = $(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS))
UL_PROTO_INFODIR    = $(PROTO_DIR)/$(CONFIGURE_INFODIR)
UL_PROTO_DATADIR    = $(PROTO_DIR)/$(CONFIGURE_PREFIX)/share
UL_PROTO_DOCDIR     = $(UL_PROTO_DATADIR)/doc/ocaml
UL_PROTO_EXAM       = $(UL_PROTO_DOCDIR)/otherlibs/labltk

# Ocaml does not use a standard configure script, but has its own handwritten
# one.  So we must specify the arguments it accepts by hand.
#
CONFIGURE_OPTIONS  = --bindir $(CONFIGURE_BINDIR.32)
CONFIGURE_OPTIONS += --libdir $(CONFIGURE_LIBDIR.$(BITS))/ocaml
CONFIGURE_OPTIONS += --x11lib $(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --x11include $(CONFIGURE_INCLUDEDIR)
CONFIGURE_OPTIONS += --mandir $(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += -cc "$(GCC_ROOT)/bin/gcc $(CC_BITS)"
CONFIGURE_OPTIONS += -aspp "$(GCC_ROOT)/bin/gcc $(CC_BITS) -c"
CONFIGURE_OPTIONS += -as "$(GAS) --$(BITS)"
CONFIGURE_OPTIONS += -spacetime
CONFIGURE_OPTIONS += -flambda
CONFIGURE_OPTIONS += -verbose

COMPONENT_PRE_CONFIGURE_ACTION = \
  ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_BUILD_TARGETS = world opt opt.opt

COMPONENT_POST_BUILD_ACTION = (cd $(@D); \
   $(GTAR) xf $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1); \
   $(GTAR) xf $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_3); \
   ($(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) \
   $(COMPONENT_BUILD_ARGS) -C emacs ocamltags)) 

COMPONENT_INSTALL_ARGS += EMACSDIR="$(UL_PROTO_DATADIR)/emacs/site-lisp"

# This action moves additional files we want to install into the proto area.
# I prefer using "cp -R" for copying the documentation tarball and example
# contents since it will make it easier to see new files need to be packaged
# when Ocaml is updated.
#
COMPONENT_POST_INSTALL_ACTION = (cd $(@D)/emacs &&\
                $(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) BINDIR=$(UL_PROTO_BINDIR) install install-ocamltags $(COMPONENT_INSTALL_ARGS) &&\
                cd $(@D) &&\
                $(MKDIR) -p $(UL_PROTO_INFODIR) &&\
                $(CP) $(@D)/infoman/ocaml*.gz $(UL_PROTO_INFODIR) &&\
                $(MKDIR) -p $(UL_PROTO_EXAM) &&\
                $(CP) $(UL_OCAML_PDFDOC) $(UL_PROTO_DOCDIR)/refman.pdf &&\
                $(CP) -R $(@D)/htmlman $(UL_PROTO_DOCDIR)) 

# target all uses the new ocamltests, legacy uses the Makefile based tests.
# All tests succeed but the parsing of the ocamltest results is wrong and 
# leads to erroneously failing tests.
# Only native tests are concerned.
#COMPONENT_TEST_TARGETS = all
COMPONENT_TEST_TARGETS = legacy
COMPONENT_TEST_ARGS += SHELL=$(SHELL) 
COMPONENT_TEST_DIR =  $(@D)/testsuite
COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS  = "'/tests passed|tests skipped|tests failed|unexpected errors|tests considered/'"

# ASLR should be enabled when 64-bit support is enabled
# ASLR_MODE = $(ASLR_DISABLE)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		  $(TEST_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += editor/gnu-emacs
