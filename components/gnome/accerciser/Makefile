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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		accerciser
COMPONENT_VERSION=	3.14.0
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/Accerciser
COMPONENT_ARCHIVE_HASH= \
	sha256:f5a5915d475e9241396414ccd167724c88807e77e69151cf0b40b32bd57d0574
COMPONENT_BUGDB= 	gnome/accessibility

TPNO=			25184

include $(WS_MAKE_RULES)/gnome-component.mk

# Assumes GNU gettext & msgfmt are first in PATH.
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

# Accerciser requires python >= 3.2
PYTHON_VERSION = 3.5
CONFIGURE_ENV += PYTHON="$(PYTHON)"

# Ensure Python modules are installed into vendor package directories.
CONFIGURE_ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)

# intltool may or may not be run depending on previous state of build dir
COMPONENT_TEST_TRANSFORMS += "-e '/\/usr\/bin\/intltool-update/d'"

REQUIRED_PACKAGES += developer/documentation-tool/itstool
REQUIRED_PACKAGES += developer/intltool
REQUIRED_PACKAGES += library/desktop/at-spi2-core
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libwnck3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/python/pyatspi2-35
REQUIRED_PACKAGES += library/python/pygobject-3-35
REQUIRED_PACKAGES += runtime/python-35
