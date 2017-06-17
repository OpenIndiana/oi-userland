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
# Copyright 2017 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= babl
COMPONENT_VERSION= 0.1.18
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= Babl is a dynamic, any to any, pixel format conversion library
COMPONENT_FMRI = image/library/babl
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:483a495bc9fa68be624e27e72d2144ebfcbbf63e061eb986db1fb82b04b6fbf9
COMPONENT_ARCHIVE_URL= \
  http://ftp.gimp.org/pub/babl/0.1/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://gegl.org/babl/
COMPONENT_LICENSE = LGLPv3
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Need GNU version of awk
export AWK=gawk

COMPONENT_PREP_ACTION = ( cd $(@D)  && \
                                autoreconf -f -i -I m4)


CONFIGURE_OPTIONS+= --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS+= --datadir=$(USRSHAREDIR)
CONFIGURE_OPTIONS+= --infodir=$(USRSHAREDIR)/info
CONFIGURE_OPTIONS+= --disable-mmx
CONFIGURE_OPTIONS+= --disable-sse

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
