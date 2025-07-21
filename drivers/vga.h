#ifndef VGA_H
#define VGA_H

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define WHITE_ON_BLACK 0x0f
#define VIDEO_MEMORY ((uint16_t*)0xB8000)

void write_text(const char* str, uint8_t row, uint8_t col) {
    volatile char* video = (volatile char*) 0xB8000 + (row * 80 + col) * 2;
    while (*str) {
        *video++ = *str++;
        *video++ = 0x0f; // white text
    }
}

void clear_screen() {
    uint16_t blank = (' ' | (WHITE_ON_BLACK << 8));
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        VIDEO_MEMORY[i] = blank;
    }
}

#endif
