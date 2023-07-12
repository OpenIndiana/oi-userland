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
# Copyright 2022 Niklas Poslovski
#

include $(WS_MAKE_RULES)/makemaker.mk

COMPONENT_CONFIGURE_ARGS =	--installdirs=vendor
$(BUILD_DIR)/%/.configured:	 $(SOURCE_DIR)/.prep
	($(RM) -r $(@D) ; $(MKDIR) $(@D))
	$(ENV) $(CLONEY_ARGS) $(CLONEY) $(SOURCE_DIR) $(@D)
	$(COMPONENT_PRE_CONFIGURE_ACTION)
	(cd $(@D) ; $(COMPONENT_CONFIGURE_ENV) $(PERL) $(PERL_FLAGS) \
				Build.PL $(COMPONENT_CONFIGURE_ARGS) $(CONFIGURE_OPTIONS))
		$(COMPONENT_POST_CONFIGURE_ACTION)
		$(TOUCH) $@

$(BUILD_DIR)/%/.built:  $(BUILD_DIR)/%/.configured
		$(COMPONENT_PRE_BUILD_ACTION)
		(cd $(@D) ; $(ENV) $(COMPONENT_BUILD_ENV) \
				./Build \
				$(COMPONENT_BUILD_TARGETS))
		$(COMPONENT_POST_BUILD_ACTION)
		$(TOUCH) $@

COMPONENT_INSTALL_ARGS =	   --destdir="$(PROTO_DIR)"
COMPONENT_INSTALL_TARGETS =	 install
$(BUILD_DIR)/%/.installed:	  $(BUILD_DIR)/%/.built
		$(COMPONENT_PRE_INSTALL_ACTION)
		(cd $(@D) ; $(ENV) $(COMPONENT_INSTALL_ENV) ./Build \
						$(COMPONENT_INSTALL_TARGETS) $(COMPONENT_INSTALL_ARGS))
		$(COMPONENT_POST_INSTALL_ACTION)
		$(TOUCH) $@

# test the built source
$(BUILD_DIR)/%/.tested-and-compared:	$(BUILD_DIR)/%/.built
		$(RM) -rf $(COMPONENT_TEST_BUILD_DIR)
		$(MKDIR) $(COMPONENT_TEST_BUILD_DIR)
		$(COMPONENT_PRE_TEST_ACTION)
		-(cd $(COMPONENT_TEST_DIR) ; \
				$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
				./Build \
				$(COMPONENT_TEST_ARGS) $(COMPONENT_TEST_TARGETS)) \
				&> $(COMPONENT_TEST_OUTPUT)
		$(COMPONENT_POST_TEST_ACTION)
		$(COMPONENT_TEST_CREATE_TRANSFORMS)
		$(COMPONENT_TEST_PERFORM_TRANSFORM)
		$(COMPONENT_TEST_COMPARE)
		$(COMPONENT_TEST_CLEANUP)
		$(TOUCH) $@

$(BUILD_DIR)/%/.tested:	SHELLOPTS=pipefail
$(BUILD_DIR)/%/.tested:	$(BUILD_DIR)/%/.built
		$(RM) -rf $(COMPONENT_TEST_BUILD_DIR)
		$(MKDIR) $(COMPONENT_TEST_BUILD_DIR)
		$(COMPONENT_PRE_TEST_ACTION)
		(cd $(COMPONENT_TEST_DIR) ; \
				$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
				./Build \
				$(COMPONENT_TEST_ARGS) $(COMPONENT_TEST_TARGETS)) \
				|& $(TEE) $(COMPONENT_TEST_OUTPUT)
		$(COMPONENT_POST_TEST_ACTION)
		$(COMPONENT_TEST_CREATE_TRANSFORMS)
		$(COMPONENT_TEST_PERFORM_TRANSFORM)
		$(COMPONENT_TEST_CLEANUP)
		$(TOUCH) $@

# Build.PL needs Module::Build
USERLAND_REQUIRED_PACKAGES.perl += library/perl-5/module-build
