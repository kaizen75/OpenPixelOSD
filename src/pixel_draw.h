/* SPDX-License-Identifier: GPL-2.0-only */
/**
 * Copyright (C) 2025 Vitaliy N <vitaliy.nimych@gmail.com>
 */
#ifndef PIXEL_DRAW_H
#define PIXEL_DRAW_H
#include <stdint.h>

#define ACTIVE_LINE_PIXELS  (360)
#define ACTIVE_DRAW_LINES   (304)

#define PIXEL_MAP_WIDTH   (ACTIVE_LINE_PIXELS / 2) // 180px
#define PIXEL_MAP_HEIGHT  (ACTIVE_DRAW_LINES / 2)  // 152px

#define PACKED_PIXELS_PER_ROW  ((PIXEL_MAP_WIDTH * 2 + 7) / 8)

typedef enum {
    PX_BLACK       = 0,
    PX_TRANSPARENT = 1,
    PX_WHITE       = 2,
    PX_GRAY        = 3
  } px_t;

void pixel_draw_buff_init(void);
void pixel_draw_set_px(uint32_t row, uint32_t col, px_t v);
void pixel_draw_line(int x0, int y0, int x1, int y1, px_t color);
void pixel_draw_rect(int x, int y, int w, int h, px_t color);
void pixel_draw_fill_rect(int x, int y, int w, int h, px_t color);
void pixel_draw_circle(int cx, int cy, int radius, px_t color);
void pixel_draw_fill_circle(int cx, int cy, int radius, px_t color);

#endif //PIXEL_DRAW_H
