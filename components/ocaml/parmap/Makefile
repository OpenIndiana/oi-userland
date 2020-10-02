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

COMPONENT_NAME= parmap
COMPONENT_VERSION= 1.0-rc11
COMPONENT_REVISION= 1
IPS_COMPONENT_VERSION=1.0.11
COMPONENT_SUMMARY= parmap - OCaml minimalistic library allowing to exploit multicore architecture
COMPONENT_PROJECT_URL= https://github.com/rdicosmo/parmap
COMPONENT_FMRI= library/ocaml/parmap
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
  https://github.com/rdicosmo/parmap/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:3420224919ce1a2910db5c40272b2a18a32e69491b55d49254cfb4a715081e5e
COMPONENT_LICENSE= GPLv2

COMPONENT_BUILD_ARGS= -j1

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk
include $(WS_MAKE_RULES)/ocaml.mk

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION  +=  $(CLONEY) $(SOURCE_DIR) $(@D) ;

COMPONENT_PRE_INSTALL_ACTION += ( $(RM) -r $(PROTO_DIR)$(OCAMLFIND_DESTDIR) && \
                                $(MKDIR) $(PROTO_DIR)$(OCAMLFIND_DESTDIR)/stublibs; )

# Build dependencies
REQUIRED_PACKAGES+= library/ocaml/ocamlbuild
REQUIRED_PACKAGES+= library/ocaml/ocaml-findlib

# Auto-generated dependencies
REQUIRED_PACKAGES+= runtime/ocaml
