#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright 2022 Daniel Chan
#

BUILD_BITS=			64
BUILD_STYLE=		justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		PyQt5
COMPONENT_VERSION=	5.15.6
COMPONENT_SUMMARY=	Python bindings for the Qt cross platform application toolkit
COMPONENT_PROJECT_URL=	https://pypi.org/project/PyQt5/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:80343bcab95ffba619f2ed2467fd828ffeb0a251ad7225be5fc06dcc333af452
COMPONENT_ARCHIVE_URL=	https://files.pythonhosted.org/packages/3b/27/fd81188a35f37be9b3b4c2db1654d9439d1418823916fe702ac3658c9c41/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/python/pyqt5
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= LICENSE

PYTHON_VERSION=	3.9
PYTHON_VERSIONS=	3.9


include $(WS_MAKE_RULES)/common.mk
PATH=$(QT5_BINDIR):$(PATH.gnu)
COMPONENT_INSTALL_ENV += INSTALL_ROOT=$(PROTO_DIR)
SIP_OPTIONS += --confirm-license
SIP_OPTIONS += --no-make
COMPONENT_COPY_ACTION = \
	cp -r $(SOURCE_DIR)/* $(@D)/
COMPONENT_PRE_BUILD_ACTION = \
	cd $(@D) && sip-build $(SIP_OPTIONS)
COMPONENT_BUILD_ACTION = \
	cd $(@D)/build; $(ENV) $(COMPONENT_BUILD_ENV) \
	$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS)
COMPONENT_INSTALL_ACTION = \
	cd $(@D)/build ; $(ENV) $(COMPONENT_INSTALL_ENV) \
	$(GMAKE) $(COMPONENT_INSTALL_ARGS) $(COMPONENT_INSTALL_TARGETS);\
	cd $(@D)/build && python$(PYTHON_VERSION) -m compileall __init__.py; \
	cd $(@D) && python$(PYTHON_VERSION) -m compileall pylupdate/*.py; \
	cd $(@D) && python$(PYTHON_VERSION) -m compileall pyrcc/*.py; \
	cd $(@D) && python$(PYTHON_VERSION) -m compileall pyuic/uic/*.py; \
	cd $(@D) && python$(PYTHON_VERSION) -m compileall pyuic/uic/Compiler/*.py; \
	cd $(@D) && python$(PYTHON_VERSION) -m compileall pyuic/uic/Loader/*.py; \
	cd $(@D) && python$(PYTHON_VERSION) -m compileall pyuic/uic/port_v2/*.py; \
	cd $(@D) && python$(PYTHON_VERSION) -m compileall pyuic/uic/port_v3/*.py; \
	cd $(@D) && python$(PYTHON_VERSION) -m compileall pyuic/uic/widget-plugins/*.py; \
	mkdir -p $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/__pycache__/; \
	mkdir -p $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/uic/__pycache__/; \
	mkdir -p $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/uic/Compiler/__pycache__/; \
	mkdir -p $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/uic/Loader/__pycache__/; \
	mkdir -p $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/uic/port_v2/__pycache__/; \
	mkdir -p $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/uic/port_v3/__pycache__/; \
	mkdir -p $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/uic/widget-plugins/__pycache__/; \
	cp $(@D)/build/__pycache__/* $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/__pycache__/; \
	cp $(@D)/pylupdate/__pycache__/* $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/__pycache__/; \
	cp $(@D)/pyrcc/__pycache__/* $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/__pycache__/; \
	cp $(@D)/pyuic/uic/__pycache__/* $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/uic/__pycache__/; \
	cp $(@D)/pyuic/uic/Compiler/__pycache__/* $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/uic/Compiler/__pycache__/; \
	cp $(@D)/pyuic/uic/Loader/__pycache__/* $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/uic/Loader/__pycache__/; \
	cp $(@D)/pyuic/uic/port_v2/__pycache__/* $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/uic/port_v2/__pycache__/; \
	cp $(@D)/pyuic/uic/port_v3/__pycache__/* $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/uic/port_v3/__pycache__/; \
	cp $(@D)/pyuic/uic/widget-plugins/__pycache__/* $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/PyQt5/uic/widget-plugins/__pycache__/


# Build dependencies
REQUIRED_PACKAGES += library/python/pyqtbuilder
REQUIRED_PACKAGES += library/python/sip

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
