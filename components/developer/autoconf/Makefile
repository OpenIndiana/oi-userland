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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		autoconf
COMPONENT_VERSION=	2.69b
IPS_COMPONENT_VERSION=	2.69.2
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/autoconf/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b87aca642b6f29dc78f0584a475524d0b4eb50e054702f54921f8169a43c1c3e
COMPONENT_ARCHIVE_URL=	  https://alpha.gnu.org/gnu/autoconf/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).sig

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS  +=		--srcdir=.
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		PERL="$(PERL)"

# Auto-generated dependencies
REQUIRED_PACKAGES += developer/macro/gnu-m4
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += SUNWcs
