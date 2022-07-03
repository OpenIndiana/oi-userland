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
# Copyright 2017 Gary Mills
# Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
#

# A simple rule to print the value of any macro.  Ex:
#    $ gmake print-REQUIRED_PACKAGES
# Note that some macros are set on a per target basis, so what you see
# is not always what you get.
print-%:
	@echo '$(subst ','\'',$*=$($*)) (origin: $(origin $*), flavor: $(flavor $*))'

# A simple rule to print only the value of any macro.
print-value-%:
	@echo '$(subst ','\'',$($*))'

# Provide default print package targets for components that do not rely on IPS.
# Define them implicitly so that the definitions do not collide with ips.mk
define print-package-rule
echo $(strip $(PACKAGE_$(1))) | tr ' ' '\n'
endef


COMPONENT_TOOL = $(WS_TOOLS)/userland-component

format:
	@$(COMPONENT_TOOL) --path $(COMPONENT_DIR);

update:
	@if [ "$(VERSION)X" = "X" ]; \
	then $(COMPONENT_TOOL) --path $(COMPONENT_DIR) --bump; \
	else $(COMPONENT_TOOL) --path $(COMPONENT_DIR) --bump $(VERSION); \
	fi;

update-latest:
	$(COMPONENT_TOOL) --path $(COMPONENT_DIR) --bump latest;

