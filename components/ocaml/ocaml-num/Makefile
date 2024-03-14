#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2020 Aurelien Larcher
#

BUILD_BITS=64
BUILD_STYLE=justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ocaml-num
COMPONENT_VERSION= 1.5
COMPONENT_SUMMARY= ocaml-num - OCaml library for arbitrary-precision integer and rational arithmetic
COMPONENT_PROJECT_URL= https://github.com/ocaml/num
COMPONENT_SRC=			num-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/ocaml/num/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:7ae07c8f5601e2dfc5008a62dcaf2719912ae596a19365c5d7bdf2230515959a
COMPONENT_FMRI= library/ocaml/ocaml-num
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE= LGPLv2.1
COMPONENT_LICENSE_FILE= LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk
include $(WS_MAKE_RULES)/ocaml.mk

PATH= $(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION += ( $(CLONEY) $(SOURCE_DIR) $(@D) );

OCAMLFIND_DESTDIR= $(strip $(shell ocamlfind printconf destdir))

COMPONENT_PRE_INSTALL_ACTION += ( \
	$(RM) -r $(PROTO_DIR)$(OCAMLFIND_DESTDIR) && \
	$(MKDIR) $(PROTO_DIR)$(OCAMLFIND_DESTDIR)/stublibs; )

COMPONENT_INSTALL_TARGETS= findlib-install
COMPONENT_INSTALL_ARGS+= OCAMLFIND_DESTDIR=$(PROTO_DIR)$(OCAMLFIND_DESTDIR)

# Build dependencies
REQUIRED_PACKAGES+= runtime/ocaml
REQUIRED_PACKAGES+= library/ocaml/ocaml-findlib

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/ocaml
REQUIRED_PACKAGES += system/library
