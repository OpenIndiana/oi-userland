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
# Copyright 2022 Gary Mills
# Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		antlr
# This is an ancient version, but a dependency of the ant package
COMPONENT_VERSION=	2.7.7
COMPONENT_REVISION=	3
COMPONENT_SUMMARY=	ANother Tool for Language Recognition
COMPONENT_DESCRIPTION=	ANTLR, ANother Tool for Language Recognition, (formerly PCCTS) is a language tool that provides a framework \
						for constructing recognizers, compilers, and translators from grammatical descriptions containing C++ or \
						Java actions [You can use PCCTS 1.xx to generate C-based parsers].
COMPONENT_PROJECT_URL=	https://www.antlr.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:853aeb021aef7586bda29e74a6b03006bcb565a755c86b66032d8ec31b67dbb9
COMPONENT_ARCHIVE_URL=	https://www.antlr2.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			developer/parser/antlr-2
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=		Public Domain
COMPONENT_LICENSE_FILE=	LICENSE.txt

# Use version of Java defined in ../../make-rules/shared-macros.mk
PATH=$(JAVA_HOME)/bin:/usr/bin

include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL = 0

CONFIGURE_OPTIONS += --without-examples
# Omit python 2.7 from this build
CONFIGURE_OPTIONS += --disable-python

COMPONENT_INSTALL_ARGS += prefix=$(PROTOUSRDIR)
COMPONENT_INSTALL_ARGS += libdir=$(PROTOUSRLIBDIR)
COMPONENT_INSTALL_ARGS += bindir=$(PROTOUSRBINDIR)
COMPONENT_INSTALL_ARGS += sbindir=$(PROTOUSRSBINDIR)

# Needed to find the antlr man page.
PKG_PROTO_DIRS += $(COMPONENT_DIR)/files

COMPONENT_TEST_TARGETS = test

ASLR_MODE = $(ASLR_ENABLE)

# Rename some files to accomodate newer versions of antlr
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRBINDIR); $(MV) antlr antlr-$(COMPONENT_VERSION); \
	$(MV) antlr-config antlr-config-$(COMPONENT_VERSION)) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRLIBDIR); $(MV) antlr.jar antlr-$(COMPONENT_VERSION).jar) ;

# Added build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
