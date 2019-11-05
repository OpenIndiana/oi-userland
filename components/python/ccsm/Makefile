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

COMPONENT_NAME=		ccsm
COMPONENT_VERSION=	0.8.10
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.northfield.ws/
COMPONENT_SUMMARY=	ccsm settings manager for the CompizConfig system
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ae622878b651ff215de2673a057ca6c34f5fe4e68d8cf2eb073fb83e4cda3254
COMPONENT_ARCHIVE_URL=	http://www.northfield.ws/projects/compiz/releases/$(COMPONENT_VERSION)/$(COMPONENT_SRC).tar.gz

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# compizconfig-python is Python 2.7 only
PYTHON_VERSIONS = 2.7

PATH=$(PATH.gnu)

COMPONENT_BUILD_ARGS += --prefix=/usr

COMPONENT_INSTALL_ARGS = --prefix=/usr
COMPONENT_INSTALL_ARGS +=       --root $(PROTO_DIR) 
COMPONENT_INSTALL_ARGS +=       --install-lib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=       --install-purelib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=       --install-platlib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=       --force

COMPONENT_POST_BUILD_ACTION = \
		(cd $(SOURCE_DIR);\
		$(GSED) -i -e '1 s/env python/python2.7/' ccm/Conflicts.py; \
		$(GSED) -i -e '1 s/env python/python2.7/' ccm/Constants.py; \
		$(GSED) -i -e '1 s/env python/python2.7/' ccm/Pages.py; \
		$(GSED) -i -e '1 s/env python/python2.7/' ccm/Settings.py; \
		$(GSED) -i -e '1 s/env python/python2.7/' ccm/Utils.py; \
		$(GSED) -i -e '1 s/env python/python2.7/' ccm/Widgets.py; \
		$(GSED) -i -e '1 s/env python/python2.7/' ccm/Window.py; \
		$(GSED) -i -e '1 s/env python/python2.7/' ccm/__init__.py; )

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/pycairo-27
REQUIRED_PACKAGES += library/python/pygobject-27
REQUIRED_PACKAGES += library/python/pygtk2-27
REQUIRED_PACKAGES += library/python/python-compizconfig-27
REQUIRED_PACKAGES += library/python/python-dbus-27
REQUIRED_PACKAGES += library/python/python-sexy-27
REQUIRED_PACKAGES += runtime/python-27
