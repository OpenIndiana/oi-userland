JENKINS_VERSION ?= 2.65
JENKINS_RELEASE ?= weekly
all: build

build: 

install: 
	mkdir -p $(DESTDIR)/usr/share/jenkins/war
	mkdir -p $(DESTDIR)/usr/share/jenkins/war/$(JENKINS_RELEASE)
	cp -f jenkins-$(JENKINS_VERSION).war $(DESTDIR)/usr/share/jenkins/war/$(JENKINS_RELEASE)/
	ln -rs $(DESTDIR)/usr/share/jenkins/war/$(JENKINS_RELEASE)/jenkins-$(JENKINS_VERSION).war $(DESTDIR)/usr/share/jenkins/war/$(JENKINS_RELEASE)/jenkins.war
	ln -rs $(DESTDIR)/usr/share/jenkins/war/$(JENKINS_RELEASE)/jenkins.war $(DESTDIR)/usr/share/jenkins/war/jenkins.war
