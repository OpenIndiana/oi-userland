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
# Copyright (c) 2021 David Stes
#
# Userland build system for packages built with a TeX live profile
# TeX live is in meta-packages/texlive and must be installed
#
# COMPONENT_TEXLIVE must be the name of a profile, e.g. latex.profile
#
# PROTO_DIR in the profile will be ran through GSED first to expand it
#

TLPKG=		/usr/share/install-tl-20210128/
TLPROFILE=	$(COMPONENT_TEXLIVE)

download::

unpack::	download

patch::		unpack

$(SOURCE_DIR)/.prep:	component-environment-prep download unpack patch
	$(COMPONENT_PREP_ACTION)
	$(TOUCH) $@

prep::	$(SOURCE_DIR)/.prep

# no-op
$(BUILD_DIR)/%/.built:  $(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	$(MKDIR) $(BUILD_DIR)
	$(GSED) "s@PROTO_DIR@$(PROTO_DIR)@" \
		< $(COMPONENT_TEXLIVE) \
		> $(BUILD_DIR)/$(TLPROFILE)
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

build::	$(BUILD_DIR)/%/.built

# install the source into the proto directory
$(BUILD_DIR)/%/.installed:      $(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	$(MKDIR) $(PROTO_DIR)
	cd $(BUILD_DIR) ; $(PERL) $(TLPKG)/install-tl --profile $(TLPROFILE)
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

install:: $(BUILD_DIR)/%/.installed

clean::
	$(PRE_CLEAN_ACTION)
	$(RM) -r $(BUILD_DIR)

clobber::	clean
	$(RM) -r $(CLOBBER_PATHS)

