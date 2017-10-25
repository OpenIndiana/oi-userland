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
COMPONENT_VERSION= 20171007
COMPONENT_SUMMARY= GeoLite geolocation databases compiled by MaxMind
COMPONENT_PROJECT_URL= https://dev.maxmind.com/geoip/legacy/geolite/
COMPONENT_FMRI= database/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_SRC=  GeoIP.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).gz
COMPONENT_ARCHIVE_URL=  http://geolite.maxmind.com/download/geoip/database/GeoLiteCountry/GeoIP.dat.gz
COMPONENT_ARCHIVE_HASH= sha256:54d33334101a6e69f2877820d8d46a6c956f72716aa76c41c6f9a1d9bba51df7
COMPONENT_LICENSE= CC-BY-SA-4.0

COMPONENT_SRC_1=GeoIPv6.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_1=$(COMPONENT_SRC_1).gz
COMPONENT_ARCHIVE_URL_1=http://geolite.maxmind.com/download/geoip/database/GeoIPv6.dat.gz
COMPONENT_ARCHIVE_HASH_1=sha256:f36aff9ae567990ff36662abde3a44497e9ba79d34fd0d43c9a3c22a8ba86a3c

COMPONENT_SRC_2=GeoLiteCity.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_2=$(COMPONENT_SRC_2).gz
COMPONENT_ARCHIVE_URL_2=http://geolite.maxmind.com/download/geoip/database/GeoLiteCity.dat.gz
COMPONENT_ARCHIVE_HASH_2=sha256:19079e8d7b757e3cda77ca14978f02662f110e7c02ab797dfaf856d15f0adceb

COMPONENT_SRC_3=GeoLiteCityv6.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_3=$(COMPONENT_SRC_3).gz
COMPONENT_ARCHIVE_URL_3=http://geolite.maxmind.com/download/geoip/database/GeoLiteCityv6-beta/GeoLiteCityv6.dat.gz 
COMPONENT_ARCHIVE_HASH_3=sha256:7337386f63bf28d914171bd6ea46b1229a05c6acf08d13915938ade242c50b46

COMPONENT_SRC_4=GeoIPASNum.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_4=$(COMPONENT_SRC_4).gz
COMPONENT_ARCHIVE_URL_4=http://download.maxmind.com/download/geoip/database/asnum/GeoIPASNum.dat.gz 
COMPONENT_ARCHIVE_HASH_4=sha256:6440502916d198a72dcc5f569fe3e661d803b4081d230794ea43a507a66ead29

COMPONENT_SRC_5=GeoIPASNumv6.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_5=$(COMPONENT_SRC_5).gz
COMPONENT_ARCHIVE_URL_5=http://download.maxmind.com/download/geoip/database/asnum/GeoIPASNumv6.dat.gz 
COMPONENT_ARCHIVE_HASH_5=sha256:45200efc7a4e5a44f17df675a4aa161ac64fcafaaed081f05779cc4bdb0659e1


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
