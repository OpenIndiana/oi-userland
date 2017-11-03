include ../../../make-rules/shared-macros.mk

X11_GATE_DIR=$(WS_TOP)/components/x11
X11_GATE_COOKIE=.x11.installed
X11_GATE_INSTALL_ACTION=!install

FULL_BUILD?=1

ifeq ($(FULL_BUILD), 1)
include components.mk 
else
include xorg.mk 
endif

clobber:
	@for d in $(COMPONENTS); \
  do \
		if [ "$$d"X != "$(X11_GATE_INSTALL_ACTION)X" ]; \
		then cd $(X11_GATE_DIR)/$$d && gmake clobber && rm -f $(X11_GATE_COOKIE) && cd -; \
    fi; \
  done;

publish:
	@typeset -i i=0;\
	for d in $(COMPONENTS); \
	do \
		if test -d $(X11_GATE_DIR)/$$d; \
		then \
			echo "Entering: $$d"; \
			if test ! -f $(X11_GATE_DIR)/$$d/$(X11_GATE_COOKIE); \
			then \
			cd $(X11_GATE_DIR)/$$d && gmake clobber \
				&& gmake env-prep && gmake publish \
				&& touch $(X11_GATE_COOKIE); \
			if test -f $(X11_GATE_COOKIE); \
			then echo "SUCCESS: $$d"; cd -; \
			else echo "FAILURE: $$d"; exit 1; fi; \
			((i=i+1));\
			fi;\
		elif [ "$$d"X = "$(X11_GATE_INSTALL_ACTION)X" ]; \
		then \
			if (( i > 0 )); \
			then \
			echo "$(X11_GATE_INSTALL_ACTION) $$i packages" && pfexec pkg update --no-backup-be ; \
			((i = 0)); \
			fi;\
		else \
			echo "Error: $$d does not exist"; \
			exit; \
		fi; \
	done;

REQUIRED_PACKAGES:
	@cat $(X11_GATE_DIR)/*/Makefile| grep 'REQUIRED_PACKAGES +=' | gsort --uniq | gsed '/x11/d'
