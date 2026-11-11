#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2020 Andreas Wacknitz
#

# Parallel builds hang on some systems:
USE_PARALLEL_BUILD = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libotr
COMPONENT_VERSION= 4.1.1
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= Off-the-Record Messaging library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:8b3b182424251067a952fb4e6c7b95a21e644fbb27fbd5f8af2b2ed87ca419f5
COMPONENT_ARCHIVE_URL= \
	http://www.cypherpunks.ca/otr/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://otr.cypherpunks.ca/
COMPONENT_FMRI =		library/libotr
COMPONENT_CLASSIFICATION =	System/Libraries
COMPONENT_LICENSE =		LGPL-2.1-only AND GPL-2.0-only

include $(WS_MAKE_RULES)/common.mk

# helper target
update-license-file: patch
	( \
		$(CAT) $(SOURCE_DIR)/README \
			| $(GSED) -n -e '/^LICENSE/,$${/^CONTACT/,$$!p}' \
			| $(GSED) -e '/^The library/,/^The Off/{/^The Off/!d}'; \
		printf '\n--- COPYING ---------------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING ; \
		printf '\n\n--- COPYING.LIB -----------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.LIB \
	) > $(COMPONENT_DIR)/$(COMPONENT_LICENSE_FILE)

# We are patching configure.ac and Makefile.am files
COMPONENT_PREP_ACTION += cd $(@D) && $(ENV) PATH="$(PATH)" autoreconf -fi ;

# This project does not support out of source build
CLONEY_MODE =

CONFIGURE_OPTIONS += --disable-static

# needed to build tests
CFLAGS += -D__EXTENSIONS__

# TODO: the reported number of tests changes with every run
COMPONENT_TEST_TRANSFORMS += "-e '0,/run\.sh test_list$$/d'"	# delete everything up to the test runner invocation
COMPONENT_TEST_TRANSFORMS += "-e 's/,  *[0-9]* wallclock.*//'"	# delete timings
COMPONENT_TEST_TRANSFORMS += "-e '/^make\[/d'"			# delete make logs

# Manually added test dependencies
TEST_REQUIRED_PACKAGES += library/perl-5/test-harness

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
