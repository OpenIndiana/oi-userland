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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		faad2
COMPONENT_FMRI =		audio/faad2
COMPONENT_VERSION =		2.8.8
COMPONENT_PROJECT_URL =		https://www.audiocoding.com/
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH =	sha256:985c3fadb9789d2815e50f4ff714511c79c2710ac27a4aaaf5c0c2662141426d
COMPONENT_ARCHIVE_URL =		https://sourceforge.net/projects/faac/files/$(COMPONENT_NAME)-src/$(COMPONENT_NAME)-2.8.0/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE =             GPLv2
COMPONENT_LICENSE_FILE =        $(COMPONENT_NAME).license
COMPONENT_SUMMARY =		FAAD2 is a HE, LC, MAIN and LTP profile, MPEG2 and MPEG-4 AAC decoder
COMPONENT_CLASSIFICATION =	System/Multimedia Libraries

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk


CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--with-drm
#CONFIGURE_OPTIONS +=	--with-xmms
#CONFIGURE_OPTIONS +=	--with-mpeg4ip

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:           $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
