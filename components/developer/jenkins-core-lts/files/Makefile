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
#JENKINS_VERSION ?= 2.73.1
#JENKINS_RELEASE ?= lts
all: build

build: 

install: 
	@case "$(DESTDIR)" in \
	    "") echo "DESTDIR must be set" >&2 ; exit 1 ;; \
	    /)  echo "DESTDIR must be set and not system rootfs" >&2 ; exit 1 ;; \
	    /*) true ;; \
	    *)  echo "DESTDIR must be set as an absolute path (got '$(DESTDIR)')" >&2 ; exit 1 ;; \
	 esac
	@[ -n "$(JENKINS_VERSION)" ] || { echo "JENKINS_VERSION not set" >&2; exit 1; }
	@[ -n "$(JENKINS_RELEASE)" ] || { echo "JENKINS_RELEASE not set" >&2; exit 1; }
	$(RM) -r $(DESTDIR)/usr
	mkdir -p $(DESTDIR)/usr/share/jenkins/war
	mkdir -p $(DESTDIR)/usr/share/jenkins/war/$(JENKINS_RELEASE)
	cp -f jenkins-$(JENKINS_RELEASE)-$(JENKINS_VERSION).war $(DESTDIR)/usr/share/jenkins/war/$(JENKINS_RELEASE)/jenkins-$(JENKINS_VERSION).war
	ln -rfs $(DESTDIR)/usr/share/jenkins/war/$(JENKINS_RELEASE)/jenkins-$(JENKINS_VERSION).war $(DESTDIR)/usr/share/jenkins/war/$(JENKINS_RELEASE)/jenkins.war
	ln -rfs $(DESTDIR)/usr/share/jenkins/war/$(JENKINS_RELEASE)/jenkins.war $(DESTDIR)/usr/share/jenkins/war/jenkins.war
