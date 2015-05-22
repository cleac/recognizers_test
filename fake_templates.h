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

#ifndef FAKE_TEMPLATES_H
#define FAKE_TEMPLATES_H

#include <stdlib.h>

void initTestTemplates(int count, int dim_count, int length);
void clearTestTemplates();
double* getTemplate(int num);
int getTemplateCount();
int getTemplateLength();

static double* test_templates;
static int templates_length = 0;
static int templates_count = 0;
static int dimension_count = 0;

void initTestTemplates(int count, int dim_count, int length) {
    templates_count = count;
    templates_length = length;
    dimension_count = dim_count;
    test_templates = (double*)
                     malloc(sizeof(double) * dim_count * count * length);
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < length; j++) {
            for (int k = 0 ; k < dim_count ; k++)
                *(test_templates + i * length * dim_count + j * dim_count + k) = i + 1;
        }
    }
}

void clearTestTemplates() {
    templates_count = 0;
    templates_length = 0;
    free(test_templates);
}

double* getTemplate(int num) {
    if (num < templates_count && num > -1)
        return test_templates + num * templates_length * dimension_count;
    else
        return NULL;
}

int getTemplateCount(){
    return templates_count;
}

int getTemplateLength(){
    return templates_length;
}

#endif // FAKE_TEMPLATES_H


