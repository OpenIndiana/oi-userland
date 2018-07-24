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
# Copyright 2018 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= geoip-database
COMPONENT_VERSION= 20180327
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= GeoLite geolocation databases compiled by MaxMind
COMPONENT_PROJECT_URL= https://dev.maxmind.com/geoip/legacy/geolite/
COMPONENT_FMRI= database/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Libraries

COMPONENT_SRC=  GeoIP.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).gz
COMPONENT_ARCHIVE_URL=  http://geolite.maxmind.com/download/geoip/database/GeoLiteCountry/GeoIP.dat.gz
COMPONENT_ARCHIVE_HASH= sha256:b9c05eb8bfcf90a6ddfdc6815caf40a8db2710f0ce3dd48fbd6c24d485ae0449
COMPONENT_LICENSE= CC-BY-SA-4.0

COMPONENT_SRC_1=GeoIPv6.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_1=$(COMPONENT_SRC_1).gz
COMPONENT_ARCHIVE_URL_1=http://geolite.maxmind.com/download/geoip/database/GeoIPv6.dat.gz
COMPONENT_ARCHIVE_HASH_1=sha256:9d6723a7db655c8f2cd3ccc4892e40844072a9f648be10c66725cbcfea62e106

COMPONENT_SRC_2=GeoLiteCity.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_2=$(COMPONENT_SRC_2).gz
COMPONENT_ARCHIVE_URL_2=http://geolite.maxmind.com/download/geoip/database/GeoLiteCity.dat.gz
COMPONENT_ARCHIVE_HASH_2=sha256:90db2e52195e3d1bcdb2c2789209006d09de5c742812dbd9a1b36c12675ec4cd

COMPONENT_SRC_3=GeoLiteCityv6.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_3=$(COMPONENT_SRC_3).gz
COMPONENT_ARCHIVE_URL_3=http://geolite.maxmind.com/download/geoip/database/GeoLiteCityv6-beta/GeoLiteCityv6.dat.gz 
COMPONENT_ARCHIVE_HASH_3=sha256:d8592dfafd3688c66d1813e68f690f57d0d55aee4c4602947b5356804ae92673

COMPONENT_SRC_4=GeoIPASNum.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_4=$(COMPONENT_SRC_4).gz
COMPONENT_ARCHIVE_URL_4=http://download.maxmind.com/download/geoip/database/asnum/GeoIPASNum.dat.gz 
COMPONENT_ARCHIVE_HASH_4=sha256:3bbe69a4f8d00c9c9ba24c0d9b40146e40ed8125f083a236e1069eaabc41f7f5

COMPONENT_SRC_5=GeoIPASNumv6.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_5=$(COMPONENT_SRC_5).gz
COMPONENT_ARCHIVE_URL_5=http://download.maxmind.com/download/geoip/database/asnum/GeoIPASNumv6.dat.gz 
COMPONENT_ARCHIVE_HASH_5=sha256:328400186915b3470fe35446c3bc9a62a53ef2a953e70c5f952918bd3fb57328


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
