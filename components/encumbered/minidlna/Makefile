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
# Copyright 2020 Alexander Pyhalov
# Copyright 2022-2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= minidlna
COMPONENT_VERSION= 1.3.2
COMPONENT_REVISION= 1
COMPONENT_SUMMARY=  MiniDLNA DLNA/UPnP-AV media server
COMPONENT_PROJECT_URL= https://sourceforge.net/projects/minidlna/
COMPONENT_FMRI= media/minidlna
COMPONENT_CLASSIFICATION= System/Media
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
	https://sourceforge.net/projects/minidlna/files/minidlna/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
	sha256:222ce45a1a60c3ce3de17527955d38e5ff7a4592d61db39577e6bf88e0ae1cb0
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= LICENCE.miniupnpd

TEST_TARGET=$(NO_TESTS)

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

# build with the distribution preferred libjpeg implementation
CFLAGS        +=    $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS      +=    $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS       +=    $(JPEG_LDFLAGS)

CFLAGS += $(CPP_XPG5MODE)

CONFIGURE_OPTIONS +=  --with-log-path=/var/log/minidlna

LDFLAGS += -lsocket -lnsl -lsendfile

# Auto-generated dependencies
REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += library/audio/libid3tag
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += video/ffmpeg
