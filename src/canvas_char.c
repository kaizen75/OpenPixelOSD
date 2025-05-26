/* SPDX-License-Identifier: GPL-2.0-only */
/**
 * Copyright (C) 2025 Vitaliy N <vitaliy.nimych@gmail.com>
 */
#include "canvas_char.h"
#include "main.h"

CCMRAM_BSS char canvas_char_map[ROW_SIZE][COLUMN_SIZE];


void canvas_char_clean(void)
{
    for (uint8_t y = 0; y < ROW_SIZE; y++) {
        for (uint8_t x = 0; x < COLUMN_SIZE; x++) {
            canvas_char_map[y][x] = ' ';
        }
    }
}

void canvas_char_write(uint8_t x, uint8_t y, const char *data, const uint16_t len)
{
    if (y >= ROW_SIZE) y = 0;
    if (x >= COLUMN_SIZE) x = 0;

    for (uint16_t i = 0; i < len; i++) {
        const uint8_t col = (x + i) % COLUMN_SIZE;
        canvas_char_map[y][col] = data[i];
    }
}
