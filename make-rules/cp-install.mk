build:
	@echo "Nothing to build"

install:
	mkdir -p $(PROTO_DIR)
	cp -rf $(SOURCE_DIR)/usr $(PROTO_DIR)
