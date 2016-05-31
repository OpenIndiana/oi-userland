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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

COMPILER =      	gcc
BUILD_BITS =            32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		glib
COMPONENT_VERSION=	2.46.0
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/GLib/
COMPONENT_ARCHIVE_HASH=	\
    sha256:b1cee83469ae7d80f17c267c37f090414e93960bd62d2b254a5a96fbc5baacb4
COMPONENT_BUGDB=	gnome/glib

TPNO=			24986

# No need to build for older versions.
PYTHON_VERSIONS= 3.4

include $(WS_MAKE_RULES)/gnome-component.mk

# Necessary to ensure patches applied to configure.ac take effect.
COMPONENT_PREP_ACTION += ( cd $(@D); NOCONFIGURE=1 $(CONFIG_SHELL) autogen.sh );

CFLAGS += $(CPP_XPG6MODE)
CFLAGS.gcc += -std=gnu11
CFLAGS.studio += -std=c11 -xlang=c11

# Disabled by default (temporarily disabled here because it significantly
# increases build time).
CONFIGURE_OPTIONS += --disable-gtk-doc

# Building dtrace probes doesn't work correctly (results in undefined symbols
# in programs), disable until we can figure out how to fix.
CONFIGURE_OPTIONS += --disable-dtrace

# The build process modifies the shebang line to use the version of Python
# automatically found; to avoid using the current system default, one is
# explicitly specified here.
CONFIGURE_OPTIONS += --with-python=$(PYTHON.3.4)

# Configure doesn't find this since it's not in $PATH
CONFIGURE_OPTIONS += DBUS_DAEMON=/usr/lib/dbus-daemon

# configure sets this to gcc's -fvisibility=hidden, replace with correct
# flag for Studio builds
COMPONENT_BUILD_ARGS.studio += GLIB_HIDDEN_VISIBILITY_CFLAGS='-xldscope=hidden'
COMPONENT_BUILD_ARGS += $(COMPONENT_BUILD_ARGS.$(COMPILER))

# Assumes GNU msgfmt in PATH.
# Need to include /usr/sbin so configure can find dtrace
CONFIGURE_ENV += PATH="$(PATH):/usr/sbin"
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH):/usr/sbin"

# Make sure SMF manifests are valid
$(BUILD_DIR)/.validated-smf-manifests-$(MACH): $(BUILD_DIR)
	@for f in files/*.xml ; do \
	    (set -ex ; /usr/sbin/svccfg validate "$$f") ; \
	done
	$(TOUCH) $@

validate-smf:	$(BUILD_DIR)/.validated-smf-manifests-$(MACH)
build:		$(BUILD_DIR)/.validated-smf-manifests-$(MACH)

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

# Strip random seeds from glib tests that use different values each run
COMPONENT_TEST_TRANSFORMS += \
	'-e "s/seed:[0-9]*/seed:/"'

# Strip filenames that are reported in different order between runs
COMPONENT_TEST_TRANSFORMS += \
	'-e "s%/bookmarks/parse/.*%%"' \
	'-e "s%/markup/parse/.*%%"' \

# Standard automake test framework results transform
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL/p" ' \
        '-e "/SKIP/p" ' \
        '-e "/PASS/p" ' \
        '-e "/FAIL/p" ' \
        '-e "/ERROR/p" '

REQUIRED_PACKAGES += data/docbook
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/file-monitor/gamin
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
