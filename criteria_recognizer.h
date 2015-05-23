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

#ifndef CRITERIA_RECOGNIZER_H
#define CRITERIA_RECOGNIZER_H


#include <stdlib.h>
#include <math.h>
#include "fake_templates.h"
#include "criteria_state.h"

#ifdef __cplusplus
extern "C" {
#endif

static _criteria tree_null_level;

void buildTree(double *input_data, int input_len, int input_count, int dim_count);

void buildTree(double *input_data, int input_len, int input_count, int dim_count) {
    //Read first point
    _criteria* first = newFork_withCoo(&tree_null_level,input_data);
    //Create first level criteria
    tree_null_level.next_level = (_criteria*)malloc(sizeof(_criteria));
}


#ifdef __cplusplus
}
#endif


#endif // CRITERIA_RECOGNIZER_H
