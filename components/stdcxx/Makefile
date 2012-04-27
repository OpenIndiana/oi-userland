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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

# we really need to use studio so we don't like that
# parfait is g++ in disguise
PARFAIT_BUILD=no

include ../../make-rules/shared-macros.mk

PATH=$(dir $(CC)):/usr/gnu/bin:/usr/bin

COMPONENT_NAME=		stdcxx
COMPONENT_VERSION=	4.2.1
COMPONENT_PROJECT_URL=	http://stdcxx.apache.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://stdcxx.apache.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:00854223cbd947bf1bd85d9dabd1b2829706d9062e0007d5022082a5e4b7e15e
COMPONENT_ARCHIVE_URL=	http://www.apache.org/dist/stdcxx/$(COMPONENT_ARCHIVE)

CLOBBER_PATHS += install.sh

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

ISA_PATCH_DIR_32 = $(WS_TOP)/components/stdcxx/isa_patches/$(MACH)
ISA_PATCH_DIR_64 = $(WS_TOP)/components/stdcxx/isa_patches/$(MACH64)
ISA_PATCH_DIR = $(ISA_PATCH_DIR_$(BITS))

ISA_PATCHES_$(MACH) = \
    $(ISA_PATCH_DIR)/1034-sunpro.config.$(MACH).patch \
    $(ISA_PATCH_DIR)/1035-GNUmakefile.tst.$(MACH).patch \
    $(ISA_PATCH_DIR)/1036-GNUmakefile.rwt.$(MACH).patch \
    $(ISA_PATCH_DIR)/1037-GNUmakefile.lib.$(MACH).patch \
    $(ISA_PATCH_DIR)/1038-GNUmakefile.ph.$(MACH).patch \
    $(ISA_PATCH_DIR)/1039-GNUmakefile.exm.$(MACH).patch \
    $(ISA_PATCH_DIR)/1040-GNUmakefile.cfg.$(MACH).patch \
    $(ISA_PATCH_DIR)/1041-GNUmakefile.bin.$(MACH).patch

ISA_PATCHES_$(MACH64) = \
    $(ISA_PATCH_DIR)/1034-sunpro.config.$(MACH64).patch \
    $(ISA_PATCH_DIR)/1035-GNUmakefile.tst.$(MACH64).patch \
    $(ISA_PATCH_DIR)/1036-GNUmakefile.rwt.$(MACH64).patch \
    $(ISA_PATCH_DIR)/1037-GNUmakefile.lib.$(MACH64).patch \
    $(ISA_PATCH_DIR)/1038-GNUmakefile.ph.$(MACH64).patch \
    $(ISA_PATCH_DIR)/1039-GNUmakefile.exm.$(MACH64).patch \
    $(ISA_PATCH_DIR)/1040-GNUmakefile.cfg.$(MACH64).patch \
    $(ISA_PATCH_DIR)/1041-GNUmakefile.bin.$(MACH64).patch

ISA_PATCHES_32 = $(ISA_PATCHES_$(MACH))
ISA_PATCHES_64 = $(ISA_PATCHES_$(MACH64))
ISA_PATCHES = $(ISA_PATCHES_$(BITS))

PATCH_LEVEL = 1

TOPDIR = $(COMPONENT_DIR)/$(COMPONENT_SRC)
LOCAL_BUILDDIR = $(TOPDIR)/build
MARG = -m$(BITS)
PICFLAG = -KPIC -DPIC

# Please see the README file in this directory for a detailed explanation
# about these flags, what they do, and why we need them.
FLAGS_sparc = -m32 -xarch=sparcvis -xmemalign=8i
FLAGS_sparcv9 = -m64 -xarch=sparcvis -xmemalign=16i
FLAGS_i386 = -m32 -xarch=386
FLAGS_amd64 = -m64 -xarch=generic
CFLAGS_sparc = -Xc -features=extinl  -xvis=yes
CFLAGS_sparc += -Qoption cg -xregs=no%appl -xbuiltin=%none -xO4 $(PICFLAG)
CFLAGS_i386 = -Xc -features=extinl -xregs=no%frameptr
CFLAGS_i386 += -xO3 -xbuiltin=%none $(PICFLAG)

CFLAGS_32 = $(FLAGS_$(MACH)) $(CFLAGS_$(MACH))
CFLAGS_64 = $(FLAGS_$(MACH64)) $(CFLAGS_$(MACH))

CXXFLAGS_sparc = -xvis=yes -xregs=no%appl -xO4
CXXFLAGS_sparc +=  -xbuiltin=%none $(PICFLAG)
CXXFLAGS_i386 = -xregs=no%frameptr -xO3  -xbuiltin=%none $(PICFLAG)
CFLAGS_GENERIC += -xc99=%all 
CFLAGS_GENERIC += -mt -D_REENTRANT -DNDEBUG
CFLAGS_GENERIC += -D__EXTENSIONS__ -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64
CFLAGS_GENERIC += -D_XPG6 -D_XOPEN_SOURCE=600 -D_POSIX_PTHREAD_SEMANTICS
CFLAGS_GENERIC += -D_POSIX_C_SOURCE=200112L -D__XOPEN_OR_POSIX
CFLAGS_GENERIC += -D_STRICT_STDC -D_STRICT_STDC__ -D_STDC_C99 -D_ISOC99_SOURCE
CFLAGS_GENERIC += -D_IN_BUILD_STDCXX
CFLAGS_GENERIC += $(CFLAGS_$(BITS))
CFLAGS = $(CFLAGS_GENERIC)

CXXFLAGS_GENERIC = -library=Cstd -library=Crun -norunpath
CXXFLAGS_GENERIC += -Qoption ccfe ++boolflag:sunwcch=false
CXXFLAGS_GENERIC += -Qoption ccfe +d2,-xgeninl=system
CXXFLAGS_GENERIC += -Qoption ccfe -expand=10000
CXXFLAGS_GENERIC += -features=except,rtti,export,extensions,nestedaccess,tmplife,tmplrefstatic
CXXFLAGS_GENERIC += -instances=global
CXXFLAGS_GENERIC += -template=geninlinefuncs
CXXFLAGS_GENERIC += -verbose=template
CXXFLAGS_GENERIC += $(CXXFLAGS_$(MACH))
CXXFLAGS_GENERIC += -xlang=c99
CXXFLAGS_GENERIC += -xbuiltin=%none
CXXFLAGS_GENERIC += -xinline=
CXXFLAGS_GENERIC += -xlibmieee
CXXFLAGS_GENERIC += -xustr=ascii_utf16_ushort
CXXFLAGS_GENERIC += -z ignore $(PICFLAG)
CXXFLAGS_GENERIC += -mt -D_REENTRANT -DNDEBUG
CXXFLAGS_GENERIC += -D_IN_BUILD_STDCXX
CXXFLAGS_GENERIC += -D__EXTENSIONS__
CXXFLAGS_GENERIC += -D_LARGEFILE_SOURCE
CXXFLAGS_GENERIC += -D_FILE_OFFSET_BITS=64
CXXFLAGS_GENERIC += -D_XOPEN_SOURCE=500
CXXFLAGS_GENERIC += -D_XPG5
CXXFLAGS_GENERIC += -D_POSIX_PTHREAD_SEMANTICS -s
CXXFLAGS_GENERIC += +w2 -errtags -erroff=hidef

CXXFLAGS_32 = $(FLAGS_$(MACH))
CXXFLAGS_64 = $(FLAGS_$(MACH64))

CXXFLAGS = $(CXXFLAGS_$(BITS)) $(CXXFLAGS_$(MACH)) $(CXXFLAGS_GENERIC)

CPPFLAGS = -I$(TOPDIR)/include/ansi
CPPFLAGS += -I$(TOPDIR)/include/tr1
CPPFLAGS += -I$(TOPDIR)/include

# -mt will automatically pass -lthread unless we pass -lpthread
#  on link line. -lthread causes regressions. see man CC(1) and -mt.
#  -lumem must be passed before -lc.
LDFLAGS = -lpthread -lumem -lm -lc -s -z ignore

# We cannot have -B direct
LD_OPTIONS = -M /usr/lib/ld/map.noexstk -M /usr/lib/ld/map.noexdata 
LD_OPTIONS += -M /usr/lib/ld/map.pagealign
LD_OPTIONS += -lpthread -lumem -lm -lc -s -z ignore

# If I name it NLSPATH, gmake insists on getting its value from the
# running environment. Also, it all has to be on one line. += prepends
# a whitespace.
BUILD_NLSPATH = :%N.cat:/usr/lib/locale/%L/%N.cat:/usr/share/locale/%L/%N.cat:$(BUILD_DIR_$(BITS))/lib/rwstderr.cat

CONFIGURE_ENV = 	CC="$(CC)"
CONFIGURE_ENV +=	CXX="$(CXX)"
CONFIGURE_ENV +=	CFLAGS="$(CFLAGS)"
CONFIGURE_ENV +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV +=	CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_ENV +=	LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV +=	LD_OPTIONS="$(LD_OPTIONS)"
CONFIGURE_ENV +=	LD="$(CXX) $(CXXFLAGS) $(LDFLAGS)"
CONFIGURE_ENV +=	MAKE="$(MAKE)"
CONFIGURE_ENV +=	TOPDIR="$(TOPDIR)"
CONFIGURE_ENV +=	MAKEFLAGS=""

CONFIGURE_OPTIONS  =		$(MARG)
CONFIGURE_OPTIONS  +=		-topdir=$(TOPDIR)
CONFIGURE_OPTIONS  +=		-builddir=$(LOCAL_BUILDDIR)

GCP = /usr/gnu/bin/cp

COMPONENT_BUILD_ENV =	MAKEFLAGS=""
COMPONENT_BUILD_ENV +=	MAKELEVEL=""
COMPONENT_BUILD_ENV +=	SHELL="/bin/bash"
COMPONENT_BUILD_ENV +=	NLSPATH="$(BUILD_NLSPATH)"

PKG_PROTO_DIRS += $(COMPONENT_DIR)/$(COMPONENT_SRC)-32
PKG_PROTO_DIRS += $(COMPONENT_DIR)/$(COMPONENT_SRC)-64

COMPONENT_PREP_ACTION = \
    ( if test -f $(TOPDIR)/.unpacked ; then \
	cd $(TOPDIR) ; \
	else $(UNPACK) $(UNPACK_ARGS) $(COMPONENT_ARCHIVE) ; \
	    $(TOUCH) $(TOPDIR)/.unpacked ; \
	    cd $(TOPDIR) ; \
	    fi ; \
	list='$(ISA_PATCHES)' ; for f in $$list ; do \
	$(GPATCH) $(GPATCH_FLAGS) <$$f ; \
	    done  )

COMPONENT_PRE_CONFIGURE_ACTION = \
    ( if test -f $(TOPDIR)/.unpacked ; then \
	cd $(TOPDIR) ; \
	else $(UNPACK) $(UNPACK_ARGS) $(COMPONENT_ARCHIVE) ; \
	    $(TOUCH) $(TOPDIR)/.unpacked ; \
	    cd $(TOPDIR) ; \
	    list1='$(ISA_PATCHES)' ; for f in $$list1 ; do \
	    $(GPATCH) $(GPATCH_FLAGS) <$$f ; \
	    done ; \
	    list2='$(PATCHES)' ; for f in $$list2 ; do \
	    $(GPATCH) $(GPATCH_FLAGS) <$(COMPONENT_DIR)/$$f ; \
	    done ; \
	    $(TOUCH) $(TOPDIR)/.patched ; \
	    fi ; \
	$(CP) -Rp $(COMPONENT_DIR)/Solaris . ; \
	$(CP) -p ./Solaris/configure . ; \
	$(TOUCH) -acm ./configure ; \
	$(CHMOD) 0755 ./configure )

COMPONENT_POST_CONFIGURE_ACTION = \
    ( $(CLONEY) $(TOPDIR) $(@D) ; \
    find ./$(COMPONENT_SRC) -type f -name "*.~1~" \
	-exec chmod 0644 {} \; > /dev/null 2>&1 )

COMPONENT_POST_BUILD_ACTION = \
    ( cd $(BUILD_DIR_$(BITS))/build ; \
	$(GMAKE) locales ; \
	cd $(TOPDIR) ; \
	$(CP) -p $(COMPONENT_DIR)/Solaris/fix_nls_symlinks.sh . ; \
	$(CHMOD) 0755 fix_nls_symlinks.sh ; \
	$(SHELL) ./fix_nls_symlinks.sh ; \
	cd $(COMPONENT_DIR) ; \
	$(GCP) -rpd $(COMPONENT_SRC) $(COMPONENT_SRC)-$(BITS) ; \
	$(RM) -rf $(COMPONENT_SRC) )

build: $(BUILD_32) $(BUILD_64)

install: $(BUILD_DIR_32)/.built $(BUILD_DIR_64)/.built
	$(CP) $(COMPONENT_DIR)/Solaris/install.sh $(COMPONENT_DIR)/
	$(CHMOD) 0755 $(COMPONENT_DIR)/install.sh
	$(MKDIR) $(PROTO_DIR)/usr
	( $(SHELL) $(COMPONENT_DIR)/install.sh \
	    -prefix=$(PROTO_DIR)/usr \
	    -builddir=$(BUILD_DIR_32) \
	    -componentdir=$(COMPONENT_DIR) \
	    -componentsrc=$(COMPONENT_SRC) \
	    -srcdir=$(TOPDIR)-32 )
	( $(SHELL) $(COMPONENT_DIR)/install.sh \
	    -prefix=$(PROTO_DIR)/usr \
	    -builddir=$(BUILD_DIR_64) \
	    -componentdir=$(COMPONENT_DIR) \
	    -componentsrc=$(COMPONENT_SRC) \
	    -srcdir=$(TOPDIR)-64 \
	    -mach64=$(MACH64) )
	test -d $(TOPDIR) || $(MKDIR) $(TOPDIR)

test:
	test -d $(BUILD_DIR_32) || echo "$(BUILD_DIR_32) does not exist!"
	test -d $(BUILD_DIR_64) || echo "$(BUILD_DIR_64) does not exist!"
	$(CP) -p $(COMPONENT_DIR)/Solaris/prep_build_area.sh \
	    $(COMPONENT_DIR)/
	$(CHMOD) 0755 $(COMPONENT_DIR)/prep_build_area.sh
	$(SHELL) $(COMPONENT_DIR)/prep_build_area.sh -m32 \
	    -builddir=$(BUILD_DIR_32) \
	    -srcdir=$(TOPDIR)-32
	$(SHELL) $(COMPONENT_DIR)/prep_build_area.sh -m64 \
	    -builddir=$(BUILD_DIR_64) \
	    -srcdir=$(TOPDIR)-64
	( cd $(BUILD_DIR_32)/build/tests ; \
	    $(CP) -p $(COMPONENT_DIR)/Solaris/run_tests.sh . ; \
	    $(CHMOD) 0755 run_tests.sh ; \
	    $(SHELL) ./run_tests.sh > \
		$(COMPONENT_DIR)/runtests-$(MACH).out 2>&1 )
	( cd $(BUILD_DIR_64)/build/tests ; \
	    $(CP) -p $(COMPONENT_DIR)/Solaris/run_tests.sh . ; \
	    $(CHMOD) 0755 run_tests.sh ; \
	    $(SHELL) ./run_tests.sh > \
		$(COMPONENT_DIR)/runtests-$(MACH64).out 2>&1 )

clean::
	$(RM) -r $(COMPONENT_SRC) $(COMPONENT_SRC)-32 $(COMPONENT_SRC)-64
	$(RM) -f *.sed *.out

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk

