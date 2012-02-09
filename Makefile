TARGET = module_analyzer
OBJS = src/exports.o src/io.o src/libraries.o src/main.o src/memory_alloc.o src/segments.o src/stubs.o

CFLAGS = -O2 -G0 -w -msingle-float -g
ASFLAGS = $(CFLAGS)

# Define to build this as a prx (instead of a static elf)
BUILD_PRX = 1

USE_USER_LIBS = 1
USE_USER_LIBC = 1

LIBS = -lpspsystemctrl_user
LDFLAGS = -nostartfiles -mno-crt0 -g

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak