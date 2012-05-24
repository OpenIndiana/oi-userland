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

ASUBDIRS = client panel

client: panel

app: panel

include $(SRC)/make-rules/Makefile.ant
include $(SRC)/make-rules/Makefile.env
include $(SRC)/make-rules/Makefile.targ

JP = java.policy
VP = vp
CLEAN_FILES += $(VP) $(JP)

$(JP): $(JP).in
	$(SED) -e 's#<VP_DIR>#$(VP_DIR)#g' \
	    -e 's#<RAD_JAVA_DIR>#$(RAD_JAVA_DIR)#g' \
	    $(JP).in > $@

$(VP): $(VP).in
	$(SED) -e 's#<VP_DIR>#$(VP_DIR)#g' \
	    -e 's#<RAD_JAVA_DIR>#$(RAD_JAVA_DIR)#g' \
	    -e 's#<VP_LOCALE>#$(VP_LOCALE)#g' \
	    -e 's#<JAVA_POLICY>#$(VP_DIR)/$(JP)#g;' $(VP).in > $@

install: $(PROTO_BIN)/$(VP) $(PROTO_VP_DIR)/$(JP)
