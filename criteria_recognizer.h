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
