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
# Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnutls
COMPONENT_VERSION=	2.8.6
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:d6f846a7064af3ee2c9aebd65dcee76953b767170cbcd719e990ed6b9688a356
COMPONENT_BUGDB=	library/gnutls

TPNO=			9291

COMPONENT_BUILD_TARGETS = all info

# Tell libtool to pass this flag through using -Wc.
# https://www.gnu.org/software/libtool/manual/html_node/Stripped-link-flags.html
studio_NORUNPATH := -Wc,$(studio_NORUNPATH)

include $(WS_MAKE_RULES)/gnu-component.mk

PATH=$(dir $(CC)):$(USRLIBDIR):$(USRBINDIR):$(USRSBINDIR):$(GNUBIN)

CONFIGURE_OPTIONS  += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS  += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS  += --disable-guile
CONFIGURE_OPTIONS  += --disable-camellia

include ../../make-rules/shared-targets.mk

COMPONENT_TEST_TRANSFORMS += \
	'-n -e "/: x509self/d" ' \
	'-e "/: x509signself/d" ' \
	'-e "/: x509dn/d " ' \
	'-e "/: openpgpself/d " ' \
	'-e "/: crq_key_id/d " ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" '

REQUIRED_PACKAGES += library/libtasn1
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
