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

#include "criteria_state.h"
#include "algo_analyzer.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_DIFF 0.5

_criteria* newFork(_criteria* parent) {
	//Result variable
	_criteria* new_fork;
	//If there exists next level (any) we have to copy them first
	if (parent->next_level && parent->next_count) {
		//Save old data to copy it afterwords
		_criteria* tmp = parent->next_level;
		//We get block of memoty for new amount of data
		parent->next_level = (_criteria*)getMemBlock(sizeof(_criteria) *
		                     (parent->next_count + 1));
		int count = parent->next_count;
		_criteria *iter_old = tmp, *iter_new = parent->next_level;
		//We copy the data, that existed before
		while (count--)
			*(iter_new++) = *(iter_old++);
		new_fork = iter_new;
		//Then free it
		free(tmp);
	} else { //Otherwise we create next level
		new_fork = parent->next_level = (_criteria*)getMemBlock(sizeof(_criteria));
	}
	//And initialize new amount of data
	new_fork->dim_count = parent->dim_count;
	new_fork->next_count = 0;
	new_fork->repeat_count = 1;
	new_fork->coordinates = (double*)getMemBlock(sizeof(double) * parent->dim_count);
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
	//Free memory of data stored on this fork
	clearLevel(parent->next_level + number * sizeof(_criteria));
	//Then if current fork is not the only one - we have to copy all forks exists
	if (parent->next_count > 1 && parent->next_level) {
		_criteria* tmp = parent->next_level;
		parent->next_level = (_criteria*)getMemBlock(sizeof(_criteria) *
		                     (parent->next_count - 1));
		int count = parent->next_count;
		_criteria *iter_old = tmp, *iter_new = parent->next_level;
		while (count-- && iter_old++) {
			if (parent->next_count - count + 1 != number)
				*(iter_new++) = *iter_old;
		}
		free(tmp);
	} else if (parent->next_count && parent->next_level) {
		clearLevel(parent->next_level);
	}
	parent->next_count--;
}

void deleteForkPtr(_criteria* parent, _criteria* ptr) {
	int number = 0, next_count = parent->next_count;
	_criteria* iter = parent->next_level;
	while (next_count--) {
		if (iter++ == ptr) {
			deleteForkNumber(parent, number++);
			break;
		}
	}
}

void clearLevel(_criteria* parent) {
	if (parent->next_level) {
		_criteria* iter = parent->next_level;
		while (parent->next_count-- > 0 && iter++)
			clearLevel(iter);
		// free(parent->next_level);
	}
	if (parent->coordinates)
		free(parent->coordinates);
}

double criteriaCompare_Gauss(_criteria* current, double* coo) {
	double modulus = 0.0;
	for (int i = 0; i < current->dim_count; ++i) {
		modulus += (current->coordinates[i] - coo[i]) *
		           (current->coordinates[i] - coo[i]);
	}
	return exp(-modulus / 8);
}

_criteria* appendFork(_criteria* parent, _criteria* fork) {
	_criteria* appended_fork = newFork(parent);
	*appended_fork = *fork;
	optimizeForks(parent);
	return appended_fork;
}

void optimizeForks(_criteria* parent) {
	int fork_count = parent->next_count;
	bool optimized = false;
	for (_criteria *iter = parent->next_level;
	        fork_count && !optimized;
	        --fork_count, iter++)
	{
		int inner_fork_count = parent->next_count;
		for (_criteria *inner_iter = parent->next_level;
		        inner_fork_count && !optimized;
		        --inner_fork_count, inner_iter++)
		{
			double similarity =
			    criteriaCompare_Gauss(iter, inner_iter->coordinates);
			fprintf(stderr, "Similarity = %lf\n", similarity);
			if (similarity > 0.65 && iter != inner_iter) {
				if (mergeForks(parent, iter, inner_iter))
					optimized = true;
			}
		}
	}
	if (optimized)
		optimizeForks(parent);
	for (int i = 0 ; i < parent->next_count; ++i) {
		optimizeForks(parent->next_level + i * sizeof(_criteria));
	}
}

_criteria* mergeForks(_criteria* parent, _criteria* lhs, _criteria* rhs) {
	//Create merged_fork
	_criteria* merged_fork = (_criteria*)getMemBlock(sizeof(_criteria));
	//Copy coordinates
	merged_fork->dim_count = parent->dim_count;
	merged_fork->coordinates = (double*)getMemBlock(merged_fork->dim_count);
	for (int i = 0; i < merged_fork->dim_count; i++) {
		merged_fork->coordinates[i] =
		    (lhs->coordinates[i] + rhs->coordinates[i]) / 2;
	}
	//Copy children of lhs, rhs to merged_fork
	merged_fork->next_count = lhs->next_count + rhs->next_count;
	_criteria* iter =
	    merged_fork->next_level =
	        (_criteria*)getMemBlock(merged_fork->next_count);
	int lhs_n_count = lhs->next_count, rhs_n_count = rhs->next_count;
	_criteria *rhs_iter = rhs->next_level;
	_criteria *lhs_iter = lhs->next_level;
	while (lhs_n_count--)
		*(iter++) = *(lhs_iter++);
	while (rhs_n_count--)
		*(iter++) = *(rhs_iter++);
	merged_fork->repeat_count = lhs->repeat_count + rhs->repeat_count;
	//Delete rhs, lhs
	deleteForkPtr(parent, rhs);
	deleteForkPtr(parent, lhs);
	//Optimize merged_fork
	optimizeForks(merged_fork);
	//Append merged_fork to parent
	_criteria* result = appendFork(parent, merged_fork);
	//free memory after merged_fork
	free(merged_fork);
	return result;
}