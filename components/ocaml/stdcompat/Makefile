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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= stdcompat
COMPONENT_VERSION= 14
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= stdcompat - Compatibility module for OCaml standard library 
COMPONENT_PROJECT_URL= https://github.com/thierry-martinez/stdcompat/
COMPONENT_FMRI= library/ocaml/stdcompat
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
  https://github.com/thierry-martinez/stdcompat/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:bfa6d16b451c55216a9f79ca4735a1ada61a6734a822d1faf5a6c77365485c3c
COMPONENT_LICENSE= BSD 2-Clause

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk
include $(WS_MAKE_RULES)/ocaml.mk

PATH=$(PATH.gnu)

COMPONENT_BUILD_ARGS=-j1

COMPONENT_PRE_CONFIGURE_ACTION  +=  $(CLONEY) $(SOURCE_DIR) $(@D) ;

CONFIGURE_LIBDIR.64=$(OCAML_LIBDIR)

# Build dependencies
REQUIRED_PACKAGES+= library/ocaml/ocamlbuild
REQUIRED_PACKAGES+= library/ocaml/ocaml-findlib
REQUIRED_PACKAGES+= runtime/ocaml

# Auto-generated dependencies
