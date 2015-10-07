include theos/makefiles/common.mk

TWEAK_NAME = Radian
Radian_FILES= Tweak.xm
Radian_LDFLAGS= -lprotractor
include $(THEOS_MAKE_PATH)/tweak.mk

after-install::
	install.exec "killall -9 SpringBoard"
