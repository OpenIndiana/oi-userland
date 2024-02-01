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
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         automake
COMPONENT_VERSION=      1.11.6
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	A Makefile generator
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/automake/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:1ffbc6cc41f0ea6c864fbe9485b981679dc5e350f6c4bc6c3512f5a4226936b5
COMPONENT_ARCHIVE_URL=  http://ftp.gnu.org/pub/gnu/automake/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		developer/build/automake-111
COMPONENT_CLASSIFICATION=Development/GNU
COMPONENT_LICENSE=	GPL-2.0-only
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_VERSION_MAJOR = $(subst $(space),.,$(wordlist 1,2,$(subst ., ,$(HUMAN_VERSION))))

CONFIGURE_OPTIONS += --docdir=$(USRSHAREDOCDIR)/automake-$(COMPONENT_VERSION_MAJOR)

# Convert unversioned binary hardlinks and man page files to symlinks
COMPONENT_POST_INSTALL_ACTION += \
	for f in aclocal automake ; do \
		$(RM) $(PROTOUSRBINDIR)/$$f ; \
		$(SYMLINK) $$f-$(COMPONENT_VERSION_MAJOR) $(PROTOUSRBINDIR)/$$f ; \
		$(RM) $(PROTOUSRSHAREMAN1DIR)/$$f.1 ; \
		$(SYMLINK) $$f-$(COMPONENT_VERSION_MAJOR).1 $(PROTOUSRSHAREMAN1DIR)/$$f.1 ; \
	done ;

# We do not want the info index file
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/info/dir ;

# Convert unversioned info files to versioned and create unversioned symlinks
COMPONENT_POST_INSTALL_ACTION += \
	for f in automake.info automake.info-1 automake.info-2 automake.info-3 ; do \
		$(MV) $(PROTOUSRSHAREDIR)/info/$$f \
			$(PROTOUSRSHAREDIR)/info/$${f%.*}-$(COMPONENT_VERSION_MAJOR).$${f\#\#*.} ; \
		$(SYMLINK) $${f%.*}-$(COMPONENT_VERSION_MAJOR).$${f\#\#*.} $(PROTOUSRSHAREDIR)/info/$$f ; \
	done ;

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
