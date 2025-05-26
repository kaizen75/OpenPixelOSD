/* SPDX-License-Identifier: GPL-2.0-only */
/**
 * Copyright (C) 2025 Vitaliy N <vitaliy.nimych@gmail.com>
 */
#ifndef CANVAS_CHAR_H
#define CANVAS_CHAR_H
#include <stdint.h>

#define COLUMN_SIZE     (30)
#define ROW_SIZE        (16)

void canvas_char_clean(void);
void canvas_char_write(uint8_t x, uint8_t y, const char *data, const uint16_t len);


#endif //CANVAS_CHAR_H
