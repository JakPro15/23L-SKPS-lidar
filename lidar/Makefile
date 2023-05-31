include $(TOPDIR)/rules.mk

PKG_NAME:=lidar
PKG_VERSION:=1.0
PKG_RELEASE:=1

SOURCE_DIR:=./src

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=skps_proj
  CATEGORY:=skps_proj
  DEPENDS:=
  TITLE:=Lidar package
endef

define Package/$(PKG_NAME)/description
  Package for using a lidar
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	cp -r $(SOURCE_DIR)/* $(PKG_BUILD_DIR)
	$(Build/Patch)
endef

define Build/Compile
	cd $(PKG_BUILD_DIR)/VL53L0X_rasp-master; API_DIR=$(PKG_BUILD_DIR)/VL53L0X_1.0.4 CROSS_COMPILE=aarch64-openwrt-linux-musl- make
	cd $(PKG_BUILD_DIR)/VL53L0X_rasp-master; API_DIR=$(PKG_BUILD_DIR)/VL53L0X_1.0.4 CROSS_COMPILE=aarch64-openwrt-linux-musl- make lidar
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/VL53L0X_rasp-master/bin/lidar $(1)/usr/bin
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
