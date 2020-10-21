header_files:=$(shell find ../include -type f)

.PHONY: copy

all: copy

copy:
	@cp usr/share/kevin.txt ../image/usr/share/kevin.txt
	@cp sys/sys.json ../image/sys/reg.json
	@cp etc/sudoers ../image/etc/sudoers
	@cp etc/cash.config ../image/etc/cash.config
	@cp etc/passwd ../image/etc/passwd
	@cp etc/sysinfo.b86 ../image/etc/sysinfo.b86
	@cp etc/sysfile ../image/etc/sysfile
	@cp sys/sysenv.env ../image/etc/sysenv.env
	@cp usr/share/fizzbuz.bfk ../image/usr/share/fizzbuz.bfk
	@cp usr/share/js-example.js ../image/usr/share/js-example.js
	@cp usr/share/test.bmp ../image/usr/share/test.bmp
	@cp usr/share/images/osdev.bmp ../image/usr/share/osdev.bmp
	@cp usr/share/images/alert.bmp ../image/usr/share/alert.bmp
	@cp usr/share/images/lena.bmp ../image/usr/share/lena.bmp
	@cp usr/share/splash/splash.bmp ../image/usr/share/splash.bmp

../image/usr/include/%: ../include/%
	@mkdir -p $(@D)
	@cp $< $@

