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
/* 0x63 */ {0x30, 0x48, 0x48, 0x48, 0x20},
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
	int i, j;

	if (c == '\n') {
		display_x = 0;
		display_y ++;
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
		} while( f < fend);
	}
	display_x++;
	nxt_lcd_force_update();
}
  
void display_string(const char *str) {
	while (*str) {
		if (*str != '\n') {
			display_char(*str);
		} else {
			display_x = 0;
			display_y++;
		}
		str++;
	}
}

void display_clear_screen(void) {
	memset((void *)display_buffer, 0x0, NXT_LCD_WIDTH * NXT_LCD_DEPTH);
	nxt_lcd_force_update();
}

int display_draw(uint8_t x, uint8_t y, uint8_t width,
			uint8_t height, uint8_t *buff) {
   	uint32_t x_offset, y_offset, i, j, k;
   	y *= 8;
   	width *= 8;
   	if((x > NXT_LCD_WIDTH) || (y > 64)) {
   		return 0;
   	}

   	width = min((NXT_LCD_WIDTH - x), width);
   	height = min((64 - y), height);

   	for(y_offset = 0; y_offset < height; y_offset += 8) {
		for(x_offset = 0; x_offset < width; x_offset ++) {
			i = (y + y_offset) >> 3;
			j = x + x_offset;
			k = (y_offset >> 3) + x_offset;
   			display_buffer[i][j] = buff[k];
		}
   	}
	nxt_lcd_force_update();
	return 0;
}

static const uint8_t graph_buff[256] = {
	      {0x00}, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
               0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A,0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
               0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
               0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A,0x3B, 0x3C, 0x3D, 0x3E, 0x3F,

               0x40, 0X41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A,0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
               0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A,0x5B, 0x5C, 0x5D, 0x5E, 0x5F,               
               0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A,0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
               0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A,0x7B, 0x7C, 0x7D, 0x7E, 0x7F,

               0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A,0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
               0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A,0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
               0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA,0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
               0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA,0xBB, 0xBC, 0xBD, 0xBE, 0xBF,

               0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA,0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
               0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA,0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
               0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA,0xEB, 0xEC, 0xED, 0xEE, 0xEF,
               0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA,0xFB, 0xFC, 0xFD, {0xFE}, {0xFF}
};

static const uint8_t graph_buff_0[8] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}; 
static const uint8_t graph_buff_1[8] = {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80}; 
static const uint8_t graph_buff_2[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
/*int const_init(void){
      // uint8_t buff[256];
       for (int i = 0; i<; i++){
               graph_buff[i] = i;
       }
       return 0;
}*/

/* q == 0 - color is black */

int nxt_color(int i, int q) {
       if (q==0){
               i = 255-i;
       }
       return i;
}

int pow(int t, int k) {
  int res = 1;
  while (k) {
	if (k & 1) res *= t;
	t *= t;
	k >>= 1;
  }
  return res;
}
#if 0
int display_fill(uint8_t x, uint8_t y, uint8_t width, uint8_t height, int q)
{
       int i ,j, k;
       uint32_t x_offset, y_offset;
       uint8_t indent_all, indent_part, height_on, width_part_on, width_all, width_part_under;
       /* integral part of y */
       indent_all = y >> 3;
       /* fraction part of y  - indent from up field*/
       indent_part = y % 8;
       /* fill under below field*/
       if (height > (8 - indent_part))  {
               height_on = 8 - indent_part;
               /*number of full fill field*/
               width_all = (height - height_on) >> 3;
               /*under full fill field*/
               width_part_under = height - height_on - 8*width_all;
               i = pow(2,height_on) - 1 ;
               j = 255 - pow(2, width_part_under);
               k = 0;
               nxt_color(i, q);
               nxt_color(j, q);
               nxt_color(k, q);
               for(x_offset = 0; x_offset < width; x_offset ++) {
                               display_draw(x+x_offset, indent_all, 1, 1, graph_buff_0[1]);
                               display_draw(x+x_offset, indent_all + 1 + width_all, 1, 1, graph_buff_0[2]);
                               for(y_offset = 0; y_offset < width_all; y_offset += 1){
                                       display_draw(x+x_offset, indent_all + 1 + y_offset, 1, 1, graph_buff_0[3]);
                               }
               }
       }
       else {
               indent_part = height;
               /*number of full fill field*/
               width_all = 0;
               i = 255-(pow(2,indent_part)+pow(2,width));
               nxt_color(i, q);
               for(x_offset = 0; x_offset < width; x_offset ++) {
                       display_draw(x+x_offset, indent_all, 1, 1, graph_buff[i]);
               }
       }
       //nxt_lcd_force_update();
       return 0;
}
#else

/*int display_part(uint8_t x, uint8_t y, uint8_t width, uint8_t height, int quint8_t x, uint8_t y, uint8_t width, uint8_t height, int q){
	
	return 0; 
}*/
/*когда всё заработает, я уберу русские коментарии*/
int display_fill(uint8_t x, uint8_t y, uint8_t width, uint8_t height, int q){
	uint32_t x_offset, y_offset;
	uint8_t col;
	if(q==0){
		col = 0xFF;
	}
	else {
		col = 0x00;
	}
	uint8_t up_offset, up_higth, up_hole_offset, hole_fild, under_higth, hole_fild_x, r_offset_x;
	up_hole_offset = y >> 3; //колличество целых полей по 8 бит, которые надо отступить от верха экрана
	up_offset = y % 8; //колличество пикселей, которые надо отступить от конца байта
	up_higth = 8 - up_offset;// колличество пикселей, ктоорые должнны быть снизу закрашены
	hole_fild = (height - up_higth) >> 3;//колличество целых байт, которые должны быть закрашены
	under_higth = height - up_higth - 8 * hole_fild; //колличество пикселей, которые должны быть закрашены в верхней части 
	hole_fild_x = width >> 3;//колличество целых восьмёрок в строке
	r_offset_x = width % 8;//остаток
	for(int i=0; i < hole_fild_x; i++) {
		display_draw(x+i*8, up_hole_offset + 1, 1, 8, &graph_buff_2[0]);
		display_draw(x+i*8, up_hole_offset, 1, 8, &graph_buff_0[0]);
		display_draw(x+i*8, up_hole_offset + hole_fild + 1, 1, 8, &graph_buff_1[0]);
	}
	display_draw(x+width-8, up_hole_offset + 1, 1, 8, &graph_buff_2[0]);
	display_draw(x+width-8, up_hole_offset, 1, 8, &graph_buff_0[0]);
	display_draw(x+width-8, up_hole_offset + hole_fild + 1, 1, 8, &graph_buff_1[0]);
	/*for(x_offset = 0; x_offset < width; x_offset ++) {
		display_part(x+x_offset, up_hole_offset, 1, 1, );
		display_part(x+x_offset, up_hole_offset + hole_fild + 1, 1, 1, ???????????);
	}*/
	return 0; 
}

#endif