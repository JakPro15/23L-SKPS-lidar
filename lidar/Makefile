include $(TOPDIR)/rules.mk

PKG_NAME:=lidar
PKG_VERSION:=1.0
PKG_RELEASE:=1

SOURCE_DIR:=./src

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=skps_proj
  CATEGORY:=skps_proj
  DEPENDS:=+libc
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
	$(TARGET_CC) $(TARGET_CFLAGS) -o $(PKG_BUILD_DIR)/main.o -c $(PKG_BUILD_DIR)/main.c
	$(TARGET_CC) $(TARGET_LDFLAGS) -o $(PKG_BUILD_DIR)/lidar $(PKG_BUILD_DIR)/main.o
#	cd $(PKG_BUILD_DIR)/VL53L0X_rasp-master; API_DIR=$(PKG_BUILD_DIR)/VL53L0X_1.0.4 CROSS_COMPILE=aarch64-openwrt-linux-musl- make
#	cd $(PKG_BUILD_DIR)/VL53L0X_rasp-master; API_DIR=$(PKG_BUILD_DIR)/VL53L0X_1.0.4 CROSS_COMPILE=aarch64-openwrt-linux-musl- make examples
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/VL53L0X_rasp-master/bin/vl53l0x_ContinuousRanging_Example $(1)/usr/bin
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/VL53L0X_rasp-master/bin/vl53l0x_SingleRanging_Long_Range_Example $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/lidar $(1)/usr/bin
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
