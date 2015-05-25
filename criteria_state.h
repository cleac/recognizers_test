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

#ifndef CRITERIA_STATE_H
#define CRITERIA_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    double* coordinates;
    int repeat_count;
    int dim_count;
    int next_count;
    void* next_level;
} _criteria;

/**
 * @brief newFork(..) - creates new fork on next level from parent
 *
 * @param parent - pointer to upper level _criteria instance
 * @return pointer to new fork
 */
_criteria* newFork(_criteria* parent);

/**
 * @brief newFork_withCoo(..) - creates new fork on next level from parent
 *                              and copies data from input coordinats to new Fork
 *
 * @param parent - pointer to upper level _criteria instance
 * @param coo - pointer to data to be copied
 *
 * @return pointer to new fork
 */
_criteria* newFork_withCoo(_criteria* parent, double* coo);

/**
 * @brief deleteForkNumber(..) - deletes fork from parent fork list
 *
 * @param parent - pointer to upper level _criteria instance
 * @param number - number of fork to be deleted (started from 0)
 */
void deleteForkNumber(_criteria* parent, int number);

/**
 * @brief deletes all the forks of current parent
 * 
 * @param parent pointer to upper level _criteria instance
 */
void clearLevel(_criteria* parent);

/**
 * @brief criteriaCompare_Gauss(..) compares element by using Gauss formula
 * 
 * @param current current _criteria to be compared with data
 * @param coo input data to be compared with current _criteria
 * 
 * @return result of comparation, in range {0..1}
 */
double criteriaCompare_Gauss(_criteria* current, double* coo);

#ifdef __cplusplus
}
#endif

#endif // CRITERIA_STATE_H
