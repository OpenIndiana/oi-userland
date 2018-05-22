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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Authen-PAM
COMPONENT_VERSION=	16
COMPONENT_REVISION=	2
COMPONENT_SRC=		$(COMPONENT_NAME)-0.16
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0e949bd9a2a9df0f829971030fe9169cbaf6cec78b92faf22f547ff6c6155c9b
COMPONENT_ARCHIVE_URL=	\
    http://search.cpan.org/CPAN/authors/id/N/NI/NIKIP/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://search.cpan.org/~nikip/Authen-PAM-0.16/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk
include $(WS_TOP)/make-rules/makemaker.mk

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# man pages go in the common area
COMPONENT_INSTALL_ENV += INSTALLVENDORMAN3DIR=$(USRSHAREMAN3DIR)

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
                                        autoconf )


COMPONENT_TEST_TARGETS = test

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
