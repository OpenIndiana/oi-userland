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
#NETBEANS_VERSION ?= 8.2.0
#NETBEANS_RELEASE ?= final
#TARBALL_TOPDIR ?= netbeans
all: build

build: 

install: 
	@case "$(DESTDIR)" in \
	    "") echo "DESTDIR must be set" >&2 ; exit 1 ;; \
	    /)  echo "DESTDIR must be set and not system rootfs" >&2 ; exit 1 ;; \
	    /*) true ;; \
	    *)  echo "DESTDIR must be set as an absolute path (got '$(DESTDIR)')" >&2 ; exit 1 ;; \
	 esac
	@[ -n "$(NETBEANS_VERSION)" ] || { echo "NETBEANS_VERSION not set" >&2; exit 1; }
	@[ -n "$(NETBEANS_RELEASE)" ] || { echo "NETBEANS_RELEASE not set" >&2; exit 1; }
	@[ -n "$(TARBALL_TOPDIR)" ] || { echo "TARBALL_TOPDIR not set" >&2; exit 1; }
	$(RM) -r $(DESTDIR)/usr
	mkdir -p $(DESTDIR)/usr/share/netbeans-$(NETBEANS_VERSION)-$(NETBEANS_RELEASE).tmp
	unzip -q -u $(COMPONENT_ARCHIVE) -d $(DESTDIR)/usr/share/netbeans-$(NETBEANS_VERSION)-$(NETBEANS_RELEASE).tmp
	cd $(DESTDIR)/usr/share/netbeans-$(NETBEANS_VERSION)-$(NETBEANS_RELEASE).tmp && \
		mv -f $(TARBALL_TOPDIR) $(DESTDIR)/usr/share/netbeans-$(NETBEANS_VERSION)-$(NETBEANS_RELEASE)
	$(RM) -r $(DESTDIR)/usr/share/netbeans-$(NETBEANS_VERSION)-$(NETBEANS_RELEASE).tmp
	ln -rfs $(DESTDIR)/usr/share/netbeans-$(NETBEANS_VERSION)-$(NETBEANS_RELEASE) $(DESTDIR)/usr/share/netbeans
	mkdir -p $(DESTDIR)/usr/bin
	ln -rfs $(DESTDIR)/usr/share/netbeans/bin/netbeans $(DESTDIR)/usr/bin/
