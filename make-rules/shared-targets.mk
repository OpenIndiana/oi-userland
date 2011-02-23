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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

#
# (hopefully) helpful common targets.
#

PROTOMAN1FILES=$(MAN1FILES:%=$(PROTOUSRSHAREMAN1DIR)/%)
PROTOMAN3FILES=$(MAN3FILES:%=$(PROTOUSRSHAREMAN3DIR)/%)

$(PROTOUSRSHAREMAN1DIR)/% $(PROTOUSRSHAREMAN3DIR)/%:    manpages/%
	$(INS.file)

PROTOSFWLINKS= $(SFWPROGS:%=$(PROTOSFWBIN)/%)

$(PROTOSFWLINKS):	$(PROTOSFWBIN)
	$(RM) $@ ; $(SYMLINK) ../../bin/$(@F) $@

PROTOSFWMAN1LINKS= $(SFWMAN1:%=$(PROTOSFWSHAREMAN1)/%)

$(PROTOSFWMAN1LINKS):	$(PROTOSFWSHAREMAN1)
	$(RM) $@ ; $(SYMLINK) ../../../../share/man/man1/$(@F) $@

PROTOGNULINKS= $(GNUPROGS:%=$(PROTOGNUBIN)/%)

$(PROTOGNULINKS):       $(PROTOGNUBIN)
	$(RM) $@ ; $(SYMLINK) ../../bin/g$(@F) $@

PROTOGNUMAN1LINKS = $(GNUMAN1:%=$(PROTOGNUSHAREMAN1)/%)

$(PROTOGNUMAN1LINKS):   $(PROTOGNUSHAREMAN1)
	$(RM) $@ ; $(SYMLINK) ../../../../share/man/man1/g$(@F) $@


$(PROTOETCDIR) \
$(PROTOUSRSHAREMAN1DIR) \
$(PROTOUSRSHAREMAN3DIR) \
$(PROTOGNUBIN) \
$(PROTOGNUSHAREMAN1) \
$(PROTOSFWBIN) \
$(PROTOSFWSHAREMAN1) \
$(PROTOUSRBINDIR):
	$(MKDIR) $@

$(PROTOMAN3FILES): $(PROTOUSRSHAREMAN3DIR)

$(PROTOMAN1FILES): $(PROTOUSRSHAREMAN1DIR)
