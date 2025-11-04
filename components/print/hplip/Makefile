#
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
# Copyright (c) 2011, 2023, Oracle and/or its affiliates.
#

USE_PARALLEL_BUILD = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         hplip
COMPONENT_VERSION=		3.25.6
COMPONENT_SUMMARY=		HP Linux Imaging and Printing
COMPONENT_PROJECT_URL=	https://hplipopensource.com/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=		sha256:a6af314a7af0572f2ab6967b2fe68760e64d74628ef0e6237f8504d81047edbe
COMPONENT_ARCHIVE_URL=	https://downloads.sourceforge.net/project/$(COMPONENT_NAME)/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= 		print/filter/hplip
COMPONENT_CLASSIFICATION=	System/Printing
COMPONENT_LICENSE=		GPLv2+ and MIT and BSD and IJG and Public Domain and GPLv2+ with exceptions and ISC
COMPONENT_LICENSE_FILE=		copyright

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Configure needs source tree.  The default cloney mode is enough.
CLONEY_MODE =

# -lnsl is needed for getdomainname
LDFLAGS += -lnsl

CONFIGURE_OPTIONS +=	--with-hpppddir=$(USRSHAREDIR)/cups/model/hplip
CONFIGURE_OPTIONS +=	--enable-new-hpcups
CONFIGURE_OPTIONS +=	--enable-cups-ppd-install
CONFIGURE_OPTIONS +=	--disable-gui-build
CONFIGURE_OPTIONS +=    --disable-imageProcessor-build
CONFIGURE_OPTIONS +=	PYTHON=$(PYTHON)
CONFIGURE_OPTIONS +=	PYTHONEXECDIR=$(PYTHON_VENDOR_PACKAGES)
# bye, bye SANE backends
CONFIGURE_OPTIONS +=	--disable-scan-build

CONFIGURE_CPPFLAGS += $(CC_PIC_ENABLE)

# Generate configuration scripts
COMPONENT_PREP_ACTION = ( cd $(@D) ; \
    PATH="$(PATH)" libtoolize --force ; \
    aclocal ; \
    automake --foreign --add-missing ; \
    autoconf ) ;

# Do not use transform to create standard ABI version tagged .so files from Python 3 ABI
PY3_CPYTHON_NAMING=\#

# We do not support udev
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOETCDIR)/udev/ ;
# We do not support systemd
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRLIBDIR)/systemd/ ;

# We miss the mandatory gui support for these files making them unusable and so
# it makes no sense to distribute them.  Drop also symlinks pointing to these
# files.
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/hplip/hpssd.py ;
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/hplip/linefeedcal.py ;
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRBINDIR)/hp-linefeedcal ;
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/hplip/pqdiag.py ;
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRBINDIR)/hp-pqdiag ;
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/hplip/systray.py ;
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRBINDIR)/hp-systray ;

# Fix python script shebang.  There are many files where we need to change
# shebang and so it is easier to construct the list of files on fly than to
# maintain the PYTHON_SCRIPTS list manually.
COMPONENT_POST_INSTALL_ACTION += \
	( cd $(PROTO_DIR) ; \
	for file in $$($(GNU_GREP) -rlI -m1 '^\#!.*python' .) ; do \
		$(call PYTHON_SCRIPT_SHEBANG_FIX_FUNC,"$$file") \
	done ) ;

# Pre-compile python source code
COMPONENT_POST_INSTALL_ACTION += $(PYTHON) -m compileall $(PROTOUSRSHAREDIR)/hplip ;

# Replace PYV by $(PYV)
GENERATE_EXTRA_SED += -e 's/\(\.cpython-\)$(subst .,,$(PYTHON_VERSION))\./\1$$(PYV)./'

# Python modules are installed in non-default location so make sure pkgdepend
# is able to find them
PKGDEPEND_RUNPATH += $(PROTOUSRSHAREDIR)/hplip

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/zbar
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += system/network/avahi
REQUIRED_PACKAGES.python += library/python/dbus-python
REQUIRED_PACKAGES.python += library/python/pillow
REQUIRED_PACKAGES.python += library/python/pyqt5
REQUIRED_PACKAGES.python += runtime/python
