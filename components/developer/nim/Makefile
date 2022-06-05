#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 Niklas Poslovski
#
BUILD_BITS=32
BUILD_STYLE=justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			nim
COMPONENT_VERSION=		1.6.6
COMPONENT_FMRI=			developer/nim
COMPONENT_SUMMARY=		Imperative, multi-paradigm, compiled programming language
COMPONENT_CLASSIFICATION=Development/Other Languages
COMPONENT_PROJECT_URL=	https://nim-lang.org
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:67b111ce6f3861503b9fcc1cae59fc34d0122566d3ecfef3a064a2174121a452
COMPONENT_ARCHIVE_URL= \
	https://nim-lang.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		MIT

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ACTION= \
    cd $(@D); $(ENV) $(COMPONENT_BUILD_ENV) ./build.sh; bin/nim c koch; ./koch boot -d:release; ./koch tools

COMPONENT_INSTALL_ACTION= \
    mkdir -p $(PROTOUSRBINDIR); cp -a $(@D)/bin/* $(PROTOUSRBINDIR); rm $(PROTOUSRBINDIR)/nim-gdb ; cp -a $(SOURCE_DIR)/bin/nim-gdb $(PROTOUSRBINDIR); mkdir -p $(PROTOETCDIR)/nim; cp -a $(SOURCE_DIR)/config/* $(PROTOETCDIR)/nim; mkdir -p $(PROTOUSRLIBDIR)/nim; cp -a $(SOURCE_DIR)/lib/* $(PROTOUSRLIBDIR)/nim; cp -a $(SOURCE_DIR)/compiler $(PROTOUSRLIBDIR)/nim/compiler; mkdir -p $(PROTOUSRINCDIR); mv $(PROTOUSRLIBDIR)/nim/*.h $(PROTOUSRINCDIR); mkdir -p $(PROTOUSRSHAREDIR)/nim; cp -a $(SOURCE_DIR)/doc $(PROTOUSRSHAREDIR)/nim

#COMPONENT_TEST_CMD= ./koch tests all # Doesn't work, a solution hasn't been found yet.

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
