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
# Copyright (c) 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		jokosher
COMPONENT_VERSION=	0.11.5
COMPONENT_PROJECT_URL=	http://jokosher.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:489e0d06c28c3a11b817e7d6e49573ad4942a9cd426ad62dbbf94f3cca03dedb
COMPONENT_ARCHIVE_URL=	http://launchpad.net/jokosher/trunk/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)

# gtk and gstreamer modules are required, but 
# they are provided for Python 2.6 only
PYTHON_VERSIONS = 2.6

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

PYTHON_DATA = /usr


# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

COMPONENT_POST_INSTALL_ACTION = \
        (cd $(PROTO_DIR)/usr/bin ; \
                $(MV) jokosher jokosher-$(PYTHON_VERSION); )

test:           $(NO_TEST)

include $(WS_TOP)/make-rules/depend.mk
