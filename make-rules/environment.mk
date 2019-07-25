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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#
PFEXEC =               /usr/bin/pfexec

define separator-line
       @$(PYTHON) -c 'l="="*(40-len("$1")/2); print("%s%s%s" % (l, "$1", l))'
endef

component-environment-check::
	$(call separator-line,Workspace)
	@echo " Path:        $(WS_TOP)"
	@echo " Branch:      $$(git rev-parse --abbrev-ref HEAD)"
	@echo " Changeset:   $$(git rev-parse HEAD)"
	$(call separator-line,System)
	@/usr/bin/uname -a
	@echo "Zone: $$(/usr/bin/zonename)"
	@echo "Zone IP type: $$(/usr/bin/zonename -t)"
	@/usr/sbin/psrinfo -vp
	@/usr/sbin/ipadm show-addr
	$(call separator-line,Required Packages)
	@/usr/bin/pkg list -vH $(REQUIRED_PACKAGES:%=/%)
	$(call separator-line)

component-environment-prep::
	@/usr/bin/pkg list -vH $(REQUIRED_PACKAGES:%=/%) >/dev/null || \
		{ echo "Adding required packages to build environment..."; \
		  $(PFEXEC) /usr/bin/pkg install --accept  $(REQUIRED_PACKAGES:%=/%) || [ $$? -eq 4 ] ; }

# Short aliases for user convenience
env-check:: component-environment-check
env-prep:: component-environment-prep
