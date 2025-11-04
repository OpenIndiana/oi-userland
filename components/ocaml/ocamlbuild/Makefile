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
# Copyright 2023 Friedrich Kink
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	ocamlbuild
COMPONENT_VERSION=	0.16.1
COMPONENT_SUMMARY=	OCamlbuild is a generic build tool that has built-in rules for building OCaml library and programs
COMPONENT_PROJECT_URL=	https://github.com/ocaml/ocamlbuild
COMPONENT_FMRI=	library/ocaml/ocamlbuild
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/ocaml/ocamlbuild/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:2ba6857f2991b7f69368e8db818b163d31cf5a367f15f5953bf8f01a77b3d4fc
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk
include $(WS_MAKE_RULES)/ocaml.mk

PATH= $(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION += ( $(CLONEY) $(SOURCE_DIR) $(@D) );

COMPONENT_BUILD_ARGS += PREFIX=$(USRDIR) MANDIR=$(USRSHAREMANDIR)
COMPONENT_INSTALL_ARGS += CHECK_IF_PREINSTALLED=false

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/ocaml
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
