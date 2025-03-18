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

BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gamin
COMPONENT_VERSION= 0.1.10
COMPONENT_REVISION= 6
COMPONENT_SUMMARY= Library providing the FAM File Alteration Monitor API
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:28085f0ae8be10eab582ff186af4fb0be92cc6c62b5cc19cd09b295c7c2899a1
COMPONENT_ARCHIVE_URL= https://download.gnome.org/sources/$(COMPONENT_NAME)/0.1/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://www.gnome.org
COMPONENT_FMRI= library/file-monitor/gamin
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE= LGPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# make gcc-14 happy.
CFLAGS += -Wno-implicit-function-declaration
CFLAGS += -Wno-return-mismatch
CFLAGS += -Wno-int-conversion

COMPONENT_PREP_ACTION= ( cd $(@D)  && \
	libtoolize --copy --force &&\
	aclocal -I . &&\
	automake -c -f -a &&\
	autoconf )

COMPONENT_POST_INSTALL_ACTION.64 += \
	EXT_SUFFIX=$(shell $(PYTHON) -c "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))") ; \
	$(MV) $(PROTO_DIR)$(PYTHON_LIB)/_gamin.so $(PROTO_DIR)$(PYTHON_LIB)/_gamin$$EXT_SUFFIX ;

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS.32 += --with-python=no
CONFIGURE_OPTIONS.64 += --with-python=/usr
CONFIGURE_OPTIONS += DAEMON_LIBS="-lglib-2.0 -lgobject-2.0 -lgio-2.0"

PYTHON_REQUIRED_PACKAGES  += runtime/python

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/glib2/32
REQUIRED_PACKAGES += system/library
