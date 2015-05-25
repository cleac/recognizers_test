/*
This file is part of recognizers_test

Copyright (C) 2015  Alexander Nesterenko <nestorf250@gmail.com>

This program is free software: you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see < http : //www.gnu.org/licenses/>.
*/

#ifndef MEMORY_COUNTER_H
#define MEMORY_COUNTER_H

#include "fake_templates.h"
#include <stdint.h>

#define init_analyze    init_test();
#define end_analyze     finish_test();

#ifdef __cplusplus
extern "C" {
#endif

void init_test();
void finish_test();

void* getMemBlock(uint64_t count);

#ifdef __cplusplus
}
#endif
#endif // MEMORY_COUNTER_H
