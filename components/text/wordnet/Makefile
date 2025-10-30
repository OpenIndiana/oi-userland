#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2025 Andreas Wacknitz
#

CONFIGURE_DEFAULT_DIRS= pre-2.60
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			WordNet
COMPONENT_VERSION=		3.0
COMPONENT_SUMMARY=		WordNet® is a large lexical database of English
COMPONENT_DESCRIPTION=	Nouns, verbs, adjectives and adverbs are grouped into sets of cognitive synonyms (synsets), \
	each expressing a distinct concept. Synsets are interlinked by means of conceptual-semantic and lexical relations.
COMPONENT_PROJECT_URL=	https://wordnet.princeton.edu
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=		https://wordnetcode.princeton.edu/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:6c492d0c7b4a40e7674d088191d3aa11f373bb1da60762e098b8ee2dda96ef22
COMPONENT_FMRI=			text/wordnet
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=		MIT-like
COMPONENT_LICENSE_FILE=		LICENSE

# Other related resources
# https://wordnetcode.princeton.edu/3.0/WNdb-3.0.tar.gz
# https://wordnetcode.princeton.edu/3.0/WNprolog-3.0.tar.gz
# https://github.com/globalwordnet/english-wordnet
# https://github.com/globalwordnet/OMW

COMPONENT_ARCHIVE_1=		wn3.1.dict.tar.gz
COMPONENT_ARCHIVE_HASH_1=	sha256:3f7d8be8ef6ecc7167d39b10d66954ec734280b5bdcd57f7d9eafe429d11c22a
COMPONENT_ARCHIVE_URL_1=	https://wordnetcode.princeton.edu/$(COMPONENT_ARCHIVE_1)

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CLEAN_PATHS += $(COMPONENT_DIR)/dict

# Replace the original dict files with newer ones
COMPONENT_POST_INSTALL_ACTION += ( \
	$(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1); \
	$(RM) -rf $(PROTOUSRDIR)/$(COMPONENT_NAME)-$(HUMAN_VERSION)/dict; \
	$(MV) dict $(PROTOUSRDIR)/$(COMPONENT_NAME)-$(HUMAN_VERSION)/; )

CFLAGS += -Wno-error=implicit-int

LDFLAGS += -L$(BUILD_DIR_$(BITS))/lib

CONFIGURE_OPTIONS += --prefix=/usr/WordNet-3.0
CONFIGURE_OPTIONS += --exec-prefix=/usr

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
