#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Alexander Pyhalov
# Copyright 2020 Michal Nowak
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		yaz
COMPONENT_VERSION=	5.34.2
COMPONENT_SUMMARY=	toolkit supporting the development of Z39.50/SRW/SRU clients and servers
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:ab45cf48036fc6da7493815c033b5db2b1e7a34632caed1a43e9cdef745b9618
COMPONENT_ARCHIVE_URL=	http://ftp.indexdata.dk/pub/yaz/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.indexdata.com/resources/software/yaz/
COMPONENT_FMRI=		database/yaz
COMPONENT_CLASSIFICATION= Development/Databases
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --with-xml2
CONFIGURE_OPTIONS += --with-xslt
CONFIGURE_OPTIONS += --without-icu
CONFIGURE_OPTIONS += --disable-static

# Without this tests fail
ENV=/usr/bin/env -i
COMPONENT_TEST_ENV += LD_OPTIONS="$(LD_OPTIONS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += database/hiredis
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libmemcached
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
