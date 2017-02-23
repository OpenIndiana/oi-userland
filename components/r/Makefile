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
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		R
COMPONENT_VERSION=	3.3.2
COMPONENT_PROJECT_URL=	http://www.r-project.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:d294ad21e9f574fb4828ebb3a94b8cb34f4f304a41687a994be00dd41a4e514c
COMPONENT_ARCHIVE_URL=	http://cran.mtu.edu/src/base/R-3/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/r
COMPONENT_ANITYA_ID=	4150

TPNO=			32832

# Requires newer version of system/linker from ON, available in S12 but not
# 11.3, so do not publish.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

# Need to build the tests before using them.
SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

STUDIO_LIBS_PATH =	$(USRLIBDIR)/studio/64
# R_LIBS_PATH is used when creating /usr/lib/64/R/etc/Makeconf
# Using a resolved pathname here (rather than say $(USRLIBDIR64)/R/lib) so
# that the Makeconf-GNU.patch patch used by the COMPONENT_POST_INSTALL_ACTION
# will just work on both platforms.
R_LIBS_PATH =		/usr/lib/64/R/lib
JAVA_LIBS_PATH =	$(JAVA8_HOME)/jre/lib/$(MACH64)/server

LDFLAGS += $(CC_BITS)
LDFLAGS += -L$(STUDIO_LIBS_PATH) -R$(STUDIO_LIBS_PATH) \
		-lsunperf -lfsu -lmtsk -lpicl -lkstat
LDFLAGS += -L$(R_LIBS_PATH) -R$(R_LIBS_PATH)

# Augment the PATH and set CC/CXX/FC/F77 such that the build environment doesn't
# leak into usr/lib/64/etc/Makeconf and force consumers to have a setup like
# our build environment to build R modules.
export PATH=$(GCC_ROOT)/bin:$(USRBINDIR):$(GNUBIN)
CC =		gcc
CXX =		g++
FC =            gfortran
F77 =           gfortran
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
export PATH=$(PARFAIT_TOOLS):$(SPRO_VROOT)/bin:$(USRBINDIR):$(GNUBIN)
endif

# We can't use $(CC_PIC) here (which provides "-fPIC -DPIC" for the GNU
# compilers), because we fail at configure time with:
# configure: error: Building R requires the 'va_copy' system call
# .../make-rules/configure.mk:170: recipe for target
# '.../components/r/build/amd64/.configured' failed
R_PIC =		-fPIC

# These CONFIGURE_ENV lines are here so that /usr/lib/64/R/etc/Makeconf (the
# configuration file used when building/installing the R CRAN packages),
# is in exactly the correct format to work properly with the GNU compilers for
# all the R CRAN packages containing C, C++, Fortran or Java code.
CONFIGURE_ENV += CC="$(CC) -std=gnu99 $(CC_BITS)"
CONFIGURE_ENV += CXX="$(CXX) $(CC_BITS)"
CONFIGURE_ENV += FC="$(FC) $(CC_BITS)"
CONFIGURE_ENV += F77="$(F77) $(CC_BITS)"

CONFIGURE_ENV += C_VISIBILITY="-fvisibility=hidden"
CONFIGURE_ENV += CFLAGS="-g -O2 -Wformat -Werror=format-security -D_FORTIFY_SOURCE=2"
CONFIGURE_ENV += CPICFLAGS="$(R_PIC)"

CONFIGURE_ENV += CXXFLAGS="$(CC_BITS) -g -O2 -Wformat -Werror=format-security -D_FORTIFY_SOURCE=2"
CONFIGURE_ENV += CXXPICFLAGS="$(R_PIC)"
CONFIGURE_ENV += CXX1X="g++"
CONFIGURE_ENV += CXX1XFLAGS="$(CC_BITS) -g -O2 -Wformat -Werror=format-security -D_FORTIFY_SOURCE=2"
CONFIGURE_ENV += CXX1XPICFLAGS="$(R_PIC)"
CONFIGURE_ENV += CXX1XSTD="-std=c++11"

CONFIGURE_ENV += FCFLAGS="-g -O2 $(CC_BITS)"
CONFIGURE_ENV += F77_VISIBILITY="-fvisibility=hidden"
CONFIGURE_ENV += FFLAGS="-g -O2 $(CC_BITS)"
CONFIGURE_ENV += FCLIBS="-lsunperf -lfsu -lsunmath"
CONFIGURE_ENV += FLIBS="-lsunperf -lfsu -lsunmath -lgfortran -lm"
CONFIGURE_ENV += FCPICFLAGS="$(R_PIC)"
CONFIGURE_ENV += FPICFLAGS="$(R_PIC)"

# Set the various Java variables otherwise it auto-detects the 32-bit ones.
CONFIGURE_ENV += JAVA_CPPFLAGS="-I$(JAVA8_HOME)/jre/../include -I$(JAVA8_HOME)/jre/../include/solaris"
CONFIGURE_ENV += JAVA_LIBS="-L$(JAVA_LIBS_PATH) -R$(JAVA_LIBS_PATH) -ljvm"

# From Brian Whitney:
# You need to define this option on SPARC, otherwise you will get quad
# arithmetic on SPARC but not on x86.  Really makes some R functions run
# very slow on SPARC (COR path).
CONFIGURE_OPTIONS.sparc +=	--disable-long-double

CONFIGURE_OPTIONS += --enable-R-shlib
CONFIGURE_OPTIONS += --with-blas='-lsunperf'
CONFIGURE_OPTIONS += --with-ICU
CONFIGURE_OPTIONS += --with-lapack
CONFIGURE_OPTIONS += --with-recommended-packages
CONFIGURE_OPTIONS += --with-tcltk
CONFIGURE_OPTIONS += --enable-prebuilt-html

COMPONENT_PRE_TEST_ACTION = \
	$(RM) $(BUILD_DIR_64)/tests/Examples/*.prev

COMPONENT_PRE_SYSTEM_TEST_ACTION = \
	$(RM) $(BUILD_DIR_64)/tests/Examples/*.prev

# Increase stack limit to allow the "infinite recursion" test to work.
COMPONENT_TEST_ENV_CMD =	ulimit -Ss 32768 ; $(ENV)
COMPONENT_SYSTEM_TEST_ENV_CMD =	ulimit -Ss 32768 ; $(ENV)

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^Testing examples for package /p" ' \
	'-e "/^running /p" ' \
	'-e "/^  expect some differences/p" ' \
	'-e "/comparing.*datetime.Rout/d" ' \
	'-e "/comparing.*reg-examples3.Rout/d" ' \
	'-e "/^  comparing /p" '

# Use the installed version of R, not the one in the build area.
# These definitions override those found in .../test/Makefile.
COMPONENT_SYSTEM_TEST_ARGS += R="LANGUAGE=en LC_ALL=C SRCDIR=$(BUILD_DIR_64)/tests R_DEFAULT_PACKAGES= $(USRBINDIR)/R --vanilla"
COMPONENT_SYSTEM_TEST_ARGS += R2="R_DEFAULT_PACKAGES= $(USRBINDIR)/R --vanilla"
COMPONENT_SYSTEM_TEST_ARGS += R3="$(USRBINDIR)/R CMD check"
COMPONENT_SYSTEM_TEST_ARGS += RDIFF="$(USRBINDIR)/R CMD Rdiff"
COMPONENT_SYSTEM_TEST_ARGS += RDCONV="LC_CTYPE=C $(USRBINDIR)/R CMD Rdconv"

COMPONENT_TEST_ARGS =		-k -i
COMPONENT_SYSTEM_TEST_ARGS +=	-k -i

REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library/fortran-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/openmp
REQUIRED_PACKAGES += system/library/sunperf
REQUIRED_PACKAGES += system/picl
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxt
