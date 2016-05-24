#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2011, Andrzej Szeszo
# Copyright 2013, Jon Tibble
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		commons-logging
COMPONENT_VERSION=	1.2
COMPONENT_PROJECT_URL=	http://commons.apache.org/proper/commons-logging/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-bin.tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:3f758805c7290d9c6d22d1451587c9f7232744aef4c984e88aa683cdea0587bd
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/commons/logging/binaries/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

build:

install: prep
	[ -d $(PROTO_DIR)/usr/share/lib ] || mkdir -p $(PROTO_DIR)/usr/share/lib
	[ -f $(PROTO_DIR)/usr/share/lib/commons-logging.jar ] || \
		cp $(SOURCE_DIR)/commons-logging-1.2.jar $(PROTO_DIR)/usr/share/lib

clean::
	rm -rf $(BUILD_DIR)
