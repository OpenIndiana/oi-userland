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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#
SUDO =		/usr/bin/sudo

define separator-line
	@$(PYTHON) -c 'l="="*(40-len("$1")/2); print("%s%s%s" % (l, "$1", l))'
endef

component-environment-check::
	$(call separator-line,Workspace)
	@echo " Path:        $(WS_TOP)"
	@echo " Branch:      $$(hg identify -b)"
	@echo " Changeset:   $$(hg identify -n)($$(hg identify -i))"
	$(call separator-line,System)
	@/usr/bin/uname -a
	@echo "Zone:  $$(/usr/sbin/zonename)"
	@/usr/sbin/psrinfo -vp
	@/usr/sbin/ipadm show-addr
	$(call separator-line,Required Packages)
	@/usr/bin/pkg list -vH $(REQUIRED_PACKAGES:%=/%)
	$(call separator-line)

component-environment-prep::
	@echo "Adding required packages to build environment..."
	@-echo $(REQUIRED_PACKAGES:%=/%) | xargs \
		$(SUDO) /usr/bin/pkg install --accept -v


#
# For building in a constructed zone.  Currently this assumes a template zone
# with /ws (tools mountpoint) and /builds (workspace mountpoint) mounted
# in the same place as in the global zone.  It also assumes the current
# $USER account is replicated in the template zone.
#
ZONENAME=bz-$(shell echo "$(WS_TOP)" | md5sum | cut -c0-7)-$(COMPONENT_NAME)

$(BUILD_DIR)/packages.xml:	Makefile	$(BUILD_DIR)
	@echo "$(REQUIRED_PACKAGES:%=\t\t<name>pkg:/%</name>\n)" >$(@)

$(BUILD_DIR)/ai_manifest.xml:	$(WS_TOOLS)/zone_default.xml $(BUILD_DIR)
	$(CP) $< $(@)

$(BUILD_DIR)/sc_profile.xml:	$(WS_TOOLS)/sc_profile.xml $(BUILD_DIR)
	$(GSED) -e "s/XXX_USER_XXX/$${USER}/g" -e "s/XXX_UID_XXX/$$(id -u)/g" $< >$(@)

component-zone-build:	$(BUILD_DIR)/ai_manifest.xml $(BUILD_DIR)/packages.xml \
			$(BUILD_DIR)/sc_profile.xml download
	$(call separator-line)
	$(call separator-line,Create $(ZONENAME))
	$(SUDO) /usr/sbin/zonecfg -z $(ZONENAME) create -t template
	#@$(SUDO) /usr/sbin/zoneadm -z $(ZONENAME) clone template 
	$(SUDO) /usr/sbin/zoneadm -z $(ZONENAME) install \
		-m $(BUILD_DIR)/ai_manifest.xml \
		-c $(BUILD_DIR)/sc_profile.xml
	$(call separator-line,Boot $(ZONENAME))
	$(SUDO) /usr/sbin/zoneadm -z $(ZONENAME) boot
	@while $$(true) ; do \
		echo "waiting for zone ..." ; \
		$(SUDO) /usr/sbin/zlogin -l $${USER} $(ZONENAME) \
				/bin/true >/dev/null 2>&1 && break ; \
		sleep 10 ; \
	done
	#$(call separator-line,Prep $(ZONENAME))
	#@$(SUDO) /usr/sbin/zlogin -S $(ZONENAME) \
	#	"cd $(COMPONENT_DIR) ; gmake component-be-prep"
	$(call separator-line,Build in $(ZONENAME))
	$(SUDO) /usr/sbin/zlogin -l $${USER} $(ZONENAME) \
		"cd $(COMPONENT_DIR) ; gmake component-be-check install"
	#	"cd $(COMPONENT_DIR) ; gmake component-be-check publish PKGLINTVAR=/bin/true"
	$(call separator-line,Halt $(ZONENAME))
	$(SUDO) /usr/sbin/zoneadm -z $(ZONENAME) halt
	$(SUDO) /usr/sbin/zoneadm -z $(ZONENAME) uninstall -F
	$(SUDO) /usr/sbin/zonecfg -z $(ZONENAME) delete -F
	$(call separator-line)

component-zone-cleanup::
	-$(SUDO) /usr/sbin/zoneadm -z $(ZONENAME) halt
	-$(SUDO) /usr/sbin/zoneadm -z $(ZONENAME) uninstall -F
	-$(SUDO) /usr/sbin/zonecfg -z $(ZONENAME) delete -F
