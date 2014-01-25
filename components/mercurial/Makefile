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
# Copyright (c) 2011, 2014, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		mercurial
COMPONENT_VERSION=	2.8.2
COMPONENT_PROJECT_URL=	http://mercurial.selenic.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c8a5baa21140c6cd6749c3b52b5e5e4a14b6b8ee7c518d9d9de09b1952efbe6f
COMPONENT_ARCHIVE_URL=	http://www.selenic.com/mercurial/release/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/hg

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_POST_INSTALL_ACTION = \
	(cd $(PROTO_DIR)/usr/bin ; $(MV) -f hg hg-$(PYTHON_VERSION))

PKG_PROTO_DIRS +=	$(COMPONENT_SRC)/contrib
PKG_PROTO_DIRS +=	$(COMPONENT_SRC)/doc

# Set mod time of patched file from patch.  Use this to ensure that the .py
# file consistently gets the same timestamp.
$(SOURCE_DIR)/.https_proxy.patched: GPATCH_FLAGS += -Z

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Assuming you have docutils installed, update the manpages patch for a new
# mercurial version based on the patches applied to the source and to the
# manpage generator.  This works either against source that's already been
# patched with the older manpages.patch or against a fresh tarball.  Eventually
# we'll have docutils in the CBE and we'll be able to regenerate the manpages
# as part of the build, rather than patching them.
patches/manpages.patch:
	if [[ -f $(COMPONENT_SRC)/doc/hg.1.~1~ ]]; then \
		cd $(COMPONENT_SRC)/doc; gmake man || true; cd ../..; \
		for f in hg.1 hgignore.5 hgrc.5; do \
			diff -u $(COMPONENT_SRC)/doc/$$f.~1~ $(COMPONENT_SRC)/doc/$$f; \
		done > $@; \
	else \
		for f in hg.1 hgignore.5 hgrc.5; do \
			cp -p $(COMPONENT_SRC)/doc/$$f $(COMPONENT_SRC)/doc/$$f.orig; \
		done; \
		cd $(COMPONENT_SRC)/doc; gmake man || true; cd ../..; \
		for f in hg.1 hgignore.5 hgrc.5; do \
			diff -u $(COMPONENT_SRC)/doc/$$f.orig $(COMPONENT_SRC)/doc/$$f; \
		done > $@; \
	fi || true

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

# Use bash in sh mode for the tests; using /bin/sh on Solaris hasn't always
# worked, and using /bin/bash doesn't always work, either.  Also skip the
# check-code test, since that ends up trying to check all the code in the
# userland gate.  And finally, test the bits from the proto area, rather than
# rebuilding.  Given the way the test suite works, the hg executable must be
# named "hg".
test:	$(INSTALL_32)
	(cd $(BUILD_DIR); rm -f sh; ln -s /bin/bash sh; \
	 echo test-check-code-hg.t > blacklist)
	(cd $(PROTOUSRBINDIR); ln -s hg-$(PYTHON_VERSION) hg)
	(cd $(COMPONENT_SRC)/tests ; \
	 PYTHONPATH=$(PROTO_DIR)/$(PYTHON_LIB) TERM=dumb \
	 $(PYTHON) ./run-tests.py --shell $(BUILD_DIR)/sh \
	 --with-hg $(PROTOUSRBINDIR)/hg --blacklist $(BUILD_DIR)/blacklist)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
