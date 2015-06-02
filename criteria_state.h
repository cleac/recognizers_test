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

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    double* coordinates;
    double repeat_count;
    uint32_t dim_count;
    uint32_t next_count;
    void* next_level;
} _criteria;

/**
 * @brief newFork(..)
 * @details creates new fork on next level from parent
 *
 * @param parent - pointer to upper level _criteria instance
 * @return pointer to new fork
 */
_criteria* newFork(_criteria* parent);

/**
 * @brief newFork_withCoo(..)
 * @details creates new fork on next level from parent and copies
 *          data from input coordinats to new Fork
 *
 * @param parent    - pointer to upper level _criteria instance
 * @param coo       - pointer to data to be copied
 *
 * @return pointer to new fork
 */
_criteria* newFork_withCoo(_criteria* parent, double* coo);

/**
 * @brief appendFork(..)
 * @details appends fork to fork list of parent and optimizes tree
 *
 * @param parent    - parent level for fork to be appended
 * @param fork      - fork to be appended
 *
 * @return pointer to appended fork
 */
_criteria* appendFork(_criteria* parent, _criteria* fork);

/**
 * @brief deleteForkNumber(..)
 * @details deletes fork from parent fork list
 *
 * @param parent    - pointer to upper level _criteria instance
 * @param number    - number of fork to be deleted (started from 0)
 */
void deleteForkNumber(_criteria* parent, int number);

/**
 * @brief deleteForkPtr(..)
 * @details deletes fork of parent by pointer;
 *          does nothing if such pointer is not child of parent
 * 
 * @param parent    - pointer to parent of ptr
 * @param ptr       - pointer to fork to be deleted
 */
void deleteForkPtr(_criteria* parent, _criteria* ptr);

/**
 * @brief deletes all the forks of current parent
 *
 * @param parent    - pointer to upper level _criteria instance
 */
void clearLevel(_criteria* parent);

/**
 * @brief criteriaCompare_Gauss(..)
 * @details compares element by using Gauss formula
 *
 * @param current   - current _criteria to be compared with data
 * @param coo       - input data to be compared with current _criteria
 *
 * @return result of comparation, in range {0..1}
 */
double criteriaCompare_Gauss(_criteria* current, double* coo);

/**
 * @brief optimizeForks(..)
 * @details optimizes forks of current parent by merging most probable copies
 *          of forks that exist, recoursively being called until tree gets
 *                                                      maximal optimization
 *
 * @param parent    - parent merge level
 */
void optimizeForks(_criteria* parent);


/**
 * @brief mergeForks(..)
 * @details merges two objects of type _criteria
 * 
 * @param parent    - object for fork to be saved
 * @param lhs       - first object 
 * @param rhs       - second object
 * 
 * @return pointer to new object that is stored in parent
 */
_criteria* mergeForks(_criteria* parent,_criteria* lhs, _criteria* rhs);

#ifdef __cplusplus
}
#endif

#endif // CRITERIA_STATE_H
