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
# Copyright (c) 2010, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnutls
COMPONENT_VERSION=	2.8.6
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://ftp.gnu.org/gnu/gnutls/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:d6f846a7064af3ee2c9aebd65dcee76953b767170cbcd719e990ed6b9688a356
COMPONENT_ARCHIVE_URL=  https://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/gnutls

TPNO=			9291

COMPONENT_BUILD_TARGETS = all info

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=$(dir $(CC)):/usr/lib:/usr/bin:/usr/sbin:/usr/gnu/bin

CC += $(CC_BITS)
CXX += $(CC_BITS)

CONFIGURE_OPTIONS  += --sysconfdir=/etc 
CONFIGURE_OPTIONS  += --infodir=/usr/share/info 
CONFIGURE_OPTIONS  += --localstatedir=/var 
CONFIGURE_OPTIONS  += --enable-guile=no 
CONFIGURE_OPTIONS  += --disable-camellia
CONFIGURE_OPTIONS  +=   CXX="$(CXX) -norunpath" 

ASLR_MODE = $(ASLR_ENABLE)

include ../../make-rules/shared-targets.mk

configure:      $(CONFIGURE_32_and_64)

build:          $(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

COMPONENT_TEST_TRANSFORMS += \
	'-n -e "/: x509self/d" ' \
	'-e "/: x509signself/d" ' \
	'-e "/: x509dn/d " ' \
	'-e "/: openpgpself/d " ' \
	'-e "/: crq_key_id/d " ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" '

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += library/libtasn1
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
