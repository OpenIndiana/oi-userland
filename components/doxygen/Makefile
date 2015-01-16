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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		doxygen
COMPONENT_VERSION=	1.8.7
COMPONENT_PROJECT_URL=	http://www.stack.nl/~dimitri/doxygen/index.html
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).src.tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c6eac6b6e82148ae15ec5aecee4631547359f284af1ce94474d046ebca6ee3d9
COMPONENT_ARCHIVE_URL=	http://ftp.stack.nl/pub/users/dimitri/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/doxygen

# Download the manual so that we don't have to keep updating it in the gate.
COMPONENT_ARCHIVE_1 =	$(COMPONENT_NAME)_manual-$(COMPONENT_VERSION).pdf.zip
COMPONENT_ARCHIVE_HASH_1 =	\
    sha256:6796de1e77f723dcb52f36395161fdfbeaeebf769a297eb78b73e19b9542aa59
COMPONENT_ARCHIVE_URL_1 =	ftp://ftp.stack.nl/pub/users/dimitri/$(COMPONENT_ARCHIVE_1)

TPNO=			17646

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Necessary to find CC during build
PATH=$(SPRO_VROOT)/bin:/usr/bin
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
PATH=$(PARFAIT_TOOLS):$(SPRO_VROOT)/bin:/usr/bin
endif


# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

# Need to override default options since configure doesn't
# understand CC, CXX, etc.
CONFIGURE_OPTIONS =	--platform solaris-cc-64
CONFIGURE_OPTIONS +=	--prefix /usr
CONFIGURE_OPTIONS +=	--enable-langs am,ar,br,ca,cn,cz,de,dk,en,eo,es,fa,fi,fr,gr,hr,hu,id,it,je,jp,ke,kr,lt,lv,mk,nl,no,pl,pt,ro,ru,sc,si,sk,sr,sv,tr,tw,ua,vi,za

# Tests not available from the top-level Makefile, nor via a standard target.
# We need to add /usr/gnu/bin to the front of the PATH environment variable
# for "diff -u" and we need to use our latest doxygen binary, not the one
# installed on the system.
#
# Test 12 is a known failure (we don't have bibtex in Solaris).
COMPONENT_TEST_ENV =		PATH="$(GNUBIN):$(PROTO_DIR)/usr/bin:$(PATH)"
COMPONENT_TEST_DIR =		$(BUILD_DIR_64)/testing
COMPONENT_TEST_TARGETS =	tests

# The additional doxygen specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
        '-e "s|\(error opening bib\).*|\1|" ' \
        '-e "s|\(test_output_012/indexpage.xml\).*|\1|" ' \
        '-e "s|\(012/indexpage.xml\).*|\1|" '

ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)
	cd $(PROTO_DIR) ; $(UNPACK) ../../../$(COMPONENT_ARCHIVE_1) 

test:		$(TEST_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
