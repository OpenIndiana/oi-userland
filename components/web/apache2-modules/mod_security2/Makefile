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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2022 Niklas Poslovski
#
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_security2
COMPONENT_VERSION=	2.9.7
COMPONENT_PROJECT_URL=	https://www.modsecurity.org/
COMPONENT_SRC_NAME=	modsecurity
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:2a28fcfccfef21581486f98d8d5fe0397499749b8380f60ec7bb1c08478e1839
COMPONENT_ARCHIVE_URL=	https://github.com/SpiderLabs/ModSecurity/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		web/server/apache-24/module/apache-security
COMPONENT_SUMMARY=	Mod Security plugin for Apache Web Server V2.4
COMPONENT_CLASSIFICATION= Web Services/Application and Web Servers

include $(WS_MAKE_RULES)/common.mk

APXS=	/usr/apache2/2.4/bin/apxs

CONFIGURE_OPTIONS += LTFLAGS="--silent --tag=CC"
CONFIGURE_OPTIONS += --with-apxs=$(APXS)
CONFIGURE_OPTIONS += --with-apr=`$(APXS) -q APR_CONFIG`
CONFIGURE_OPTIONS += --with-apu=`$(APXS) -q APU_CONFIG`

COMPONENT_PRE_INSTALL_ACTION = mkdir -p $(PROTOUSRDIR)/apache2/2.4/libexec

COMPONENT_TEST_ARGS += CFLAGS="$(CFLAGS) -DMSC_TEST"

# Build dependencies
REQUIRED_PACKAGES += web/server/apache-24

# Auto-generated dependencies
REQUIRED_PACKAGES += library/apr
REQUIRED_PACKAGES += library/apr-util
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libyajl2
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
