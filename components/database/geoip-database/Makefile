#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Adam Stevko
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= geoip-database
COMPONENT_VERSION= 20170701
COMPONENT_SUMMARY= GeoLite geolocation databases compiled by MaxMind
COMPONENT_PROJECT_URL= https://dev.maxmind.com/geoip/legacy/geolite/
COMPONENT_FMRI= database/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_SRC=  GeoIP.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).gz
COMPONENT_ARCHIVE_URL=  http://geolite.maxmind.com/download/geoip/database/GeoLiteCountry/GeoIP.dat.gz
COMPONENT_ARCHIVE_HASH= sha256:cb7dd6ce84383835d226a4c0cd21cc79810b289ca2a6cc5a6189c4c9873cc7b1
COMPONENT_LICENSE= CC-BY-SA-4.0

COMPONENT_SRC_1=GeoIPv6.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_1=$(COMPONENT_SRC_1).gz
COMPONENT_ARCHIVE_URL_1=http://geolite.maxmind.com/download/geoip/database/GeoIPv6.dat.gz
COMPONENT_ARCHIVE_HASH_1=sha256:7401b50de3eec11651b764205041dd53519520f4182f581b6f16b422c8372a42

COMPONENT_SRC_2=GeoLiteCity.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_2=$(COMPONENT_SRC_2).gz
COMPONENT_ARCHIVE_URL_2=http://geolite.maxmind.com/download/geoip/database/GeoLiteCity.dat.gz
COMPONENT_ARCHIVE_HASH_2=sha256:730ec7c38dd1b6bc7f833928969bf5d060267536b599ecdc34e0d6e5d83c3de9

COMPONENT_SRC_3=GeoLiteCityv6.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_3=$(COMPONENT_SRC_3).gz
COMPONENT_ARCHIVE_URL_3=http://geolite.maxmind.com/download/geoip/database/GeoLiteCityv6-beta/GeoLiteCityv6.dat.gz 
COMPONENT_ARCHIVE_HASH_3=sha256:8f16f4f6029cbbe1ad8a5915c6384e5e6bf2fd84c7c5bca6750929cebfaa9e50

COMPONENT_SRC_4=GeoIPASNum.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_4=$(COMPONENT_SRC_4).gz
COMPONENT_ARCHIVE_URL_4=http://download.maxmind.com/download/geoip/database/asnum/GeoIPASNum.dat.gz 
COMPONENT_ARCHIVE_HASH_4=sha256:ccf02ee0516e10c722cd93d2b1c8805ae3e0a069931ad688ef05e473085c41b8

COMPONENT_SRC_5=GeoIPASNumv6.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_5=$(COMPONENT_SRC_5).gz
COMPONENT_ARCHIVE_URL_5=http://download.maxmind.com/download/geoip/database/asnum/GeoIPASNumv6.dat.gz 
COMPONENT_ARCHIVE_HASH_5=sha256:ffae87b117f6b69a685466de8436ef218814ced1a068e1ecacc34c843b7b136f


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

UNPACK=/usr/bin/gzip -kcfd

CLEAN_PATHS+= $(BUILD_DIR)

$(SOURCE_DIR)/.unpacked:
	$(MKDIR) $(SOURCE_DIR)
	$(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_SRC) > $(SOURCE_DIR)/$(COMPONENT_SRC)
	$(TOUCH) $(@)

$(SOURCE_DIR_1)/.unpacked:
	$(MKDIR) $(SOURCE_DIR_1)
	$(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_SRC_1) > $(SOURCE_DIR_1)/$(COMPONENT_SRC_1)
	$(TOUCH) $(@)

$(SOURCE_DIR_2)/.unpacked:
	$(MKDIR) $(SOURCE_DIR_2)
	$(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_SRC_2) > $(SOURCE_DIR_2)/$(COMPONENT_SRC_2)
	$(TOUCH) $(@)

$(SOURCE_DIR_3)/.unpacked:
	$(MKDIR) $(SOURCE_DIR_3)
	$(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_SRC_3) > $(SOURCE_DIR_3)/$(COMPONENT_SRC_3)
	$(TOUCH) $(@)

$(SOURCE_DIR_4)/.unpacked:
	$(MKDIR) $(SOURCE_DIR_4)
	$(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_SRC_4) >  $(SOURCE_DIR_4)/$(COMPONENT_SRC_4)
	$(TOUCH) $(@)

$(SOURCE_DIR_5)/.unpacked:
	$(MKDIR) $(SOURCE_DIR_5)
	$(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_SRC_5) > $(SOURCE_DIR_5)/$(COMPONENT_SRC_5)
	$(TOUCH) $(@)

$(BUILD_DIR_64)/.built:
	$(MKDIR) $(BUILD_DIR_64)
	$(TOUCH) $(@)

$(INSTALL_64):
	$(MKDIR) $(PROTOUSRSHAREDIR)/GeoIP
        
	$(INSTALL) -m 0644 $(SOURCE_DIR)/GeoIP.dat-$(COMPONENT_VERSION) $(PROTOUSRSHAREDIR)/GeoIP/GeoIP.dat 
	$(INSTALL) -m 0644 $(SOURCE_DIR_1)/GeoIPv6.dat-$(COMPONENT_VERSION) $(PROTOUSRSHAREDIR)/GeoIP/GeoIPv6.dat 
	$(INSTALL) -m 0644 $(SOURCE_DIR_2)/GeoLiteCity.dat-$(COMPONENT_VERSION) $(PROTOUSRSHAREDIR)/GeoIP/GeoIPCity.dat 
	$(INSTALL) -m 0644 $(SOURCE_DIR_3)/GeoLiteCityv6.dat-$(COMPONENT_VERSION) $(PROTOUSRSHAREDIR)/GeoIP/GeoIPCityv6.dat 
	$(INSTALL) -m 0644 $(SOURCE_DIR_4)/GeoIPASNum.dat-$(COMPONENT_VERSION) $(PROTOUSRSHAREDIR)/GeoIP/GeoIPASNum.dat 
	$(INSTALL) -m 0644 $(SOURCE_DIR_5)/GeoIPASNumv6.dat-$(COMPONENT_VERSION) $(PROTOUSRSHAREDIR)/GeoIP/GeoIPASNumv6.dat

	$(TOUCH) $(@)


build:          $(BUILD_64) prep

install:        $(INSTALL_64) build     

test:           $(TEST_32)
