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
# Copyright 2012, Andrzej Szeszo
# Copyright 2017, Andre Lupa
# Copyright 2017, Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		driver-graphics-nvidia
NVIDIA_DRIVER_MAJOR_VERSION=	340
NVIDIA_DRIVER_MINOR_VERSION=	104
COMPONENT_VERSION=	$(NVIDIA_DRIVER_MAJOR_VERSION).$(NVIDIA_DRIVER_MINOR_VERSION)
IPS_COMPONENT_VERSION=	0.$(COMPONENT_VERSION)
COMPONENT_SRC=		NVIDIA-Solaris-x86-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).run
COMPONENT_ARCHIVE_HASH= \
	sha256:1fb837b7047e6b08df2a5eb973ae70ea07e5194570b24b966d3f97572cb6a450
#COMPONENT_ARCHIVE_URL=	http://uk.download.nvidia.com/solaris/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
#COMPONENT_ARCHIVE_URL=	ftp://download.nvidia.com/solaris/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
#COMPONENT_ARCHIVE_URL=	http://download.nvidia.com/solaris/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_URL=	http://us.download.nvidia.com/solaris/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.nvidia.com/object/solaris-display-archive.html

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

PKG_OPTIONS +=	-D NVIDIA_DRIVER_MAJOR_VERSION="$(NVIDIA_DRIVER_MAJOR_VERSION)"
PKG_OPTIONS +=	-D NVIDIA_DRIVER_MINOR_VERSION="$(NVIDIA_DRIVER_MINOR_VERSION)"
PKG_OPTIONS +=	-D NVIDIA_MEDIATOR="mediator=nvidia-drv mediator-implementation=nvidia-drv-proprietary mediator-version=$(NVIDIA_DRIVER_MAJOR_VERSION)"

$(SOURCE_DIR)/.unpacked: download Makefile $(PATCHES)
	$(RM) -r $(SOURCE_DIR)
	$(SHELL) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE) -x
	$(TOUCH) $@

$(BUILD_32):	$(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(TOUCH) $@

check_protodir_32:	$(BUILD_32)
	[ -n "$(PROTO_DIR)" ] && [ x"$(PROTO_DIR)" != x/ ] || exit

$(BUILD_DIR_32)/.installed_drv:	check_protodir_32
	$(RM) -r "$(PROTO_DIR)/kernel"
	[ -d "$(PROTO_DIR)/kernel/drv/$(MACH64)" ] || $(MKDIR) "$(PROTO_DIR)/kernel/drv/$(MACH64)"
	for i in \
	    kernel/drv/$(MACH64)/nvidia kernel/drv/nvidia \
	; do \
	    cp "$(SOURCE_DIR)/NVDAgraphicsr/reloc/$$i" \
	        "$(PROTO_DIR)/$$i-$(NVIDIA_DRIVER_MAJOR_VERSION)" \
	    && ln -s "`basename $$i`-$(NVIDIA_DRIVER_MAJOR_VERSION)" "$(PROTO_DIR)/$$i" \
	    || exit ; \
	done
	cp "$(SOURCE_DIR)/NVDAgraphicsr/reloc/kernel/drv/nvidia.conf" \
	    "$(PROTO_DIR)/kernel/drv/nvidia-$(NVIDIA_DRIVER_MAJOR_VERSION).conf" \
	    && ln -s "nvidia-$(NVIDIA_DRIVER_MAJOR_VERSION).conf" \
	        "$(PROTO_DIR)/kernel/drv/nvidia.conf"
	$(TOUCH) $@

install_drv_32: $(BUILD_DIR_32)/.installed_drv

$(BUILD_DIR_32)/.installed_reloc:	check_protodir_32
	$(RM) -r "$(PROTO_DIR)/usr"
	cp -a "$(SOURCE_DIR)/NVDAgraphics/reloc" "$(PROTO_DIR)/usr"
	$(TOUCH) $@

install_reloc_32: $(BUILD_DIR_32)/.installed_reloc

install_mv_bigdirs_32:	install_reloc_32
	for i in \
	    share/doc/NVIDIA \
	    share/icons/NVIDIA \
	    X11/lib/NVIDIA \
	    X11/lib/modules/extensions/NVIDIA \
	    X11/lib/modules/NVIDIA \
	    share/nvidia \
	; do \
	    mv -f "$(PROTO_DIR)/usr/$$i" \
	        "$(PROTO_DIR)/usr/$$i-$(NVIDIA_DRIVER_MAJOR_VERSION)" \
	    && ln -s "`basename $$i`-$(NVIDIA_DRIVER_MAJOR_VERSION)" "$(PROTO_DIR)/usr/$$i" \
	    || exit ; \
	done

install_mv_desktop_32:	install_reloc_32
	mv -f "$(PROTO_DIR)/usr/share/applications/nvidia-settings.desktop" \
	    "$(PROTO_DIR)/usr/share/applications/nvidia-settings-$(NVIDIA_DRIVER_MAJOR_VERSION).desktop" \
	    && ln -s "nvidia-settings-$(NVIDIA_DRIVER_MAJOR_VERSION).desktop" \
	        "$(PROTO_DIR)/usr/share/applications/nvidia-settings.desktop"
	mv -f "$(PROTO_DIR)/usr/share/control-center-2.0/capplets/nvidia-settings.s10.desktop" \
	    "$(PROTO_DIR)/usr/share/control-center-2.0/capplets/nvidia-settings-$(NVIDIA_DRIVER_MAJOR_VERSION).s10.desktop" \
	    && ln -s "nvidia-settings-$(NVIDIA_DRIVER_MAJOR_VERSION).s10.desktop" \
	        "$(PROTO_DIR)/usr/share/control-center-2.0/capplets/nvidia-settings.s10.desktop"
	mv -f "$(PROTO_DIR)/usr/dt/appconfig/appmanager/C/Desktop_Apps/nvidia-settings" \
	    "$(PROTO_DIR)/usr/dt/appconfig/appmanager/C/Desktop_Apps/nvidia-settings-$(NVIDIA_DRIVER_MAJOR_VERSION)" \
	    && ln -s "nvidia-settings-$(NVIDIA_DRIVER_MAJOR_VERSION)" \
	        "$(PROTO_DIR)/usr/dt/appconfig/appmanager/C/Desktop_Apps/nvidia-settings"
	mv -f "$(PROTO_DIR)/usr/dt/appconfig/icons/C" \
	    "$(PROTO_DIR)/usr/dt/appconfig/icons/C-NVIDIA-$(NVIDIA_DRIVER_MAJOR_VERSION)"
	$(MKDIR) "$(PROTO_DIR)/usr/dt/appconfig/icons/C"
	cd "$(PROTO_DIR)/usr/dt/appconfig/icons/C" \
	    && ln -s "../C-NVIDIA-$(NVIDIA_DRIVER_MAJOR_VERSION)/"* .
	mv -f "$(PROTO_DIR)/usr/dt/appconfig/types/C/nvidia-settings.dt" \
	    "$(PROTO_DIR)/usr/dt/appconfig/types/C/nvidia-settings-$(NVIDIA_DRIVER_MAJOR_VERSION).dt" \
	    && ln -s "nvidia-settings-$(NVIDIA_DRIVER_MAJOR_VERSION).dt" \
	        "$(PROTO_DIR)/usr/dt/appconfig/types/C/nvidia-settings.dt"

install_mv_tools_32:	install_reloc_32
	for i in settings xconfig ; do \
	    mv -f "$(PROTO_DIR)/usr/share/man/man1/nvidia-$$i.1" \
	        "$(PROTO_DIR)/usr/share/man/man1/nvidia-$$i-$(NVIDIA_DRIVER_MAJOR_VERSION).1" \
	    && ln -s "nvidia-$$i-$(NVIDIA_DRIVER_MAJOR_VERSION).1" "$(PROTO_DIR)/usr/share/man/man1/nvidia-$$i.1" \
	    || exit ; \
	    mv -f "$(PROTO_DIR)/usr/bin/$(MACH32)/nvidia-$$i" \
	        "$(PROTO_DIR)/usr/bin/$(MACH32)/nvidia-$$i-$(NVIDIA_DRIVER_MAJOR_VERSION)" \
	    && ln -s "nvidia-$$i-$(NVIDIA_DRIVER_MAJOR_VERSION)" "$(PROTO_DIR)/usr/bin/$(MACH32)/nvidia-$$i" \
	    || exit ; \
	    mv -f "$(PROTO_DIR)/usr/bin/$(MACH64)/nvidia-$$i" \
	        "$(PROTO_DIR)/usr/bin/$(MACH64)/nvidia-$$i-$(NVIDIA_DRIVER_MAJOR_VERSION)" \
	    && ln -s "nvidia-$$i-$(NVIDIA_DRIVER_MAJOR_VERSION)" "$(PROTO_DIR)/usr/bin/$(MACH64)/nvidia-$$i" \
	    || exit ; \
	done
	mv -f "$(PROTO_DIR)/usr/bin/nvidia-SunOS-bug-report.sh" \
	    "$(PROTO_DIR)/usr/bin/nvidia-SunOS-bug-report-$(NVIDIA_DRIVER_MAJOR_VERSION).sh" \
	    && ln -s "nvidia-SunOS-bug-report-$(NVIDIA_DRIVER_MAJOR_VERSION).sh" "$(PROTO_DIR)/usr/bin/nvidia-SunOS-bug-report.sh"
	mv -f "$(PROTO_DIR)/usr/lib/libnvidia-cfg.so.1" \
	    "$(PROTO_DIR)/usr/lib/libnvidia-cfg-$(NVIDIA_DRIVER_MAJOR_VERSION).so.1" \
	    && ln -s "libnvidia-cfg-$(NVIDIA_DRIVER_MAJOR_VERSION).so.1" \
	        "$(PROTO_DIR)/usr/lib/libnvidia-cfg.so.1"
	mv -f "$(PROTO_DIR)/usr/lib/$(MACH64)/libnvidia-cfg.so.1" \
	    "$(PROTO_DIR)/usr/lib/$(MACH64)/libnvidia-cfg-$(NVIDIA_DRIVER_MAJOR_VERSION).so.1" \
	    && ln -s "libnvidia-cfg-$(NVIDIA_DRIVER_MAJOR_VERSION).so.1" \
	        "$(PROTO_DIR)/usr/lib/$(MACH64)/libnvidia-cfg.so.1"
	mv -f "$(PROTO_DIR)/usr/X11/lib/X11/getconfig/nvda.cfg" \
	    "$(PROTO_DIR)/usr/X11/lib/X11/getconfig/nvda-$(NVIDIA_DRIVER_MAJOR_VERSION).cfg" \
	    && ln -s "nvda-$(NVIDIA_DRIVER_MAJOR_VERSION).cfg" \
	        "$(PROTO_DIR)/usr/X11/lib/X11/getconfig/nvda.cfg"

install_mv_X11drv_32:	install_reloc_32
	mv -f "$(PROTO_DIR)/usr/X11/lib/modules/drivers" \
	    "$(PROTO_DIR)/usr/X11/lib/modules/NVIDIA-$(NVIDIA_DRIVER_MAJOR_VERSION)/drivers"
	$(MKDIR) "$(PROTO_DIR)/usr/X11/lib/modules/drivers/$(MACH64)"
	cd "$(PROTO_DIR)/usr/X11/lib/modules/drivers" \
	    && ln -s "../NVIDIA-$(NVIDIA_DRIVER_MAJOR_VERSION)/drivers/"*.* .
	cd "$(PROTO_DIR)/usr/X11/lib/modules/drivers/$(MACH64)" \
	    && ln -s "../../NVIDIA-$(NVIDIA_DRIVER_MAJOR_VERSION)/drivers/$(MACH64)/"*.* .

install_headers_32:	install_reloc_32
	$(MKDIR) "$(PROTO_DIR)/usr/X11/include/NVIDIA-$(NVIDIA_DRIVER_MAJOR_VERSION)/GL"
	cp $(COMPONENT_DIR)/Solaris/gl*.h "$(PROTO_DIR)/usr/X11/include/NVIDIA-$(NVIDIA_DRIVER_MAJOR_VERSION)/GL"
	$(MKDIR) "$(PROTO_DIR)/usr/X11/include/NVIDIA-$(NVIDIA_DRIVER_MAJOR_VERSION)/vdpau"
	cp $(COMPONENT_DIR)/Solaris/vdp*.h "$(PROTO_DIR)/usr/X11/include/NVIDIA-$(NVIDIA_DRIVER_MAJOR_VERSION)/vdpau"
	ln -s "NVIDIA-$(NVIDIA_DRIVER_MAJOR_VERSION)" "$(PROTO_DIR)/usr/X11/include/NVIDIA"

# Help to register PCI IDs served by this driver with nvidia-select
install_driver_aliases_32:	install_mv_bigdirs_32
	$(SHELL) $(COMPONENT_DIR)/print-pci-ids.sh $(SOURCE_DIR) >> "$(PROTO_DIR)/usr/share/nvidia-$(NVIDIA_DRIVER_MAJOR_VERSION)/driver_aliases.txt"

$(INSTALL_32):	$(BUILD_32) install_drv_32 install_mv_bigdirs_32 install_mv_desktop_32 install_mv_tools_32 install_mv_X11drv_32 install_headers_32 install_driver_aliases_32
	$(TOUCH) $@

$(SAMPLE_MANIFEST_FILE):	sample-manifest
	[ -s "$@" ] && $(TOUCH) $@

$(SAMPLE_MANIFEST_FILE).nvidia:	$(SAMPLE_MANIFEST_FILE)
	sed -e 's,-$(NVIDIA_DRIVER_MAJOR_VERSION),-$$\(NVIDIA_DRIVER_MAJOR_VERSION\),g' \
	    -e 's,^\(link .*[^\\]\)$$,\1 $$\(NVIDIA_MEDIATOR\),g' \
	    -e 's,^\(    target=.*[^\\]\)$$, \1 $$\(NVIDIA_MEDIATOR\),g' \
	    < $< > $@

sample-manifest-nvidia: $(SAMPLE_MANIFEST_FILE).nvidia

build: $(BUILD_32)

install: $(INSTALL_32)

clean::
	if [ -d $(BUILD_DIR) ] ;  then \
	  rm -rf $(BUILD_DIR) ; \
	fi

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/compatibility/links-xorg
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
