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
# Copyright 2016, Jim Klimov. All rights reserved.
# Copyright 2022, Friedrich Kink. All rights reserved.
#

BUILD_BITS=             64
BUILD_STYLE=            cmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		clamav
### For X.Y.0 versions the TGZ and DIR do not include trailing .0 piece
### But our IPS version should better have same number of components.
### So the COMPONENT_VERSION may be 0.99 or 0.99.1 (as in original),
### but the IPS_COMPONENT_VERSION is forced to 3-part 0.99.0 or 0.99.1.
COMPONENT_VERSION=	0.104.2
ifeq ($(words $(subst ., ,$(COMPONENT_VERSION))),2)
 IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).0
else
 IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION)
endif
COMPONENT_SUMMARY=	ClamAV $(IPS_COMPONENT_VERSION) opensource antivirus toolkit
COMPONENT_FMRI= 	antivirus/$(COMPONENT_NAME)
COMPONENT_DESCRIPTION=	ClamAV is an open source (GPLv2) anti-virus toolkit, designed \
			especially for e-mail scanning on mail gateways. It provides a \
			number of utilities including a flexible and scalable \
			multi-threaded daemon, a command line scanner and advanced tool \
			for automatic database updates. The core of the package is an \
			anti-virus engine available in a form of shared library.
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:3e45e46d9aaeb3a6956ed30376237ab7c4cd9573bc0f5d6fc15c588d30978d9d
COMPONENT_PROJECT_URL=	http://www.clamav.net/
COMPONENT_ARCHIVE_URL=	http://www.clamav.net/downloads/production/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).sig
COMPONENT_LICENSE_FILE=	COPYING.$(COMPONENT_NAME)
COMPONENT_LICENSE=	GPLv2,LGPL,Apache
# We need to use non-default User-Agent for the fetch, otherwise we are denied
# to download the source file.
COMPONENT_FETCH_USER_AGENT=	fetch

include $(WS_MAKE_RULES)/common.mk

# Note: This is done just in case, because according to
# https://github.com/vrtadmin/clamav-devel/issues/45 currently
#   ClamAV doesn't support scanning files larger than 2.7GB due
#   to constraints in the scanning engine.
# Still, this can help with not dying on e.g. huge log files :-)
CFLAGS += $(CPP_LARGEFILES)
CFLAGS   += $(CPP_XPG5MODE)

CPPFLAGS += $(CPP_LARGEFILES)

# gather all License files in one
COMPONENT_PREP_ACTION= (cd $(@D) && for f in COPYING/*; do cat $$f >> COPYING.$(COMPONENT_NAME) ; done )

CMAKE_ENV+=		LDFLAGS="-lsocket -lnsl"

CMAKE_OPTIONS+=		-DPCRE2_INCLUDE_DIR=/usr/include/pcre
CMAKE_OPTIONS+=		-DBYTECODE_RUNTIME=interpreter
#CMAKE_OPTIONS+=		-DLLVM_ROOT_DIR=/usr/clang/9.0
CMAKE_OPTIONS+=		-DAPP_CONFIG_DIRECTORY=/etc/clamav
CMAKE_OPTIONS+=		-DCMAKE_SKIP_RPATH=ON
CMAKE_OPTIONS+=		-DENABLE_UNRAR=ON
CMAKE_OPTIONS+=		-DENABLE_SYSTEMD=OFF

# ClamAV has a JIT bytecode support based on CLang LLVM.
# All currently available CLang LLVM versions does not build with clamav
# Additionly included CLang LLVM was removed, so only available
# bytecode support is interpreter.

COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/passed/p" '

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TESTS_64)

# Needed for cmake tests
REQUIRED_PACKAGES += system/library/iconv/unicode
REQUIRED_PACKAGES += developer/check
# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/json-c
REQUIRED_PACKAGES += library/libmilter
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
