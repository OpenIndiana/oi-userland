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
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../Makefile.doc

APISDIR = ../../apis
APIS_CMD = (cd $(APISDIR); $(LS) -1 *.xml 2>/dev/null; $(TRUE))
#APIS = $(APIS_CMD:sh)
#APIS = kstat.xml smf.xml zonesbridge.xml
#APIS = smf.xml

#MANPAGES_1 = radadrgen.1 vp.1
MANPAGES_1 = vp.1
#MANPAGES_1m = rad.1m
#MANPAGES_3rad = $(APIS:%.xml=%.3rad)
#MANPAGES = $(MANPAGES_1) $(MANPAGES_1m) $(MANPAGES_3rad)
MANPAGES = $(MANPAGES_1)
CLOBBER_FILES += $(MANPAGES)
SRCS = \
	$(MANPAGES_1:%=%.xml)
INSTALLED_FILES = \
	$(MANPAGES_1:%=$(PROTO_MAN)/man1/%)

build:	$(MANPAGES)

lint:	
	$(XMLLINT) $(SRCS)

install: $(INSTALLED_FILES)

# Man page rules.  Must be updated if new sections are added.

DBOPTS += --param refentry.meta.get.quietly 1

# DocBook's man page stylesheets assume we are using groff with its left-
# and right-quote character constants.  A more portable approach would be
# to reference the left- and right-quote string constants.  FIX_MAN maps
# from one to the other.

FIX_MAN = -echo '1,$$s/(lq/*(lq/g\n1,$$s/(rq/*(rq\nw' | ed -s $@

$(PROTO_MAN)/man1/% $(PROTO_MAN)/man1m/% $(PROTO_MAN)/man3rad/%: %
	$(INS.file)

%.1: %.1.xml
	$(XSLT.man)
	$(FIX_MAN)

%.1m: %.1m.xml
	$(XSLT.man)
	$(FIX_MAN)

%.3rad: $(APISDIR)/%.xml
	$(RADADRGEN) -N -o man $< > $@

include $(SRC)/make-rules/Makefile.targ
