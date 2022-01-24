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
# Copyright 2015 Alexander Pyhalov
#

BUILD_STYLE=justmake
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gsm
COMPONENT_VERSION=      1.0.16
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=      GSM audio encoding/decoding library
COMPONENT_SRC=          $(COMPONENT_NAME)-1.0-pl16
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:725a3768a1e23ab8648b4df9d470aed38eb1635af3cbc8d0b64fef077236f4ce
COMPONENT_ARCHIVE_URL=  \
	http://www.quut.com/gsm/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.quut.com/gsm/
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE= COPYRIGHT
COMPONENT_CLASSIFICATION=System/Media
COMPONENT_FMRI=         library/audio/libgsm

COMPONENT_ENV += CC="$(CC)"
COMPONENT_ENV += PICFLAG="$(CC_PIC)"
COMPONENT_ENV += MYCFLAGS="$(CFLAGS)"
COMPONENT_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_ENV += $(COMPONENT_ENV)

COMPONENT_INSTALL_ENV.64 = ARCH=/$(MACH64)
COMPONENT_INSTALL_ENV += $(COMPONENT_ENV)
COMPONENT_INSTALL_ENV += $(COMPONENT_INSTALL_ENV.$(BITS))

COMPONENT_INSTALL_ARGS += INSTALL_ROOT=$(USRDIR)

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_INSTALL_ACTION += ( $(GNUBIN)/install -d \
		$(PROTOUSRBINDIR) \
		$(PROTOUSRINCDIR)/gsm \
		$(PROTOUSRLIBDIR) \
		$(PROTOUSRLIBDIR64) \
		$(PROTOUSRSHAREMANDIR)/man1 \
		$(PROTOUSRSHAREMANDIR)/man3 )

COMPONENT_POST_INSTALL_ACTION += ( cp -r $(COMPONENT_SRC)/inc/*.h \
		$(PROTOUSRINCDIR)/gsm/ )

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
