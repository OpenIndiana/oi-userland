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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS = 		32_and_64
COMPILER = 		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pulseaudio
COMPONENT_VERSION=	6.0
COMPONENT_PROJECT_URL=	http://freedesktop.org/software/pulseaudio
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:b50640e0b80b1607600accfad2e45aabb79d379bf6354c9671efa2065477f6f6
COMPONENT_ARCHIVE_URL=	http://freedesktop.org/software/$(COMPONENT_NAME)/releases/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/multimedia

TPNO=			25017

# Only build for 2.7 for now as we need 32-bit and 64-bit support; all of the
# GNOME and desktop components must be built for Python 2.7 for now.
PYTHON_VERSIONS= 2.7

# Needs updated glib2, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/common.mk

# Assumes GNU xgettext in PATH
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)

# No one should be using esd anymore.
CONFIGURE_OPTIONS += --disable-esound
CONFIGURE_OPTIONS += --disable-force-preopen
# Solaris has native OSS; don't use PulseAudio wrapper.
CONFIGURE_OPTIONS += --disable-oss-wrapper
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-avahi
CONFIGURE_OPTIONS += --enable-dbus
CONFIGURE_OPTIONS += --disable-gconf
CONFIGURE_OPTIONS += --enable-glib2
CONFIGURE_OPTIONS += --enable-gtk3
CONFIGURE_OPTIONS += --enable-hal-compat
CONFIGURE_OPTIONS += --enable-ipv6
CONFIGURE_OPTIONS += --enable-manpages
CONFIGURE_OPTIONS += --enable-openssl
CONFIGURE_OPTIONS += --enable-orc
CONFIGURE_OPTIONS += --enable-oss-output
CONFIGURE_OPTIONS += --enable-solaris
CONFIGURE_OPTIONS += --with-database=gdbm
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --with-zsh-completion-dir=/usr/share/zsh/5.2/functions/Completion/Unix

# To avoid using the current system default, one is explicitly specified here.
CONFIGURE_ENV += PYTHON=$(PYTHON)

# Required due to patches; must use special bootstrap script and not standard
# autoreconf due to use of both gettext and intltool in the same project! If
# you use standard autoreconf, configure will fail.
COMPONENT_PREP_ACTION += ( cd $(@D) ; NOCONFIGURE=1 $(CONFIG_SHELL) bootstrap.sh );

unexport SHELLOPTS
COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH)-$(BITS).master
COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

# qpaeq (equalizer gui) needs Qt4 and PyQt4 so is omitted from p5m for now.
REQUIRED_PACKAGES += codec/speex
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/desktop/orc
REQUIRED_PACKAGES += library/fftw-3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/json-c
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/network/avahi
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxtst
