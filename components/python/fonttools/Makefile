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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		fonttools
COMPONENT_VERSION=	3.0
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/netifaces
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:df92dc0ad80eaf3c67c0ce48dd4c8dcc1027266f9bb128157cc30fb72e5d9138
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/F/FontTools/$(COMPONENT_ARCHIVE)

# Uses code which python 2.6 doesn't understand
PYTHON_VERSIONS=	2.7

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

FONTTOOLS_CMDS=pyftinspect pyftmerge pyftsubset ttx

COMPONENT_POST_INSTALL_ACTION= \
        (for cmd in $(FONTTOOLS_CMDS) ; \
        do $(MV) -f $(PROTO_DIR)/usr/bin/$${cmd} \
                $(PROTO_DIR)/usr/bin/$${cmd}-$(PYTHON_VERSION); \
        done;)


# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:           $(NO_TEST)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += runtime/python-27
