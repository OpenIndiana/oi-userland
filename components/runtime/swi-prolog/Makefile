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
# Copyright 2022 Andreas Wacknitz
#

BUILD_STYLE= cmake
OPENSSL_VERSION= 3.1
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		swipl
COMPONENT_VERSION=	9.0.4
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Robust, mature, free. Prolog for the real world.
COMPONENT_PROJECT_URL= https://www.swi-prolog.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/download/stable/src/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:feb2815a51d34fa81cb34e8149830405935a7e1d1c1950461239750baa8b49f0
COMPONENT_FMRI=		runtime/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/System
COMPONENT_LICENSE=	BSD-2 license, others
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

JAVA_HOME=/usr/jdk/openjdk1.8.0
PCRE_INCLUDE=/usr/include/pcre

CXXFLAGS += -D_POSIX_PTHREAD_SEMANTICS
CFLAGS += -D_POSIX_PTHREAD_SEMANTICS
CFLAGS += -D_XOPEN_SOURCE=600
CFLAGS += -D__EXTENSIONS__
CPPFLAGS += -I$(PCRE_INCLUDE)
CPPFLAGS += -I$(JAVA_HOME)/include/solaris

LDFLAGS += -lsocket -lnsl
LD_OPTIONS += -L$(QT5_LIBDIR) -R$(QT5_LIBDIR)

CMAKE_OPTIONS += -DCMAKE_INSTALL_SYSCONFDIR="/etc"
CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX=/usr
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DSWIPL_PACKAGES_QT=ON
CMAKE_OPTIONS += -DQt5_DIR=/$(QT5_LIBDIR)/cmake/Qt5
CMAKE_OPTIONS += -DQt5Widgets_DIR=$(QT5_LIBDIR)/cmake/Qt5Widgets
CMAKE_OPTIONS += -DWITH_PCRE=system
CMAKE_OPTIONS += -DPCRE_INCLUDE_DIR=$(PCRE_INCLUDE)
CMAKE_OPTIONS += -DJAVA_INCLUDE_PATH=$(JAVA_HOME)/include
CMAKE_OPTIONS += -DJAVA_AWT_LIBRARY=/usr/java/jre/lib/amd64/libjawt.so
CMAKE_OPTIONS += -DJAVA_JVM_LIBRARY=/usr/java/jre/lib/amd64/server/libjvm.so

CMAKE_ENV += CPPFLAGS="$(CPPFLAGS)"

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/\s\s*[0-9][0-9]*\.[0-9][0-9]* sec/ SEC sec/"'

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += library/unixodbc
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/java/openjdk8
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += x11/library/toolkit/libxt
