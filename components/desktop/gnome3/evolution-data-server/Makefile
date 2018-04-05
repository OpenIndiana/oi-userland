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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#
include ../../../../make-rules/shared-macros.mk

# Despite its name, evolution-data-server is no longer just a backend for the
# Evolution Mail Client; it is also a backend for various bits of data that
# GNOME stores and various components now expect it to be present.

COMPONENT_NAME=		evolution-data-server
COMPONENT_MJR_VERSION=	3.24
COMPONENT_MNR_VERSION=	0
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_SUMMARY=      The GNOME backend for contacts, tasks, and calendar information
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Apps/Evolution
COMPONENT_ARCHIVE_HASH= \
	sha256:41ddb60b08ee287e82be52ebbe49b5a336984e52584a5fd34c82d45493f8031b
COMPONENT_ARCHIVE_URL=  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_FMRI=	library/desktop/evolution-data-server
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

# __EXTENSIONS__ required for timezone, altzone variables.
CFLAGS += -D__EXTENSIONS__ -DHAVE_SUN_KRB5
CXXFLAGS += -std=c++11 -D__EXTENSIONS__ -DHAVE_SUN_KRB5
CPPFLAGS += -I/usr/include/kerberosv5/
CFLAGS += $(XPG6MODE)

LDFLAGS += -lsocket -lnsl

COMPONENT_PRE_CMAKE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D))

CMAKE_OPTIONS += -DENABLE_GOOGLE_AUTH=OFF
CMAKE_OPTIONS += -DENABLE_UOA=OFF
CMAKE_OPTIONS += -DENABLE_GOA=OFF
CMAKE_OPTIONS += -DENABLE_INTROSPECTION=ON
CMAKE_OPTIONS += -DENABLE_GTK_DOC=ON
CMAKE_OPTIONS += -DWITH_OPENLDAP=OFF
CMAKE_OPTIONS += -DWITH_SUNLDAP=ON
CMAKE_OPTIONS += -DENABLE_VALA_BINDINGS=ON
CMAKE_OPTIONS += -DSYSCONF_INSTALL_DIR="/etc"

# Parallel build fails
#COMPONENT_BUILD_ARGS=

# common targets
build:          $(BUILD_64)

install:        $(INSTALL_64)

test:           $(TEST_64)

# Tests are not reliable. Some tests which failed sporadically were removed,
# but some other still sometimes fail. Test framework also fails when 
# g_warning is used, even when it's not a serious issue.
# So we have interesting results here.
unexport SHELLOPTS
COMPONENT_TEST_ENV += PATH="/usr/lib:$(PATH)"
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
	'-e "s%\([0-9\.]\)* sec%%"' \
        '-e "/Test /p" ' \
	'-e "/The following tests FAILED:/,\$$p" '

# Build dependencies
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libgdata
REQUIRED_PACKAGES += library/desktop/libgweather
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gcr
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libical
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/library/mozilla-nss
REQUIRED_PACKAGES += system/library/security/gss
