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
# Copyright 2022, Daniel Chan
# Copyright 2022-2023 Niklas Poslovski
#

BUILD_STYLE= justmake
USE_PARALLEL_BUILD = yes
DROP_STATIC_LIBRARIES = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cryptopp
COMPONENT_VERSION=	8.9.0
COMPONENT_REVISION=	4
COMPONENT_SUMMARY=	Free C++ Class Library of Cryptographic Schemes
COMPONENT_PROJECT_URL=	https://cryptopp.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_URL=	https://github.com/weidai11/$(COMPONENT_NAME)/releases/download/CRYPTOPP_$(subst .,_,$(COMPONENT_VERSION))/$(COMPONENT_NAME)$(subst .,,$(COMPONENT_VERSION)).zip
COMPONENT_ARCHIVE_HASH=	sha256:4cc0ccc324625b80b695fcd3dee63a66f1a460d3e51b71640cdbfc4cd1a3779c
COMPONENT_FMRI=		library/cryptopp
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=	BSLv1
COMPONENT_LICENSE_FILE=	License.txt

include $(WS_MAKE_RULES)/common.mk

UNPACK_ARGS += -r $(COMPONENT_SRC)
CXXFLAGS += -g2
CXXFLAGS += -fPIC

COMPONENT_BUILD_ARGS += file=GNUmakefile
COMPONENT_BUILD_ARGS += PREFIX=$(USRDIR)
COMPONENT_BUILD_ARGS += LIBDIR=$(USRLIBDIR.$(BITS))
COMPONENT_BUILD_ARGS += IS_SUN=1
COMPONENT_BUILD_ARGS += libcryptopp.so
COMPONENT_BUILD_ARGS += libcryptopp.pc
COMPONENT_BUILD_ARGS += cryptest.exe

COMPONENT_INSTALL_ARGS += file=GNUmakefile
COMPONENT_INSTALL_ARGS += PREFIX=$(USRDIR)
COMPONENT_INSTALL_ARGS += LIBDIR=$(USRLIBDIR.$(BITS))

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^passed/p" ' \
	'-e "/^behaved as expected/p" ' \
	'-e "/^failed/p" ' \
	'-e "/^did not behave as expected/p" ' \
	'-e "/^test was not run/p" ' \
	'-e "/^tests were not run/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
