
# A simple rule to print the value of any macro.  Ex:
#    $ gmake print-REQUIRED_PACKAGES
# Note that some macros are set on a per target basis, so what you see
# is not always what you get.
print-%:
	@echo '$(subst ','\'',$*=$($*)) (origin: $(origin $*), flavor: $(flavor $*))'

# A simple rule to print only the value of any macro.
print-value-%:
	@echo '$(subst ','\'',$($*))'

# Provide default print package targets for components that do not rely on IPS.
# Define them implicitly so that the definitions do not collide with ips.mk
define print-package-rule
echo $(strip $(PACKAGE_$(1))) | tr ' ' '\n'
endef


COMPONENT_TOOL = $(WS_TOOLS)/userland-component

format:
	@$(COMPONENT_TOOL) --path $(COMPONENT_DIR);

update:
	@if [ "$(VERSION)X" = "X" ]; \
	then $(COMPONENT_TOOL) --path $(COMPONENT_DIR) --bump; \
	else $(COMPONENT_TOOL) --path $(COMPONENT_DIR) --bump $(VERSION); \
	fi;

update-latest:
	$(COMPONENT_TOOL) --path $(COMPONENT_DIR) --bump latest;

