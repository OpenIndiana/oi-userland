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

NETBEANS_VERSION ?= 8.2.0
NETBEANS_RELEASE ?= final
TARBALL_TOPDIR ?= netbeans
all: build

build: 

install: 
	$(RM) -r $(DESTDIR)/usr
	mkdir -p $(DESTDIR)/usr/share/netbeans-$(NETBEANS_VERSION)-$(NETBEANS_RELEASE).tmp
	unzip -q -u $(COMPONENT_ARCHIVE) -d $(DESTDIR)/usr/share/netbeans-$(NETBEANS_VERSION)-$(NETBEANS_RELEASE).tmp
	cd $(DESTDIR)/usr/share/netbeans-$(NETBEANS_VERSION)-$(NETBEANS_RELEASE).tmp && \
		mv -f $(TARBALL_TOPDIR) $(DESTDIR)/usr/share/netbeans-$(NETBEANS_VERSION)-$(NETBEANS_RELEASE)
	$(RM) -r $(DESTDIR)/usr/share/netbeans-$(NETBEANS_VERSION)-$(NETBEANS_RELEASE).tmp
	ln -rfs $(DESTDIR)/usr/share/netbeans-$(NETBEANS_VERSION)-$(NETBEANS_RELEASE) $(DESTDIR)/usr/share/netbeans
	mkdir -p $(DESTDIR)/usr/bin
	ln -rfs $(DESTDIR)/usr/share/netbeans/bin/netbeans $(DESTDIR)/usr/bin/
