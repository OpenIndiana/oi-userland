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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright 2020 Rouven Weiler
#

BUILD_BITS=			32
BUILD_STYLE=			archive

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		lms
COMPONENT_FMRI =		service/multimedia/
COMPONENT_VERSION =		7.9
COMPONENT_PROJECT_URL =		https://github.org/Logitech/slimserver.git
COMPONENT_SUMMARY =		Logitech Media Server
COMPONENT_LICENSE =		GPLv2
COMPONENT_LICENSE_FILE =	$(COMPONENT_NAME).license
COMPONENT_CLASSIFICATION =	System/File System

COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
GIT_HASH =			sha256:520c0d1633d707a03e3e7d9fd741b7019592660b648f697e0ca1083053edec9f
GIT_REPO =			https://github.com/Logitech/slimserver.git
GIT_BRANCH =			public/7.9

COMPONENT_SRC_1 =		$(COMPONENT_NAME)-vendor-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_1 =		$(COMPONENT_SRC_1).tar.gz
GIT_HASH_1 =			sha256:f262c4df58de291c17ad939d6cd73fd24510d8c76e9d58b75ce1cdb0d01bbf86
GIT_REPO_1 =			https://github.com/chincheta0815/slimserver-vendor.git
GIT_BRANCH_1 =			oi-userland/7.9

PERL_VERSION =			5.22

BUILD_TARGET =			$(BUILD_DIR)/lms-base/.built $(BUILD_DIR)/lms-vendor/.built

include $(WS_MAKE_RULES)/common.mk

$(BUILD_DIR)/lms-base/.built:	$(SOURCE_DIR)/.prep
				$(RM) -r $(@D) ; $(MKDIR) $(@D) 
				$(CLONEY) $(SOURCE_DIR) $(@D) 
				$(TOUCH) $@

$(BUILD_DIR)/lms-vendor/.built: $(COMPONENT_SRC_1)/.unpacked
				$(RM) -r $(@D) ; $(MKDIR) $(@D)
				$(CLONEY) $(COMPONENT_DIR)/$(COMPONENT_SRC_1) $(@D)
				(PATH=$(PATH.gnu) ; cd $(@D)/CPAN ; ./buildme.sh -i $(BUILD_DIR)/lms-base -p $(PERL))
				$(TOUCH) $@

# Set the pkg... path to search files in ./Solaris/ dir (mainly the SMF manifests are there)
PKG_PROTO_DIRS +=		$(COMPONENT_DIR)

# Runtime dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += runtime/perl-522

# Dependencies for build
REQUIRED_PACKAGES += network/rsync
