SDK_PATH:=$(shell pwd)/ARDroneLib
PC_TARGET=yes
USE_LINUX=yes


ifdef MYKONOS
   include $(ARDRONE_CUSTOM_CONFIG)
   include $(ARDRONE_BUILD_CONFIG)
else
   include $(SDK_PATH)/Soft/Build/custom.makefile
   include $(SDK_PATH)/Soft/Build/config.makefile
endif

$(SDK_TARGET_DIR)

SDK_FLAGS+="USE_APP=no"
SDK_FLAGS+="USE_LIB=yes"

all: 
	@$(MAKE) -C $(SDK_PATH)/Soft/Build $(TMP_SDK_FLAGS) $(SDK_FLAGS) $(MAKECMDGOALS) USE_LINUX=yes
	@$(MAKE) -C $(SDK_PATH)/VP_SDK/Build $(TMP_SDK_FLAGS) $(SDK_FLAGS) $(MAKECMDGOALS) USE_LINUX=yes
              
install:
	mkdir -p ${INSTALL_PREFIX}/lib
	find $(SDK_PATH)/Soft/Build -type f -name '*.a' -exec cp '{}' ${INSTALL_PREFIX}/lib \;
	mkdir -p ${INSTALL_PREFIX}/include/ARDroneLib
	find $(SDK_PATH)/Soft/ -type d -name ardrone_tool -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find $(SDK_PATH)/Soft/ -type d -name ATcodec -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find $(SDK_PATH)/Soft/ -type d -name Common -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find $(SDK_PATH)/Soft/ -type d -name VP_Api -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find $(SDK_PATH)/Soft/ -type d -name Maths -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find $(SDK_PATH)/Soft/ -type d -name utils -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find $(SDK_PATH)/Soft/ -type d -name iniparser3.0b -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find $(SDK_PATH)/ -type d -name VLIB -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find $(SDK_PATH)/ -type d -name VP_Os -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find $(SDK_PATH)/ -type d -name VP_SDK -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find $(SDK_PATH)/ -type d -name libavcodec -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find $(SDK_PATH)/ -type d -name libavdevice -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find $(SDK_PATH)/ -type d -name libavfilter -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find $(SDK_PATH)/ -type d -name libavformat -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find $(SDK_PATH)/ -type d -name libavutil -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find $(SDK_PATH)/ -type d -name libswscale -exec cp -r '{}' ${INSTALL_PREFIX}/include/ARDroneLib/ \;
	find ${INSTALL_PREFIX}/include/ARDroneLib -type f -name \*.o -exec rm -f '{}' \;
	find ${INSTALL_PREFIX}/include/ARDroneLib -type f -name \*.c -exec rm -f '{}' \;
	find ${INSTALL_PREFIX}/include/ARDroneLib -type f -name \*.d -exec rm -f '{}' \;
