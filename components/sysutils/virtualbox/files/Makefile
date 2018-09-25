BINDIR = out/solaris.amd64/release/bin
DRVS = vboxnet vboxdrv vboxflt vboxusb vboxusbmon
ISA = $(shell /usr/bin/isainfo -k)

DRVDIR = $(DESTDIR)/platform/i86pc/kernel/drv/$(ISA)
CONFDIR = $(DESTDIR)/platform/i86pc/kernel/drv

IDRVS= $(DRVS:%=$(DRVDIR)/%)
ICONFIGS=$(DRVS:%=$(CONFDIR)/%.conf)

INS= /usr/sbin/install

INS.file= $(RM) $@; $(INS) -s -f $(@D) $<

$(DRVDIR): 
	mkdir -p $(@)

$(CONFDIR):
	mkdir -p $(@)

$(DRVDIR)/%: $(DRVDIR) 

$(DRVDIR)/%: $(BINDIR)/%
	$(INS.file)

$(CONFDIR)/%: $(CONFDIR)

$(CONFDIR)/%: $(BINDIR)/%
	$(INS.file)

install:  $(DESTDIR)/platform/i86pc/kernel/drv/$(ISA) $(ICONFIGS) $(IDRVS)

print-%:
	@echo '$(subst ','\'',$*=$($*)) (origin: $(origin $*), flavor: $(flavor $*))'
