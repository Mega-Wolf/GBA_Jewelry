#pragma once

#include "macro_helper.h"

// TODO: This seems nicer; but not supported
//#include <varargs.h>
#include <stdarg.h>

#define PRINT_FLAG_LEFT_JUSTIFY
#define PRINT_FLAG_FORCE_PLUS
#define PRINT_FLAG_FORCE_SPACE
//#define PRINT_FLAG_HASH
#define PRINT_FLAG_0_PAD

#define PRINT_WIDTH_ASTERISK

#define PRINT_PRECISION_ASTERISK

#define PRINT_PHASE_FLAGS 0
#define PRINT_PHASE_WIDTH 1
#define PRINT_PHASE_PRECISION 2
#define PRINT_PHASE_MODIFIERS 3

int printPhase = PRINT_PHASE_FLAGS;

int invertedIntToString(char* invertedNumber, int number) {
    int pos = 0;
    while (number < 0) {
        int lastDigit = number % 10;
        invertedNumber[pos++] = (char) -lastDigit + '0';
        number /= 10;
    }
    while (number > 0) {
        int lastDigit = number % 10;
        invertedNumber[pos++] = (char) lastDigit + '0';
        number /= 10;
    }
    
    return pos;
}

int invertedUIntToString(char* invertedNumber, unsigned int number) {
    int pos = 0;
    while (number > 0) {
        int lastDigit = number % 10;
        invertedNumber[pos++] = (char) lastDigit + '0';
        number /= 10;
    }
    
    return pos;
}

int mysnprintf (char* buffer, uint32 bufferCount, char* format, ... ) {
    va_list vlist;
    va_start(vlist, format);
    
    uint32 pos = 0;
    for (char* cp = format; char c = *cp++; ) {
        if (pos >= bufferCount) { goto _end; }
        
        if (c == '%') {
            
            if (*cp == '%') {
                buffer[pos++] = '%';
                cp++;
                continue;
            }
            
            bool useLeftJustify = false;
            bool forcePlus = false;
            bool useSpace = false;
            bool flagHash = false; // definitely not used
            bool leftPad = false;
            
            // Flags
            while ((c = *cp++) != '\0') {
                switch (c) {
                    case '-': {
                        useLeftJustify = true;
                    } break;
                    case '+': {
                        forcePlus = true;
                    } break;
                    case ' ': {
                        useSpace = true;
                    } break;
                    case '#': {
                        flagHash = true;
                    } break;
                    case '0': {
                        leftPad = true;
                    } break;
                    
                    default: {
                        // This is not a flag anymore
                        --cp;
                        goto _after_flags;
                    } break;
                }
            }
            goto _endError;
            _after_flags:
            
            // Width
            int minWidth = 0;
            while ((c = *cp++) != '\0') {
                if (c >= '0' && c <= '9') {
                    int number = c - '0';
                    minWidth = 10 * minWidth + number;
                } else {
                    if (c == '*') {
                        minWidth = va_arg(vlist, int);
                        c = *cp++;
                    }
                    goto _after_width;
                }
            }
            goto _endError;
            _after_width:
            
            // character c already has been read
            int precision = -1;
            if (c == '.') {
                
                // Precision
                while ((c = *cp++) != '\0') {
                    if (c >= '0' && c <= '9') {
                        if (precision == -1) {
                            precision = 0;
                        }
                        int number = c - '0';
                        precision = 10 * precision + number;
                    } else {
                        if (c == '*') {
                            precision = va_arg(vlist, int);
                            c = *cp++;
                        }
                        goto _after_precision;
                    }
                }
                goto _endError;
            }
            _after_precision:
            //--cp;
            
            // sizeprefix
            // TODO: Ignore for now
            
            // type
            switch (c) {
                case 'c': {
                    buffer[pos++] =  va_arg(vlist, int);
                } break;
                case 'd': {
                    int number = va_arg(vlist, int);
                    // TODO: use the leftPad and left Blank (shouldn't be tooo difficult now)
                    // if (number == 0) {
                    //     buffer[pos++] = '0';  
                    // }
                    uint32 posBefore = pos;

                    if (number < 0) {
                        buffer[pos++] = '-';
                    } else {
                        if (forcePlus) {
                            buffer[pos++] = '+';
                        } else if(useSpace) {
                            buffer[pos++] = ' ';
                        }
                    }
                    char maxBufferSize[10];
                    int digits = invertedIntToString(maxBufferSize, number);
                    for (int i = 0; i < minWidth - digits; ++i) {
                        if (pos >= bufferCount) { goto _end; }
                        if (leftPad) {
                            buffer[pos++] = '0';
                        } else {
                            buffer[pos++] = ' ';
                        }
                    }
                    for (int i = 0; i < digits; ++i) {
                        if (pos >= bufferCount) { goto _end; }
                        buffer[pos++] = maxBufferSize[digits - i - 1];
                    }

                    // 0 has not been printed yet
                    if (number == 0 && pos == posBefore) {
                        buffer[pos++] = '0';  
                    }
                } break;
                case 'u': {
                    int number = va_arg(vlist, int);
                    // TODO: use the leftPad and left Blank (shouldn't be tooo difficult now)
                    if (number == 0) {
                      buffer[pos] = '0';  
                    } else {
                        if (forcePlus) {
                            buffer[pos++] = '+';
                        } else if(useSpace) {
                            buffer[pos++] = ' ';
                        }
                        char maxBufferSize[10];
                        int digits = invertedUIntToString(maxBufferSize, number);
                        for (int i = 0; i < minWidth - digits; ++i) {
                            if (pos >= bufferCount) { goto _end; }
                            if (leftPad) {
                                buffer[pos++] = '0';
                            } else {
                                buffer[pos++] = ' ';
                            }
                        }
                        for (int i = 0; i < digits; ++i) {
                            if (pos >= bufferCount) { goto _end; }
                            buffer[pos++] = maxBufferSize[digits - i - 1];
                        }
                    }
                } break;
                case 'f': {
                    
                    double number = va_arg(vlist, double);
                    // TODO:Care about width (+d +u)
                    
                    if (number == 0) {
                      buffer[pos] = '0';  
                    } else {
                        if (number < 0) {
                            buffer[pos++] = '-';
                            number *= -1;
                        } else {
                            if (forcePlus) {
                                buffer[pos++] = '+';
                            } else if(useSpace) {
                                buffer[pos++] = ' ';
                            }
                        }
                        
                        // TODO: This is not correct; but I can live with that
                        char maxBufferSize[10];
                        unsigned int intNumber = (int) number;
                        int digitsFront = invertedUIntToString(maxBufferSize, intNumber);
                        for (int i = 0; i < digitsFront; ++i) {
                            if (pos >= bufferCount) { goto _end; }
                            buffer[pos++] = maxBufferSize[digitsFront - i - 1];
                        }
                        
                        // Decimal point
                        if (pos >= bufferCount) { goto _end; }
                        buffer[pos++] = '.';
                        
                        if (precision == -1) {
                            precision = 6;
                        } else if (precision > 9) {
                            goto _endError;
                        }
                        
                        //  NOTE: I could also do that with a loop
                        int possibleMultipliers[] = {
                            1,
                            10,
                            100,
                            1000,
                            10000,
                            100000,
                            1000000,
                            10000000,
                            100000000,
                            1000000000
                        };
                        
                        float floatAfterComma = number - intNumber;
                        floatAfterComma *= possibleMultipliers[precision];
                        int intAfterComma = (int) (floatAfterComma + 0.5f);
                        int digitsBack = invertedUIntToString(maxBufferSize, intAfterComma);
                        for (int i = 0; i < digitsBack; ++i) {
                            if (pos >= bufferCount) { goto _end; }
                            buffer[pos++] = maxBufferSize[digitsBack - i - 1];
                        }
                    }

                } break;
                case 's': {
                    char* paramString = va_arg(vlist, char*);
                    for (char* cpParam = paramString; char cParam = *cpParam++; ) {
                        buffer[pos++] = cParam;
                        if (pos >= bufferCount) { goto _end; }
                    }
                } break;
                default: {
                    goto _endError;
                }
            }
        } else {
            // Normal character
            buffer[pos++] = c;
        }
        
        
        
    }

    _end:
    va_end(vlist);


    if (bufferCount == 0) { return 0; }

    if (pos == bufferCount) {
        --pos;
    }
    buffer[pos] = '\0';

    // NOTE: Mimimi, this is not according to specs
    return pos;
    
    _endError:
    va_end(vlist);
    return -1; // TODO: Do I even want that
}
