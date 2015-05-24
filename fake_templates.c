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

#include <stdlib.h>
#include "fake_templates.h"

static double* test_templates;
static int templates_length = 0;
static int templates_count = 0;
static int dimension_count = 0;

static double* fake_data;

static unsigned int memory_usage = 0;

void initTestTemplates(int count, int dim_count, int length) {
    memory_usage = 0;
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
    if (num < templates_count && num > -1) {
        memory_usage += dimension_count * templates_length;
        return test_templates + num * templates_length * dimension_count;
    }
    else
        return NULL;
}

double* getTemplateValueOnPos(int templ_num, int pos) {
    if (templ_num < templates_count && templ_num > -1 &&
            pos > -1 && pos < templates_length)
    {
        memory_usage += dimension_count;
        return test_templates +
               templ_num * templates_length * dimension_count +
               pos * dimension_count;
    }
    else
        return NULL;
}

const int getTemplateCount() {
    return templates_count;
}

const int getTemplateLength() {
    return templates_length;
}

const unsigned int getTemplateMemoryUsage() {
    return memory_usage;
}


double* getFakeData(int dim_count, int length) {
    if (!fake_data)
        fake_data = (double*)malloc(sizeof(double) * dim_count * length);
    return fake_data;
}

void freeFakeData() {
    if(fake_data)
        free(fake_data);
}