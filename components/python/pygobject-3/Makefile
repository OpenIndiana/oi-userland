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
# Copyright 2017 Alexander Pyhalov
#

BUILD_BITS=	64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pygobject
COMPONENT_VERSION=	3.18.2
COMPONENT_REVISION=	5
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Python bindings for GObject
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:2a3cad1517916b74e131e6002c3824361aee0671ffb0d55ded119477fc1c2c5f
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/3.18/$(COMPONENT_ARCHIVE)

PYTHON_VERSIONS = 2.7 3.5

VARIANT_PYTHON27 = $(BUILD_DIR)/python-27
VARIANT_PYTHON35 = $(BUILD_DIR)/python-35

VARIANTS_64 = $(VARIANT_PYTHON27) $(VARIANT_PYTHON35)

BUILD_64 = $(VARIANTS_64:%=%/.built)

INSTALL_64 = $(VARIANTS_64:%=%/.installed)

# Avoid overwriting python2.7 files in /usr/share
$(VARIANT_PYTHON27)/.installed:      $(VARIANT_PYTHON35)/.installed

$(VARIANT_PYTHON27)/.installed:      PYTHON_VERSION=2.7
$(VARIANT_PYTHON27)/.installed:      PYTHON_VERSION=2.7
$(VARIANT_PYTHON27)/.installed:      

$(VARIANT_PYTHON35)/.installed:      PYTHON_VERSION=3.5

$(VARIANT_PYTHON27)/.configured: BITS=64
$(VARIANT_PYTHON27)/.configured: PYTHON=$(PYTHON.2.7.64)
# Install modules to /usr/lib/python2.7/vendor-packages
$(VARIANT_PYTHON27)/.configured: am_cv_python_pyexecdir=$(PYTHON.2.7.VENDOR_PACKAGES.32)
$(VARIANT_PYTHON27)/.configured: am_cv_python_pythondir=$(PYTHON.2.7.VENDOR_PACKAGES.32)

$(VARIANT_PYTHON35)/.configured: BITS=64
$(VARIANT_PYTHON35)/.configured: PYTHON=$(PYTHON.3.5.64)
$(VARIANT_PYTHON35)/.configured: am_cv_python_pyexecdir=$(PYTHON.3.5.VENDOR_PACKAGES)
$(VARIANT_PYTHON35)/.configured: am_cv_python_pythondir=$(PYTHON.3.5.VENDOR_PACKAGES)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= (cd $(@D) && autoreconf -f -i)

CFLAGS += $(gcc_C99_ENABLE)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

CONFIGURE_ENV+=         PYTHON=$(PYTHON)
CONFIGURE_ENV+=         am_cv_python_pythondir="$(am_cv_python_pythondir)"
CONFIGURE_ENV+=         am_cv_python_pyexecdir="$(am_cv_python_pyexecdir)"

COMPONENT_POST_INSTALL_ACTION.2.7 = ( cd $(PROTO_DIR) && \
					$(MKDIR) usr/lib/python$(PYTHON_VERSION)/vendor-packages/gi/64;  \
					$(MV) -f usr/lib/python$(PYTHON_VERSION)/vendor-packages/gi/*.so \
			 			usr/lib/python$(PYTHON_VERSION)/vendor-packages/gi/64/ )
COMPONENT_POST_INSTALL_ACTION.3.5 =

COMPONENT_POST_INSTALL_ACTION = $(COMPONENT_POST_INSTALL_ACTION.$(PYTHON_VERSION))

COMPONENT_POST_BUILD_ACTION = ($(TOUCH) $(BUILD_DIR))


REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
