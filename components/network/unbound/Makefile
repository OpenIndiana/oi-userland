#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			unbound
COMPONENT_VERSION=		1.22.0
COMPONENT_SUMMARY=		Unbound is a validating, recursive, caching DNS resolver
COMPONENT_PROJECT_URL=	https://nlnetlabs.nl/projects/unbound/about/
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/NLnetLabs/unbound/archive/refs/tags/release-$(COMPONENT_VERSION).tar.gz
COMPONENT_SIG_URL=		$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_ARCHIVE_HASH=	sha256:4e32a36d57cda666b1c8ee02185ba73462330452162d1b9c31a5b91a853ba946
COMPONENT_FMRI=			service/network/unbound
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=		BSD
COMPONENT_LICENSE_FILE=	LICENSE
# For check_anitya target, https://release-monitoring.org/project/5042
COMPONENT_ANITYA_ID=	5042

include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_UNPACK_ACTION= ( $(MV) $(COMPONENT_NAME)-release-$(COMPONENT_VERSION) $(COMPONENT_SRC) )

COMPONENT_PREP_ACTION= ( cd $(@D) ; autoreconf -fiv )

# Provide paths for OpenSSL 3.1
CFLAGS  += -I$(OPENSSL_INCDIR)
LDFLAGS += -L$(OPENSSL_LIBDIR)

CLAGS += $(XPG6MODE)

CPPFLAGS += -I/usr/include/libevent2
LDFLAGS += -L/usr/lib/$(MACH64) -levent-2.1

PATH= $(PATH.gnu)

CONFIGURE_ENV += CPPFLAGS=$(CPPFLAGS)

CONFIGURE_OPTIONS += --enable-static=no
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --with-ssl=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS += --with-pthreads
CONFIGURE_OPTIONS += --with-libevent
CONFIGURE_OPTIONS += --with-libnghttp2
CONFIGURE_OPTIONS += --with-username=unbound

COMPONENT_TEST_TRANSFORMS += \
	'-e "0,/^\.\/unittest$$/d"' \
	'-e "/^\[0\] did 10000 in/d"' \
	'-e "/^[0-9]* checks ok./d"' \
	'-e "/Leaving directory/d"'

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += library/nghttp2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
