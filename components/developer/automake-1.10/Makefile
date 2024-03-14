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

COMPONENT_NAME=         automake
COMPONENT_VERSION=      1.10.3
COMPONENT_REVISION=	1
COMPONENT_SUMMARY =	A Makefile generator
COMPONENT_PROJECT_URL=  http://www.gnu.org/software/automake/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:e98ab43bb839c31696a4202e5b6ff388b391659ef2387cf9365019fad17e1adc
COMPONENT_ARCHIVE_URL=  http://ftp.gnu.org/pub/gnu/automake/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =		developer/build/automake-110
COMPONENT_CLASSIFICATION =	Development/GNU
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_VERSION_MAJOR = $(subst $(space),.,$(wordlist 1,2,$(subst ., ,$(HUMAN_VERSION))))

CONFIGURE_OPTIONS += --docdir=$(USRSHAREDOCDIR)/automake-$(COMPONENT_VERSION_MAJOR)

# Convert unversioned hardlinks to symlinks
COMPONENT_POST_INSTALL_ACTION += \
	for f in aclocal automake ; do \
		$(RM) $(PROTOUSRBINDIR)/$$f ; \
		$(SYMLINK) $$f-$(COMPONENT_VERSION_MAJOR) $(PROTOUSRBINDIR)/$$f ; \
	done ;

# We do not want the info index file
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/info/dir ;

# Convert unversioned info files to versioned and create unversioned symlinks
COMPONENT_POST_INSTALL_ACTION += \
	for f in automake.info automake.info-1 automake.info-2 ; do \
		$(MV) $(PROTOUSRSHAREDIR)/info/$$f \
			$(PROTOUSRSHAREDIR)/info/$${f%.*}-$(COMPONENT_VERSION_MAJOR).$${f\#\#*.} ; \
		$(SYMLINK) $${f%.*}-$(COMPONENT_VERSION_MAJOR).$${f\#\#*.} $(PROTOUSRSHAREDIR)/info/$$f ; \
	done ;

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
