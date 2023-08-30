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
# Copyright 2023, Friedrich Kink. All rights reserved.
#

BUILD_BITS= 64
BUILD_STYLE= cmake
USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	clamav
### For X.Y.0 versions the TGZ and DIR do not include trailing .0 piece
### But our IPS version should better have same number of components.
### So the COMPONENT_VERSION may be 0.99 or 0.99.1 (as in original),
### but the IPS_COMPONENT_VERSION is forced to 3-part 0.99.0 or 0.99.1.
COMPONENT_VERSION=	1.2.0
ifeq ($(words $(subst ., ,$(COMPONENT_VERSION))),2)
 IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).0
else
 IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION)
endif
COMPONENT_SUMMARY=	ClamAV $(IPS_COMPONENT_VERSION) opensource antivirus toolkit
COMPONENT_DESCRIPTION=	ClamAV is an open source (GPLv2) anti-virus toolkit, designed \
			especially for e-mail scanning on mail gateways. It provides a \
			number of utilities including a flexible and scalable \
			multi-threaded daemon, a command line scanner and advanced tool \
			for automatic database updates. The core of the package is an \
			anti-virus engine available in a form of shared library.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:97a192dffe141480b56cabf1063d79a9fc55cd59203241fa41bfc7a98a548020
COMPONENT_PROJECT_URL=	https://www.clamav.net
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/downloads/production/$(COMPONENT_ARCHIVE)
#COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).sig
COMPONENT_FMRI= 	antivirus/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv2,LGPL,Apache
COMPONENT_LICENSE_FILE=	COPYING.$(COMPONENT_NAME)
# We need to use non-default User-Agent for the fetch, otherwise we are denied
# to download the source file.
COMPONENT_FETCH_USER_AGENT=	fetch

include $(WS_MAKE_RULES)/common.mk

# clamav now additionally also depends on rust :-(
CARGO_HOME=		$(BUILD_DIR)/.cargo

PATH=			$(PATH.gnu)

ENV +=			CARGO_HOME=$(CARGO_HOME)

CONFIGURE_ENV=		$(ENV)
COMPONENT_BUILD_ENV=	$(ENV)

# Note: This is done just in case, because according to
# https://github.com/vrtadmin/clamav-devel/issues/45 currently
#   ClamAV doesn't support scanning files larger than 2.7GB due
#   to constraints in the scanning engine.
# Still, this can help with not dying on e.g. huge log files :-)
CFLAGS += $(CPP_LARGEFILES)
CFLAGS += $(CPP_XPG5MODE)

CPPFLAGS += $(CPP_LARGEFILES) -I$(OPENSSL_INCDIR)

# gather all License files in one
COMPONENT_PREP_ACTION= (cd $(@D) && for f in COPYING/*; do cat $$f >> COPYING.$(COMPONENT_NAME) ; done )

CMAKE_ENV += LDFLAGS="-L$(OPENSSL_LIBDIR) -lsocket -lnsl"

CMAKE_OPTIONS += -DPCRE2_INCLUDE_DIR=/usr/include/pcre
# clang still does not work
#CMAKE_OPTIONS+= -DBYTECODE_RUNTIME=llvm
CMAKE_OPTIONS += -DBYTECODE_RUNTIME=interpreter
CMAKE_OPTIONS += -DLLVM_ROOT_DIR=$(CLANG_PREFIX)
CMAKE_OPTIONS += -DAPP_CONFIG_DIRECTORY=/etc/clamav
CMAKE_OPTIONS += -DCMAKE_SKIP_RPATH=ON
CMAKE_OPTIONS += -DENABLE_JSON_SHARED=OFF
CMAKE_OPTIONS += -DENABLE_UNRAR=ON
CMAKE_OPTIONS += -DENABLE_SYSTEMD=OFF

# ClamAV has a JIT bytecode support based on CLang LLVM.
# All currently available CLang LLVM versions do not build with clamav
# Additionlly the included CLang LLVM was removed, so the only available
# bytecode support is interpreter.

COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/passed/p" '

# Needed for cmake tests
REQUIRED_PACKAGES += system/library/iconv/unicode
REQUIRED_PACKAGES += developer/check
REQUIRED_PACKAGES += developer/lang/rustc

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/libmilter
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
