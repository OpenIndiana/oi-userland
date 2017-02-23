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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_ARCH= i386
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		yasm
COMPONENT_VERSION=	1.3.0
COMPONENT_PROJECT_URL=	http://yasm.tortall.net/
COMPONENT_ARCHIVE_HASH=	\
    sha256:3dce6601b495f5b3d45b59f7d2492a340ee7e84b5beca17e48f862502bd5603f
COMPONENT_ARCHIVE_URL=	http://www.tortall.net/projects/$(COMPONENT_NAME)/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	5286

TPNO=			23620

PYTHON_VERSIONS= 2.7

include $(WS_MAKE_RULES)/common.mk

# Adjust all the source files in all the Makefile.inc files to generate
# shared libraries rather than a library archive.
# Note that the version number (in the shared-libraries.patch file) should be
# bumped anytime upstream makes an incompatible change (that we're aware of).
COMPONENT_PRE_CONFIGURE_ACTION = \
	$(CLONEY) $(SOURCE_DIR) $(@D) ; \
	mlist=`/usr/bin/find $(SOURCE_DIR) -name 'Makefile.inc'` ; \
	for f in $$mlist ; do \
	    $(GSED) -i -e 's|libyasm_a_SOURCES|libyasm_la_SOURCES|g' \
			-e 's|LDADD = libyasm.a|LDADD = libyasm.la|g' \
			$$f ; \
	done ; \
	(cd $(@D) ; \
	libtoolize --automake --copy ; \
	aclocal -I m4 ; \
	autoheader ; \
	automake --add-missing --copy ; \
	autoconf)

CONFIGURE_ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)

CONFIGURE_OPTIONS += --enable-python
CONFIGURE_OPTIONS += --disable-python-bindings

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^.*$(CC).*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*source=.*libtool=no.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*DEPDIR=.deps.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Nothing to be.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*warning:.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*s up to date.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "/^XXX_REMOVE_XXX$$/d" '

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Required for man pages.
REQUIRED_PACKAGES += developer/documentation-tool/xmlto
