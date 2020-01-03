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
# Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		32

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rsyslog
COMPONENT_VERSION=	7.6.6
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://rsyslog.com/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:c77ae0db6204c5bd670fa96c354ee5fe1c62c876bd84ec06ed429138c78885bb
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/download/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/common.mk

COMPONENT_PREP_ACTION =        ( cd $(@D) && autoreconf -f -i )

CONFIGURE_OPTIONS +=    --enable-imsolaris
CONFIGURE_OPTIONS +=    --enable-mail
CONFIGURE_OPTIONS +=    --enable-gssapi_krb5
CONFIGURE_OPTIONS +=    --enable-gnutls
CONFIGURE_OPTIONS +=    --disable-klog
CONFIGURE_OPTIONS +=    --sbindir=/usr/lib/rsyslog

CONFIGURE_ENV += LD_OPTIONS="$(LD_OPTIONS)"

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

REQUIRED_PACKAGES += library/python/docutils-27
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/json-c
REQUIRED_PACKAGES += library/libestr
REQUIRED_PACKAGES += library/liblogging
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += system/library/security/libgcrypt
