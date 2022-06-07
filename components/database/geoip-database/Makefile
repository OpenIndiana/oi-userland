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
# Copyright 2022 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= geoip-database
COMPONENT_VERSION= 20220607
#COMPONENT_REVISION= 1
COMPONENT_SUMMARY= GeoLite geolocation databases compiled by MaxMind
COMPONENT_PROJECT_URL= https://mailfud.org/geoip-legacy
COMPONENT_FMRI= database/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Libraries

COMPONENT_SRC=  GeoIP.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).gz
COMPONENT_ARCHIVE_URL=  https://mailfud.org/geoip-legacy/GeoIP.dat.gz
COMPONENT_ARCHIVE_HASH= sha256:db209fb8c49108e1873f105c1873f1ef1ca8a5c1be69c772c9e3f5b873be7239
COMPONENT_LICENSE= CC-BY-SA-4.0

COMPONENT_SRC_1=GeoIPv6.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_1=$(COMPONENT_SRC_1).gz
COMPONENT_ARCHIVE_URL_1=https://mailfud.org/geoip-legacy/GeoIPv6.dat.gz
COMPONENT_ARCHIVE_HASH_1=sha256:4f47579f1a082ead597dfd79ae57fa7b7eeeb120128ec16b3137eeb1b0d40e9b

COMPONENT_SRC_2=GeoIPCity.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_2=$(COMPONENT_SRC_2).gz
COMPONENT_ARCHIVE_URL_2=https://mailfud.org/geoip-legacy/GeoIPCity.dat.gz
COMPONENT_ARCHIVE_HASH_2=sha256:0be9e5e0fce82cba27afe2af9ada50468a9bc270a5ecf31b2c0793d509ac895c

COMPONENT_SRC_3=GeoIPCityv6.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_3=$(COMPONENT_SRC_3).gz
COMPONENT_ARCHIVE_URL_3=https://mailfud.org/geoip-legacy/GeoIPCityv6.dat.gz
COMPONENT_ARCHIVE_HASH_3=sha256:799dd33125910b75360787faa31557befd76a4917a4201642d7840309fc7080e

COMPONENT_SRC_4=GeoIPASNum.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_4=$(COMPONENT_SRC_4).gz
COMPONENT_ARCHIVE_URL_4=https://mailfud.org/geoip-legacy/GeoIPASNum.dat.gz
COMPONENT_ARCHIVE_HASH_4=sha256:ae37411000d25f62cab23606d3d33d1d1d6c4d117560411a3661f95d477ba97e

COMPONENT_SRC_5=GeoIPASNumv6.dat-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_5=$(COMPONENT_SRC_5).gz
COMPONENT_ARCHIVE_URL_5=https://mailfud.org/geoip-legacy/GeoIPASNumv6.dat.gz
COMPONENT_ARCHIVE_HASH_5=sha256:88e1a9f2814d989c26efdb58eb86a0f9541ff7d78bcd818695c2eae3338873c1


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
	$(INSTALL) -m 0644 $(SOURCE_DIR_2)/GeoIPCity.dat-$(COMPONENT_VERSION) $(PROTOUSRSHAREDIR)/GeoIP/GeoIPCity.dat
	$(INSTALL) -m 0644 $(SOURCE_DIR_3)/GeoIPCityv6.dat-$(COMPONENT_VERSION) $(PROTOUSRSHAREDIR)/GeoIP/GeoIPCityv6.dat
	$(INSTALL) -m 0644 $(SOURCE_DIR_4)/GeoIPASNum.dat-$(COMPONENT_VERSION) $(PROTOUSRSHAREDIR)/GeoIP/GeoIPASNum.dat
	$(INSTALL) -m 0644 $(SOURCE_DIR_5)/GeoIPASNumv6.dat-$(COMPONENT_VERSION) $(PROTOUSRSHAREDIR)/GeoIP/GeoIPASNumv6.dat

	$(TOUCH) $(@)

build:          $(BUILD_64) prep

install:        $(INSTALL_64) build
