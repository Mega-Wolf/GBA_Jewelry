// https://www.youtube.com/watch?v=Rj0lf46iljc
// https://github.com/JamieDStewart/GBA_VSCode_Basic/blob/master/.vscode/tasks.json

#include "helpers/macro_helper.h"

#include "helpers/mystdio.h"
#include "helpers/gba.h"

struct game_field {
    s32 Colours[20][7]; // Setting it to 20/7 for easier checks
    // TODO: The top row is not part of the game
    // Probably even y=1
};

struct tromino {
    point_s32 Position;
    s32 Colours[3];
};

game_field GameField;

tromino ActiveTromino;
tromino NextTromino;

uint32 Timer;

uint32 ClearCount;
uint32 LastJoker;

#define JOKER_NUMBER 70

void SetAllClearingToColour(uint32 (*shallClear)[19][6], uint32 colorValue) {
    inc0 (y_i,   19) {
        inc0 (x_i,   6) {
            if ((*shallClear)[y_i][x_i]) {
                SE_S_MEM[0][y_i][x_i] = 1 + (colorValue << 12);
            }
        }
    }
    BusyWaitVsync();
    BusyWaitVsync();
    BusyWaitVsync();
    BusyWaitVsync();
    BusyWaitVsync();
}

void SetAllClearingToColour(uint32 (*shallClear)[19][6]) {
    inc0 (y_i,   19) {
        inc0 (x_i,   6) {
            if ((*shallClear)[y_i][x_i]) {
                SE_S_MEM[0][y_i][x_i] = 1 + (GameField.Colours[y_i][x_i] << 12);
            }
        }
    }
    BusyWaitVsync();
    BusyWaitVsync();
    BusyWaitVsync();
    BusyWaitVsync();
    BusyWaitVsync();
}

int main() {
    REG_DISPCTRL = DCTRL_MODE0 | DCTRL_BG0;

    REG_BG0_CTRL = BG_CHAR_BASE1;

    // Setup palette
    BG_PALETTE_LINE_MEM[1][1] = RGB_RED;
    BG_PALETTE_LINE_MEM[2][1] = RGB_CYAN;
    BG_PALETTE_LINE_MEM[3][1] = RGB_YELLOW;
    BG_PALETTE_LINE_MEM[4][1] = RGB_LIME;
    BG_PALETTE_LINE_MEM[5][1] = RGB_ORANGE;
    BG_PALETTE_LINE_MEM[6][1] = RGB_MAGENTA;

    // Bonus colour
    BG_PALETTE_LINE_MEM[0][1] = RGB_GREY;

    // Game part
    TILE_MEM[1][1].Data[0] = 0x11111111;
    TILE_MEM[1][1].Data[1] = 0x10000001;
    TILE_MEM[1][1].Data[2] = 0x10111101;
    TILE_MEM[1][1].Data[3] = 0x10111101;
    TILE_MEM[1][1].Data[4] = 0x10111101;
    TILE_MEM[1][1].Data[5] = 0x10111101;
    TILE_MEM[1][1].Data[6] = 0x10000001;
    TILE_MEM[1][1].Data[7] = 0x11111111;

    // Setup screen blocks for the game border
    inc0 (y_i,   20) {
        SE_S_MEM[0][y_i][6] = 1 + (0 << 12);
        SE_S_MEM[0][y_i][31] = 1 + (0 << 12);
    }
    inc0 (x_i,   6) {
        SE_S_MEM[0][19][x_i] = 1 + (0 << 12);
    }

    // Move background
    REG_BG0_HOFS = -88;


    // Init trominos
    ActiveTromino.Colours[0] = RandRange(1, 7);
    ActiveTromino.Colours[1] = RandRange(1, 7);
    ActiveTromino.Colours[2] = RandRange(1, 7);
    ActiveTromino.Position = point_s32 { 3, 0 };
    NextTromino.Colours[0] = RandRange(1, 7);
    NextTromino.Colours[1] = RandRange(1, 7);
    NextTromino.Colours[2] = RandRange(1, 7);
    NextTromino.Position = point_s32 { 3, 0 };

    // TODO: Always show the new tromino

    Timer = 60;

    // Game Loop
    for (;;) {
        static u32 maxFrameLength = 0;
        u32 frameLength = ProfilerEnd();
        if (frameLength > maxFrameLength) {
            maxFrameLength = frameLength;
        }

        BusyWaitVsync();
        ProfilerStart();

        KeyPoll();

        // Clear old position
        SE_S_MEM[0][ActiveTromino.Position.Y    ][ActiveTromino.Position.X] = 0;
        SE_S_MEM[0][ActiveTromino.Position.Y + 1][ActiveTromino.Position.X] = 0;
        SE_S_MEM[0][ActiveTromino.Position.Y + 2][ActiveTromino.Position.X] = 0;
        
        if (KeyPressedDown(KEY_A | KEY_B)) {
            // Shuffle active tromino
            int32 last = ActiveTromino.Colours[2];
            ActiveTromino.Colours[2] = ActiveTromino.Colours[1];
            ActiveTromino.Colours[1] = ActiveTromino.Colours[0];
            ActiveTromino.Colours[0] = last;
        }

        // TODO: Delay input for D-PAD

        int32 xOffset = 0;
        if (KeyPressedDown(KEY_LEFT)) {
            --xOffset;
        }
        if (KeyPressedDown(KEY_RIGHT)) {
            ++xOffset;
        }

        if (xOffset != 0) {
            uint32 projectedX = ActiveTromino.Position.X + xOffset;
            if (projectedX >= 0 && projectedX < 6) {
                if (
                    GameField.Colours[ActiveTromino.Position.Y    ][projectedX] == 0 &&
                    GameField.Colours[ActiveTromino.Position.Y + 1][projectedX] == 0 &&
                    GameField.Colours[ActiveTromino.Position.Y + 2][projectedX] == 0
                ) {
                    ActiveTromino.Position.X = projectedX;
                }
            }
        }

        // Vertical movement
        if (--Timer == 0 || KeyPressedDown(KEY_DOWN)) {

            if (ActiveTromino.Position.Y + 2 == 19 - 1 || GameField.Colours[ActiveTromino.Position.Y + 3][ActiveTromino.Position.X] != 0) {
                // Smash to ground

                // Write to background
                GameField.Colours[ActiveTromino.Position.Y    ][ActiveTromino.Position.X] = ActiveTromino.Colours[0];
                GameField.Colours[ActiveTromino.Position.Y + 1][ActiveTromino.Position.X] = ActiveTromino.Colours[1];
                GameField.Colours[ActiveTromino.Position.Y + 2][ActiveTromino.Position.X] = ActiveTromino.Colours[2];

                // Write the tiles again, since they have been cleared before
                SE_S_MEM[0][ActiveTromino.Position.Y    ][ActiveTromino.Position.X] = 1 + (ActiveTromino.Colours[0] << 12);
                SE_S_MEM[0][ActiveTromino.Position.Y + 1][ActiveTromino.Position.X] = 1 + (ActiveTromino.Colours[1] << 12);
                SE_S_MEM[0][ActiveTromino.Position.Y + 2][ActiveTromino.Position.X] = 1 + (ActiveTromino.Colours[2] << 12);

                // NOTE: Check and clear related stuff is super expensive; always a whole frame

                bool clearedSomething;
                do { // while clearedSomething
                    uint32 shallClear[19][6] = {};
                    clearedSomething = false;

                    // Joker check
                    if (ActiveTromino.Colours[0] == 0) {
                        ActiveTromino.Colours[0] = -1;
                        shallClear[ActiveTromino.Position.Y    ][ActiveTromino.Position.X] = true;
                        shallClear[ActiveTromino.Position.Y + 1][ActiveTromino.Position.X] = true;
                        shallClear[ActiveTromino.Position.Y + 2][ActiveTromino.Position.X] = true;
                        clearedSomething = true;
                        if (ActiveTromino.Position.Y < 19 - 3) {
                            int32 touchedColour = GameField.Colours[ActiveTromino.Position.Y + 3][ActiveTromino.Position.X];
                            inc0 (y_i,   19) {
                                inc0 (x_i,   6) {
                                    if (GameField.Colours[y_i][x_i] == touchedColour) {
                                        shallClear[y_i][x_i] = true;
                                    }
                                }
                            }
                        }
                    }

                    // Horizontal checks
                    inc0 (y_i,   19) {
                        int32 lastColour = 0;
                        int32 sameAlready = 0;
                        inc0 (x_i,   7) {
                            int32 colour = GameField.Colours[y_i][x_i];
                            if (colour != 0 && colour == lastColour) {
                                ++sameAlready;
                            } else {
                                if (sameAlready >= 3) {
                                    inc (xSame_i,   x_i - sameAlready,    x_i) {
                                        clearedSomething = true;
                                        shallClear[y_i][xSame_i] = true;
                                    }
                                }
                                lastColour = colour;
                                sameAlready = 1;
                            }
                        }
                    }

                    // Vertical check
                    inc0 (x_i,   6) {
                        int32 lastColour = 0;
                        int32 sameAlready = 0;
                        inc0 (y_i,   20) {
                            int32 colour = GameField.Colours[y_i][x_i];
                            if (colour != 0 && colour == lastColour) {
                                ++sameAlready;
                            } else {
                                if (sameAlready >= 3) {
                                    inc (ySame_i,   y_i - sameAlready,    y_i) {
                                        clearedSomething = true;
                                        shallClear[ySame_i][x_i] = true;
                                    }
                                }
                                lastColour = colour;
                                sameAlready = 1;
                            }
                        }
                    }

                    // Diagonal upwards
                    inc (diagonal_i,   6 - 3,    19 + 6 - 3) {
                        int32 lastColour = 0;
                        int32 sameAlready = 0;
                        inc0 (x_i,   7) {
                            int32 y = diagonal_i - x_i;
                            if (y < 0 || y >= 19) { continue; }

                            int32 colour = GameField.Colours[y][x_i];
                            if (colour != 0 && colour == lastColour) {
                                ++sameAlready;
                            } else {
                                if (sameAlready >= 3) {
                                    inc (xSame_i,   x_i - sameAlready,    x_i) {
                                        int ySame = diagonal_i - xSame_i;
                                        clearedSomething = true;
                                        shallClear[ySame][xSame_i] = true;
                                    }
                                }
                                lastColour = colour;
                                sameAlready = 1;
                            }
                        }
                    }

                    // Diagonal downwards
                    inc (diagonal_i,   -3,    19 - 2) {
                        int32 lastColour = 0;
                        int32 sameAlready = 0;
                        inc0 (x_i,   7) {
                            int32 y = diagonal_i + x_i;
                            if (y < 0 || y >= 19 + 1) { continue; }

                            int32 colour = GameField.Colours[y][x_i];
                            if (colour != 0 && colour == lastColour) {
                                ++sameAlready;
                            } else {
                                if (sameAlready >= 3) {
                                    inc (xSame_i,   x_i - sameAlready,    x_i) {
                                        int ySame = diagonal_i + xSame_i;
                                        clearedSomething = true;
                                        shallClear[ySame][xSame_i] = true;
                                    }
                                }
                                lastColour = colour;
                                sameAlready = 1;
                            }
                        }
                    }

                    if (clearedSomething) {

                        SetAllClearingToColour(&shallClear, 7);
                        SetAllClearingToColour(&shallClear);
                        SetAllClearingToColour(&shallClear, 7);
                        SetAllClearingToColour(&shallClear);
                        SetAllClearingToColour(&shallClear, 7);

                        SetAllClearingToColour(&shallClear, 1);
                        SetAllClearingToColour(&shallClear, 2);
                        SetAllClearingToColour(&shallClear, 3);
                        SetAllClearingToColour(&shallClear, 4);
                        SetAllClearingToColour(&shallClear, 5);
                        SetAllClearingToColour(&shallClear, 6);

                        SetAllClearingToColour(&shallClear, 1);
                        SetAllClearingToColour(&shallClear, 2);
                        SetAllClearingToColour(&shallClear, 3);
                        SetAllClearingToColour(&shallClear, 4);
                        SetAllClearingToColour(&shallClear, 5);
                        SetAllClearingToColour(&shallClear, 6);
                    

                        // Clear and FallDown
                        inc0 (x_i,   6) {
                            int32 currentPosition = 19;
                            dec0 (y_i,   19) {
                                if (shallClear[y_i][x_i]) {
                                    ++ClearCount;
                                    GameField.Colours[y_i][x_i] = 0;
                                }
                                int32 colorValue = GameField.Colours[y_i][x_i];
                                if (colorValue != 0) {
                                    GameField.Colours[--currentPosition][x_i] = colorValue;
                                    SE_S_MEM[0][currentPosition][x_i] = 1 + (colorValue << 12);
                                }
                            }
                            inc0 (y_i,   currentPosition) {
                                GameField.Colours[y_i][x_i] = 0;
                                SE_S_MEM[0][y_i][x_i] = 0;
                            }
                        }
                    }
                } while (clearedSomething);

                if (ClearCount >= LastJoker + JOKER_NUMBER) {
                    // JOKER (keep next intact)
                    ActiveTromino.Position = NextTromino.Position;
                    ActiveTromino.Colours[0] = 0;
                    ActiveTromino.Colours[1] = 0;
                    ActiveTromino.Colours[2] = 0;
                    // TODO: Theoretically the joker has to flash when moving (is that level-dependent?)
                    LastJoker += JOKER_NUMBER;
                } else {
                    ActiveTromino = NextTromino;
                    NextTromino.Colours[0] = RandRange(1, 7);
                    NextTromino.Colours[1] = RandRange(1, 7);
                    NextTromino.Colours[2] = RandRange(1, 7);
                }
                

            } else {
                // Move down
                ++ActiveTromino.Position.Y;
            }

            // Reset the timer
            Timer = 30; // TODO: Use a variable value
        }

        // Write new position
        SE_S_MEM[0][ActiveTromino.Position.Y    ][ActiveTromino.Position.X] = 1 + (ActiveTromino.Colours[0] << 12);
        SE_S_MEM[0][ActiveTromino.Position.Y + 1][ActiveTromino.Position.X] = 1 + (ActiveTromino.Colours[1] << 12);
        SE_S_MEM[0][ActiveTromino.Position.Y + 2][ActiveTromino.Position.X] = 1 + (ActiveTromino.Colours[2] << 12);
    }


    for (;;) {}

    return 0;
}