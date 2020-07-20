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
# Copyright (c) 2014 Alexander Pyhalov
#

BUILD_STYLE= setup.py
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		terminator
COMPONENT_VERSION=	1.92
COMPONENT_PROJECT_URL=	https://gnome-terminator.org/
COMPONENT_COMMIT=	0cbdbd89a23eaea52ae0fa30d3d6a6c6b9b3fbda
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=	\
    sha256:9dea305337fba9e6c87f704b167ee12e3e32e063a9861b82817f04ef95af4f38
COMPONENT_ARCHIVE_URL=	https://github.com/gnome-terminator/terminator/archive/$(COMPONENT_COMMIT).zip

PYTHON_VERSIONS=	3.5

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

PYTHON_DATA=/usr

COMPONENT_POST_INSTALL_ACTION += \
        (cd $(PROTO_DIR)/usr/bin && \
	  $(MV) -f terminator terminator-$(PYTHON_VERSION) && \
	  $(MV) -f remotinator remotinator-$(PYTHON_VERSION) \
	)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/psutil-35
REQUIRED_PACKAGES += library/python/pygobject-3-35
REQUIRED_PACKAGES += library/python/python-dbus-35
REQUIRED_PACKAGES += runtime/python-35
