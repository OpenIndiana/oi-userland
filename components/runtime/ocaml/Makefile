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
# Copyright 2023 Friedrich Kink. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			ocaml
COMPONENT_VERSION_MAJOR=	5.2
COMPONENT_VERSION=		$(COMPONENT_VERSION_MAJOR).0
COMPONENT_SUMMARY=		Objective Caml compiler and programming environment
COMPONENT_DESCRIPTION=	Objective Caml is a high-level, strongly-typed, functional and object-oriented programming language \
from the ML family of languages. This package comprises two batch compilers \
(a fast bytecode compiler and an optimizing native-code compiler), an interactive toplevel system, \
parsing tools (Lex,Yacc,Camlp4), a replay debugger,  documentation generator, and a comprehensive library.
COMPONENT_PROJECT_URL=		https://ocaml.org
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_SRC=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:48554abfd530fcdaa08f23f801b699e4f74c320ddf7d0bd56b0e8c24e55fc911
COMPONENT_ARCHIVE_URL=	https://github.com/$(COMPONENT_NAME)/$(COMPONENT_NAME)/archive/$(COMPONENT_ARCHIVE_SRC)
COMPONENT_FMRI=			runtime/ocaml
COMPONENT_CLASSIFICATION=	Development/System
COMPONENT_LICENSE=		QPLv1, GPLv2
COMPONENT_LICENSE_FILE=	LICENSE

# Documentation sources
COMPONENT_ARCHIVE_1=		ocaml-$(COMPONENT_VERSION_MAJOR)-refman-html.tar.gz
COMPONENT_ARCHIVE_HASH_1=	sha256:361b7096d0092b11b96f0beee217af2b8c6fe3981145a2c4b4d43d656e4dcaf5
COMPONENT_ARCHIVE_URL_1=	https://caml.inria.fr/distrib/ocaml-$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_ARCHIVE_1)

COMPONENT_ARCHIVE_2=		ocaml-$(COMPONENT_VERSION_MAJOR)-refman.pdf
COMPONENT_ARCHIVE_HASH_2=	sha256:898c1d57eff48fb4756e87a96af5a144686e8fd5413f44ca3f8b47831917d621
COMPONENT_ARCHIVE_URL_2=	https://caml.inria.fr/distrib/ocaml-$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_ARCHIVE_2)

COMPONENT_ARCHIVE_3=		ocaml-$(COMPONENT_VERSION_MAJOR)-refman.info.tar.gz
COMPONENT_ARCHIVE_HASH_3=	sha256:947d1f44d27a096b421e791dd2b46776e5bc87cee1f451bf701687d87d09553e
COMPONENT_ARCHIVE_URL_3=	https://caml.inria.fr/distrib/ocaml-$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_ARCHIVE_3)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ARGS= -j1

# Set up some environment variables to make things look nicer.
# We make an 64 build and use /usr/bin/ for the commands
UL_OCAML_PDFDOC     = $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_2)

CONFIGURE_OPTIONS  = --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))/$(COMPONENT_NAME)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --datarootdir=$(CONFIGURE_PREFIX)/share/$(COMPONENT_NAME)
CONFIGURE_OPTIONS += --disable-debug-runtime
CONFIGURE_OPTIONS += --without-gnu-ld
CONFIGURE_OPTIONS += --enable-installing-bytecode-programs
CONFIGURE_OPTIONS += --enable-flambda
# otherwise no tests possible
CONFIGURE_OPTIONS += --enable-ocamltest

COMPONENT_PRE_CONFIGURE_ACTION= ($(CLONEY) $(SOURCE_DIR) $(@D))

# otherwise test run would not succeed
COMPONENT_POST_CONFIGURE_ACTION= $(GSED) -i -e 's:$(SOURCE_DIR):$(@D):' $(@D)/ocamltest/ocamltest_config.ml

COMPONENT_BUILD_TARGETS= world opt opt.opt

COMPONENT_POST_BUILD_ACTION= ( \
	cd $(@D); \
	$(GTAR) xf $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1); \
	$(GTAR) xf $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_3); )

# This action moves additional files we want to install into the proto area.
# I prefer using "cp -R" for copying the documentation tarball and example
# contents since it will make it easier to see new files need to be packaged
# when Ocaml is updated.
#
COMPONENT_POST_INSTALL_ACTION= ( \
	cd $(@D) && \
	$(MKDIR) $(PROTOUSRSHAREDIR)/info && \
	$(MKDIR) $(PROTOUSRSHAREDOCDIR)/$(COMPONENT_NAME) && \
	$(CP) $(@D)/infoman/ocaml*.gz $(PROTOUSRSHAREDIR)/info && \
	$(CP) $(UL_OCAML_PDFDOC) $(PROTOUSRSHAREDOCDIR)/$(COMPONENT_NAME)/refman.pdf && \
	$(CP) -R $(@D)/htmlman $(PROTOUSRSHAREDOCDIR)/$(COMPONENT_NAME))

# target all uses the new ocamltests, legacy uses the Makefile based tests.
# All tests succeed but the parsing of the ocamltest results is wrong and 
# leads to erroneously failing tests.
# Only native tests are concerned.
COMPONENT_TEST_TARGETS= all
#COMPONENT_TEST_TARGETS = legacy
COMPONENT_TEST_ARGS += SHELL=$(SHELL) 
COMPONENT_TEST_DIR=  $(@D)/testsuite
COMPONENT_TEST_TRANSFORMER= $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/tests passed|tests skipped|tests failed|unexpected errors|tests considered/'"

ASLR_MODE= $(ASLR_ENABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
