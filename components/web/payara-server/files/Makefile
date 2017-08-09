#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016-2017 Jim Klimov
#

# component/Makefile should set values similar to the following example:
#COMPONENT_VERSION ?= 4.1.2.172.0
#PAYARA_RELEASE ?= server
#TARBALL_TOPDIR ?= payara41
all: build

build: 

# Note: for given release type (e.g. payara-server) we keep updates
# falling into same directory, replacing an older version, because
# configuration files and default appserver domains etc. evolve there.
# Domain volatile data is moved from /usr to /var though, as it has
# the most R/W churn; the configs might stay unchanged.
install: 
	@case "$(DESTDIR)" in \
	    "") echo "DESTDIR must be set" >&2 ; exit 1 ;; \
	    /)  echo "DESTDIR must be set and not system rootfs" >&2 ; exit 1 ;; \
	    /*) true ;; \
	    *)  echo "DESTDIR must be set as an absolute path (got '$(DESTDIR)')" >&2 ; exit 1 ;; \
	 esac
	@[ -n "$(COMPONENT_VERSION)" ] || { echo "COMPONENT_VERSION not set" >&2; exit 1; }
	@[ -n "$(PAYARA_RELEASE)" ] || { echo "PAYARA_RELEASE not set" >&2; exit 1; }
	@[ -n "$(TARBALL_TOPDIR)" ] || { echo "TARBALL_TOPDIR not set" >&2; exit 1; }
	$(RM) -r $(DESTDIR)/usr $(DESTDIR)/var
	mkdir -p $(DESTDIR)/usr/share/payara-$(PAYARA_RELEASE)-$(COMPONENT_VERSION).tmp
	unzip -q -u $(COMPONENT_ARCHIVE) -d $(DESTDIR)/usr/share/payara-$(PAYARA_RELEASE)-$(COMPONENT_VERSION).tmp
	cd $(DESTDIR)/usr/share/payara-$(PAYARA_RELEASE)-$(COMPONENT_VERSION).tmp && \
		mv -f $(TARBALL_TOPDIR) $(DESTDIR)/usr/share/payara-$(PAYARA_RELEASE)
	$(RM) -r $(DESTDIR)/usr/share/payara-$(PAYARA_RELEASE)-$(COMPONENT_VERSION).tmp
	ln -rfs $(DESTDIR)/usr/share/payara-$(PAYARA_RELEASE) $(DESTDIR)/usr/share/payara
	mkdir -p $(DESTDIR)/var/lib/payara-$(PAYARA_RELEASE)
	mv -f $(DESTDIR)/usr/share/payara/glassfish/domains $(DESTDIR)/var/lib/payara-$(PAYARA_RELEASE)/domains
	ln -rfs $(DESTDIR)/var/lib/payara-$(PAYARA_RELEASE)/domains $(DESTDIR)/usr/share/payara/glassfish/domains
