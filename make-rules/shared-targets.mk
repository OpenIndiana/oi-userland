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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#

#
# (hopefully) helpful common targets.
#

PROTOMAN1FILES=$(MAN1FILES:%=$(PROTOUSRSHAREMAN1DIR)/%)
PROTOMAN1MFILES=$(MAN1MFILES:%=$(PROTOUSRSHAREMAN1MDIR)/%)
PROTOMAN3FILES=$(MAN3FILES:%=$(PROTOUSRSHAREMAN3DIR)/%)
PROTOMAN4FILES=$(MAN4FILES:%=$(PROTOUSRSHAREMAN4DIR)/%)
PROTOMAN5FILES=$(MAN5FILES:%=$(PROTOUSRSHAREMAN5DIR)/%)
PROTOMAN8FILES=$(MAN8FILES:%=$(PROTOUSRSHAREMAN8DIR)/%)

$(PROTOUSRSHAREMAN1DIR)/% $(PROTOUSRSHAREMAN1MDIR)/% $(PROTOUSRSHAREMAN3DIR)/% \
$(PROTOUSRSHAREMAN4DIR)/% $(PROTOUSRSHAREMAN5DIR)/% $(PROTOUSRSHAREMAN8DIR)/%: \
	manpages/%
	$(INS.file)

PROTOGNULINKS= $(GNUPROGS:%=$(PROTOGNUBIN)/%)

$(PROTOGNULINKS):       $(PROTOGNUBIN)
	$(RM) $@ ; $(SYMLINK) ../../bin/g$(@F) $@

PROTOGNUMAN1LINKS = $(GNUMAN1:%=$(PROTOGNUSHAREMAN1)/%)

$(PROTOGNUMAN1LINKS):   $(PROTOGNUSHAREMAN1)
	$(RM) $@ ; $(SYMLINK) ../../../../share/man/man1/g$(@F) $@


$(PROTO_DIR) \
$(PROTOETCDIR) \
$(PROTOETCSECDIR) \
$(PROTOLIBDIR) \
$(PROTOUSRSHAREMAN1DIR) \
$(PROTOUSRSHAREMAN1MDIR) \
$(PROTOUSRSHAREMAN3DIR) \
$(PROTOUSRSHAREMAN4DIR) \
$(PROTOUSRSHAREMAN5DIR) \
$(PROTOUSRSHAREMAN8DIR) \
$(PROTOUSRSHAREDOCDIR) \
$(PROTOGNUBIN) \
$(PROTOGNUSHAREMAN1) \
$(PROTOUSRSBINDIR) \
$(PROTOUSRBINDIR):
	$(MKDIR) $@


$(PROTOMAN1FILES): $(PROTOUSRSHAREMAN1DIR)

$(PROTOMAN1MFILES): $(PROTOUSRSHAREMAN1MDIR)

$(PROTOMAN3FILES): $(PROTOUSRSHAREMAN3DIR)

$(PROTOMAN4FILES): $(PROTOUSRSHAREMAN4DIR)

$(PROTOMAN5FILES): $(PROTOUSRSHAREMAN5DIR)

$(PROTOMAN8FILES): $(PROTOUSRSHAREMAN8DIR)
