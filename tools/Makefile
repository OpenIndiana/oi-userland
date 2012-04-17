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
# Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../make-rules/shared-macros.mk

download setup prep build install publish \
validate:	links time-$(MACH32).so time-$(MACH64).so

# generate wrappers for parfait. we need to generate them
# with the correct compiler variables from the common makefiles because
# some things reset the environment which causes lovely infinite
# loops
links:
	$(MKDIR) parfait
	@for i in cc CC gcc g++ ld ; do \
		$(MKDIR) parfait ; \
		$(RM) parfait/$$i ; \
		echo "#!/bin/ksh" > parfait/$$i ; \
		echo "IFS=" >> parfait/$$i ; \
		echo "export PARFAIT_NATIVESUNCC=$(SPRO_VROOT)/bin/cc" >> parfait/$$i ; \
		echo "export PARFAIT_NATIVESUNCXX=$(SPRO_VROOT)/bin/CC" >> parfait/$$i ; \
		echo "export PARFAIT_NATIVEGCC=$(GCC_ROOT)/bin/gcc" >> parfait/$$i ; \
		echo "export PARFAIT_NATIVEGXX=$(GCC_ROOT)/bin/g++" >> parfait/$$i ; \
		echo "export PARFAIT_CLANG="$(PARFAIT_CLANG) >> parfait/$$i ; \
		echo "exec" $(PARFAIT_ROOT)/bin/parfait-$$i '$$*' >> parfait/$$i ; \
		chmod +x parfait/$$i ; \
	done


time-$(MACH64).o:			BITS=64
time-$(MACH32).o time-$(MACH64).o:	CFLAGS += -Kpic

time-$(MACH32).o time-$(MACH64).o:	time.c
	$(CC) $(CFLAGS) -c -o $@ $<

time-%.so:	time-%.o
	$(LD) -G -o $@ $<

clean:
	$(RM) time-*.o time*.bc

clobber:	clean
	$(RM) time-*.so python/pkglint/*.pyc
	$(RM) -r parfait

