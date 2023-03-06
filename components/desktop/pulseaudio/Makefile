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
# Copyright 2017 Alexander Pyhalov
# Copyright 2019 Michal Nowak
#

PREFERRED_BITS=		64
BUILD_BITS=			32_and_64
USE_OPENSSL11=		yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pulseaudio
COMPONENT_VERSION=	13.0
COMPONENT_REVISION=	3
COMPONENT_FMRI=		library/audio/pulseaudio
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_SUMMARY=	Sample Rate Converter for audio
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:961b23ca1acfd28f2bc87414c27bb40e12436efcf2158d29721b1e89f3f28057
COMPONENT_ARCHIVE_URL= https://freedesktop.org/software/pulseaudio/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Software/PulseAudio/
COMPONENT_LICENSE=	LGPLv2.1,GPLv2,MIT,adrian-license,Sun Public Domain license

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

LDFLAGS += -lnsl -lsocket -lgobject-2.0

CPPFLAGS += -I/usr/include/gc
CFLAGS += -std=c99

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --disable-esound
CONFIGURE_OPTIONS += --disable-force-preopen
# Solaris has native OSS; don't use PulseAudio wrapper.
CONFIGURE_OPTIONS += --disable-oss-wrapper
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-avahi
CONFIGURE_OPTIONS += --enable-dbus
CONFIGURE_OPTIONS += --disable-gconf
CONFIGURE_OPTIONS += --enable-glib2
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
CONFIGURE_OPTIONS += --enable-tests

CONFIGURE_ENV	+= CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV	+= PERL=$(PERL)
CONFIGURE_ENV	+= PYTHON=$(PYTHON)
CONFIGURE_ENV	+= GLIB_COMPILE_SCHEMAS=/usr/bin/glib-compile-schemas

# Required due to patches; must use special bootstrap script and not standard
# autoreconf due to use of both gettext and intltool in the same project! If
# you use standard autoreconf, configure will fail.
COMPONENT_PREP_ACTION += ( cd $(@D) ; NOCONFIGURE=1 $(CONFIG_SHELL) bootstrap.sh );

COMPONENT_BUILD_ARGS += V=0

unexport SHELLOPTS
COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));

$(INSTALL_32):	$(INSTALL_64)

COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/TOTAL|PASS|FAIL|XFAIL|SKIP|XPASS|ERROR/'"

# For tests
REQUIRED_PACKAGES += developer/check

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/soxr
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/fftw-3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/speexdsp
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/orc
REQUIRED_PACKAGES += system/network/avahi
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxtst
