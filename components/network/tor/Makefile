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
# Copyright 2014-2017 Alexander Pyhalov
# Copyright 2019, Michal Nowak
# Copyright 2023, Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tor
COMPONENT_VERSION=	0.4.8.14
COMPONENT_PROJECT_URL=	https://www.torproject.org
COMPONENT_SUMMARY=	Anonymizing overlay network for TCP
COMPONENT_FMRI=		network/tor
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:5047e1ded12d9aac4eb858f7634a627714dd58ce99053d517691a4b304a66d10
COMPONENT_ARCHIVE_URL=	https://dist.torproject.org/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc	
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_LICENSE=	BSD, OPEN DATA LICENSE

include $(WS_MAKE_RULES)/common.mk

CPPFLAGS += -I/usr/include/libevent2 -I$(OPENSSL_INCDIR)
LDFLAGS  += -L$(OPENSSL_LIBDIR)

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -f)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--localstatedir=/var
CONFIGURE_OPTIONS+=	--disable-dependency-tracking

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_TEST_ENV+=	PATH=$(PATH.gnu)

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/TOTAL:/p" ' \
	'-e "/SKIP:/p" ' \
	'-e "/PASS:/p" ' \
	'-e "/FAIL:/p" ' \
	'-e "/ERROR:/p" '

# Tests require GNU diff
REQUIRED_PACKAGES += text/gnu-diffutils
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)

# Bogus dependency due to libssp
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
