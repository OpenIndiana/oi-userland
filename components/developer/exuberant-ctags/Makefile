#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2016 Sergey Avseyev
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		exuberant-ctags
COMPONENT_VERSION=	5.8
COMPONENT_PROJECT_URL=	http://ctags.sourceforge.net/
COMPONENT_SUMMARY=	A C programming language indexing and/or cross-reference tool
COMPONENT_DESCRIPTION=	\
Ctags generates an index (or tag) file of C language objects found in \
C source and header files.  The index makes it easy for text editors or \
other utilities to locate the indexed items.  Ctags can also generate a \
cross reference file which lists information about the various objects \
found in a set of C language files in human readable form.  Exuberant \
Ctags improves on ctags because it can find all types of C language tags, \
including macro definitions, enumerated values (values inside enum{...}), \
function and method definitions, enum/struct/union tags, external \
function prototypes, typedef names and variable declarations.  Exuberant \
Ctags is far less likely to be fooled by code containing \#if preprocessor \
conditional constructs than ctags.  Exuberant ctags supports output of \
Emacs style TAGS files and can be used to print out a list of selected \
objects found in source files.
COMPONENT_FMRI=         developer/exuberant-ctags
COMPONENT_CLASSIFICATION=	Development/Editors
COMPONENT_SRC=		ctags-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:0e44b45dcabe969e0bbbb11e30c246f81abe5d32012db37395eb57d66e9e99c7
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/ctags/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2+ and LGPLv2+ and Public Domain
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV=	DEST_DIR=$(PROTO_DIR)
COMPONENT_INSTALL_ENV=	DEST_DIR=$(PROTO_DIR)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
