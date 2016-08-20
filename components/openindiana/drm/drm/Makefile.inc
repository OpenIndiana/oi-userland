#
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
#
###############################################################################
#
#  Makefile.inc - rules common to the kernel directory
#
###############################################################################

MODTYPE=driver

# Hierarchical parent for pkg names in this area
# Note that each driver needs to set the MODULE_PKGTAIL
# value so that it can be appropriately installed in that package
# e.g. i915/drm define this as "MODULE_PKGTAIL = drm"
MODTYPE_PKGHIER		= driver/graphics
MODTYPE_PKGHIER_SET	= yes
MODULE_COMPILER		= gcc

# PKGCLASS - Drivers/Display for framebuffers.
MODULE_PKGCLASS		= Drivers/Display
MODULE_PKGCLASS_SET	= yes

# The package that this belongs in - must match the name in pkg/manifests
# This is something that should be a bit more dynamic.
MODULE_PKG		= driver-graphics-drm

# Default module description for packages in this area
MODTYPE_DESC	 = the $(MODULE_NAME) driver

# Set comments in ELF binaries to help identify versions/builds
# XXXX - We probably need something here, but not sure what.
# MODTYPE_ADD_BUILD_TARGETS=set-elf-comments

# Define common LDFLAGS
MODTYPE_LDFLAGS	=

#
# Defines that are specific to kernel drivers
#
# Default build options
USE_DEFAULT_CONFIG_LDFLAGS	= no
USE_DEFAULT_CONFIG_CPPFLAGS	= no
USE_DEFAULT_CONFIG_ENV		= no

#
# Much of the below is the redefinition of defines in the common
# Makefiles.  It was changed here as the environment is sufficiently
# different for kernel modules that it introduced a fair amount of
# changed code.  So it was initially decided to separate the work
# and figure later how to move this into common code (which can be
# accomplished in smaller increments).

#
# Due to the common Makefile's use of DEFAULT_LD_OPTIONS, we clear it here.
#
DEFAULT_LD_OPTIONS	=

#
# Define CONFIG_ENV for kernel modules here.
# Note that _anything_ needed to build these modules must be listed here
# as they are not retained from the common Makefiles.
#
CONFIG_ENV	= CC="$(CC)" CXX="$(CXX)" AR="$(AR)"
CONFIG_ENV	+= LD="$(LD)"
CONFIG_ENV	+= CFLAGS="$(MODTYPE_CFLAGS) $(MODULE_CFLAGS)"
CONFIG_ENV	+= CXXFLAGS="$(MODTYPE_CXXFLAGS) $(MODULE_CXXFLAGS)"
CONFIG_ENV	+= CPPFLAGS="$(DEFAULT_CONFIG_CPPFLAGS) $(MODTYPE_CPPFLAGS) $(MODULE_CPPFLAGS)"
CONFIG_ENV	+= LDFLAGS="$(MODULE_LDFLAGS) $(MODTYPE_LDFLAGS)"
CONFIG_ENV	+= PKG_CONFIG_PATH="$(DEFAULT_PKG_CONFIG_PATH)"
CONFIG_ENV	+= INSTALL="$(INSTALL_SCRIPT)" CPPROG="cp -p"
CONFIG_ENV	+= MAKE="$(MODULE_MAKE)" CONFIG_SHELL="$(CONFIG_SHELL)"
CONFIG_ENV	+= NM="/usr/gnu/bin/nm"
CONFIG_ENV	+= POUND_SIGN="$(POUND_SIGN)"
CONFIG_ENV	+= PROTOMETA="$(PROTOMETA)/$(MODULE_PKG)"


###############################################################
# Where to find the common include files
# Search first in kernel/sys
DRM_INCL	= -I$(TOP)/sys
# sys/drm should be removed after all includes properly expand to <drm/...>
DRM_INCL	+= -I$(TOP)/sys/drm


###############################################################
# CFLAGS for modules in open-src/kernel
#
# Standard defines needed for this driver on solaris independent of compiler
KDEFINES	= -D_KERNEL -D_ELF64  -D_DDI_STRICT -Dsun -D__sun \
		-D__SVR4 -D_SYSCALL32 -D_SYSCALL32_IMPL -D_ASM_INLINES

# Don't use defines based on MACH.
KDEFINES	+= -U$(MACH) -U__$(MACH)

# Debug flags
KDEFINES_DEBUG	+= -DDEBUG

# Driver features.

###############################################################
# Studio flags
# Note: KFLAGS without a "compiler" extension are common across
# all compilers.
# Use C11
KFLAGS_suncc		+= -std=c11
KFLAGS_suncc		+= -features=extensions

# Create 64bit code
KFLAGS_suncc		+= -m64

# Be verbose
KFLAGS_suncc            += -v

# Use optimizer level 3
KFLAGS_suncc		+= -xO3

# Generate code for the "kernel" model
KFLAGS_suncc            += -xmodel=kernel

# Pass "save_args" to code generator
KFLAGS_suncc            += -Wu,-save_args

# Use STABS for debug tags (or mdb won't be useful).
KFLAGS_suncc            += -xdebugformat=stabs

# Don't use a vector library
KFLAGS_suncc            += -xvector=none

# Don't optimize if it increases size
KFLAGS_suncc		+= -xspace

# Error flags
# Display the tag associated with the error
KFLAGS_suncc		+= -errtags=yes

# Exit on all warnings except specified
# e.g.: KFLAGS_suncc	+= -errwarn=%all,no%E_PTR_TO_VOID_IN_ARITHMETIC
KFLAGS_suncc		+= -errwarn=%all

# Print only tags when displaying warnings
KFLAGS_suncc		+= -errshort=tags

# Errors/Warnings that can be ignored
# e.g.: KFLAGS_suncc	+= -erroff=E_PTR_TO_VOID_IN_ARITHMETIC
KFLAGS_suncc		+= -erroff=E_EMPTY_INITIALIZER
KFLAGS_suncc		+= -erroff=E_ZERO_SIZED_STRUCT_UNION

# Architecture specific flags
# Do not allow float in passed args for kernel modules
KFLAGS_suncc_i386	+= -W2,-xregs=no%float
KFLAGS_suncc_i386	+= -Wu,-xregs=no%float
KFLAGS_suncc_i386	+= -W0,-y-xregs=no%float

# To make sure ctfconvert has STABS/Dwarf data and doesn't
# "globalize"
CTF_FLAGS	= -g

###############################################################
# Add GCC flags here.
#
KFLAGS_gcc	+= -std=gnu11
KFLAGS_gcc	+= -m64
KFLAGS_gcc	+= -FPIC
KFLAGS_gcc	+= -mtune=generic
KFLAGS_gcc	+= -mcmodel=kernel
#KFLAGS_gcc	+= -Werror
#KFLAGS_gcc	+= -Wfatal-errors
KFLAGS_gcc	+= -gdwarf-2
KFLAGS_gcc	+= -feliminate-unused-debug-symbols
KFLAGS_gcc	+= -gno-strict-dwarf
#KFLAGS_gcc	+= -feliminate-dwarf2-dups
KFLAGS_gcc      += -ffreestanding
KFLAGS_gcc      += -mno-red-zone

###############################################################

INC_PATH	= -I. $(DRM_INCL) -I/usr/platform/i86pc/include -I/usr/include


# Debug, anyone???
PROG_FLAGS	+= $(KDEFINES_$(DEBUG)) $(KFLAGS_$(DEBUG))

# KFLAGS based on compiler
KFLAGS		+= $(KFLAGS_$(MODULE_COMPILER))
#KFLAGS based on compiler and machine
KFLAGS		+= $(KFLAGS_$(MODULE_COMPILER)_$(MACH))

MODTYPE_CPPFLAGS = $(INC_PATH)
MODTYPE_CFLAGS	= $(INC_PATH) $(KDEFINES) $(KFLAGS) $(CTF_FLAGS) $(PROG_FLAGS)

#
# Define the MODTYPE environment
#
MODTYPE_BUILD_ENV	= CFLAGS='$(MODTYPE_CFLAGS)'
MODTYPE_BUILD_ENV	+= CC='$(CC)' LD='$(LD)' LINT='$(LINT)'
