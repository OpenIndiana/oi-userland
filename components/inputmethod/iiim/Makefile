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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= iiim
COMPONENT_VERSION= 0.5.11
COMPONENT_REVISION= 3
COMPONENT_SUMMARY= Internet/Intranet Input Method Framework Package
COMPONENT_SRC= im-sdk
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:adcf1d8fff8b62372eab7318354ebe010c850fa57efc16e3f383dc95c8ca723d
COMPONENT_ARCHIVE_URL= \
  http://dlc.openindiana.org/oi-build/source-archives/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.oracle.com/technetwork/opensource/systems-solaris-1562786.html

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk

PATH = /usr/gnu/bin:/usr/bin

CFLAGS.32 =	-std=gnu89 -fPIC -DPIC -DHAS_IIIM_PROPERTIES=1 -D__EXTENSIONS__ -DHAVE_POSIX_GETPWUID_R
CFLAGS.64 =	-std=gnu89 -m64 -fPIC -DPIC -DHAS_IIIM_PROPERTIES=1 -D__EXTENSIONS__ -DHAVE_POSIX_GETPWUID_R
CXXFLAGS.32 =	-std=c++98 -DHAS_IIIM_PROPERTIES=1 -DHAVE_POSIX_GETPWUID_R
CXXFLAGS.64 =	-std=c++98 $(CFLAGS64)

MY_LDFLAGS =	-Wl,-zignore -Wl,-zcombreloc -Wl,-Bdirect
MY_LDFLAGS1 =	$(MY_LDFLAGS) -R/usr/lib/iiim -L/usr/lib/iiim
MY_LDFLAGS2 =	$(MY_LDFLAGS)

# Prep target

$(SOURCE_DIR)/.prep:
	cd $(@D)/lib/CSConv; autoreconf -f -i
	cd $(@D)/lib/EIMIL; autoreconf -f -i
	cd $(@D)/lib/iiimp; autoreconf -f -i
	cd $(@D)/lib/kbltrans; autoreconf -f -i
	cd $(@D)/lib/iiimcf; autoreconf -f -i
	cd $(@D)/iiimxcf/xiiimp.so; autoreconf -f -i
	cd $(@D)/iiimgcf && glib-gettextize --force --copy && intltoolize --copy --force --automake && libtoolize --force --copy && autoreconf -f -i
	cd $(@D)/iiimsf; autoreconf -f -i
	cd $(@D)/leif; autoreconf -f -i
	cd $(@D)/iiimxcf/htt_xbe; autoreconf -f -i
	cd $(@D)/doc; autoreconf -f -i
	$(TOUCH) $@

# Build targets

BUILD_CSConv_32 = $(BUILD_DIR_32)/.built_CSConv
BUILD_CSConv_64 = $(BUILD_DIR_64)/.built_CSConv

BUILD_EIMIL_32 = $(BUILD_DIR_32)/.built_EIMIL
BUILD_EIMIL_64 = $(BUILD_DIR_64)/.built_EIMIL

BUILD_iiimp_32 = $(BUILD_DIR_32)/.built_iiimp
BUILD_iiimp_64 = $(BUILD_DIR_64)/.built_iiimp

BUILD_kbltrans_32 = $(BUILD_DIR_32)/.built_kbltrans
BUILD_kbltrans_64 = $(BUILD_DIR_64)/.built_kbltrans

BUILD_iiimcf_32 = $(BUILD_DIR_32)/.built_iiimcf
BUILD_iiimcf_64 = $(BUILD_DIR_64)/.built_iiimcf

BUILD_xiiimp_so_32 = $(BUILD_DIR_32)/.built_xiiimp_so
BUILD_xiiimp_so_64 = $(BUILD_DIR_64)/.built_xiiimp_so

BUILD_iiimgcf_32 = $(BUILD_DIR_32)/.built_iiimgcf
BUILD_iiimgcf_64 = $(BUILD_DIR_64)/.built_iiimgcf

BUILD_iiimsf_32 = $(BUILD_DIR_32)/.built_iiimsf

BUILD_cle_32 = $(BUILD_DIR_32)/.built_cle
BUILD_cle_auxiliary_object_64 = $(BUILD_DIR_64)/.built_cle_auxiliary_object

BUILD_twle_32 = $(BUILD_DIR_32)/.built_twle
BUILD_twle_auxiliary_object_64 = $(BUILD_DIR_64)/.built_twle_auxiliary_object

BUILD_hkle_32 = $(BUILD_DIR_32)/.built_hkle
BUILD_hkle_auxiliary_object_64 = $(BUILD_DIR_64)/.built_hkle_auxiliary_object

BUILD_htt_xbe_32 = $(BUILD_DIR_32)/.built_htt_xbe

BUILD_leif_32 = $(BUILD_DIR_32)/.built_leif

BUILD_doc_32 = $(BUILD_DIR_32)/.built_doc

BUILD_gnome_im_switcher_32 = $(BUILD_DIR_32)/.built_gnome_im_switcher

BUILD_iiim_properties_32 = $(BUILD_DIR_32)/.built_iiim_properties

BUILD_iiim_panel_32 = $(BUILD_DIR_32)/.built_iiim_panel

BUILD_vkb_native_32 = $(BUILD_DIR_32)/.built_vkb_native

BUILD_iiim_keyboard_32 = $(BUILD_DIR_32)/.built_iiim_keyboard


$(BUILD_32):  $(BUILD_64)

$(BUILD_32): $(BUILD_CSConv_32) $(BUILD_EIMIL_32) $(BUILD_iiimp_32) $(BUILD_kbltrans_32) $(BUILD_iiimcf_32) \
	$(BUILD_xiiimp_so_32) $(BUILD_iiimgcf_32) $(BUILD_iiimsf_32) $(BUILD_leif_32) $(BUILD_cle_32) $(BUILD_twle_32) $(BUILD_hkle_32) $(BUILD_htt_xbe_32) \
	$(BUILD_doc_32) $(BUILD_gnome_im_switcher_32) $(BUILD_iiim_properties_32) $(BUILD_iiim_panel_32) \
	$(BUILD_vkb_native_32) $(BUILD_iiim_keyboard_32)

$(BUILD_64): $(BUILD_CSConv_64) $(BUILD_EIMIL_64) $(BUILD_iiimp_64) $(BUILD_kbltrans_64) $(BUILD_iiimcf_64) \
	$(BUILD_xiiimp_so_64) $(BUILD_iiimgcf_64) $(BUILD_cle_auxiliary_object_64) $(BUILD_twle_auxiliary_object_64) \
	$(BUILD_hkle_auxiliary_object_64)

$(BUILD_CSConv_64): $(SOURCE_DIR)/.prep
	$(RM) -r $(BUILD_DIR_64)/lib/CSConv
	$(MKDIR) $(BUILD_DIR_64)/lib/CSConv
	cd $(BUILD_DIR_64)/lib/CSConv; /usr/bin/env CC=$(CC) CXX=$(CXX)  LDFLAGS="$(MY_LDFLAGS2)" CFLAGS="$(CFLAGS.64)" CXXFLAGS="$(CXXFLAGS.64)" $(SOURCE_DIR)/lib/CSConv/configure --prefix=/usr    \
            --libdir=/usr/lib/$(MACH64)           \
            --libexecdir=/usr/lib/$(MACH64)   \
            --sysconfdir=/etc/$(MACH64)
	cd $(BUILD_DIR_64)/lib/CSConv; $(GMAKE)
	cd $(BUILD_DIR_64)/lib/CSConv; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	[ -d $(PROTO_DIR)/usr/lib/iiim/csconv/$(MACH64) ] || $(MKDIR) $(PROTO_DIR)/usr/lib/iiim/csconv/$(MACH64)
	mv $(PROTO_DIR)/usr/lib/iiim/csconv/csconv.so $(PROTO_DIR)/usr/lib/iiim/csconv/$(MACH64)/
	$(TOUCH) $@

$(BUILD_CSConv_32): $(SOURCE_DIR)/.prep
	$(RM) -r $(BUILD_DIR_32)/lib/CSConv
	$(MKDIR) $(BUILD_DIR_32)/lib/CSConv
	cd $(BUILD_DIR_32)/lib/CSConv; /usr/bin/env CC=$(CC) CXX=$(CXX) LDFLAGS="$(MY_LDFLAGS2)" CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" $(SOURCE_DIR)/lib/CSConv/configure --prefix=/usr    \
            --libdir=/usr/lib/$(MACH64)           \
            --libexecdir=/usr/lib/$(MACH64)   \
            --sysconfdir=/etc/$(MACH64)
	cd $(BUILD_DIR_32)/lib/CSConv; $(GMAKE)
	cd $(BUILD_DIR_32)/lib/CSConv; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_EIMIL_64): $(SOURCE_DIR)/.prep
	$(RM) -r $(BUILD_DIR_64)/lib/EIMIL
	$(MKDIR) $(BUILD_DIR_64)/lib/EIMIL
	cd $(BUILD_DIR_64)/lib/EIMIL; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.64)" CXXFLAGS="$(CXXFLAGS.64)" $(SOURCE_DIR)/lib/EIMIL/configure  --prefix=/usr
	cd $(BUILD_DIR_64)/lib/EIMIL; $(GMAKE)
	$(TOUCH) $@

$(BUILD_EIMIL_32): $(SOURCE_DIR)/.prep
	$(RM) -r $(BUILD_DIR_32)/lib/EIMIL
	$(MKDIR) $(BUILD_DIR_32)/lib/EIMIL
	cd $(BUILD_DIR_32)/lib/EIMIL; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" $(SOURCE_DIR)/lib/EIMIL/configure  --prefix=/usr
	cd $(BUILD_DIR_32)/lib/EIMIL; $(GMAKE)
	cd $(BUILD_DIR_32)/lib/EIMIL; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_iiimp_64): $(BUILD_EIMIL_64)
	$(RM) -r $(BUILD_DIR_64)/lib/iiimp
	$(MKDIR) $(BUILD_DIR_64)/lib/iiimp
	cd $(BUILD_DIR_64)/lib/iiimp; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.64)" CXXFLAGS="$(CXXFLAGS.64)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/lib/iiimp/configure --prefix=/usr --localstatedir=/var  \
            --libdir=/usr/lib/$(MACH64)           \
            --libexecdir=/usr/lib/$(MACH64)   \
            --sysconfdir=/etc/$(MACH64)
	cd $(BUILD_DIR_64)/lib/iiimp; $(GMAKE)
	cd $(BUILD_DIR_64)/lib/iiimp; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_iiimp_32): $(BUILD_EIMIL_32)
	$(RM) -r $(BUILD_DIR_32)/lib/iiimp
	$(MKDIR) $(BUILD_DIR_32)/lib/iiimp
	cd $(BUILD_DIR_32)/lib/iiimp; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/lib/iiimp/configure --prefix=/usr --localstatedir=/var
	cd $(BUILD_DIR_32)/lib/iiimp; $(GMAKE)
	cd $(BUILD_DIR_32)/lib/iiimp; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_kbltrans_64): $(BUILD_iiimp_64)
	$(RM) -r $(BUILD_DIR_64)/lib/kbltrans
	$(MKDIR) $(BUILD_DIR_64)/lib/kbltrans
	cd $(BUILD_DIR_64)/lib/kbltrans; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.64)" CXXFLAGS="$(CXXFLAGS.64)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/lib/kbltrans/autogen.sh --prefix=/usr    \
             --sysconfdir=/etc \
             --libdir=/usr/lib/iiim/$(MACH64) \
             --localstatedir=/var
	cd $(BUILD_DIR_64)/lib/kbltrans; $(GMAKE)
	cd $(BUILD_DIR_64)/lib/kbltrans; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_kbltrans_32): $(BUILD_iiimp_32)
	$(RM) -r $(BUILD_DIR_32)/lib/kbltrans
	$(MKDIR) $(BUILD_DIR_32)/lib/kbltrans
	cd $(BUILD_DIR_32)/lib/kbltrans; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/lib/kbltrans/autogen.sh --prefix=/usr    \
             --sysconfdir=/etc \
             --libdir=/usr/lib/iiim \
             --localstatedir=/var
	cd $(BUILD_DIR_32)/lib/kbltrans; $(GMAKE)
	cd $(BUILD_DIR_32)/lib/kbltrans; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_iiimcf_64): $(BUILD_kbltrans_64)
	$(RM) -r $(BUILD_DIR_64)/lib/iiimcf
	$(MKDIR) $(BUILD_DIR_64)/lib/iiimcf
	cd $(BUILD_DIR_64)/lib/iiimcf; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.64)" CXXFLAGS="$(CXXFLAGS.64)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/lib/iiimcf/configure --prefix=/usr --localstatedir=/var  \
            --libdir=/usr/lib/$(MACH64)           \
            --libexecdir=/usr/lib/$(MACH64)   \
            --sysconfdir=/etc/$(MACH64)
	cd $(BUILD_DIR_64)/lib/iiimcf; $(GMAKE)
	cd $(BUILD_DIR_64)/lib/iiimcf; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_iiimcf_32): $(BUILD_kbltrans_32)
	$(RM) -r $(BUILD_DIR_32)/lib/iiimcf
	$(MKDIR) $(BUILD_DIR_32)/lib/iiimcf
	cd $(BUILD_DIR_32)/lib/iiimcf; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/lib/iiimcf/configure --prefix=/usr --localstatedir=/var
	cd $(BUILD_DIR_32)/lib/iiimcf; $(GMAKE)
	cd $(BUILD_DIR_32)/lib/iiimcf; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_iiimsf_32): $(BUILD_iiimcf_32)
	$(RM) -r $(BUILD_DIR_32)/iiimsf
	$(MKDIR) $(BUILD_DIR_32)/iiimsf
	cd $(BUILD_DIR_32)/iiimsf; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS1)" $(SOURCE_DIR)/iiimsf/configure --prefix=/usr --localstatedir=/var \
		--sysconfdir=/etc --localstatedir=/var --without-iconv --with-iconv=no --with-iconv-library=no
	$(PERL) -i -p -e 's/\/usr\/local\/lib//g' $(BUILD_DIR_32)/iiimsf/libtool
	cd $(BUILD_DIR_32)/iiimsf; $(GMAKE)
	cd $(BUILD_DIR_32)/iiimsf; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@


$(BUILD_xiiimp_so_64): $(BUILD_iiimcf_64)
	$(RM) -r $(BUILD_DIR_64)/iiimxcf/xiiimp.so
	$(MKDIR) $(BUILD_DIR_64)/iiimxcf/xiiimp.so
	cd $(BUILD_DIR_64)/iiimxcf/xiiimp.so; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.64)" CXXFLAGS="$(CXXFLAGS.64)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/iiimxcf/xiiimp.so/configure --prefix=/usr --localstatedir=/var  \
            --libdir=/usr/lib/$(MACH64)           \
            --libexecdir=/usr/lib/$(MACH64)   \
            --sysconfdir=/etc/$(MACH64)
	cd $(BUILD_DIR_64)/iiimxcf/xiiimp.so; $(GMAKE)
	cd $(BUILD_DIR_64)/iiimxcf/xiiimp.so; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	[ -d $(PROTO_DIR)/usr/lib/iiim/$(MACH64) ] || $(MKDIR) $(PROTO_DIR)/usr/lib/iiim/$(MACH64)
	mv $(PROTO_DIR)/usr/lib/iiim/xiiimp.so* $(PROTO_DIR)/usr/lib/iiim/$(MACH64)/
	$(TOUCH) $@

$(BUILD_xiiimp_so_32): $(BUILD_iiimsf_32)
	$(RM) -r $(BUILD_DIR_32)/iiimxcf/xiiimp.so
	$(MKDIR) $(BUILD_DIR_32)/iiimxcf/xiiimp.so
	cd $(BUILD_DIR_32)/iiimxcf/xiiimp.so; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/iiimxcf/xiiimp.so/configure --prefix=/usr --localstatedir=/var
	cd $(BUILD_DIR_32)/iiimxcf/xiiimp.so; $(GMAKE)
	cd $(BUILD_DIR_32)/iiimxcf/xiiimp.so; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_iiimgcf_64): $(BUILD_xiiimp_so_64)
	$(RM) -r $(BUILD_DIR_64)/iiimgcf
	$(MKDIR) $(BUILD_DIR_64)/iiimgcf
	cd $(BUILD_DIR_64)/iiimgcf; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.64)" CXXFLAGS="$(CXXFLAGS.64)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/iiimgcf/configure --prefix=/usr --localstatedir=/var  \
            --libdir=/usr/lib/$(MACH64)           \
            --libexecdir=/usr/lib/$(MACH64)   \
            --sysconfdir=/etc/$(MACH64)
	cd $(BUILD_DIR_64)/iiimgcf; $(GMAKE)
	cd $(BUILD_DIR_64)/iiimgcf; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	[ -d $(PROTO_DIR)/usr/lib/$(MACH64)/gtk-2.0/2.10.0/immodules ] || $(MKDIR) $(PROTO_DIR)/usr/lib/$(MACH64)/gtk-2.0/2.10.0/immodules
	mv $(PROTO_DIR)/usr/lib/gtk-2.0/2.10.0/immodules/im-iiim.so $(PROTO_DIR)/usr/lib/$(MACH64)/gtk-2.0/2.10.0/immodules/im-iiim.so
	$(TOUCH) $@

$(BUILD_iiimgcf_32): $(BUILD_xiiimp_so_32)
	$(RM) -r $(BUILD_DIR_32)/iiimgcf
	$(MKDIR) $(BUILD_DIR_32)/iiimgcf
	cd $(BUILD_DIR_32)/iiimgcf; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/iiimgcf/configure --prefix=/usr -sysconfdir=/etc --localstatedir=/var 
	cd $(BUILD_DIR_32)/iiimgcf; $(GMAKE)
	cd $(BUILD_DIR_32)/iiimgcf; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_cle_auxiliary_object_64): $(BUILD_iiimgcf_64)
	$(RM) -r $(BUILD_DIR_64)/sch_le_sun_cle
	$(MKDIR) $(BUILD_DIR_64)/sch_le_sun_cle
	cd $(BUILD_DIR_64)/sch_le_sun_cle; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.64)" CXXFLAGS="$(CXXFLAGS.64)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/leif/sch_le_sun/autogen.sh --prefix=/usr \
			--disable-debug --libdir=/usr/lib/$(MACH64) --libexecdir=/usr/lib/$(MACH64) --sysconfdir=/etc/$(MACH64)
	cd $(BUILD_DIR_64)/sch_le_sun_cle/src/auxiliary_windows/auxiliary_object; $(GMAKE)
	cd $(BUILD_DIR_64)/sch_le_sun_cle/src/auxiliary_windows/auxiliary_object; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	[ -d $(PROTO_DIR)/usr/lib/iiim/le/cle/auxiliary_windows/$(MACH64) ] || $(MKDIR) $(PROTO_DIR)/usr/lib/iiim/le/cle/auxiliary_windows/$(MACH64)
	mv $(PROTO_DIR)/usr/lib/iiim/le/cle/auxiliary_windows/auxiliary_object.so $(PROTO_DIR)/usr/lib/iiim/le/cle/auxiliary_windows/$(MACH64)/
	$(TOUCH) $@

$(BUILD_leif_32): $(BUILD_iiimgcf_32)
	$(RM) -r $(BUILD_DIR_32)/leif
	$(MKDIR) $(BUILD_DIR_32)/leif
	cd $(BUILD_DIR_32)/leif; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/leif/configure --prefix=/usr --sysconfdir=/etc --localstatedir=/var
	cd $(BUILD_DIR_32)/leif/unit; $(GMAKE)
	cd $(BUILD_DIR_32)/leif/unit; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_cle_32): $(BUILD_leif_32)
	$(RM) -r $(BUILD_DIR_32)/sch_le_sun_cle
	$(MKDIR) $(BUILD_DIR_32)/sch_le_sun_cle
	cp -r $(SOURCE_DIR)/leif/sch_le_sun/* $(BUILD_DIR_32)/sch_le_sun_cle
	cd $(BUILD_DIR_32)/sch_le_sun_cle; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS2) -lm" $(BUILD_DIR_32)/sch_le_sun_cle/autogen.sh --prefix=/usr \
			--disable-debug
	cd $(BUILD_DIR_32)/sch_le_sun_cle; $(GMAKE)
	cd $(BUILD_DIR_32)/sch_le_sun_cle; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_twle_auxiliary_object_64): $(BUILD_cle_auxiliary_object_64)
	$(RM) -r $(BUILD_DIR_64)/tch_le_sun_twle
	$(MKDIR) $(BUILD_DIR_64)/tch_le_sun_twle
	cd $(BUILD_DIR_64)/tch_le_sun_twle; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.64)" CXXFLAGS="$(CXXFLAGS.64)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/leif/tch_le_sun/autogen.sh --prefix=/usr \
			--disable-debug --libdir=/usr/lib/$(MACH64) --libexecdir=/usr/lib/$(MACH64) --sysconfdir=/etc/$(MACH64)
	cd $(BUILD_DIR_64)/tch_le_sun_twle/src/auxiliary_windows/auxiliary_object; $(GMAKE)
	cd $(BUILD_DIR_64)/tch_le_sun_twle/src/auxiliary_windows/auxiliary_object; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	[ -d $(PROTO_DIR)/usr/lib/iiim/le/twle/auxiliary_windows/$(MACH64) ] || $(MKDIR) $(PROTO_DIR)/usr/lib/iiim/le/twle/auxiliary_windows/$(MACH64)
	mv $(PROTO_DIR)/usr/lib/iiim/le/twle/auxiliary_windows/auxiliary_object.so $(PROTO_DIR)/usr/lib/iiim/le/twle/auxiliary_windows/$(MACH64)/
	$(TOUCH) $@

$(BUILD_twle_32): $(BUILD_cle_32)
	$(RM) -r $(BUILD_DIR_32)/tch_le_sun_twle
	$(MKDIR) $(BUILD_DIR_32)/tch_le_sun_twle
	cp -r $(SOURCE_DIR)/leif/tch_le_sun/* $(BUILD_DIR_32)/tch_le_sun_twle
	cd $(BUILD_DIR_32)/tch_le_sun_twle; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS2) -lm" $(BUILD_DIR_32)/tch_le_sun_twle/autogen.sh --disable-debug --with-lang=zh_TW
	cd $(BUILD_DIR_32)/tch_le_sun_twle; $(GMAKE)
	cd $(BUILD_DIR_32)/tch_le_sun_twle; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_hkle_auxiliary_object_64): $(BUILD_twle_auxiliary_object_64)
	$(RM) -r $(BUILD_DIR_64)/tch_le_sun_hkle
	$(MKDIR) $(BUILD_DIR_64)/tch_le_sun_hkle
	cd $(BUILD_DIR_64)/tch_le_sun_hkle; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.64)" CXXFLAGS="$(CXXFLAGS.64)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/leif/tch_le_sun/autogen.sh --prefix=/usr \
			--disable-debug --libdir=/usr/lib/$(MACH64) --libexecdir=/usr/lib/$(MACH64) --sysconfdir=/etc/$(MACH64) --with-lang=zh_HK
	cd $(BUILD_DIR_64)/tch_le_sun_hkle/src/auxiliary_windows/auxiliary_object; $(GMAKE)
	cd $(BUILD_DIR_64)/tch_le_sun_hkle/src/auxiliary_windows/auxiliary_object; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	[ -d $(PROTO_DIR)/usr/lib/iiim/le/hkle/auxiliary_windows/$(MACH64) ] || $(MKDIR) $(PROTO_DIR)/usr/lib/iiim/le/hkle/auxiliary_windows/$(MACH64)
	mv $(PROTO_DIR)/usr/lib/iiim/le/hkle/auxiliary_windows/auxiliary_object.so $(PROTO_DIR)/usr/lib/iiim/le/hkle/auxiliary_windows/$(MACH64)/
	$(TOUCH) $@

$(BUILD_hkle_32): $(BUILD_twle_32)
	$(RM) -r $(BUILD_DIR_32)/tch_le_sun_hkle
	$(MKDIR) $(BUILD_DIR_32)/tch_le_sun_hkle
	cp -r $(SOURCE_DIR)/leif/tch_le_sun/* $(BUILD_DIR_32)/tch_le_sun_hkle
	cd $(BUILD_DIR_32)/tch_le_sun_hkle; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS2) -lm" $(BUILD_DIR_32)/tch_le_sun_hkle/autogen.sh --disable-debug --with-lang=zh_HK
	cd $(BUILD_DIR_32)/tch_le_sun_hkle; $(GMAKE)
	cd $(BUILD_DIR_32)/tch_le_sun_hkle; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_htt_xbe_32): $(BUILD_hkle_32)
	$(RM) -r $(BUILD_DIR_32)/iiimxcf/htt_xbe
	$(MKDIR) $(BUILD_DIR_32)/iiimxcf/htt_xbe
	cd $(BUILD_DIR_32)/iiimxcf/htt_xbe; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/iiimxcf/htt_xbe/configure --prefix=/usr --localstatedir=/var
	cd $(BUILD_DIR_32)/iiimxcf/htt_xbe; $(GMAKE)
	cd $(BUILD_DIR_32)/iiimxcf/htt_xbe; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_doc_32): $(BUILD_htt_xbe_32)
	$(RM) -r $(BUILD_DIR_32)/doc
	$(MKDIR) $(BUILD_DIR_32)/doc
	cd $(BUILD_DIR_32)/doc; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/doc/configure --prefix=/usr --sysconfdir=/etc --localstatedir=/var
	cd $(BUILD_DIR_32)/doc; $(GMAKE)
	cd $(BUILD_DIR_32)/doc; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_gnome_im_switcher_32): $(BUILD_doc_32)
	$(RM) -r $(BUILD_DIR_32)/gnome-im-switcher
	$(MKDIR) $(BUILD_DIR_32)/gnome-im-switcher
	cd $(BUILD_DIR_32)/gnome-im-switcher; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/gnome-im-switcher/autogen.sh --prefix=/usr    \
             --sysconfdir=/etc \
             --libexecdir=/usr/lib \
             --localstatedir=/var/lib
	cd $(BUILD_DIR_32)/gnome-im-switcher; $(GMAKE)
	cd $(BUILD_DIR_32)/gnome-im-switcher/src; $(GMAKE) DESTDIR=$(PROTO_DIR) install-iconsDATA
	$(TOUCH) $@

$(BUILD_iiim_properties_32): $(BUILD_gnome_im_switcher_32)
	$(RM) -r $(BUILD_DIR_32)/program/iiim-properties
	$(MKDIR) $(BUILD_DIR_32)/program/iiim-properties
	cd $(BUILD_DIR_32)/program/iiim-properties; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/program/iiim-properties/autogen.sh --prefix=/usr    \
             --sysconfdir=/etc \
             --libexecdir=/usr/lib \
             --localstatedir=/var/lib
	cd $(BUILD_DIR_32)/program/iiim-properties; $(GMAKE)
	cd $(BUILD_DIR_32)/program/iiim-properties; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_iiim_panel_32): $(BUILD_iiim_properties_32)
	$(RM) -r $(BUILD_DIR_32)/program/iiim-panel
	$(MKDIR) $(BUILD_DIR_32)/program/iiim-panel
	cd $(BUILD_DIR_32)/program/iiim-panel; /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS2)" $(SOURCE_DIR)/program/iiim-panel/autogen.sh --prefix=/usr    \
             --sysconfdir=/etc \
             --libexecdir=/usr/lib \
             --localstatedir=/var/lib
	cd $(BUILD_DIR_32)/program/iiim-panel; $(GMAKE)
	cd $(BUILD_DIR_32)/program/iiim-panel; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_vkb_native_32):	$(BUILD_iiim_panel_32)
	$(RM) -r $(BUILD_DIR_32)/program/iiim-keyboard
	$(MKDIR) $(BUILD_DIR_32)/program/iiim-keyboard
	cp -r $(SOURCE_DIR)/program/iiim-keyboard/* $(BUILD_DIR_32)/program/iiim-keyboard
	cd $(BUILD_DIR_32)/program/iiim-keyboard/vkb_native;  /usr/bin/env CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS.32)" CXXFLAGS="$(CXXFLAGS.32)" LDFLAGS="$(MY_LDFLAGS2) -L$(BUILD_DIR_32)/lib/iiimcf" $(SOURCE_DIR)/program/iiim-keyboard/vkb_native/autogen.sh \
		--prefix=/usr  --sysconfdir=/etc --libdir=/usr/lib/iiim
	cd $(BUILD_DIR_32)/program/iiim-keyboard/vkb_native; $(GMAKE) 
	cd $(BUILD_DIR_32)/program/iiim-keyboard/vkb_native; $(GMAKE) DESTDIR=$(PROTO_DIR) install
	$(TOUCH) $@

$(BUILD_iiim_keyboard_32): $(BUILD_vkb_native_32)
	cd $(BUILD_DIR_32)/program/iiim-keyboard; /usr/bin/env JAVA_HOME=$(JAVA_HOME) /usr/bin/ant jar
	$(TOUCH) $@

# Install targets

$(INSTALL_32):  $(INSTALL_64)

$(INSTALL_64): $(BUILD_64)

INSTALL_iiimsf_confDATA_32 = $(BUILD_DIR_32)/.installed_iiimsf_confDATA

INSTALL_gnome_im_switcher_32 = $(BUILD_DIR_32)/.installed_gnome_im_switcher

INSTALL_kbltrans_32 = $(BUILD_DIR_32)/.installed_kbltrans

INSTALL_iiim_properties_32 = $(BUILD_DIR_32)/.installed_iiim_properties

INSTALL_gnome_im_switcher_schemas_32 = $(BUILD_DIR_32)/.installed_gnome_im_switcher_schemas

INSTALL_immodules_32 = $(BUILD_DIR_32)/.installed_immodules

INSTALL_iiim_keyboard_32 = $(BUILD_DIR_32)/.installed_iiim_keyboard

INSTALL_iiim_properties_desktop_32 = $(BUILD_DIR_32)/.installed_iiim_properties_desktop

INSTALL_final_cleanup_32 = $(BUILD_DIR_32)/.cleaned_up


$(INSTALL_32): $(BUILD_32) $(INSTALL_iiimsf_confDATA_32) $(INSTALL_gnome_im_switcher_32) $(INSTALL_kbltrans_32) $(INSTALL_iiim_properties_32) $(INSTALL_gnome-im-switcher_schemas_32) \
	$(INSTALL_immodules_32) $(INSTALL_iiim_keyboard_32) $(INSTALL_iiim_properties_desktop_32) $(INSTALL_final_cleanup_32)

$(INSTALL_iiimsf_confDATA_32): $(BUILD_32)
	cd $(BUILD_DIR_32)/iiimsf; $(GMAKE) DESTDIR=$(PROTO_DIR) install-confDATA
	$(TOUCH) $@

$(INSTALL_gnome_im_switcher_32): $(INSTALL_iiimsf_confDATA_32)
	cd $(BUILD_DIR_32)/gnome-im-switcher/src; $(GMAKE) DESTDIR=$(PROTO_DIR) install-schemasDATA
	cd $(BUILD_DIR_32)/gnome-im-switcher/capplet; $(GMAKE) DESTDIR=$(PROTO_DIR) install-schemasDATA
	$(TOUCH) $@

$(INSTALL_kbltrans_32): $(INSTALL_gnome_im_switcher_32)
	cd $(BUILD_DIR_32)/lib/kbltrans; $(GMAKE) DESTDIR=$(PROTO_DIR) install-confDATA
	$(TOUCH) $@

$(INSTALL_iiim_properties_32): $(INSTALL_kbltrans_32)
	cd $(BUILD_DIR_32)/program/iiim-properties; $(GMAKE) DESTDIR=$(PROTO_DIR) install-confDATA
	$(TOUCH) $@

$(INSTALL_gnome_im_switcher_schemas_32): $(INSTALL_iiim_properties_32)
	cd $(PROTO_DIR); /usr/bin/env GCONF_CONFIG_SOURCE="xml::$(PROTO_DIR)/etc/gconf/gconf.xml.defaults" /usr/bin/gconftool-2 --makefile-install-rule $(PROTO_DIR)/etc/gconf/schemas/gnome-im-switcher.schemas
	cd $(PROTO_DIR); for f in apps/%gconf.xml \
		schemas/%gconf.xml \
		schemas/apps/%gconf.xml; do \
		test ! -s $(PROTO_DIR)/etc/gconf/gconf.xml.defaults/$$f && \
		rm -rf $(PROTO_DIR)/etc/gconf/gconf.xml.defaults/$$f ; \
	done
	$(TOUCH) $@

$(INSTALL_immodules_32): $(INSTALL_gnome_im_switcher_schemas_32)
	[ -d $(PROTO_DIR)/etc/gtk-2.0 ] || $(MKDIR) $(PROTO_DIR)/etc/gtk-2.0
	$(GSED) -e '/^\#/d' $(COMPONENT_DIR)/files/etc_gtk-2.0_gtk.immodules > \
		$(PROTO_DIR)/etc/gtk-2.0/gtk.immodules
	[ -d $(PROTO_DIR)/etc/$(MACH64)/gtk-2.0 ] || $(MKDIR) $(PROTO_DIR)/etc/$(MACH64)/gtk-2.0
	$(GSED) -e '/^\#/d' -e "s/@ARCH@/$(MACH64)/" $(COMPONENT_DIR)/files/etc_ARCH_gtk-2.0_gtk.immodules > \
		$(PROTO_DIR)/etc/$(MARCH64)/gtk-2.0/gtk.immodules
	[ -d $(PROTO_DIR)/etc/X11/xinit/imf.d ] || $(MKDIR) $(PROTO_DIR)/etc/X11/xinit/imf.d
	cp $(COMPONENT_DIR)/files/imf_0020.iiim $(PROTO_DIR)/etc/X11/xinit/imf.d/0020.iiim
	$(TOUCH) $@

$(INSTALL_iiim_keyboard_32): $(INSTALL_immodules_32)
	cp $(BUILD_DIR_32)/program/iiim-keyboard/dist/VKB.jar $(PROTO_DIR)/usr/lib/iiim/VKB.jar
	cp $(BUILD_DIR_32)/program/iiim-keyboard/data/geometry.vkz $(PROTO_DIR)/etc/iiim/geometry.vkz
	cp $(BUILD_DIR_32)/program/iiim-keyboard/bin/iiim-keyboard $(PROTO_DIR)/usr/bin/iiim-keyboard
	[ -d $(PROTO_DIR)/usr/share/iiim/vkb/help/html ] || $(MKDIR) $(PROTO_DIR)/usr/share/iiim/vkb/help/html
	cp -r $(BUILD_DIR_32)/program/iiim-keyboard/help/solaris/html/* $(PROTO_DIR)/usr/share/iiim/vkb/help/html
	$(TOUCH) $@

$(INSTALL_iiim_properties_desktop_32): $(INSTALL_iiim_keyboard_32)
	[ -d $(PROTO_DIR)/usr/share/applications ] || $(MKDIR) $(PROTO_DIR)/usr/share/applications
	mv $(PROTO_DIR)/usr/share/control-center-2.0/capplets/iiim-properties.desktop $(PROTO_DIR)/usr/share/applications
	$(TOUCH) $@

$(INSTALL_final_cleanup_32): $(INSTALL_iiim_properties_desktop_32)
	$(RM) -f $(PROTO_DIR)/usr/bin/iiimf-le-tools
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/iiimd-watchdog
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/csconv/csconv.la
	$(RM) -f $(PROTO_DIR)/usr/share/pixmaps/gimlet-*.png
	mv $(PROTO_DIR)/usr/lib/libiiimutils.so.0.0.0 $(PROTO_DIR)/usr/lib/iiim/libiiimutils.so
	[ -d $(PROTO_DIR)/usr/lib/X11/locale/common ] || $(MKDIR) $(PROTO_DIR)/usr/lib/X11/locale/common
	mv $(PROTO_DIR)/usr/lib/iiim/xiiimp.so.2.0.0 $(PROTO_DIR)/usr/lib/X11/locale/common/xiiimp.so.2
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/xiiimp.so*
	[ -d $(PROTO_DIR)/usr/lib/X11/locale/$(MACH64)/common ] || $(MKDIR) $(PROTO_DIR)/usr/lib/X11/locale/$(MACH64)/common
	mv $(PROTO_DIR)/usr/lib/iiim/$(MACH64)/xiiimp.so.2.0.0 $(PROTO_DIR)/usr/lib/X11/locale/$(MACH64)/common/xiiimp.so.2
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/$(MACH64)/xiiimp.so*
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/libiiimvkb_jni.la
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/libiiimvkb_jni.a
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/libiiimvkb_jni.so
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/libiiimvkb_jni.so.0
	mv $(PROTO_DIR)/usr/lib/iiim/libiiimvkb_jni.so.0.0.0 $(PROTO_DIR)/usr/lib/iiim/libiiimvkb_jni.so
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/libkbltrans.la
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/libkbltrans.a
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/$(MACH64)/libkbltrans.la
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/$(MACH64)/libkbltrans.a
	$(RM) -fr $(PROTO_DIR)/usr/include/kbltrans
	mv $(PROTO_DIR)/usr/bin/iiimx-settings-init $(PROTO_DIR)/usr/lib/iiim/iiimx-settings-init
	$(RM) -fr $(PROTO_DIR)/usr/bin/*test
	$(RM) -fr $(PROTO_DIR)/usr/lib/gtk-2.0/2.10.0/immodules/im-iiim.la
	$(RM) -fr $(PROTO_DIR)/usr/lib/gtk-2.0/2.10.0/immodules/im-iiim.a
	$(RM) -fr $(PROTO_DIR)/usr/lib/libiiimcf.la
	$(RM) -fr $(PROTO_DIR)/usr/lib/libiiimcf.a
	$(RM) -fr $(PROTO_DIR)/usr/lib/libiiimutils.la
	$(RM) -fr $(PROTO_DIR)/usr/lib/libiiimutils.a
	$(RM) -fr $(PROTO_DIR)/usr/lib/libiiimp.la
	$(RM) -fr $(PROTO_DIR)/usr/lib/libiiimp.a
	$(RM) -fr $(PROTO_DIR)/usr/lib/$(MACH64)/gtk-2.0/2.10.0/immodules/im-iiim.la
	$(RM) -fr $(PROTO_DIR)/usr/lib/$(MACH64)/gtk-2.0/2.10.0/immodules/im-iiim.a
	$(RM) -fr $(PROTO_DIR)/usr/lib/$(MACH64)/libiiimp.la
	$(RM) -fr $(PROTO_DIR)/usr/lib/$(MACH64)/libiiimp.a
	$(RM) -fr $(PROTO_DIR)/usr/lib/$(MACH64)/libiiimcf.la
	$(RM) -fr $(PROTO_DIR)/usr/lib/$(MACH64)/libiiimcf.a
	$(RM) -fr $(PROTO_DIR)/usr/lib/iiim/xiiimp.la
	$(RM) -fr $(PROTO_DIR)/usr/lib/iiim/xiiimp.a
	$(RM) -fr $(PROTO_DIR)/usr/include/iiim/lexmlconf.h
	$(RM) -fr $(PROTO_DIR)/var/
	$(RM) -fr $(PROTO_DIR)/usr/lib/libiiimutils.so
	$(RM) -fr $(PROTO_DIR)/usr/lib/libiiimutils.so.0
	$(RM) -fr $(PROTO_DIR)/usr/lib/iiim/le/unitle/common/*.a
	$(RM) -fr $(PROTO_DIR)/usr/lib/iiim/le/unitle/common/*.la
	$(RM) -fr $(PROTO_DIR)/usr/lib/iiim/le/unitle/*.a
	$(RM) -fr $(PROTO_DIR)/usr/lib/iiim/le/unitle/*.la
	$(RM) -fr $(PROTO_DIR)/usr/lib/iiim/le/unitle/unitle.so
	$(RM) -fr $(PROTO_DIR)/usr/lib/iiim/le/unitle/unitle.so.0
	mv $(PROTO_DIR)/usr/lib/iiim/le/unitle/unitle.so.0.0.0 $(PROTO_DIR)/usr/lib/iiim/le/unitle/unitle.so
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/le/unitle/common/codepoint_im.so
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/le/unitle/common/codepoint_im.so.0
	mv $(PROTO_DIR)/usr/lib/iiim/le/unitle/common/codepoint_im.so.0.0.0 $(PROTO_DIR)/usr/lib/iiim/le/unitle/common/codepoint_im.so
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/le/unitle/common/compose_im.so
	$(RM) -f $(PROTO_DIR)/usr/lib/iiim/le/unitle/common/compose_im.so.0
	mv $(PROTO_DIR)/usr/lib/iiim/le/unitle/common/compose_im.so.0.0.0 $(PROTO_DIR)/usr/lib/iiim/le/unitle/common/compose_im.so
	cd $(PROTO_DIR)/usr/lib/iiim; $(RM) libiiimutils.so.0; ln -s libiiimutils.so libiiimutils.so.0
	$(RM) -rf $(PROTO_DIR)/usr/share/gnome/help/imswitcher
	$(TOUCH) $@
		
# Common targets

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libgnome
REQUIRED_PACKAGES += library/desktop/libgnomeui
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/java/openjdk8
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/toolkit/libxt
