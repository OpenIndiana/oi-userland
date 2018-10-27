PREFIX = /opt/VirtualBox
OUTDIR = out/solaris.amd64/release
BLDDIR = $(OUTDIR)/bin
ISA = $(shell /usr/bin/isainfo -k)
BIT = $(shell /usr/bin/isainfo -b)
SYS = solaris

INS = /usr/sbin/install

INS.file = mkdir -p $(@D); $(INS) -s -f $(@D) $<

define install-rule
$$($(1)DIR)/%: $$($(1)DST)/%
	$$(INS.file)
endef

#-------------------------------------------------------------------------------
# Drivers and driver configuration

DRVS = vboxnet vboxdrv vboxflt vboxusb vboxusbmon

DRVDIR = $(DESTDIR)/platform/i86pc/kernel/drv/$(ISA)
DRVDST = $(BLDDIR)
IDRVS  = $(DRVS:%=$(DRVDIR)/%)

$(eval $(call install-rule,DRV)) 

DRVCONFDIR = $(DESTDIR)/platform/i86pc/kernel/drv
DRVCONFDST = $(BLDDIR)
IDRVCONFS  = $(DRVS:%=$(DRVCONFDIR)/%.conf)

$(eval $(call install-rule,DRVCONF)) 

#-------------------------------------------------------------------------------
# Localization %.qm

NLSDIR = $(DESTDIR)$(PREFIX)/nls
NLSDST = $(BLDDIR)/nls
INLSS  = $(subst $(NLSDST),$(NLSDIR),$(shell find $(NLSDST) -name *.qm))

$(eval $(call install-rule,NLS)) 

#-------------------------------------------------------------------------------
# Icons %.png

FILE.png = $(subst $(1),$(2),$(shell find $(1) -type f -name *.png))
define icon-rule
ICN$(1)DIR = $(DESTDIR)/usr/share/icons/hicolor/$(1)x$(1)/mimetypes
ICN$(1)DST = $(BLDDIR)/icons/$(1)x$(1)/mimetypes
IICNS += $(call FILE.png,$(BLDDIR)/icons/$(1)x$(1)/mimetypes,$(DESTDIR)/usr/share/icons/hicolor/$(1)x$(1)/mimetypes)
endef

ICNSIZE= 16 20 24 32 48 64 72 96 128 256

$(foreach s,$(ICNSIZE),$(eval $(call icon-rule,$(s))))
$(foreach s,$(ICNSIZE),$(eval $(call install-rule,ICN$(s))))

#-------------------------------------------------------------------------------
#
VBOXDIR = $(DESTDIR)$(PREFIX)
VBOXDST = $(BLDDIR)
VBOXS += VBox.sh
VBOXS += VBoxAutostart
VBOXS += VBoxBalloonCtrl
VBOXS += VBoxBugReport
VBOXS += VBoxCpuReport
VBOXS += VBoxDTrace
VBOXS += VBoxExtPackHelperApp
VBOXS += VBoxHeadless
VBOXS += VBoxISAExec
VBOXS += VBoxManage
VBOXS += VBoxNetAdpCtl
VBOXS += VBoxNetDHCP
VBOXS += VBoxNetNAT
VBOXS += VBoxSDL
VBOXS += VBoxSVC
VBOXS += VBoxTestOGL
VBOXS += VBoxVMMPreload
VBOXS += VBoxXPCOMIPCD
VBOXS += VBoxZoneAccess
VBOXS += VBoxDD2RC.rc
VBOXS += VBoxDDRC.rc
VBOXS += VMMRC.rc
VBOXS += VBoxDD2R0.r0
VBOXS += VBoxDDR0.r0
VBOXS += VMMR0.r0
VBOXS += VBoxEFI32.fd
VBOXS += VBoxEFI64.fd
VBOXS += VirtualBox
VBOXS += DbgPlugInDiggers.so
VBOXS += VBoxAuth.so
VBOXS += VBoxAuthSimple.so
VBOXS += VBoxDbg.so
VBOXS += VBoxDD.so
VBOXS += VBoxDD2.so
VBOXS += VBoxDDU.so
VBOXS += VBoxDragAndDropSvc.so
VBOXS += VBoxGuestControlSvc.so
VBOXS += VBoxGuestPropSvc.so
VBOXS += VBoxHeadless.so
VBOXS += VBoxHostChannel.so
VBOXS += VBoxKeyboard.so
VBOXS += VBoxNetDHCP.so
VBOXS += VBoxNetNAT.so
VBOXS += VBoxOGLhostcrutil.so
VBOXS += VBoxOGLhosterrorspu.so
VBOXS += VBoxOGLrenderspu.so
VBOXS += VBoxREM.so
VBOXS += VBoxRT.so
VBOXS += VBoxSDL.so
VBOXS += VBoxSharedClipboard.so
VBOXS += VBoxSharedCrOpenGL.so
VBOXS += VBoxSharedFolders.so
VBOXS += VBoxVMM.so
VBOXS += VBoxVMMPreload.so
VBOXS += VBoxXPCOM.so
VBOXS += VBoxXPCOMC.so
VBOXS += VirtualBox.so
VBOXS += components/VBoxC.so
VBOXS += components/VBoxSVCM.so
VBOXS += components/VBoxXPCOMBase.xpt
VBOXS += components/VBoxXPCOMIPCC.so
VBOXS += components/VirtualBox_XPCOM.xpt
VBOXS += libvboxjxpcom.so
VBOXS += vboxconfig.sh
VBOXS += LICENSE
VBOXS += ExtensionPacks/Oracle_VBoxDTrace_Extension_Pack/ExtPack.xml
VBOXS += ExtensionPacks/Oracle_VBoxDTrace_Extension_Pack/ExtPack-SourceCodeLicense.txt
VBOXS += ExtensionPacks/Oracle_VBoxDTrace_Extension_Pack/solaris.amd64/VBoxDTraceMain.so
IVBOXS = $(VBOXS:%=$(VBOXDIR)/%)

$(eval $(call install-rule,VBOX)) 

#-------------------------------------------------------------------------------
# Pixmaps
PIXDIR = $(DESTDIR)/usr/share/pixmaps
PIXDST = $(BLDDIR)
PIXS  = VBox.png
PIXS += virtualbox.png
IPIXS = $(PIXS:%=$(PIXDIR)/%)

$(eval $(call install-rule,PIX)) 

#-------------------------------------------------------------------------------
# SVC
SVCDIR = $(DESTDIR)/var/svc/manifest/application/virtualbox
SVCDST = src/VBox/Installer/$(SYS)
SVCS  = virtualbox-autostart.xml
SVCS += virtualbox-balloonctrl.xml
SVCS += virtualbox-zoneaccess.xml
ISVCS = $(SVCS:%=$(SVCDIR)/%)

$(eval $(call install-rule,SVC)) 

#-------------------------------------------------------------------------------
#

install:  $(IDRVS) $(IDRVCONFS) $(INLSS) $(IICNS) $(IVBOXS) $(IPIXS) $(ISVCS)

print-%:
	@echo '$(subst ','\'',$*=$($*)) (origin: $(origin $*), flavor: $(flavor $*))'
