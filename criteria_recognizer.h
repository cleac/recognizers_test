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

#include "fake_templates.h"
#include "criteria_state.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief addToTree(..)
 * @details adds new patg to tree (or updates path that exists)
 *
 * @param input_data    - analyzed data to be appended
 * @param input_len     - length of input_data
 * @param dim_count     - count of dimensions of inputted data
 */
void addToTree(double *input_data, int input_len, int dim_count);

/**
 * @brief initRecognizer()
 * @details function that init's recognizer (in test cases takes fake data)
 */
void initRecognizer();

/**
 * @brief releaseRecignizer()
 * @details function that free's memory of recognizer
 */
void releaseRecognizer();

/**
 * @brief findMatch(..)
 * @details finds match to current data
 * 
 * @param input_data    - data to be analyzed
 * @param dim_count     - count of dimensions of data
 */
int findMatch(double *input_data, int dim_count);

#ifdef __cplusplus
}
#endif


#endif // CRITERIA_RECOGNIZER_H
