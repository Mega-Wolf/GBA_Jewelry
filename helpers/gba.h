#pragma once

#include "macro_helper.h"

#define ALIGN16 __attribute__ ((aligned (16)))
#define ALIGN8 __attribute__ ((aligned ( 8)))
#define ALIGN4 __attribute__ ((aligned ( 4)))
#define ALIGN2 __attribute__ ((aligned ( 2)))

// Variables

u16 KeyCurrent;
u16 KeyPrevious;





//                            // Bus size


#define SYSTEM_ROM 0x00000000 // 32 bit
#define     EW_RAM 0x02000000 // 16 bit
#define     IW_RAM 0x03000000 // 32 bit
#define     IO_RAM 0x04000000 // 16 bit
#define    PAL_RAM 0x05000000 // 16 bit
#define      V_RAM 0x06000000 // 16 bit
#define        OAM 0x07000000 // 32 bit
#define    PAK_ROM 0x08000000 // 16 bit
#define   CART_ROM 0x0E000000 //  8 bit

#define SYSTEM_ROM_LENGTH  16 * kB
#define     EW_RAM_LENGTH 256 * kB
#define     IW_RAM_LENGTH  32 * kB
#define     IO_RAM_LENGTH   1 * kB
#define    PAL_RAM_LENGTH   1 * kB
#define      V_RAM_LENGTH  96 * kB
#define        OAM_LENGTH   1 * kB

#define SYSTEM_ROM_PAST_END (SYSTEM_ROM + SYSTEM_ROM_LENGTH)
#define     EW_RAM_PAST_END (    EW_RAM +     EW_RAM_LENGTH)
#define     IW_RAM_PAST_END (    IW_RAM +     IW_RAM_LENGTH)
#define     IO_RAM_PAST_END (    IO_RAM +     IO_RAM_LENGTH)
#define    PAL_RAM_PAST_END (   PAL_RAM +    PAL_RAM_LENGTH)
#define      V_RAM_PAST_END (     V_RAM +      V_RAM_LENGTH)
#define        OAM_PAST_END (       OAM +        OAM_LENGTH)

// These two are variable
// #define    PAK_ROM_LENGTH * kB
// #define   CART_ROM_LENGTH * kB

#define REGISTER(type, start, offset) *(type*) ((start) + (offset))


#define REG_DISPCTRL REGISTER(vu32, IO_RAM, 0x0000)
#define REG_DISPSTAT REGISTER(vu16, IO_RAM, 0x0004)
#define REG_VCOUNT   REGISTER(vu16, IO_RAM, 0x0006)

#define REG_BG0_CTRL  REGISTER(vu16, IO_RAM, 0x0008)
#define REG_BG1_CTRL  REGISTER(vu16, IO_RAM, 0x000A)
#define REG_BG2_CTRL  REGISTER(vu16, IO_RAM, 0x000C)
#define REG_BG3_CTRL  REGISTER(vu16, IO_RAM, 0x000E)
#define REG_BG0_HOFS  REGISTER(vu16, IO_RAM, 0x0010)
#define REG_BG0_VOFS  REGISTER(vu16, IO_RAM, 0x0012)
#define REG_BG1_HOFS  REGISTER(vu16, IO_RAM, 0x0014)
#define REG_BG1_VOFS  REGISTER(vu16, IO_RAM, 0x0016)
#define REG_BG2_HOFS  REGISTER(vu16, IO_RAM, 0x0018)
#define REG_BG2_VOFS  REGISTER(vu16, IO_RAM, 0x001A)
#define REG_BG3_HOFS  REGISTER(vu16, IO_RAM, 0x001C)
#define REG_BG3_VOFS  REGISTER(vu16, IO_RAM, 0x001E)

#define REG_TM0_DATA REGISTER(vu16, IO_RAM, 0x0100)
#define REG_TM0_CTRL REGISTER(vu16, IO_RAM, 0x0102)
#define REG_TM1_DATA REGISTER(vu16, IO_RAM, 0x0104)
#define REG_TM1_CTRL REGISTER(vu16, IO_RAM, 0x0106)
#define REG_TM2_DATA REGISTER(vu16, IO_RAM, 0x0108)
#define REG_TM2_CTRL REGISTER(vu16, IO_RAM, 0x010A)
#define REG_TM3_DATA REGISTER(vu16, IO_RAM, 0x010C)
#define REG_TM3_CTRL REGISTER(vu16, IO_RAM, 0x010E)

#define REG_KEYINPUT REGISTER(vu16, IO_RAM, 0x0130)
#define REG_KEYCTRL  REGISTER(vu16, IO_RAM, 0x0132)

#define REG_IE       REGISTER(vu16, IORAM, 0x0200)
#define REG_IF       REGISTER(vu16, IORAM, 0x0202)
#define REG_IME      REGISTER(vu16, IORAM, 0x0208)

#define IRQ_VBLANK      (1 <<  0) // also requires REG_DIPSTAT{3}
#define IRQ_HBLANK      (1 <<  1) // also requires REG_DIPSTAT{4}; after HDRaw; so effects next line
#define IRQ_VCOUNT      (1 <<  2) // also requires REG_DIPSTAT{5}; beginning of scanline
#define IRQ_TIMER0      (1 <<  3) // also requires REG_TMxCTRL; Happens when timer overflows
#define IRQ_TIMER1      (1 <<  4)
#define IRQ_TIMER2      (1 <<  5)
#define IRQ_TIMER3      (1 <<  6)
#define IRQ_COM         (1 <<  7) // Serial communication; might also need REG_SCCTRL{E}
#define IRQ_DMA0        (1 <<  8) // also requires (REG_DMAxCTRL); raised when full transfer is complete
#define IRQ_DMA1        (1 <<  9)
#define IRQ_DMA2        (1 << 10)
#define IRQ_DMA3        (1 << 11)
#define IRQ_KEYPAD      (1 << 12) // also requires REG_KEYCTRL{E}; raised when either any or all of the keys are pressed
#define IRQ_GAEPAK      (1 << 13) // raised when cart is removed from GBA

#define TIMER_FREQ_1    0x0000
#define TIMER_FREQ_64   0x0001
#define TIMER_FREQ_256  0x0002
#define TIMER_FREQ_1024 0x0003

#define TIMER_CASCADE (1 << 2)
#define TIMER_IRQ     (1 << 6)
#define TIMER_ENABLE  (1 << 7)

// Keys
#define KEY_A      (1 <<  0)
#define KEY_B      (1 <<  1)
#define KEY_SELECT (1 <<  2)
#define KEY_START  (1 <<  3)
#define KEY_RIGHT  (1 <<  4)
#define KEY_LEFT   (1 <<  5)
#define KEY_UP     (1 <<  6)
#define KEY_DOWN   (1 <<  7)
#define KEY_R      (1 <<  8)
#define KEY_L      (1 <<  9)

#define KCTRL_IRQ   (1 << 14)
#define KCTRL_AND   (1 << 15)

#define KEY_MASK    0b0000001111111111
#define KEY_KEYPAD  0b0000000011110000


#define BG_PRIO0      (0b00 << 0)
#define BG_PRIO1      (0b01 << 0)
#define BG_PRIO2      (0b10 << 0)
#define BG_PRIO3      (0b11 << 0)
#define BG_CHAR_BASE0 (0b00 << 2)
#define BG_CHAR_BASE1 (0b01 << 2)
#define BG_CHAR_BASE2 (0b10 << 2)
#define BG_CHAR_BASE3 (0b11 << 2)

#define BG_MOSAIC       (1 << 6)
#define BG_COLOR_MODE_8 (1 << 7)
#define BG_COLOR_MODE_4 0

#define BG_SPRITE_BASE0 (0 << 8)
#define BG_SPRITE_BASE1 (1 << 8)
#define BG_SPRITE_BASE2 (2 << 8)
#define BG_SPRITE_BASE3 (3 << 8)
#define BG_SPRITE_BASE4 (4 << 8)
#define BG_SPRITE_BASE5 (5 << 8)
#define BG_SPRITE_BASE6 (6 << 8)
#define BG_SPRITE_BASE7 (7 << 8)
#define BG_SPRITE_BASE8 (8 << 8)
#define BG_SPRITE_BASE9 (9 << 8)
#define BG_SPRITE_BASE10 (10 << 8)
#define BG_SPRITE_BASE11 (11 << 8)
#define BG_SPRITE_BASE12 (12 << 8)
#define BG_SPRITE_BASE13 (13 << 8)
#define BG_SPRITE_BASE14 (14 << 8)
#define BG_SPRITE_BASE15 (15 << 8)
#define BG_SPRITE_BASE16 (16 << 8)
#define BG_SPRITE_BASE17 (17 << 8)
#define BG_SPRITE_BASE18 (18 << 8)
#define BG_SPRITE_BASE19 (19 << 8)
#define BG_SPRITE_BASE20 (20 << 8)
#define BG_SPRITE_BASE21 (21 << 8)
#define BG_SPRITE_BASE22 (22 << 8)
#define BG_SPRITE_BASE23 (23 << 8)
#define BG_SPRITE_BASE24 (24 << 8)
#define BG_SPRITE_BASE25 (25 << 8)
#define BG_SPRITE_BASE26 (26 << 8)
#define BG_SPRITE_BASE27 (27 << 8)
#define BG_SPRITE_BASE28 (28 << 8)
#define BG_SPRITE_BASE29 (29 << 8)
#define BG_SPRITE_BASE30 (30 << 8)
#define BG_SPRITE_BASE31 (31 << 8)

#define BG_AFFINE  (1 << 13)
#define BG_REG_32_32 0b0000000000000000
#define BG_REG_64_32 0b0100000000000000
#define BG_REG_32_64 0b1000000000000000
#define BG_REG_64_64 0b1100000000000000
#define BG_AFF_16_16   0b0000000000000000
#define BG_AFF_32_32   0b0100000000000000
#define BG_AFF_64_64   0b1000000000000000
#define BG_AFF_128_128 0b1100000000000000

// --- REG_DISPCTRL defines ---
#define DCTRL_MODE0 0x0000
#define DCTRL_MODE1 0x0001
#define DCTRL_MODE2 0x0002
#define DCTRL_MODE3 0x0003
#define DCTRL_MODE4 0x0004
#define DCTRL_MODE5 0x0005

// Background layers - object layers
#define DCTRL_BG0   0x0100
#define DCTRL_BG1   0x0200
#define DCTRL_BG2   0x0400
#define DCTRL_BG3   0x0800
#define DCTRL_OBJ   0x1000

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 160

#define VIDEO_MEM ((u16*) V_RAM)

typedef u16 color;

inline color RGB15(u32 r, u32 g, u32 b) {
    return r | (g << 5) | (b << 10);
}

#define RGB_RED     RGB15(31,  0,  0)
#define RGB_LIME    RGB15( 0, 31,  0)
#define RGB_BLUE    RGB15( 0,  0, 31)

#define RGB_WHITE   RGB15(31, 31, 31)
#define RGB_BLACK   RGB15( 0,  0,  0)

#define RGB_CYAN    RGB15( 0, 31, 31)
#define RGB_YELLOW  RGB15(31, 31,  0)
#define RGB_MAGENTA RGB15(31,  0, 31)

#define RGB_GREY    RGB15(15, 15, 15)
#define RGB_ROSE    RGB15(31, 15, 15)
#define RGB_ORANGE  RGB15(31, 15,  0)

inline void Mode3Plot(int32 x, int32 y, color clr) {
    VIDEO_MEM[INDEX_2D(x, y, SCREEN_WIDTH)] = clr;
}

inline void KeyPoll() {
    KeyPrevious = KeyCurrent;
    KeyCurrent = ~REG_KEYINPUT & KEY_MASK; // Is the and necessary here; as far as I thought, the front bits are always correct
}

//inline u32 KeyCurrentState()  { return KeyCurrent; }
//inline u32 KeyPreviousState() { return KeyPrevious; }

inline u32 KeyIsDown (u32 key) { return  KeyCurrent  & key; }
inline u32 KeyIsUp   (u32 key) { return ~KeyCurrent  & key; }
inline u32 KeyWasDown(u32 key) { return  KeyPrevious & key; }
inline u32 KeyWasUp  (u32 key) { return ~KeyPrevious & key; }

inline u32 KeyPressedDown  (u32 key) { return (~KeyPrevious &  KeyCurrent) & key; }
inline u32 KeyReleased     (u32 key) { return ( KeyPrevious & ~KeyCurrent) & key; }
inline u32 KeyHeldDown     (u32 key) { return ( KeyPrevious &  KeyCurrent) & key; }
inline u32 KeyTransitioned (u32 key) { return ( KeyPrevious ^  KeyCurrent) & key; }

inline int32 KeyTriBool(u32 state, int32 positiveButton, int32 negativeButton) {
    return ((state >> positiveButton) & 1) - ((state >> negativeButton) & 1);
}

#define KEY_IDX_A      0
#define KEY_IDX_B      1
#define KEY_IDX_SELECT 2
#define KEY_IDX_START  3
#define KEY_IDX_RIGHT  4
#define KEY_IDX_LEFT   5
#define KEY_IDX_UP     6
#define KEY_IDX_DOWN   7
#define KEY_IDX_R      8
#define KEY_IDX_L      9

inline int32 KeyTriX()        { return KeyTriBool(KeyCurrent, KEY_IDX_RIGHT, KEY_IDX_LEFT); } // left .. right
inline int32 KeyTriY()        { return KeyTriBool(KeyCurrent, KEY_IDX_DOWN,  KEY_IDX_UP); }   //   up .. down
inline int32 KeyTriShoulder() { return KeyTriBool(KeyCurrent, KEY_IDX_R,     KEY_IDX_L); }    //    L .. R
inline int32 KeyTriAB()       { return KeyTriBool(KeyCurrent, KEY_IDX_A,     KEY_IDX_B); }    //    B .. A


struct tile {
    u32 Data[8]; // 4 * 8 * 8 bit
};

typedef tile tile4;

struct tile8 {
    u32 Data[2 * 8]; // 8 * 8 * 8 bit
};

typedef u16 scr_entry;
typedef scr_entry screenblock[1024];

typedef scr_entry screen_small[32][32];
typedef scr_entry screen_big_small[64][32];
typedef scr_entry screen_small_big[32][64];
typedef scr_entry screen_big[64][64];

typedef tile4 tileblock[512];
typedef tile8 tileblock8[256];

#define TILE_MEM  ((volatile tileblock*) V_RAM)
#define TILE8_MEM ((volatile tileblock*) V_RAM)
#define SE_MEM    ((volatile screenblock*) V_RAM)
#define SE_S_MEM    ((volatile screen_small*) V_RAM)

typedef color color_line[16];

#define BG_PALETTE_MEM ((volatile color*) (PAL_RAM+0x0000))
#define BG_PALETTE_LINE_MEM ((volatile color_line*) (PAL_RAM+0x0000))
#define SP_PALETTE_MEM ((volatile color*) (PAL_RAM+0x0200))
#define SP_PALETTE_LINE_MEM ((volatile color_line*) (PAL_RAM+0x0200))

struct point_s32 {
    s32 X;
    s32 Y;
};

point_s32 operator+(point_s32 vec1, point_s32 vec2) {
    return point_s32 { vec1.X + vec2.X, vec1.Y + vec2.Y };
}

point_s32 operator-(point_s32 vec1, point_s32 vec2) {
    return point_s32 { vec1.X - vec2.X, vec1.Y - vec2.Y };
}

inline void ProfilerStart() {
    REG_TM2_DATA = 0;
    REG_TM3_DATA = 0;
    REG_TM2_CTRL = 0;
    REG_TM3_CTRL = 0;
    REG_TM3_CTRL = TIMER_ENABLE | TIMER_CASCADE; // I first disable them because that will reset them
    REG_TM2_CTRL = TIMER_ENABLE;
}

inline u32 ProfilerEnd() {
    REG_TM2_CTRL = 0;
    return (REG_TM3_DATA << 16) | REG_TM2_DATA;
}

struct obj_attr {
    u16 Attribute0;
    u16 Attribute1;
    u16 Attribute2;
    u16 Fill;
} ALIGN4; // TODO: Why 4; why not 8


struct obj_affine {
    u16 Fill0[3];
    s16 PA;

    u16 Fill1[3];
    s16 PB;

    u16 Fill2[3];
    s16 PC;

    u16 Fill3[3];
    s16 PD;
} ALIGN4;

#define OAM_SPRITE     ((volatile obj_attr*) (OAM))
#define OAM_SPRITE_AFF ((volatile obj_affine*) (OAM))

void OAMWriteSprites(obj_attr* data, int32 count) {
    inc0(i,   count) {
        OAM_SPRITE[i].Attribute0 = data[i].Attribute0;
        OAM_SPRITE[i].Attribute1 = data[i].Attribute1;
        OAM_SPRITE[i].Attribute2 = data[i].Attribute2;
        OAM_SPRITE[i].Fill       = data[i].Fill;
    }
}

#define ATTR0_Y  0b0000000011111111

#define ATTR0_REG      (0b00 << 8)
#define ATTR0_AFF      (0b01 << 8)
#define ATTR0_HIDE     (0b10 << 8)
#define ATTR0_AFFL_DBL (0b11 << 8)
#define ATTR0_TYPE     (0b11 << 8) // The category of the stuff before

//#define ATTR0_NORMAL (0b00 << 10)
#define ATTR0_ALPHA    (0b01 << 10)
#define ATTR0_OBJ_WIN  (0b10 << 10)
//#define ATTR0_       (0b11 << 10)
#define ATTR0_MOSAIC   (1 << 11)
#define ATTR0_4BPP     0
#define ATTR0_8BPP     (1 << 13)
#define ATTR0_SQUARE   (0b00 << 14)
#define ATTR0_WIDE     (0b01 << 14)
#define ATTR0_TALL     (0b10 << 14)
//#define ATTR0_       (0b11 << 14)
#define ATTR0_SHAPE_MASK (0b11 << 14)

#define ATTR1_X       0b0000000111111111
#define ATTR1_AFF_IDX 0b0011111000000000
#define ATTR1_HF      (1 << 12)
#define ATTR1_VF      (1 << 13)
#define ATTR1_SIZE0   (0b00 << 14)
#define ATTR1_SIZE1   (0b01 << 14)
#define ATTR1_SIZE2   (0b10 << 14)
#define ATTR1_SIZE3   (0b11 << 14)
#define ATTR1_SIZE_MASK (0b11 << 14)



//shape\size	00	    01	    10	    11
//00 SQUARE     8x8     16x16	32x32	64x64
//01 WIDE       16x8	32x8	32x16	64x32
//10 TALL       8x16	8x32	16x32	32x64

#define ATTR2_TID       0b0000001111111111
#define ATTR2_PRIO0     (0b00 << 10)
#define ATTR2_PRIO1     (0b01 << 10)
#define ATTR2_PRIO2     (0b10 << 10)
#define ATTR2_PRIO3     (0b11 << 10)
#define ATTR2_PALBANK   0b1111000000000000
#define ATTR2_PALBANK0 ( 0 << 12)
#define ATTR2_PALBANK1 ( 1 << 12)
#define ATTR2_PALBANK2 ( 2 << 12)
#define ATTR2_PALBANK3 ( 3 << 12)
#define ATTR2_PALBANK4 ( 4 << 12)
#define ATTR2_PALBANK5 ( 5 << 12)
#define ATTR2_PALBANK6 ( 6 << 12)
#define ATTR2_PALBANK7 ( 7 << 12)
#define ATTR2_PALBANK8 ( 8 << 12)
#define ATTR2_PALBANK9 ( 9 << 12)
#define ATTR2_PALBANK10 (10 << 12)
#define ATTR2_PALBANK11 (11 << 12)
#define ATTR2_PALBANK12 (12 << 12)
#define ATTR2_PALBANK13 (13 << 12)
#define ATTR2_PALBANK14 (14 << 12)
#define ATTR2_PALBANK15 (15 << 12)




// Sound stuff

#define REG_SND1_SWEEP REGISTER(vu16, IO_RAM, 0x60)
#define REG_SND1_CTRL  REGISTER(vu16, IO_RAM, 0x62)
#define REG_SND1_FREQ  REGISTER(vu16, IO_RAM, 0x64)

#define REG_SND2_CTRL  REGISTER(vu16, IO_RAM, 0x68)
#define REG_SND2_FREQ  REGISTER(vu16, IO_RAM, 0x6C)

#define REG_SND3_MODE  REGISTER(vu16, IO_RAM, 0x70)
#define REG_SND3_CTRL  REGISTER(vu16, IO_RAM, 0x72)
#define REG_SND3_FREQ  REGISTER(vu16, IO_RAM, 0x74)

#define REG_SND4_CTRL  REGISTER(vu16, IO_RAM, 0x78)
#define REG_SND4_FREQ  REGISTER(vu16, IO_RAM, 0x7C)

#define REG_SND_DMG_CTRL REGISTER(vu16, IO_RAM, 0x80)
#define REG_SND_DS_CTRL  REGISTER(vu16, IO_RAM, 0x82)
#define REG_SND_STAT     REGISTER(vu16, IO_RAM, 0x84)
#define REG_SND_BIAS     REGISTER(vu16, IO_RAM, 0x88)

#define SND_DMG_LEFT_VOLUME  0b0000000000000111
#define SND_DMG_RIGHT_VOLUME 0b0000000001110000
#define SND_DMG_LSQR1        (1 <<  8)
#define SND_DMG_LSQR2        (1 <<  9)
#define SND_DMG_LWAVE        (1 << 10)
#define SND_DMG_LNOISE       (1 << 11)
#define SND_DMG_RSQR1        (1 << 12)
#define SND_DMG_RSQR2        (1 << 13)
#define SND_DMG_RWAVE        (1 << 14)
#define SND_DMG_RNOISE       (1 << 15)

#define SND_DS_DMG25        (0b00)
#define SND_DS_DMG50        (0b01)
#define SND_DS_DMG100       (0b10)
//#define SND_DS_DMG        (0b1)
#define SND_DS_A50          0
#define SND_DS_A100         (1 <<  2)
#define SND_DS_B50          0
#define SND_DS_B100         (1 <<  3)
#define SND_DS_AR           (1 <<  8)
#define SND_DS_AL           (1 <<  9)
#define SND_DS_ATMR0        0
#define SND_DS_ATMR1        (1 << 10)
#define SND_DS_ARESET       (1 << 11)
#define SND_DS_BR           (1 << 12)
#define SND_DS_BL           (1 << 13)
#define SND_DS_BTMR0        0
#define SND_DS_BTMR1        (1 << 14)
#define SND_DS_BRESET       (1 << 15)

#define SND_STAT_SQR1       (1 << 0) // READ_ONLY
#define SND_STAT_SQR2       (1 << 1) // READ_ONLY
#define SND_STAT_WAVE       (1 << 2) // READ_ONLY
#define SND_STAT_NOISE      (1 << 3) // READ_ONLY
#define SND_STAT_ENABLE     (1 << 7) // SET BEFORE ANYTHING ELSE

#define SND_CTRL_LENGTH     0b0000000000111111
#define SND_CTRL_DUTY1_8    (0b00 << 6)
#define SND_CTRL_DUTY1_4    (0b01 << 6)
#define SND_CTRL_DUTY1_2    (0b10 << 6)
#define SND_CTRL_DUTY3_4    (0b11 << 6)
#define SND_CTRL_TIME0      (   0 << 8)
#define SND_CTRL_TIME1      (   1 << 8)
#define SND_CTRL_TIME2      (   2 << 8)
#define SND_CTRL_TIME3      (   3 << 8)
#define SND_CTRL_TIME4      (   4 << 8)
#define SND_CTRL_TIME5      (   5 << 8)
#define SND_CTRL_TIME6      (   6 << 8)
#define SND_CTRL_TIME7      (   7 << 8)
#define SND_CTRL_DEC        0
#define SND_CTRL_INC        ( 1 << 11)
#define SND_CTRL_INIT_VOL0  ( 0 << 12)
#define SND_CTRL_INIT_VOL1  ( 1 << 12)
#define SND_CTRL_INIT_VOL2  ( 2 << 12)
#define SND_CTRL_INIT_VOL3  ( 3 << 12)
#define SND_CTRL_INIT_VOL4  ( 4 << 12)
#define SND_CTRL_INIT_VOL5  ( 5 << 12)
#define SND_CTRL_INIT_VOL6  ( 6 << 12)
#define SND_CTRL_INIT_VOL7  ( 7 << 12)
#define SND_CTRL_INIT_VOL8  ( 8 << 12)
#define SND_CTRL_INIT_VOL9  ( 9 << 12)
#define SND_CTRL_INIT_VOL10 (10 << 12)
#define SND_CTRL_INIT_VOL11 (11 << 12)
#define SND_CTRL_INIT_VOL12 (12 << 12)
#define SND_CTRL_INIT_VOL13 (13 << 12)
#define SND_CTRL_INIT_VOL14 (14 << 12)
#define SND_CTRL_INIT_VOL15 (15 << 12)

#define SND_FREQ_SOUND_RATE 0b0000011111111111
#define SND_FREQ_TIMED      (1 << 14)
#define SND_FREQ_RESET      (1 << 15)

#define SND_SWEEP_NUMBER    0b0000000000000111
#define SND_SWEEP_INC       0
#define SND_SWEEP_DEC       (1 << 3)
#define SND_SWEEP_TIME0     (0 << 4)
#define SND_SWEEP_TIME1     (1 << 4)
#define SND_SWEEP_TIME2     (2 << 4)
#define SND_SWEEP_TIME3     (3 << 4)
#define SND_SWEEP_TIME4     (4 << 4)
#define SND_SWEEP_TIME5     (5 << 4)
#define SND_SWEEP_TIME6     (6 << 4)
#define SND_SWEEP_TIME7     (7 << 4)

enum note_id {
    NOTE_C=0, NOTE_CIS, NOTE_D,   NOTE_DIS, 
    NOTE_E,   NOTE_F,   NOTE_FIS, NOTE_G, 
    NOTE_GIS, NOTE_A,   NOTE_BES, NOTE_B
};

// Rates for traditional notes in octave +5
const u32 soundRates[12] = {
    8013, 7566, 7144, 6742, // C , C#, D , D#
    6362, 6005, 5666, 5346, // E , F , F#, G
    5048, 4766, 4499, 4246  // G#, A , A#, B
};

#define SND_RATE(note, oct) ( 2048-(soundRates[note]>>(4+(oct))) )

inline void DebugWriteCharacter(int32 x, int32 y, char c, int palette) {
    SE_S_MEM[31][y][x] = (c - 32) | (palette << 12);
}

inline void DebugWriteString(int32 x, int32 y, char* str, int palette) {
    for (char* cp = str; *cp; ++cp) {
        DebugWriteCharacter(x++, y, *cp, palette);
    }
}

inline void BusyWaitVsync() {
    u32 cycles = ProfilerEnd();
    if (cycles > 1000) {
        char dummy[64];
        mysnprintf(dummy, ArrayCount(dummy), "%u       ", cycles);
        DebugWriteString(0, 10, dummy, 12);
    }

    while (REG_VCOUNT >= 160); // wait till VDraw
    while (REG_VCOUNT < 160);  // wait till VBlank
    ProfilerStart();
}