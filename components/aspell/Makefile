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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#
COMPILER =		gcc

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		aspell
COMPONENT_VERSION=	0.60.6.1
COMPONENT_PROJECT_URL=	http://aspell.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f52583a83a63633701c5f71db3dc40aab87b7f76b29723aeb27941eff42df6e1
COMPONENT_ARCHIVE_URL=	ftp://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

COMPONENT_NAME_1=	aspell6-en
COMPONENT_VERSION_1=	7.1-0
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.bz2
COMPONENT_ARCHIVE_HASH_1= \
    sha256:ff9df3c2e8c5bb19c6a66078b36a0ef4c4dfb0fcb969e29f7b5345e26d748d0a
COMPONENT_ARCHIVE_URL_1= ftp://ftp.gnu.org/gnu/$(COMPONENT_NAME)/dict/en/$(COMPONENT_ARCHIVE_1)
SOURCE_DIR_1=		$(COMPONENT_DIR)/$(COMPONENT_SRC_1)

COMPONENT_BUGDB=	utility/aspell

TPNO=			23575

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

ASPELL_BIN_DIR.32 =	$(PROTOUSRBINDIR)
ASPELL_BIN_DIR.64 =	$(PROTOUSRBINDIR64)
ASPELL_BIN_DIR =	$(ASPELL_BIN_DIR.$(BITS))

ASPELL_LIB_DIR.32 =	$(PROTOUSRLIBDIR)
ASPELL_LIB_DIR.64 =	$(PROTOUSRLIBDIR64)
ASPELL_LIB_DIR =	$(ASPELL_LIB_DIR.$(BITS))

# Needed to successfully find .../gen/mk-dirs_h.pl
COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));

# Needed to configure, build and install the aspell English dictionary.
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(SOURCE_DIR_1) ; \
		PATH="$(ASPELL_BIN_DIR):$(PATH)" \
		./configure --vars \
		    ASPELL_FLAGS=--data-dir=$(ASPELL_LIB_DIR)/aspell-0.60 \
		    DESTDIR=$(PROTO_DIR));
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(SOURCE_DIR_1) ; \
		export LD_LIBRARY_PATH=$(ASPELL_LIB_DIR); \
		PATH="$(ASPELL_BIN_DIR):$(PATH)" \
		$(GMAKE) install);

CXX +=			$(CC_BITS)
CC +=			$(CC_BITS)

CONFIGURE_ENV +=	LD_OPTIONS="$(LD_OPTIONS)"

CLEAN_PATHS +=		$(SOURCE_DIR_1)
PKG_PROTO_DIRS +=	$(SOURCE_DIR_1)

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
