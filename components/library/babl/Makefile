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
# Copyright 2017 Gary Mills
# Copyright 2020 Alexander Pyhalov
#

BUILD_BITS= 64
BUILD_STYLE= meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= babl
COMPONENT_VERSION= 0.1.78
COMPONENT_SUMMARY= Babl is a dynamic, any to any, pixel format conversion library
COMPONENT_FMRI = image/library/babl
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:17d5493633bff5585d9f375bc4df5925157cd1c70ccd7c22a635be75c172523a
COMPONENT_ARCHIVE_URL= \
  http://ftp.gimp.org/pub/babl/0.1/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://gegl.org/babl/
COMPONENT_LICENSE = LGLPv3
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/common.mk

# Need GNU version of awk
export AWK=gawk

CPPFLAGS += -I/usr/include/lcms2

CONFIGURE_OPTIONS+= --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS+= --datadir=$(USRSHAREDIR)
CONFIGURE_OPTIONS+= --infodir=$(USRSHAREDIR)/info
CONFIGURE_OPTIONS+= -Denable-mmx=false
CONFIGURE_OPTIONS+= -Denable-sse=false

# gobject-introspection requires this
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# Without this we get issues with gobject-introspection
LD_B_DIRECT=
LD_Z_IGNORE=

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

# Build dependencies
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += web/browser/w3m

# Auto-generated dependencies
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
