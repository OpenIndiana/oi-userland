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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2021, Andreas Wacknitz
#

BUILD_BITS= 64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		p11-kit
COMPONENT_VERSION=	0.25.5
COMPONENT_FMRI=		library/desktop/p11-kit
COMPONENT_SUMMARY=	p11-kit provides a way to load and enumerate PKCS\#11 modules
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_PROJECT_URL=	https://p11-glue.github.io/p11-glue/p11-kit.html
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:04d0a86450cdb1be018f26af6699857171a188ac6d5b8c90786a60854e1198e5
COMPONENT_ARCHIVE_URL=	https://github.com/p11-glue/p11-kit/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD-3-Clause
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CFLAGS += $(XPG7MODE)
CFLAGS += -D_POSIX_PTHREAD_SEMANTICS
LDFLAGS += -lsocket -lnsl

# Needed due to patch to automake-related files.
COMPONENT_PREP_ACTION += (cd $(@D); PATH="$(PATH)" autoreconf -fiv);

CONFIGURE_OPTIONS    += --enable-doc
CONFIGURE_OPTIONS    += --disable-doc-html
CONFIGURE_OPTIONS    += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS    += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS    += --with-module-path=/usr/lib/security/$(MACH64)
CONFIGURE_OPTIONS    += --with-trust-paths=/etc/certs/ca-certificates.crt

COMPONENT_BUILD_ENV += PATH=$(PATH)
COMPONENT_TEST_ENV += PATH=$(PATH)

COMPONENT_TEST_TRANSFORMS += \
	'-e "/^ *CC/d" ' \
	'-e "/is up to date/d" ' \
	'-e "/ok/p" ' 

# bash-completion is needed to get the following two files installed into proto area:
# - usr/share/bash-completion/completions/p11-kit
# - usr/share/bash-completion/completions/trust
REQUIRED_PACKAGES += utility/bash-completion

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/libtasn1
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
