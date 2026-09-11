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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= stdcompat
COMPONENT_VERSION= 21.1.1
HUMAN_VERSION= 21.1+comp5.5
COMPONENT_SUMMARY= Compatibility module for OCaml standard library 
COMPONENT_PROJECT_URL= https://github.com/thierry-martinez/stdcompat
COMPONENT_FMRI= library/ocaml/stdcompat
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/compatibility_with_OCaml_5.4_and_5.5.tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:90dab103e9fda68021a81fcc1789707058a501d7de49510094fc9aa3fc5f0c34
COMPONENT_LICENSE=	LGPGL-2.1
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk
include $(WS_MAKE_RULES)/ocaml.mk

PATH=$(PATH.gnu)

COMPONENT_BUILD_ARGS=-j1

COMPONENT_POST_UNPACK_ACTION += ( $(MV) stdcompat-compatibility_with_OCaml_5.4_and_5.5 $(COMPONENT_SRC) ) ;
COMPONENT_PRE_CONFIGURE_ACTION += ( $(CLONEY) $(SOURCE_DIR) $(@D) ) ;

CONFIGURE_LIBDIR.64=$(OCAML_LIBDIR)

# Build dependencies
REQUIRED_PACKAGES+= library/ocaml/ocamlbuild
REQUIRED_PACKAGES+= library/ocaml/ocaml-findlib
REQUIRED_PACKAGES+= runtime/ocaml

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/ocaml
REQUIRED_PACKAGES += system/library
