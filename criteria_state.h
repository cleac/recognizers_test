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

struct _criteria {
    double* coordinates;
    int dim_count;
    int next_count;
    _criteria* next_level;
};
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
void clearForks(_criteria* parent);

_criteria* newFork(_criteria* parent) {
    //Result variable
    _criteria* new_fork;
    //If there exists next level (any) we have to copy them first
    if (parent->next_level) {
        //Save old data to copy it afterwords
        _criteria* tmp = parent->next_level;
        //We get block of memoty for new amount of data
        parent->next_level = (_criteria*)malloc(sizeof(_criteria) *
                                                (parent->next_count + 1));
        int count = parent->next_count;
        _criteria *iter_old = tmp, *iter_new = parent->next_level;
        //We copy the data, that existed before
        while (count--)
            *(iter_new++) = *(iter_old++);
        //Then free it
        free(tmp);
        //And initialize new amount of data
        iter_new->dim_count = parent->dim_count;
        iter_new->next_count = 0;
        iter_new->coordinates = (double*)malloc(sizeof(double) * parent->dim_count);
        new_fork = iter_new;
    } else { //Otherwise we create next level
        new_fork = parent->next_level = (_criteria*)malloc(sizeof(_criteria));
    }
    //And increment new counter of next level forks
    (parent->next_count)++;
    return new_fork;
}

_criteria* newFork_withCoo(_criteria* parent, double* coo) {
    //We get pointer to new fork
    _criteria* new_fork = newFork(parent);
    //And copy data from input pointer coo to this fork
    for (int i = 0; i < new_fork->dim_count; ++i) {
        new_fork->coordinates[i] = coo[i];
    }
    return new_fork;
}

void deleteForkNumber(_criteria* parent, int number) {
    //Recoursively clear all forks under fork to be deleted
    for (int i = 0 ; i < parent->next_count; ++i)
        deleteForkNumber(parent->next_level + number, i);
    //Then if current fork is not the only one - we have to copy all forks exists
    if (parent->next_count > 1) {
        _criteria* tmp = parent->next_level;
        parent->next_level = (_criteria*)malloc(sizeof(_criteria) *
                                                (parent->next_count - 1));
        int count = parent->next_count;
        _criteria *iter_old = tmp, *iter_new = parent->next_level;
        while (count--, iter_old++) {
            if (parent->next_count - count != number)
                *iter_new = *iter_old;
        }
        free(tmp);
    } else if (parent->next_count) {
        free(parent->next_level);
    }
    parent->next_count--;
}

void clearForks(_criteria* parent) {
    _criteria* iter = parent->next_level;
    while (parent->next_count--, iter++)
        clearForks(iter);
    free(parent->coordinates);
    free(parent->next_level);
}

#ifdef __cplusplus
}
#endif

#endif // CRITERIA_STATE_H
