X11_CATEGORY=DRIVER
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=xf86-video-illumosfb
COMPONENT_VERSION=0.5
COMPONENT_REVISION=2
COMPONENT_SUMMARY=Xorg driver for illumos UEFI frame buffer
COMPONENT_PROJECT_URL=  https://github.com/LuminousMonkey/xf86-video-illumosfb/
COMPONENT_FMRI=         x11/server/xorg/driver/xorg-video-illumosfb
# Upstream has no release tags yet; use a pinned commit archive.
COMPONENT_COMMIT=       8ad57812ca2e99be6281f5142101811482026c55
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:f601e824c7a08189656d77515d9df0c302b669e79f990684527b5e75865c3355
COMPONENT_ARCHIVE_URL=  https://github.com/LuminousMonkey/xf86-video-illumosfb/archive/$(COMPONENT_COMMIT).tar.gz
COMPONENT_CLASSIFICATION=       Drivers/Display
COMPONENT_LICENSE=      ISC
COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_PREP_ACTION= cd $(@D) && PATH="$(PATH)" NOCONFIGURE=1 /usr/bin/bash ./autogen.sh

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# autoconf 2.72 selects -std=gnu23, where bool is a keyword; the xorg-server
# 1.19 headers use bool as a struct member name.
CONFIGURE_ENV += ac_cv_prog_cc_c23=no

# Upstream installs into $(libdir)/xorg/modules/drivers; the X server looks
# in /usr/lib/xorg/modules/drivers/$(MACH64).
COMPONENT_INSTALL_ARGS += illumosfb_drv_ladir='$(X11_SERVERMODS_DRIVERS_DIR)'

REQUIRED_PACKAGES += x11/server/xorg
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += developer/build/autoconf/xorg-macros

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
