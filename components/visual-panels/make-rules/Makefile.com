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
# Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
#

CFLAGS += -g -mt -errwarn=%all
CPPFLAGS += -I../../daemon -I$(ROOT)/usr/include
LDLIBS += -L$(PROTO_LIB) -ladr

RADDIR_XPORT=$(PROTO_RAD)/transport
RADDIR_PROTO=$(PROTO_RAD)/protocol
RADDIR_MODULE=$(PROTO_RAD)/module

ADROPTS=$(MOD_ADROPTS)
MOD_API_OBJS=$(MOD_APIS:%=api_%_impl.o)
MOD_API_CFILES=$(MOD_APIS:%=api_%_impl.c)
MOD_API_HDRS=$(MOD_APIS:%=api_%.h)
MOD_ALLOBJS=$(MOD_OBJS) $(MOD_API_OBJS)

SRCS = $(MOD_ALLOBJS:%.o=%.c)

LNFILES=$(SRCS:%.c=%.ln) rad_dummy.ln

CLEAN_FILES += $(MOD_ALLOBJS) $(MOD_API_HDRS) $(MOD_API_CFILES) $(CLEANFILES) \
	$(LNFILES)
CLOBBER_FILES += $(MOD_LIBNAME)
CTFCONVERT_HOOK = && $(CTFCONVERT) -l foo $@

LDFLAGS = $(MAPOPTS) -Wl,-zdefs -lc

LINTFLAGS += -x -erroff=E_PTRDIFF_OVERFLOW
MAPFILES += $(SRC)/make-rules/mapfile.module

build: $(MOD_LIBNAME)

.NO_PARALLEL: $(MOD_API_HDRS) $(MOD_API_CFILES)

.PARALLEL: $(MOD_ALLOBJS) $(LNFILES)

$(MOD_API_CFILES) $(MOD_API_HFILES): $(ADRLOC)

$(LNFILES) $(MOD_ALLOBJS): $(MOD_API_HDRS) $(MOD_API_CFILES)

$(MOD_LIBNAME):	$(MOD_ALLOBJS) $(MAPFILES)
	$(CC) -G -o $@ $(MOD_ALLOBJS) $(LDFLAGS) $(LDLIBS)
	$(CTFMERGE) -l foo -o $(MOD_LIBNAME) $(MOD_ALLOBJS)

install: $(MOD_INSTALLDIR)/$(MOD_LIBNAME)

lint: $(LNFILES)
	$(LINT.c) $(LNFILES) $(LDLIBS) -lrad

$(MOD_INSTALLDIR)/$(MOD_LIBNAME) := FILEMODE=555

$(MOD_INSTALLDIR)/%: %
	$(INS.file)

%.o: ../%.c
	$(COMPILE.c) $(OUTPUT_OPTION) $< $(CTFCONVERT_HOOK)

%.ln: ../%.c
	$(LINT.c) $(OUTPUT_OPTION) -c $<

include $(SRC)/make-rules/Makefile.targ
