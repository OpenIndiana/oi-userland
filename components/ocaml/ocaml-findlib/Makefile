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

COMPONENT_NAME= ocaml-findlib
COMPONENT_VERSION= 1.8.1
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= ocaml-find - OCaml library manager
COMPONENT_PROJECT_URL= http://projects.camlcity.org/projects/findlib.html
COMPONENT_FMRI= library/ocaml/ocaml-findlib
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_SRC=		ocamlfind-findlib-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL= https://github.com/ocaml/ocamlfind/archive/findlib-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:90e2d16e0e479ea61b7889c41f008530ffa7b6e48f0f52d5d22e006233f35cd2
COMPONENT_LICENSE= MIT

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk
include $(WS_MAKE_RULES)/ocaml.mk

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION  +=  $(CLONEY) $(SOURCE_DIR) $(@D) ;

COMPONENT_BUILD_TARGETS = all opt

CONFIGURE_OPTIONS = -sitelib $(OCAML_LIBDIR)
CONFIGURE_OPTIONS+= -config $(OCAML_ETCDIR)/findlib.conf
CONFIGURE_OPTIONS+= -mandir $(USRSHAREMANDIR) 

COMPONENT_INSTALL_ARGS+= prefix=$(PROTO_DIR)

# Build dependencies
REQUIRED_PACKAGES+= developer/documentation-tool/openjade 
REQUIRED_PACKAGES+= runtime/ocaml

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
