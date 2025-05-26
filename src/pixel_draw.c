/* SPDX-License-Identifier: GPL-2.0-only */
/**
 * Copyright (C) 2025 Vitaliy N <vitaliy.nimych@gmail.com>
 */
#include <stdlib.h>
#include "pixel_draw.h"

#include <main.h>

uint8_t raw_pixel_buff[PIXEL_MAP_HEIGHT][PACKED_PIXELS_PER_ROW];


void pixel_draw_buff_init(void)
{
    for (uint32_t yy = 0; yy < PIXEL_MAP_HEIGHT; yy++) {
        for (uint32_t xx = 0; xx < PIXEL_MAP_WIDTH; xx++) {
            pixel_draw_set_px(yy, xx, PX_TRANSPARENT);
        }
    }
}

/**
 * Set a 2-bit pixel value in the packed pixel buffer.
 *
 * Each pixel is represented by 2 bits and packed into bytes (4 pixels per byte).
 *
 * Parameters:
 *  - row:    The row index of the pixel (vertical position).
 *  - col:    The column index of the pixel (horizontal position).
 *  - v:      The 2-bit pixel value to set (0 to 3).
 *
 * The function calculates the exact byte and bit position within that byte
 * where the pixel value is stored, clears the existing 2 bits for that pixel,
 * and writes the new pixel value in place.
 */
void pixel_draw_set_px(uint32_t row, uint32_t col, px_t v)
{
    if (row >= PIXEL_MAP_HEIGHT || col >= PIXEL_MAP_WIDTH) return;
    uint32_t bit   = col * 2;
    uint32_t idx   = bit >> 3;
    uint32_t shift = 6 - (bit & 7);
    raw_pixel_buff[row][idx] = (raw_pixel_buff[row][idx] & ~(0x3u << shift)) | (((uint32_t)v & 0x3u) << shift);
}

void pixel_draw_line(int x0, int y0, int x1, int y1, px_t color)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;
    while (1) {
        pixel_draw_set_px(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void pixel_draw_rect(int x, int y, int w, int h, px_t color)
{
    pixel_draw_line(x, y, x + w - 1, y, color);
    pixel_draw_line(x, y, x, y + h - 1, color);
    pixel_draw_line(x + w - 1, y, x + w - 1, y + h - 1, color);
    pixel_draw_line(x, y + h - 1, x + w - 1, y + h - 1, color);
}

void pixel_draw_fill_rect(int x, int y, int w, int h, px_t color)
{
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pixel_draw_set_px(x + i, y + j, color);
        }
    }
}

void pixel_draw_circle(int cx, int cy, int r, px_t color)
{
    int x = -r, y = 0, err = 2 - 2 * r;
    do {
        pixel_draw_set_px(cx - x, cy + y, color);
        pixel_draw_set_px(cx - y, cy - x, color);
        pixel_draw_set_px(cx + x, cy - y, color);
        pixel_draw_set_px(cx + y, cy + x, color);
        int e2 = err;
        if (e2 <= y) { err += ++y * 2 + 1; }
        if (e2 > x || err > y) { err += ++x * 2 + 1; }
    } while (x < 0);
}

void pixel_draw_fill_circle(int cx, int cy, int r, px_t color)
{
    int x = -r, y = 0, err = 2 - 2 * r;
    do {
        pixel_draw_line(cx - x, cy - y, cx + x, cy - y, color);
        pixel_draw_line(cx - x, cy + y, cx + x, cy + y, color);
        int e2 = err;
        if (e2 <= y) { err += ++y * 2 + 1; }
        if (e2 > x || err > y) { err += ++x * 2 + 1; }
    } while (x < 0);
}
