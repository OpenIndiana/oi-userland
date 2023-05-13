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
# Copyright (c) 2020, Adam Stevko
#

PFEXEC =	/usr/bin/pfexec

ZONE =	$(WS_TOOLS)/userland-zone

define separator-line
       @$(PYTHON) -c 'l="="*int(40-len("$1")/2); print("%s%s%s" % (l, "$1", l))'
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
	@/usr/bin/pkg list -vH $(USERLAND_REQUIRED_PACKAGES:%=/%) $(REQUIRED_PACKAGES:%=/%)
	$(call separator-line)

component-environment-prep::
	@/usr/bin/pkg list -vH $(USERLAND_REQUIRED_PACKAGES:%=/%) $(REQUIRED_PACKAGES:%=/%) >/dev/null || \
		{ echo "Adding required packages to build environment..."; \
		while true ; do \
		  $(PFEXEC) /usr/bin/pkg install --accept -v $(USERLAND_REQUIRED_PACKAGES:%=/%) $(REQUIRED_PACKAGES:%=/%) ; \
		  RETVAL=$$? ; \
		  [ $$RETVAL -eq 0 ] && break; \
		  [ $$RETVAL -eq 4 ] && break; \
		  [ $$RETVAL -ne 7 ] && echo "pkg install returned $$RETVAL" && exit 1; \
		  sleep 10; \
		done; }

component-test-environment-check:: component-environment-check
	$(call separator-line,Required Additional Packages Needed for Testing Only)
	@[ -z "$(strip $(USERLAND_TEST_REQUIRED_PACKAGES))$(strip $(TEST_REQUIRED_PACKAGES))" ] || \
		/usr/bin/pkg list -vH $(USERLAND_TEST_REQUIRED_PACKAGES:%=/%) $(TEST_REQUIRED_PACKAGES:%=/%)
	@C=0 ; \
		for p in $(TEST_CONFLICTING_PACKAGES) ; do \
			/usr/bin/pkg list -q /$$p && echo "Conflicting package $$p found" && C=1 ; \
		done ; \
		exit $$C
	$(call separator-line)

component-test-environment-prep::
	@[ -z "$(strip $(USERLAND_TEST_REQUIRED_PACKAGES))$(strip $(TEST_REQUIRED_PACKAGES))" ] || \
		/usr/bin/pkg list -vH $(USERLAND_TEST_REQUIRED_PACKAGES:%=/%) $(TEST_REQUIRED_PACKAGES:%=/%) >/dev/null || \
		{ echo "Adding required packages to testing environment..."; \
		while true ; do \
		  $(PFEXEC) /usr/bin/pkg install --accept -v $(USERLAND_TEST_REQUIRED_PACKAGES:%=/%) $(TEST_REQUIRED_PACKAGES:%=/%) ; \
		  RETVAL=$$? ; \
		  [ $$RETVAL -eq 0 ] && break; \
		  [ $$RETVAL -eq 4 ] && break; \
		  [ $$RETVAL -ne 7 ] && echo "pkg install returned $$RETVAL" && exit 1; \
		  sleep 10; \
		done; }

ZONENAME_PREFIX = bz
ZONENAME_ID = $(shell echo "$(WS_TOP)" | sha1sum | cut -c0-7)-$(COMPONENT_NAME)
ZONENAME = $(ZONENAME_PREFIX)-$(ZONENAME_ID)

component-zone-template:
	$(call separator-line)
	$(call separator-line,Create template zone)
	USER_ID=$$(id -u) && \
	$(PFEXEC) $(ZONE) --prefix $(ZONENAME_PREFIX) create-template -u $${USER} -i $${USER_ID}

component-zone-build:
	$(call separator-line)
	$(call separator-line,Create $(ZONENAME))
	$(PFEXEC) $(ZONE) --prefix $(ZONENAME_PREFIX) spawn-zone --id $(ZONENAME_ID)
	$(call separator-line,Boot $(ZONENAME))
	@while $$(true); do \
		echo "Waiting for zone $(ZONENAME) to boot..."; \
		$(PFEXEC) /usr/sbin/zlogin -l $${USER} $(ZONENAME) \
				/bin/true >/dev/null 2>&1 && break; \
		sleep 10; \
	done
	# FIXME:
	# - remove once we figure out a better way how to enable zoneproxy-client inside the nlipkg brand
	@while $$(true); do \
  		echo "Waiting for $(ZONENAME) config repository.."; \
  		$(PFEXEC) /usr/bin/svcs -z $(ZONENAME) -a >/dev/null 2>&1 && break; \
  		sleep 10; \
  	done
	# We need to create door inside  after zone-proxy-client is running
	$(call separator-line,Configure IPS for $(ZONENAME))
	$(PFEXEC) /usr/lib/zones/zoneproxy-adm $(ZONENAME)
	@while $$(true); do \
  		echo "Waiting for zoneproxyd to be ready.."; \
  		PROXY_PID=$$(/usr/bin/svcs -p svc:/application/pkg/zones-proxyd:default | \
  			nawk '$$0 ~ /zoneproxyd/ {print $$2}') && \
  			$(PFEXEC) /usr/bin/pfiles $${PROXY_PID} | \
  			$(GNU_GREP) $(ZONENAME) >/dev/null 2>&1 && break; \
  		sleep 10; \
  	done
	$(PFEXEC) /usr/sbin/svcadm -z $(ZONENAME) \
		enable svc:/application/pkg/zones-proxy-client:default
	ZONEROOT="$$(/usr/sbin/zoneadm -z $(ZONENAME) list -p | cut -d: -f4)/root" && \
		$(PFEXEC) /usr/bin/pkg -R $${ZONEROOT} set-property use-system-repo True && \
	while $$(true); do \
		echo "Waiting for sysrepo to be ready..." && \
		$(PFEXEC) /usr/bin/pkg -R $${ZONEROOT} publisher | \
		$(GNU_GREP) syspub >/dev/null 2>&1 && break; \
		sleep 10; \
	done
	$(call separator-line,Build in $(ZONENAME))
	$(PFEXEC) /usr/sbin/zlogin -l $${USER} $(ZONENAME) \
		"cd $(COMPONENT_DIR); gmake install"
	$(call separator-line)

component-zone-cleanup:
	$(PFEXEC) $(ZONE) destroy-zone --id $(ZONENAME_ID)

# Short aliases for user convenience
env-check:: component-environment-check
env-prep:: component-environment-prep
test-env-check:: component-test-environment-check
test-env-prep:: component-test-environment-prep
