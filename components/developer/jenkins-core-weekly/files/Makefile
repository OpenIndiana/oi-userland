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

JENKINS_VERSION ?= 2.70
JENKINS_RELEASE ?= weekly
all: build

build: 

install: 
	mkdir -p $(DESTDIR)/usr/share/jenkins/war
	mkdir -p $(DESTDIR)/usr/share/jenkins/war/$(JENKINS_RELEASE)
	cp -f jenkins-$(JENKINS_VERSION).war $(DESTDIR)/usr/share/jenkins/war/$(JENKINS_RELEASE)/
	ln -rfs $(DESTDIR)/usr/share/jenkins/war/$(JENKINS_RELEASE)/jenkins-$(JENKINS_VERSION).war $(DESTDIR)/usr/share/jenkins/war/$(JENKINS_RELEASE)/jenkins.war
	ln -rfs $(DESTDIR)/usr/share/jenkins/war/$(JENKINS_RELEASE)/jenkins.war $(DESTDIR)/usr/share/jenkins/war/jenkins.war
