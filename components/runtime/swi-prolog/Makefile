#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2024 Andreas Wacknitz
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		swipl
COMPONENT_VERSION=	9.2.7
COMPONENT_SUMMARY=	Robust, mature, free. Prolog for the real world.
COMPONENT_PROJECT_URL= https://www.swi-prolog.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/download/stable/src/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:fd4126f047e0784112741a874e2f7f8c68b5edd6426ded621df355c62d18c96f
COMPONENT_FMRI=		runtime/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/System
COMPONENT_LICENSE=	BSD-2 license, others
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

# At the moment open_shared_object/3 fails because of missing PyBool_Type. This probably happens because libpython3.9.so isn't found.
COMPONENT_POST_UNPACK_ACTION= ( $(RM) -r $(COMPONENT_SRC)/packages/swipy )

PCRE_INCLUDE=/usr/include/pcre

CFLAGS += -D_POSIX_PTHREAD_SEMANTICS
CFLAGS += $(XPG8MODE)
CFLAGS += -I$(PCRE_INCLUDE)
CFLAGS += -I$(JAVA_HOME)/include/solaris

LDFLAGS += -lsocket -lnsl
LD_OPTIONS += -L$(QT5_LIBDIR) -R$(QT5_LIBDIR)

CMAKE_OPTIONS += -DCMAKE_INSTALL_SYSCONFDIR=$(ETCDIR)
CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX=$(USRDIR)
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DSWIPL_PACKAGES_QT=ON
CMAKE_OPTIONS += -DQt5_DIR=/$(QT5_LIBDIR)/cmake/Qt5
CMAKE_OPTIONS += -DQt5Widgets_DIR=$(QT5_LIBDIR)/cmake/Qt5Widgets
CMAKE_OPTIONS += -DCPYTHON_VERSION="3.9"
CMAKE_OPTIONS += -DWITH_PCRE=system
CMAKE_OPTIONS += -DPCRE_INCLUDE_DIR=$(PCRE_INCLUDE)
CMAKE_OPTIONS += -DJAVA_INCLUDE_PATH=$(JAVA_HOME)/include
CMAKE_OPTIONS += -DJAVA_AWT_LIBRARY=$(JAVA_HOME)/lib/libjawt.so
CMAKE_OPTIONS += -DJAVA_JVM_LIBRARY=$(JAVA_HOME)/lib/server/libjvm.so

CMAKE_ENV += CPPFLAGS="$(CPPFLAGS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += image/library/libjpeg-turbo
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/unixodbc
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/java/openjdk17
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/toolkit/libxt
