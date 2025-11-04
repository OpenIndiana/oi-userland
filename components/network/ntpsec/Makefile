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
# Copyright (c) 2025, Friedrich.kink
#

BUILD_STYLE =           waf

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ntpsec
COMPONENT_VERSION=	1.2.4
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Network Time Protocol Daemon v4
COMPONENT_DESCRIPTION=	Network Time Protocol v4, NTP Daemon and Utilities
COMPONENT_PROJECT_URL=	https://www.ntpsec.org/
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:443e54a6149d1b0bf08677d17b18fced9028b101fc2ffd2c81e0834f87eebc7d
COMPONENT_ARCHIVE_URL=	https://ftp.ntpsec.org/pub/releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	service/network/ntpsec
COMPONENT_CLASSIFICATION=	System/Services
COMPONENT_LICENSE=	ntp license
COMPONENT_LICENSE_FILE=	LICENSE

ASLR_MODE=	$(ASLR_ENABLE)
ENV=

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TARGETS = check

CONFIGURE_OPTIONS += --cflags="-std=gnu11 -D__sun"
CONFIGURE_OPTIONS += --enable-early-droproot
CONFIGURE_OPTIONS += --enable-leap-smear
CONFIGURE_OPTIONS += --enable-mssntp
CONFIGURE_OPTIONS += --refclock=all
CONFIGURE_OPTIONS += --enable-manpage
# depends on Linux Macros like CTL_KERN
#CONFIGURE_OPTIONS += --enable-attic
CONFIGURE_OPTIONS += --pyshebang="$(PYTHON)"

COMPONENT_POST_INSTALL_ACTION += \
	cd $(SOURCE_DIR)/LICENSES && \
	for file in `ls -1`; do \
          cat $$file >> ../LICENSE; \
        done

COMPONENT_TEST_TRANSFORMS = \
        '-e "/build/d" ' \
        '-e "/check/d" '

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/psutil
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += service/network/dns/mdns
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
