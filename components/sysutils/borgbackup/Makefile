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
# Copyright 2019 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		borgbackup
COMPONENT_VERSION=	1.1.8
COMPONENT_PROJECT_URL=	https://borgbackup.readthedocs.org/en/stable/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0b4370480ca0114cb0bb534286241af8a35c6ffb71404dfa409ed06099661b63
COMPONENT_ARCHIVE_URL=	https://github.com/borgbackup/borg/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

# Borg requirement
PYTHON_VERSIONS=	3.4

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_FETCH_USER_AGENT=wget

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += library/python/setuptools-34
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += system/library
