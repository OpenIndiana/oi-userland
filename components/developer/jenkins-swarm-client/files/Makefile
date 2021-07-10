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
# Copyright 2016-2021 Jim Klimov
#

# component/Makefile should set values similar to the following example:
#COMPONENT_NAME ?= jenkins-swarm-client
#COMPONENT_VERSION ?= 3.25
all: build

build: 

install: 
	@case "$(DESTDIR)" in \
	    "") echo "DESTDIR must be set" >&2 ; exit 1 ;; \
	    /)  echo "DESTDIR must be set and not system rootfs" >&2 ; exit 1 ;; \
	    /*) true ;; \
	    *)  echo "DESTDIR must be set as an absolute path (got '$(DESTDIR)')" >&2 ; exit 1 ;; \
	 esac
	@[ -n "$(COMPONENT_VERSION)" ] || { echo "COMPONENT_VERSION not set" >&2; exit 1; }
	@[ -n "$(COMPONENT_NAME)" ] || { echo "COMPONENT_NAME not set" >&2; exit 1; }
	$(RM) -r $(DESTDIR)/usr
	mkdir -p $(DESTDIR)/usr/share/jenkins/jar
	cp -f $(COMPONENT_NAME)-$(COMPONENT_VERSION).jar $(DESTDIR)/usr/share/jenkins/jar/
	ln -rfs $(DESTDIR)/usr/share/jenkins/jar/$(COMPONENT_NAME)-$(COMPONENT_VERSION).jar $(DESTDIR)/usr/share/jenkins/jar/$(COMPONENT_NAME).jar
