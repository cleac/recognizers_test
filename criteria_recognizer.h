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

void createFakeStateTable();
void learnNewState(const double* data, int len);
void updateState(const double* data, int len, _state* targ);
void initRecognizer();
const int findMatch(const double* data, int len);

float pointDifferenceGaussian(int *first, int *second, int dimension_count);

void initRecognizer() {
    if (!state)
        state = (_state*)malloc(sizeof(_state));
}

float pointDifferenceGaussian(int *first, int *second, int dimension_count) {
    int arg = 0;
    while (dimension_count--) {
        arg += (*first) * (*first) + (*second) * (*second);
        first++;
        second++;
    }
    return exp(-(arg) / 8);
}

const int findMatch(const double* data, int len) {
    initRecognizer();
    createFakeStateTable();
    return 0;
}

void createFakeStateTable() {
    int count = getTemplateCount();
    for (int i = 0 ; i < count; i++)
        learnNewState(getTemplate(i), getTemplateLength());
}

void learnNewState(const double* data, int len) {
    _state* lastState = getLastState();
    lastState->next = (_state*)malloc(sizeof(state));
    lastState->next->index = lastState->index;
    int* coordinate_criteria = {};
    while (len--) {

    }
}

#ifdef __cplusplus
}
#endif


#endif // CRITERIA_RECOGNIZER_H
