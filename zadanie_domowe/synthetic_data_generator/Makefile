include $(TOPDIR)/rules.mk

PKG_NAME:=synthetic_data_generator
PKG_VERSION:=1.0
PKG_RELEASE:=1

SOURCE_DIR:=./src

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=project
  CATEGORY:=Project
  TITLE:=Synthetic Data Generator
endef

define Package/$(PKG_NAME)/description
  Application generating synthetic lidar data and sending it over the network.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	cp $(SOURCE_DIR)/* $(PKG_BUILD_DIR)
	$(Build/Patch)
endef

define Build/Compile
	$(TARGET_CC) $(TARGET_CFLAGS) -o $(PKG_BUILD_DIR)/main.o -c $(PKG_BUILD_DIR)/main.c
	$(TARGET_CC) $(TARGET_LDFLAGS) -o $(PKG_BUILD_DIR)/synthetic_data_generator $(PKG_BUILD_DIR)/main.o
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/synthetic_data_generator $(1)/usr/bin
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

