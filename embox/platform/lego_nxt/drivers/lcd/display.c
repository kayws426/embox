/**
 * @file
 *
 * @date 11.10.10
 * @author Nikolay Korotky
 * @author Darya Dzendzik
 */

#include <hal/reg.h>
#include <util/math.h>
#include <drivers/at91sam7s256.h>
#include <drivers/lcd.h>
#include <string.h>

extern __u8 display_buffer[NXT_LCD_DEPTH+1][NXT_LCD_WIDTH];

static int display_x;
static int display_y;

__u8 font[N_CHARS][FONT_WIDTH] = {
/* 0x00 */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x01 */ {0x3E, 0x55, 0x61, 0x55, 0x3E},
/* 0x02 */ {0x3E, 0x6B, 0x5F, 0x6B, 0x3E},
/* 0x03 */ {0x0C, 0x1E, 0x3C, 0x1E, 0x0C},
/* 0x04 */ {0x08, 0x1C, 0x3E, 0x1C, 0x08},
/* 0x05 */ {0x08, 0x7c, 0x0e, 0x7c, 0x08},
/* 0x06 */ {0x18, 0x5C, 0x7E, 0x5C, 0x18},
/* 0x07 */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x08 */ {0x08, 0x1c, 0x3e, 0x08, 0x08},
/* 0x09 */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x0A */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x0B */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x0C */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x0D */ {0x10, 0x38, 0x7c, 0x10, 0x1e},
/* 0x0E */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x0F */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x10 */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x11 */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x12 */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x13 */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x14 */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x15 */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x16 */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x17 */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x18 */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x19 */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x1A */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x1B */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x1C */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x1D */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x1E */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x1F */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
/* 0x20 */ {0x00, 0x00, 0x00, 0x00, 0x00},
/* 0x21 */ {0x00, 0x00, 0x5F, 0x00, 0x00},
/* 0x22 */ {0x00, 0x07, 0x00, 0x07, 0x00},
/* 0x23 */ {0x14, 0x3E, 0x14, 0x3E, 0x14},
/* 0x24 */ {0x04, 0x2A, 0x7F, 0x2A, 0x10},
/* 0x25 */ {0x26, 0x16, 0x08, 0x34, 0x32},
/* 0x26 */ {0x36, 0x49, 0x59, 0x26, 0x50},
/* 0x27 */ {0x00, 0x00, 0x07, 0x00, 0x00},
/* 0x28 */ {0x00, 0x1C, 0x22, 0x41, 0x00},
/* 0x29 */ {0x00, 0x41, 0x22, 0x1C, 0x00},
/* 0x2A */ {0x2A, 0x1C, 0x7F, 0x1C, 0x2A},
/* 0x2B */ {0x08, 0x08, 0x3E, 0x08, 0x08},
/* 0x2C */ {0x00, 0x50, 0x30, 0x00, 0x00},
/* 0x2D */ {0x08, 0x08, 0x08, 0x08, 0x08},
/* 0x2E */ {0x00, 0x60, 0x60, 0x00, 0x00},
/* 0x2F */ {0x20, 0x10, 0x08, 0x04, 0x02},
/* 0x30 */ {0x3E, 0x51, 0x49, 0x45, 0x3E},
/* 0x31 */ {0x00, 0x42, 0x7F, 0x40, 0x00},
/* 0x32 */ {0x42, 0x61, 0x51, 0x49, 0x46},
/* 0x33 */ {0x21, 0x41, 0x45, 0x4B, 0x31},
/* 0x34 */ {0x18, 0x14, 0x12, 0x7F, 0x10},
/* 0x35 */ {0x27, 0x45, 0x45, 0x45, 0x39},
/* 0x36 */ {0x3C, 0x4A, 0x49, 0x49, 0x30},
/* 0x37 */ {0x01, 0x01, 0x79, 0x05, 0x03},
/* 0x38 */ {0x36, 0x49, 0x49, 0x49, 0x36},
/* 0x39 */ {0x06, 0x49, 0x49, 0x29, 0x1E},
/* 0x3A */ {0x00, 0x36, 0x36, 0x00, 0x00},
/* 0x3B */ {0x00, 0x56, 0x36, 0x00, 0x00},
/* 0x3C */ {0x08, 0x14, 0x22, 0x41, 0x00},
/* 0x3D */ {0x14, 0x14, 0x14, 0x14, 0x14},
/* 0x3E */ {0x41, 0x22, 0x14, 0x08, 0x00},
/* 0x3F */ {0x02, 0x01, 0x59, 0x05, 0x02},
/* 0x40 */ {0x1C, 0x2A, 0x36, 0x3E, 0x0C},
/* 0x41 */ {0x7E, 0x09, 0x09, 0x09, 0x7E},
/* 0x42 */ {0x7F, 0x49, 0x49, 0x49, 0x3E},
/* 0x43 */ {0x3E, 0x41, 0x41, 0x41, 0x22},
/* 0x44 */ {0x7F, 0x41, 0x41, 0x22, 0x1C},
/* 0x45 */ {0x7F, 0x49, 0x49, 0x49, 0x41},
/* 0x46 */ {0x7F, 0x09, 0x09, 0x09, 0x01},
/* 0x47 */ {0x3E, 0x41, 0x41, 0x49, 0x3A},
/* 0x48 */ {0x7F, 0x08, 0x08, 0x08, 0x7F},
/* 0x49 */ {0x00, 0x41, 0x7F, 0x41, 0x00},
/* 0x4A */ {0x20, 0x40, 0x41, 0x3F, 0x01},
/* 0x4B */ {0x7F, 0x08, 0x14, 0x22, 0x41},
/* 0x4C */ {0x7F, 0x40, 0x40, 0x40, 0x40},
/* 0x4D */ {0x7F, 0x02, 0x04, 0x02, 0x7F},
/* 0x4E */ {0x7F, 0x04, 0x08, 0x10, 0x7F},
/* 0x4F */ {0x3E, 0x41, 0x41, 0x41, 0x3E},
/* 0x50 */ {0x7F, 0x09, 0x09, 0x09, 0x06},
/* 0x51 */ {0x3E, 0x41, 0x51, 0x21, 0x5E},
/* 0x52 */ {0x7F, 0x09, 0x19, 0x29, 0x46},
/* 0x53 */ {0x26, 0x49, 0x49, 0x49, 0x32},
/* 0x54 */ {0x01, 0x01, 0x7F, 0x01, 0x01},
/* 0x55 */ {0x3F, 0x40, 0x40, 0x40, 0x3F},
/* 0x56 */ {0x1F, 0x20, 0x40, 0x20, 0x1F},
/* 0x57 */ {0x7F, 0x20, 0x18, 0x20, 0x7F},
/* 0x58 */ {0x63, 0x14, 0x08, 0x14, 0x63},
/* 0x59 */ {0x03, 0x04, 0x78, 0x04, 0x03},
/* 0x5A */ {0x61, 0x51, 0x49, 0x45, 0x43},
/* 0x5B */ {0x00, 0x7F, 0x41, 0x41, 0x00},
/* 0x5C */ {0x02, 0x04, 0x08, 0x10, 0x20},
/* 0x5D */ {0x00, 0x41, 0x41, 0x7F, 0x00},
/* 0x5E */ {0x04, 0x02, 0x01, 0x02, 0x04},
/* 0x5F */ {0x40, 0x40, 0x40, 0x40, 0x40},
/* 0x60 */ {0x00, 0x01, 0x02, 0x04, 0x00},
/* 0x61 */ {0x20, 0x54, 0x54, 0x54, 0x78},
/* 0x62 */ {0x7f, 0x48, 0x44, 0x44, 0x38},
/* 0x63 */ {0x38, 0x44, 0x44, 0x44, 0x28},
/* 0x64 */ {0x38, 0x44, 0x44, 0x48, 0x7f},
/* 0x65 */ {0x38, 0x54, 0x54, 0x54, 0x18},
/* 0x66 */ {0x08, 0x7e, 0x09, 0x09, 0x02},
/* 0x67 */ {0x0c, 0x52, 0x52, 0x52, 0x3e},
/* 0x68 */ {0x7f, 0x08, 0x04, 0x04, 0x78},
/* 0x69 */ {0x00, 0x44, 0x7d, 0x40, 0x00},
/* 0x6A */ {0x20, 0x40, 0x40, 0x3d, 0x00},
/* 0x6B */ {0x7f, 0x10, 0x28, 0x44, 0x00},
/* 0x6C */ {0x00, 0x41, 0x7f, 0x40, 0x00},
/* 0x6D */ {0x7c, 0x04, 0x18, 0x04, 0x78},
/* 0x6E */ {0x7c, 0x08, 0x04, 0x04, 0x78},
/* 0x6F */ {0x38, 0x44, 0x44, 0x44, 0x38},
/* 0x70 */ {0xfc, 0x14, 0x14, 0x14, 0x08},
/* 0x71 */ {0x08, 0x14, 0x14, 0x18, 0x7c},
/* 0x72 */ {0x7c, 0x08, 0x04, 0x04, 0x08},
/* 0x73 */ {0x48, 0x54, 0x54, 0x54, 0x20},
/* 0x74 */ {0x04, 0x3f, 0x44, 0x40, 0x20},
/* 0x75 */ {0x3c, 0x40, 0x40, 0x20, 0x7c},
/* 0x76 */ {0x1c, 0x20, 0x40, 0x20, 0x1c},
/* 0x77 */ {0x3c, 0x40, 0x38, 0x40, 0x3c},
/* 0x78 */ {0x44, 0x28, 0x10, 0x28, 0x44},
/* 0x79 */ {0x0c, 0x50, 0x50, 0x50, 0x3c},
/* 0x7A */ {0x44, 0x64, 0x54, 0x4c, 0x44},
/* 0x7B */ {0x00, 0x08, 0x36, 0x41, 0x00},
/* 0x7C */ {0x00, 0x00, 0x7F, 0x00, 0x00},
/* 0x7D */ {0x00, 0x41, 0x36, 0x08, 0x00},
/* 0x7E */ {0x08, 0x06, 0x08, 0x30, 0x08},
/* 0x7F */ {0x3E, 0x36, 0x2A, 0x36, 0x3E},
};

void display_char(int c) {
	__u8 *b;
	const __u8 *f, *fend;
	size_t i, j;

	if (c == '\n') {
		display_x = 0;
		display_y++;
	}

	if ((unsigned int) display_x == DISPLAY_CHAR_WIDTH) {
		display_x = 0;
		display_y++;
	};

	if ((unsigned int) display_y == DISPLAY_CHAR_DEPTH) {
		for (i = 0; i < NXT_LCD_DEPTH - 1; i++) {
			for (j = 0; j < NXT_LCD_WIDTH; j++) {
				display_buffer[i][j] = display_buffer[i + 1][j];
			}
		}
		display_y = DISPLAY_CHAR_DEPTH - 1;
		for (j = 0; j < NXT_LCD_WIDTH; j++) {
			display_buffer[display_y][j] = 0;
		}
	};

	if ((unsigned int) c < N_CHARS) {
		b = &display_buffer[display_y][display_x * CELL_WIDTH];
		f = font[c];
		fend = f + FONT_WIDTH;

		do {
			*b++ = *f++;
		} while (f < fend);
	}
	display_x++;
	nxt_lcd_force_update();
}

void display_string(const char *str) {
	display_x = 8;
	while (*str) {
		if (*str != '\n') {
			display_char(*str);
		} else {
			display_x = 8;
			display_y++;
		}
		str++;
	}
}

void display_clear_screen(void) {
	memset((void *) display_buffer, 0x0, NXT_LCD_WIDTH * NXT_LCD_DEPTH);
	display_x = 0;
	display_y = 0;
	nxt_lcd_force_update();
}

int display_draw(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t *buff) {
   	uint32_t x_offset, y_offset, i, j, k;
   	y *= 8;
   	width *= 8;
   	if ((x > NXT_LCD_WIDTH) || (y > 64)) {
   		return 0;
   	}

   	width = min((NXT_LCD_WIDTH - x), width);
   	height = min((64 - y), height);

   	for (y_offset = 0; y_offset < height; y_offset += 8) {
		for (x_offset = 0; x_offset < width; x_offset++) {
			i = (y + y_offset) >> 3;
			j = x + x_offset;
			k = (y_offset >> 3) + x_offset;
   			display_buffer[i][j] = buff[k];
		}
   	}
	nxt_lcd_force_update();
	return 0;
}

/* q == 1 - color is black */

int display_part(uint8_t x, uint8_t y, uint8_t part_of_byte, uint8_t q) {
	uint8_t i;
	i = (1 << part_of_byte) - 1;
	display_buffer[y][x] = (q == 1 ? ~i : i);
	return 0;
}

int display_little_field(uint8_t x, uint8_t y, uint8_t height, uint8_t offset,  uint8_t q) {
	uint8_t i;
	i = ((1 << height) - 1) << offset;
	display_buffer[y][x] = (q == 1 ? i : ~i );
	return 0;
}


int display_fill(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t q) {
	uint32_t x_offset, y_offset;
	uint8_t up_offset, up_height, up_whole_offset, whole_field_y, under_height, x_fill, y_fill;
	uint8_t t;
	up_whole_offset = y >> 3;
	up_offset = y % 8;
	up_height = 8 - up_offset;
	if (height <= up_height) {
		for (x_offset = 0; x_offset < width; x_offset++) {
			x_fill = x + x_offset;
			display_little_field(x_fill, up_whole_offset, height, up_offset, q);
		}
	} else {
		whole_field_y = (height - up_height) >> 3;
		under_height = (height - up_height) % 8;
		for (x_offset = 0; x_offset < width; x_offset++) {
			x_fill = x + x_offset;
			display_part(x_fill, up_whole_offset, up_offset, q);
			for (y_offset = 0; y_offset < whole_field_y; y_offset++) {
				y_fill = up_whole_offset+1 + y_offset;
				display_buffer[y_fill][x_fill] = (q == 0 ? 0 : 0xFF);
			}
			if (under_height != 0) {
				t = (q + 1) % 2;
				display_part(x_fill, up_whole_offset+whole_field_y+1, under_height, t);
			}
		}
	}
	nxt_lcd_force_update();
	return 0;
}


void tab_display(const char *str) {
	int i = 0;
	display_x = 2;
	while (*str && ( i < 13)) {
		if (*str != '\n') {
			display_char(*str);
		}
		str++;
		i++;
	}
	display_y++;
}

