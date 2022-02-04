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
# Copyright 2022 Friedrich Kink
#

BUILD_BITS=		64 
USE_OPENSSL11=		yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pigeonhole
COMPONENT_VERSION=	0.5.18
COMPONENT_SUMMARY=	Sieve Support for Dovecot
COMPONENT_DESCRIPTION=	The Pigeonhole project provides Sieve support as a plugin for \
			Dovecot's Local Delivery Agent (LDA) and also for its LMTP \
			service. The plugin implements a Sieve interpreter, which filters \
			incoming messages using a script specified in the Sieve language \
			(RFC 5228). The Sieve script is provided by the user and, using \
			that Sieve script, the user can customize how incoming messages \
			are handled. Messages can be delivered to specific folders, \
			forwarded, rejected, discarded, etc.
COMPONENT_PROJECT_URL=	https://dovecot.org/
COMPONENT_FMRI=		mail/dovecot/pigeonhole
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_SRC=		dovecot-2.3-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_SIG_URL=	https://pigeonhole.dovecot.org/releases/2.3/$(COMPONENT_ARCHIVE).sig
COMPONENT_ARCHIVE_URL=	https://pigeonhole.dovecot.org/releases/2.3/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:a6d828f8d6f2decba5105343ece5c7a65245bd94e46a8ae4432a6d97543108a5
COMPONENT_LICENSE=	MIT,LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV+=		PANDOC=false
CONFIGURE_ENV+=		CPPFLAGS=-I/usr/include/openldap

PATH=$(PATH.gnu):/usr/mariadb/10.3/bin

CONFIGURE_OPTIONS+= --sysconfdir=/etc \
                    --with-ldap=plugin \
		    --enable-static=no \
		    --with-dovecot=/usr/lib/amd64/dovecot \
		    --with-dovecot-install-dirs \
		    LDFLAGS="-Wl,-rpath=/usr/lib/amd64/dovecot -lldap_r"

COMPONENT_TEST_TRANSFORMS = \
	'-n ' \
        '-e "/: ok$$/p" ' \
        '-e "/tests failed$$/p" ' \
        '-e "/: FAILED$$/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += mail/dovecot
REQUIRED_PACKAGES += system/library
