
TARGET = 'embox'

PLATFORM = 'stm32vl'

ARCH = 'arm'

CROSS_COMPILE = 'arm-none-eabi-'

CFLAGS = ['-O0', '-g']
CFLAGS += ['-mthumb', '-mlittle-endian', '-mcpu=cortex-m3', '-ffreestanding']

LDFLAGS = ['-N', '-g']
