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
# Copyright (c) 2017 Predrag Zečević.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		import_profiler
COMPONENT_VERSION=	0.0.3
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/import-profiler
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8ca93c521d3360390ee18eefd2bf666704ba4d95d6bd9d683bb9b50c6d48f0b5
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/1f/cf/6a60ab41279a8c9a75c6370ccd41449bcc09a39385dd6c282bd8c123053a/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/python/import-profiler
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_LICENSE=       MIT

PYTHON_VERSIONS=	2.7 3.4

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_FETCH_USER_AGENT=wget

# setup.py needs README.md, but file is missing in archive?
COMPONENT_PRE_BUILD_ACTION=cd $(SOURCE_DIR) && touch README.md

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:           $(NO_TEST)

REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += system/library
