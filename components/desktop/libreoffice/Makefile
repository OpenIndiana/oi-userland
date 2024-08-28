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
# Copyright 2020 Alexander Pyhalov
# Copyright 2022 Daniel Bell
#

OPENSSL_VERSION= 3.1
USE_PARALLEL_BUILD = yes
include ../../../make-rules/shared-macros.mk
BITS=64
ENV = /usr/bin/env

# BUILD_BETA is the beta version; define with build number for beta release
# BUILD_BETA=1

# BUILD_ALPHA is the alpha version; define with build number for beta release
# BUILD_ALPHA=1

# BUILD_FIX is the build fix number, i.e. libreoffice-7.6.0.2-buildfix1
# Define only if needed.
# BUILD_FIX=1

# BUILD_GITHUB is defined only if the source is from github instead of the
# documentfoundation website
# BUILD_GITHUB=1

COMPONENT_NAME=         libreoffice
COMPONENT_VERSION=      24.8.1
COMPONENT_RC_VERSION=	1
ifdef BUILD_ALPHA
COMPONENT_FULL_VERSION=$(COMPONENT_VERSION).$(COMPONENT_RC_VERSION).alpha$(BUILD_ALPHA)
else ifdef BUILD_BETA
COMPONENT_FULL_VERSION=$(COMPONENT_VERSION).$(COMPONENT_RC_VERSION).beta$(BUILD_BETA)
else
COMPONENT_FULL_VERSION=$(COMPONENT_VERSION).$(COMPONENT_RC_VERSION)
endif
ifdef BUILD_FIX
COMPONENT_FULL_VERSION=$(COMPONENT_FULL_VERSION)-buildfix$(BUILD_FIX)
endif
# repology wants to use HUMAN_VERSION
HUMAN_VERSION=          $(COMPONENT_FULL_VERSION)
COMPONENT_SUMMARY=      LibreOffice is a powerful office suite
COMPONENT_PROJECT_URL=  https://www.libreoffice.org/
ifdef BUILD_GITHUB
COMPONENT_SHA=		ef51c4a0cd35185debf25ad9d0db6a1c14bed5a0
COMPONENT_SRC=          core-$(COMPONENT_SHA)
COMPONENT_ARCHIVE=      $(COMPONENT_SHA).zip
COMPONENT_ARCHIVE_URL=  https://github.com/LibreOffice/core/archive/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:3f637039aa0366de0f25288806100007d72d3e9d1f557aac985e8eecb64173b2
else
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_FULL_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL= https://download.documentfoundation.org/libreoffice/src/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL= $(COMPONENT_ARCHIVE_URL).asc
endif
COMPONENT_FMRI=         desktop/office/libreoffice
COMPONENT_CLASSIFICATION= Applications/Office
COMPONENT_LICENSE=      MPL2.0
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

COMPONENT_ARCHIVE_1 = 0168229624cfac409e766913506961a8-ucpp-1.3.2.tar.gz
COMPONENT_ARCHIVE_HASH_1 = sha256:983941d31ee8d366085cadf28db75eb1f5cb03ba1e5853b98f12f7f51c63b776
COMPONENT_ARCHIVE_URL_1 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_1)

COMPONENT_ARCHIVE_2 = 1f5def51ca0026cd192958ef07228b52-rasqal-0.9.33.tar.gz
COMPONENT_ARCHIVE_HASH_2 = sha256:6924c9ac6570bd241a9669f83b467c728a322470bf34f4b2da4f69492ccfd97c
COMPONENT_ARCHIVE_URL_2 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_2)

COMPONENT_ARCHIVE_3 = 26b3e95ddf3d9c077c480ea45874b3b8-lp_solve_5.5.tar.gz
COMPONENT_ARCHIVE_HASH_3 = sha256:171816288f14215c69e730f7a4f1c325739873e21f946ff83884b350574e6695
COMPONENT_ARCHIVE_URL_3 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_3)

COMPONENT_ARCHIVE_4 = 48d647fbd8ef8889e5a7f422c1bfda94-clucene-core-2.3.3.4.tar.gz
COMPONENT_ARCHIVE_HASH_4 = sha256:ddfdc433dd8ad31b5c5819cc4404a8d2127472a3b720d3e744e8c51d79732eab
COMPONENT_ARCHIVE_URL_4 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_4)

COMPONENT_ARCHIVE_5 = 5ade6ae2a99bc1e9e57031ca88d36dad-hyphen-2.8.8.tar.gz
COMPONENT_ARCHIVE_HASH_5 = sha256:304636d4eccd81a14b6914d07b84c79ebb815288c76fe027b9ebff6ff24d5705
COMPONENT_ARCHIVE_URL_5 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_5)

COMPONENT_ARCHIVE_6 = f543e6e2d7275557a839a164941c0a86e5f2c3f2a0042bfc434c88c6dde9e140-opens___.ttf
COMPONENT_ARCHIVE_HASH_6 = sha256:f543e6e2d7275557a839a164941c0a86e5f2c3f2a0042bfc434c88c6dde9e140
COMPONENT_ARCHIVE_URL_6 = https://dev-www.libreoffice.org/extern/$(COMPONENT_ARCHIVE_6)

COMPONENT_ARCHIVE_7 = mariadb-connector-c-3.1.8-src.tar.gz
COMPONENT_ARCHIVE_HASH_7 = sha256:431434d3926f4bcce2e5c97240609983f60d7ff50df5a72083934759bb863f7b
COMPONENT_ARCHIVE_URL_7 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_7)

COMPONENT_ARCHIVE_8 = a39f6c07ddb20d7dd2ff1f95fa21e2cd-raptor2-2.0.15.tar.gz
COMPONENT_ARCHIVE_HASH_8 = sha256:ada7f0ba54787b33485d090d3d2680533520cd4426d2f7fb4782dd4a6a1480ed
COMPONENT_ARCHIVE_URL_8 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_8)

COMPONENT_ARCHIVE_9 = mythes-1.2.5.tar.xz
COMPONENT_ARCHIVE_HASH_9 = sha256:19279f70707bbe5ffa619f2dc319f888cec0c4a8d339dc0a21330517bd6f521d
COMPONENT_ARCHIVE_URL_9 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_9)

COMPONENT_ARCHIVE_10 = glm-1.0.1.zip
COMPONENT_ARCHIVE_HASH_10 = sha256:09c5716296787e1f7fcb87b1cbdbf26814ec1288ed6259ccd30d5d9795809fa5
COMPONENT_ARCHIVE_URL_10 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_10)

COMPONENT_ARCHIVE_11 = CoinMP-1.8.4.tgz
COMPONENT_ARCHIVE_HASH_11 = sha256:3459fb0ccbdd39342744684338984ac4cc153fb0434f4cae8cf74bd67490a38d
COMPONENT_ARCHIVE_URL_11 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_11)

COMPONENT_ARCHIVE_12 = e5be03eda13ef68aabab6e42aa67715e-redland-1.0.17.tar.gz
COMPONENT_ARCHIVE_HASH_12 = sha256:de1847f7b59021c16bdc72abb4d8e2d9187cd6124d69156f3326dd34ee043681
COMPONENT_ARCHIVE_URL_12 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_12)

COMPONENT_ARCHIVE_13 = language-subtag-registry-2023-05-11.tar.bz2
COMPONENT_ARCHIVE_HASH_13 = sha256:9042b64cd473bf36073513b474046f13778107b57c2ac47fb2633104120d69da
COMPONENT_ARCHIVE_URL_13 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_13)

COMPONENT_ARCHIVE_14 = libexttextcat-3.4.7.tar.xz
COMPONENT_ARCHIVE_HASH_14 = sha256:df0a59d413a5b202573d8d4f5159e33a8538da4f8e8e60979facc64d6290cebd
COMPONENT_ARCHIVE_URL_14 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_14)

COMPONENT_ARCHIVE_15 = libnumbertext-1.0.11.tar.xz
COMPONENT_ARCHIVE_HASH_15 = sha256:5dcb4db3b2340f81f601ce86d8d76b69e34d70f84f804192c901e4b7f84d5fb0
COMPONENT_ARCHIVE_URL_15 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_15)

COMPONENT_ARCHIVE_16 = liborcus-0.19.2.tar.xz
COMPONENT_ARCHIVE_HASH_16 = sha256:69ed26a00d4aaa7688e62a6e003cbc81928521a45e96605e53365aa499719e39
COMPONENT_ARCHIVE_URL_16 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_16)

COMPONENT_ARCHIVE_17 = QR-Code-generator-1.4.0.tar.gz
COMPONENT_ARCHIVE_HASH_17 = sha256:fcdf9fd69fde07ae4dca2351d84271a9de8093002f733b77c70f52f1630f6e4a
COMPONENT_ARCHIVE_URL_17 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_17)

COMPONENT_ARCHIVE_18 = xmlsec1-1.3.5.tar.gz
COMPONENT_ARCHIVE_HASH_18 = sha256:2ffd4ad1f860ec93e47a680310ab2bc94968bd07566e71976bd96133d9504917
COMPONENT_ARCHIVE_URL_18 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_18)

#libreoffice-translations
ifdef BUILD_GITHUB
COMPONENT_ARCHIVE_19_GIT_HASH = a26bda99ff1506defcf6bad3c2bcfec56f2893b1
COMPONENT_ARCHIVE_19 = $(COMPONENT_ARCHIVE_19_GIT_HASH).tar.gz
COMPONENT_ARCHIVE_HASH_19 = sha256:1e6bd8395cf8e38b7597992697066a2c1651c52aaf1fa71e2267910e96b700c8
COMPONENT_ARCHIVE_URL_19 = https://github.com/LibreOffice/translations/archive/$(COMPONENT_ARCHIVE_19)
else
COMPONENT_ARCHIVE_19 = libreoffice-translations-$(COMPONENT_FULL_VERSION).tar.xz
COMPONENT_ARCHIVE_URL_19 = https://download.documentfoundation.org/libreoffice/src/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_19)
COMPONENT_SIG_URL_19= $(COMPONENT_ARCHIVE_URL_19).asc
endif

# libreoffice-dictionaries
ifdef BUILD_GITHUB
COMPONENT_ARCHIVE_20_GIT_HASH = 0fbb94c57efcb6b30b88a6e181de54651e395e7c
COMPONENT_ARCHIVE_20 = $(COMPONENT_ARCHIVE_20_GIT_HASH).tar.gz
COMPONENT_ARCHIVE_HASH_20 = sha256:eaa98be2b20e3ef1c90e5438a9dac1129a0a7aa5e92c31b240b08e0fa162ef86
COMPONENT_ARCHIVE_URL_20 = https://github.com/LibreOffice/dictionaries/archive/$(COMPONENT_ARCHIVE_20)
else
COMPONENT_ARCHIVE_20 = libreoffice-dictionaries-$(COMPONENT_FULL_VERSION).tar.xz
COMPONENT_ARCHIVE_URL_20 = https://download.documentfoundation.org/libreoffice/src/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_20)
COMPONENT_SIG_URL_20= $(COMPONENT_ARCHIVE_URL_20).asc
endif

#COMPONENT_ARCHIVE_21 = boost_1_69_0.tar.bz2
#COMPONENT_ARCHIVE_HASH_21 = sha256:8f32d4617390d1c2d16f26a27ab60d97807b35440d45891fa340fc2648b04406
#COMPONENT_ARCHIVE_URL_21 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_21)

COMPONENT_ARCHIVE_22 = neon-0.31.2.tar.gz
COMPONENT_ARCHIVE_HASH_22 = sha256:cf1ee3ac27a215814a9c80803fcee4f0ede8466ebead40267a9bd115e16a8678
COMPONENT_ARCHIVE_URL_22 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_22)

COMPONENT_ARCHIVE_23 = zxing-cpp-2.2.1.tar.gz
COMPONENT_ARCHIVE_HASH_23 = sha256:02078ae15f19f9d423a441f205b1d1bee32349ddda7467e2c84e8f08876f8635
COMPONENT_ARCHIVE_URL_23 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_23)

COMPONENT_ARCHIVE_24 = box2d-2.4.1.tar.gz
COMPONENT_ARCHIVE_HASH_24 = sha256:d6b4650ff897ee1ead27cf77a5933ea197cbeef6705638dd181adc2e816b23c2
COMPONENT_ARCHIVE_URL_24 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_24)


COMPONENT_ARCHIVE_25 = dtoa-20180411.tgz
COMPONENT_ARCHIVE_HASH_25 = sha256:0082d0684f7db6f62361b76c4b7faba19e0c7ce5cb8e36c4b65fea8281e711b4
COMPONENT_ARCHIVE_URL_25 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_25)

COMPONENT_ARCHIVE_26 = skia-m116-2ddcf183eb260f63698aa74d1bb380f247ad7ccd.tar.xz
COMPONENT_ARCHIVE_HASH_26 = sha256:2223ebce534458a37826e8fe4f24635b0712cde7ed1bd3208f089f6fdd796e01
COMPONENT_ARCHIVE_URL_26 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_26)

COMPONENT_ARCHIVE_27 = libcmis-0.6.2.tar.xz
COMPONENT_ARCHIVE_HASH_27 = sha256:1b5c2d7258ff93eb5f9958ff0e4dfd7332dc75a071bb717dde2217a26602a644
COMPONENT_ARCHIVE_URL_27 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_27)

COMPONENT_ARCHIVE_28 = gpgme-1.23.2.tar.bz2
COMPONENT_ARCHIVE_HASH_28 = sha256:9499e8b1f33cccb6815527a1bc16049d35a6198a6c5fae0185f2bd561bce5224
COMPONENT_ARCHIVE_URL_28 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_28)

COMPONENT_ARCHIVE_29 = libassuan-3.0.1.tar.bz2
COMPONENT_ARCHIVE_HASH_29 = sha256:c8f0f42e6103dea4b1a6a483cb556654e97302c7465308f58363778f95f194b1
COMPONENT_ARCHIVE_URL_29 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_29)

COMPONENT_ARCHIVE_30 = libgpg-error-1.50.tar.bz2
COMPONENT_ARCHIVE_HASH_30 = sha256:69405349e0a633e444a28c5b35ce8f14484684518a508dc48a089992fe93e20a
COMPONENT_ARCHIVE_URL_30 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_30)

COMPONENT_ARCHIVE_31 = frozen-1.1.1.tar.gz
COMPONENT_ARCHIVE_HASH_31 = sha256:f7c7075750e8fceeac081e9ef01944f221b36d9725beac8681cbd2838d26be45
COMPONENT_ARCHIVE_URL_31 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_31)

COMPONENT_ARCHIVE_32 = dragonbox-1.1.3.tar.gz
COMPONENT_ARCHIVE_HASH_32 = sha256:09d63b05e9c594ec423778ab59b7a5aa1d76fdd71d25c7048b0258c4ec9c3384
COMPONENT_ARCHIVE_URL_32 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_32)

COMPONENT_ARCHIVE_33 = mdds-2.1.1.tar.xz
COMPONENT_ARCHIVE_HASH_33 = sha256:1483d90cefb8aa4563c4d0a85cb7b243aa95217d235d422e9ca6722fd5b97e56
COMPONENT_ARCHIVE_URL_33 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_33)

COMPONENT_ARCHIVE_34 = zxcvbn-c-2.5.tar.gz
COMPONENT_ARCHIVE_HASH_34 = sha256:77d6c6ecb35952a8d8ce7f736b7a2bf466275c48210e309b73782d6b7e84dffd
COMPONENT_ARCHIVE_URL_34 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_34)

COMPONENT_ARCHIVE_35 = bsh-2.1.1-src.zip
COMPONENT_ARCHIVE_HASH_35 = sha256:2248387ceaa319840434a3547a8b2fec12f95a8418ee039ce5ff5726053a139c
COMPONENT_ARCHIVE_URL_35 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_35)

COMPONENT_ARCHIVE_36 = 17410483b5b5f267aa18b7e00b65e6e0-hsqldb_1_8_0.zip
COMPONENT_ARCHIVE_HASH_36 = sha256:d30b13f4ba2e3b6a2d4f020c0dee0a9fb9fc6fbcc2d561f36b78da4bf3802370
COMPONENT_ARCHIVE_URL_36 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_36)

COMPONENT_ARCHIVE_37 = Java-WebSocket-1.5.6.tar.gz
COMPONENT_ARCHIVE_HASH_37 = sha256:167e86561cd7b5ed21b67d7543536134edcb14b373892739b28c417566a3832f
COMPONENT_ARCHIVE_URL_37 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_37)

COMPONENT_ARCHIVE_38 = ba2930200c9f019c2d93a8c88c651a0f-flow-engine-0.9.4.zip
COMPONENT_ARCHIVE_HASH_38 = sha256:233f66e8d25c5dd971716d4200203a612a407649686ef3b52075d04b4c9df0dd
COMPONENT_ARCHIVE_URL_38 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_38)

COMPONENT_ARCHIVE_39 = d8bd5eed178db6e2b18eeed243f85aa8-flute-1.1.6.zip
COMPONENT_ARCHIVE_HASH_39 = sha256:1b5b24f7bc543c0362b667692f78db8bab4ed6dafc6172f104d0bd3757d8a133
COMPONENT_ARCHIVE_URL_39 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_39)

COMPONENT_ARCHIVE_40 = eeb2c7ddf0d302fba4bfc6e97eac9624-libbase-1.1.6.zip
COMPONENT_ARCHIVE_HASH_40 = sha256:75c80359c9ce343c20aab8a36a45cb3b9ee7c61cf92c13ae45399d854423a9ba
COMPONENT_ARCHIVE_URL_40 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_40)

COMPONENT_ARCHIVE_41 = 3bdf40c0d199af31923e900d082ca2dd-libfonts-1.1.6.zip
COMPONENT_ARCHIVE_HASH_41 = sha256:e0531091787c0f16c83965fdcbc49162c059d7f0c64669e7f119699321549743
COMPONENT_ARCHIVE_URL_41 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_41)

COMPONENT_ARCHIVE_42 = 3404ab6b1792ae5f16bbd603bd1e1d03-libformula-1.1.7.zip
COMPONENT_ARCHIVE_HASH_42 = sha256:5826d1551bf599b85742545f6e01a0079b93c1b2c8434bf409eddb3a29e4726b
COMPONENT_ARCHIVE_URL_42 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_42)

COMPONENT_ARCHIVE_43 = db60e4fde8dd6d6807523deb71ee34dc-liblayout-0.2.10.zip
COMPONENT_ARCHIVE_HASH_43 = sha256:e1fb87f3f7b980d33414473279615c4644027e013012d156efa538bc2b031772
COMPONENT_ARCHIVE_URL_43 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_43)

COMPONENT_ARCHIVE_44 = 97b2d4dba862397f446b217e2b623e71-libloader-1.1.6.zip
COMPONENT_ARCHIVE_HASH_44 = sha256:3d853b19b1d94a6efa69e7af90f7f2b09ecf302913bee3da796c15ecfebcfac8
COMPONENT_ARCHIVE_URL_44 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_44)

COMPONENT_ARCHIVE_45 = 8ce2fcd72becf06c41f7201d15373ed9-librepository-1.1.6.zip
COMPONENT_ARCHIVE_HASH_45 = sha256:abe2c57ac12ba45d83563b02e240fa95d973376de2f720aab8fe11f2e621c095
COMPONENT_ARCHIVE_URL_45 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_45)

COMPONENT_ARCHIVE_46 = f94d9870737518e3b597f9265f4e9803-libserializer-1.1.6.zip
COMPONENT_ARCHIVE_HASH_46 = sha256:05640a1f6805b2b2d7e2cb9c50db9a5cb084e3c52ab1a71ce015239b4a1d4343
COMPONENT_ARCHIVE_URL_46 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_46)

COMPONENT_ARCHIVE_47 = ace6ab49184e329db254e454a010f56d-libxml-1.1.7.zip
COMPONENT_ARCHIVE_HASH_47 = sha256:7d2797fe9f79a77009721e3f14fa4a1dec17a6d706bdc93f85f1f01d124fab66
COMPONENT_ARCHIVE_URL_47 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_47)

COMPONENT_ARCHIVE_48 = 39bb3fcea1514f1369fcfc87542390fd-sacjava-1.3.zip
COMPONENT_ARCHIVE_HASH_48 = sha256:085f2112c51fa8c1783fac12fbd452650596415121348393bb51f0f7e85a9045
COMPONENT_ARCHIVE_URL_48 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_48)

COMPONENT_ARCHIVE_49 = rhino-1.7.14.zip
COMPONENT_ARCHIVE_HASH_49 = sha256:bf4d2d0c5ff8889fd494486db09291cb7965f0bf2f93ef005d3b08070a5a4f5c
COMPONENT_ARCHIVE_URL_49 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_49)

COMPONENT_ARCHIVE_50 = 35c94d2df8893241173de1d16b6034c0-swingExSrc.zip
COMPONENT_ARCHIVE_HASH_50 = sha256:64585ac36a81291a58269ec5347e7e3e2e8596dbacb9221015c208191333c6e1
COMPONENT_ARCHIVE_URL_50 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_50)

COMPONENT_ARCHIVE_51 = a7983f859eafb2677d7ff386a023bc40-xsltml_2.1.2.zip
COMPONENT_ARCHIVE_HASH_51 = sha256:75823776fb51a9c526af904f1503a7afaaab900fba83eda64f8a41073724c870
COMPONENT_ARCHIVE_URL_51 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_51)

COMPONENT_ARCHIVE_52 = odfvalidator-0.9.0-RC2-SNAPSHOT-jar-with-dependencies-2726ab578664434a545f8379a01a9faffac0ae73.jar
COMPONENT_ARCHIVE_HASH_52 = sha256:d55495ab3a86544650587de2a72180ddf8bfc6376d14ddfa923992dbc86a06e0
COMPONENT_ARCHIVE_URL_52 = https://dev-www.libreoffice.org/extern/$(COMPONENT_ARCHIVE_52)

# libreoffice-help
ifdef BUILD_GITHUB
COMPONENT_ARCHIVE_53_GIT_HASH = 3542a6dade252f7d6b9e8332437e88a52e782db6
COMPONENT_ARCHIVE_53 = $(COMPONENT_ARCHIVE_53_GIT_HASH).tar.gz
COMPONENT_ARCHIVE_HASH_53 = sha256:745b89d0aeca93aded9f18e7060680c2cef1311453e5e43ec05ea3d40be8902b
COMPONENT_ARCHIVE_URL_53 = https://github.com/LibreOffice/help/archive/$(COMPONENT_ARCHIVE_53)
else
COMPONENT_ARCHIVE_53 = libreoffice-help-$(COMPONENT_FULL_VERSION).tar.xz
COMPONENT_ARCHIVE_URL_53 = https://download.documentfoundation.org/libreoffice/src/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_53)
COMPONENT_SIG_URL_53= $(COMPONENT_ARCHIVE_URL_53).asc
endif

COMPONENT_ARCHIVE_54 = 8249374c274932a21846fa7629c2aa9b-officeotron-0.7.4-master.jar
COMPONENT_ARCHIVE_HASH_54 = sha256:f2443f27561af52324eee03a1892d9f569adc8db9e7bca55614898bc2a13a770
COMPONENT_ARCHIVE_URL_54 = https://dev-www.libreoffice.org/extern/$(COMPONENT_ARCHIVE_54)

COMPONENT_ARCHIVE_55 = phc-winner-argon2-20190702.tar.gz
COMPONENT_ARCHIVE_HASH_55 = sha256:4d1dac6ef66528b7a2bc910ff45c1015a1b83cb928515ca18a78dc76e688627b
COMPONENT_ARCHIVE_URL_55 = https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE_55)

# ignore archive 21 (boost)
NUM_EXTRA_ARCHIVES = $(shell seq 1 20) $(shell 22 54)

# github source archive files are a different compression than what is found on
# the documentfoundation site
ifdef BUILD_GITHUB
ADDITIONAL_PATCHES += patches/dictionaries-translations-help-already-downloaded-as-tar-gz.patch.github
endif

include $(WS_MAKE_RULES)/common.mk

PATH= $(GCC_BINDIR):$(PATH.gnu)

#Ensure asm is built in 64-bit.
AFLAGS= -m64

#CFLAGS / CXXFLAGS not passed to all external libraries! Add -m64 to ensure 64-bit is built.
CC+= -m64
CXX+= -m64

COMPONENT_BUILD_ENV=   CONFIG_SHELL="$(CONFIG_SHELL)"
COMPONENT_BUILD_ENV+=  SHELL="$(CONFIG_SHELL)"
COMPONENT_BUILD_ENV+=  AFLAGS="$(AFLAGS)"
COMPONENT_BUILD_ENV+=  LD_LIBRARY_PATH="$(GCC_LIBDIR)"

COMPONENT_TEST_ENV= LD_LIBRARY_PATH='$(GCC_LIBDIR):$(BUILD_DIR_64)/instdir/program/' GMAKE_OPTIONS=-rsk

CONFIGURE_ENV = $(COMPONENT_BUILD_ENV)
CONFIGURE_ENV += PYTHON=$(PYTHON.3.9)
CONFIGURE_ENV += GPG=/usr/bin/gpg2
CONFIGURE_ENV += GPGCONF=/usr/bin/gpgconf

CONFIGURE_ENV += MARIADBCONFIG=$(MYSQL_CONFIG)
MARIADB_LIBDIR= $(MYSQL_LIBDIR)

CONFIGURE_LIBDIR= $(CONFIGURE_LIBDIR.64)

CONFIGURE_SCRIPT= $(SOURCE_DIR)/autogen.sh

COMPONENT_PREP_ACTION = ( mkdir -p $(@D)/external/tarballs && \
	for i in $(ARCHIVES) ; do \
		rm -f $(@D)/external/tarballs/$$i && \
		ln -s $(USERLAND_ARCHIVES)/$$i $(@D)/external/tarballs/$$i ; \
	done

# Add missing files that exist in the documentfoundation source archives that
# are not included in the github source--this allows the build steps to be the
# same using source from either location
# Note: need this adds the closing parenthesis for COMPONENT_PREP_ACTION
ifdef BUILD_GITHUB
COMPONENT_PREP_ACTION += && \
        ln -s $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE_20) $(@D)/external/tarballs/libreoffice-dictionaries-$(COMPONENT_VERSION).$(COMPONENT_RC_VERSION).tar.gz && \
        ln -s $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE_19) $(@D)/external/tarballs/libreoffice-translations-$(COMPONENT_VERSION).$(COMPONENT_RC_VERSION).tar.gz && \
        ln -s $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE_53) $(@D)/external/tarballs/libreoffice-help-$(COMPONENT_VERSION).$(COMPONENT_RC_VERSION).tar.gz && \
	touch $(SOURCE_DIR)/dictionaries/Repository.mk && \
	touch $(SOURCE_DIR)/translations/Repository.mk && \
	touch $(SOURCE_DIR)/helpcontent2/Repository.mk && \
	touch $(SOURCE_DIR)/dictionaries/sources.ver && \
	touch $(SOURCE_DIR)/translations/sources.ver && \
	touch $(SOURCE_DIR)/helpcontent2/sources.ver && \
	ln -s $(SOURCE_DIR)/helpcontent2 $(SOURCE_DIR)/help && \
	echo "lo_sources_ver=$(COMPONENT_VERSION).$(COMPONENT_RC_VERSION)" > $(SOURCE_DIR)/sources.ver )
else
COMPONENT_PREP_ACTION += )
endif

LDFLAGS += $(JPEG_LDFLAGS) -lX11-xcb -lX11 

CFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS) -lssp_nonshared
#CONFIGURE_OPTIONS += --enable-debug
#CONFIGURE_OPTIONS += --enable-optimized=no
CXXFLAGS = $(CFLAGS)

# 64-bit
CONFIGURE_OPTIONS += --build=amd64-pc-solaris2.11

ifdef DEBUG
CONFIGURE_OPTIONS += --enable-debug
else
CONFIGURE_OPTIONS += --enable-release-build
endif

CONFIGURE_OPTIONS += --with-myspell-dicts
CONFIGURE_OPTIONS += --with-help=common
CONFIGURE_OPTIONS += --enable-gstreamer-1-0
CONFIGURE_OPTIONS += --enable-gtk3
CONFIGURE_OPTIONS += --enable-gtk4
CONFIGURE_OPTIONS += --enable-qt5
CONFIGURE_OPTIONS += --enable-qt6
CONFIGURE_OPTIONS += --disable-odk
CONFIGURE_OPTIONS += --with-system-cairo
CONFIGURE_OPTIONS += --with-system-expat
CONFIGURE_OPTIONS += --with-system-libxml
CONFIGURE_OPTIONS += --with-system-icu
CONFIGURE_OPTIONS += --with-system-poppler
CONFIGURE_OPTIONS += --with-system-curl
CONFIGURE_OPTIONS += --with-system-boost
CONFIGURE_OPTIONS += --with-system-nss
# library/libneon < 0.31.2
# CONFIGURE_OPTIONS += --with-system-neon
CONFIGURE_OPTIONS += --with-system-openssl
CONFIGURE_OPTIONS += --with-system-libpng
CONFIGURE_OPTIONS += --with-system-jpeg
CONFIGURE_OPTIONS += --with-system-harfbuzz

CONFIGURE_OPTIONS += --with-system-graphite
CONFIGURE_OPTIONS += --with-system-cppunit

CONFIGURE_OPTIONS += --with-system-lcms2
CONFIGURE_OPTIONS += --with-system-dicts
CONFIGURE_OPTIONS += --with-system-epoxy
CONFIGURE_OPTIONS += --with-system-hunspell
# We have mdds-2.0.3 now which is not compatible with this libreoffice version:
#CONFIGURE_OPTIONS += --with-system-mdds
CONFIGURE_OPTIONS += --with-system-libabw
CONFIGURE_OPTIONS += --with-system-libcdr
# libreoffice uses functionality not packaged in latest libcmis (0.5.2)
#CONFIGURE_OPTIONS += --with-system-libcmis
CONFIGURE_OPTIONS += --with-system-libetonyek
CONFIGURE_OPTIONS += --with-system-libebook
CONFIGURE_OPTIONS += --with-system-libepubgen
CONFIGURE_OPTIONS += --with-system-libfreehand
CONFIGURE_OPTIONS += --with-system-liblangtag
CONFIGURE_OPTIONS += --with-system-libmspub
CONFIGURE_OPTIONS += --with-system-libmwaw
CONFIGURE_OPTIONS += --with-system-libodfgen
CONFIGURE_OPTIONS += --with-system-libpagemaker
CONFIGURE_OPTIONS += --with-system-libqxp
CONFIGURE_OPTIONS += --with-system-librevenge
CONFIGURE_OPTIONS += --with-system-libstaroffice
CONFIGURE_OPTIONS += --with-system-libtiff
CONFIGURE_OPTIONS += --with-system-libvisio
CONFIGURE_OPTIONS += --with-system-libwebp
CONFIGURE_OPTIONS += --with-system-libwpd
CONFIGURE_OPTIONS += --with-system-libwpg
CONFIGURE_OPTIONS += --with-system-libwps
CONFIGURE_OPTIONS += --with-system-libzmf

# Use packaged mariadb client with solaris patches
CONFIGURE_OPTIONS += --with-system-mariadb
CONFIGURE_OPTIONS += --enable-gio
CONFIGURE_OPTIONS += --with-lang=ALL
CONFIGURE_OPTIONS += --disable-firebird-sdbc
CONFIGURE_OPTIONS += --disable-postgresql-sdbc
CONFIGURE_OPTIONS += --disable-pdfium
CONFIGURE_OPTIONS += --with-help
CONFIGURE_OPTIONS += --without-fonts
CONFIGURE_OPTIONS += --enable-cups
CONFIGURE_OPTIONS += --enable-dbus
CONFIGURE_OPTIONS += --with-epm=internal
CONFIGURE_OPTIONS += --with-vendor="OpenIndiana"
CONFIGURE_OPTIONS += --with-tls="openssl"
CONFIGURE_OPTIONS += --with-system-openldap
CONFIGURE_OPTIONS += --enable-python=system
CONFIGURE_OPTIONS += --disable-cve-tests
CONFIGURE_OPTIONS += --with-java
CONFIGURE_OPTIONS += --with-jdk-home="/usr/jdk/openjdk17/"
CONFIGURE_OPTIONS += --without-system-beanshell
CONFIGURE_OPTIONS += --without-system-hsqldb
CONFIGURE_OPTIONS += --without-system-jfreereport
CONFIGURE_OPTIONS += --enable-ext-wiki-publisher
CONFIGURE_OPTIONS += --enable-ext-nlpsolver
CONFIGURE_OPTIONS += --with-export-validation
CONFIGURE_OPTIONS += --enable-scripting-beanshell
CONFIGURE_OPTIONS += --enable-scripting-javascript
CONFIGURE_OPTIONS += SED=/usr/bin/gsed

COMPONENT_BUILD_ENV += GMAKE_OPTIONS='VERBOSE=1 gb_SUPPRESS_TESTS=x'

COMPONENT_INSTALL_TARGETS = distro-pack-install

LIBREOFFICE_PROGRAM_DIR = /usr/lib/amd64/libreoffice/program
LIBREOFFICE_SHARE_DIR = /usr/lib/amd64/libreoffice/share

NSS_LIB_DIR=/usr/lib/mps/amd64

JAVA17_LIB_DIR=/usr/jdk/openjdk17/lib

COMPONENT_POST_INSTALL_ACTION  = \
    for file in $(PROTO_DIR)$(LIBREOFFICE_PROGRAM_DIR)/*.so*; do \
        /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(GCC_LIBDIR):$(LIBREOFFICE_PROGRAM_DIR):$(NSS_LIB_DIR):$(JPEG_LIBDIR):$(MARIADB_LIBDIR):$(QT5_LIBDIR):$(QT6_LIBDIR):$(JAVA17_LIB_DIR)"' $$file ; \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH "$(GCC_LIBDIR):$(LIBREOFFICE_PROGRAM_DIR):$(NSS_LIB_DIR):$(JPEG_LIBDIR):$(MARIADB_LIBDIR):$(QT5_LIBDIR):$(QT6_LIBDIR):$(JAVA17_LIB_DIR)"' $$file ; \
    done ; 

# Replace "#!/usr/bin/env ..." shebang line with properly versioned one
COMPONENT_POST_INSTALL_ACTION += \
    $(GSED) -i 's/env\ python3/python$(PYTHON_VERSION)/' \
        $(PROTO_DIR)$(LIBREOFFICE_SHARE_DIR)/extensions/dict-pt-BR/test_compile_rules.py ;

# dynamically generate license file to include all of the third party component licenses
COMPONENT_POST_INSTALL_ACTION += \
    LC_ALL=en_US.UTF-8 lynx --display_charset=utf-8 --dump -nolist $(PROTOUSRLIBDIR64)/$(COMPONENT_NAME)/LICENSE.html > $(COMPONENT_NAME).license ;


# the license file is dynamically built, thus we need to remove it:
clean::
	$(RM) $(COMPONENT_LICENSE_FILE)

# Filter out test result lines with truncated $(BUILD_DIR) paths
COMPONENT_TEST_TRANSFORMS +=    "-e 's|$(COMPONENT_DIR)|\$$(COMPONENT_DIR)|g'"
COMPONENT_TEST_TRANSFORMS +=    '-e "s/ [0-9]*ms//g"'

# debug specific test
testtrace:
	@[ -n "$(SPECTEST)" ] || (echo "No SPECTEST specified."; exit 1;)
	(cd $(BUILD_DIR); \
		$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) CPPUNITTRACE="gdb --args" \
		$(COMPONENT_TEST_CMD) \
		$(COMPONENT_TEST_ARGS) $(CPPUNIT_TEST_NAME) $(SPECTEST))

# Build dependencies
REQUIRED_PACKAGES += developer/assembler/nasm
REQUIRED_PACKAGES += developer/build/ant
REQUIRED_PACKAGES += developer/cppunit
REQUIRED_PACKAGES += developer/gperf
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += library/c++/mdds
REQUIRED_PACKAGES += $(MYSQL_CLIENT_PKG)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += gnome/config/dconf
REQUIRED_PACKAGES += image/library/libjpeg-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/c++/graphite2
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/c++/libabw
REQUIRED_PACKAGES += library/c++/libcdr
REQUIRED_PACKAGES += library/c++/libe-book
REQUIRED_PACKAGES += library/c++/libepubgen
REQUIRED_PACKAGES += library/c++/libetonyek
REQUIRED_PACKAGES += library/c++/libfreehand
REQUIRED_PACKAGES += library/c++/libmspub
REQUIRED_PACKAGES += library/c++/libmwaw
REQUIRED_PACKAGES += library/c++/libodfgen
REQUIRED_PACKAGES += library/c++/libpagemaker
REQUIRED_PACKAGES += library/c++/libqxp
REQUIRED_PACKAGES += library/c++/librevenge
REQUIRED_PACKAGES += library/c++/libstaroffice
REQUIRED_PACKAGES += library/c++/libvisio
REQUIRED_PACKAGES += library/c++/libwpd
REQUIRED_PACKAGES += library/c++/libwpg
REQUIRED_PACKAGES += library/c++/libwps
REQUIRED_PACKAGES += library/c++/libzmf
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/graphene
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/liblangtag
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/qt6
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/java/openjdk17
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/boost
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/mozilla-nss
REQUIRED_PACKAGES += text/hunspell
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libepoxy
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
