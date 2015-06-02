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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief initTestTemplates(..) - inits test templates
 *
 * @param count - count of templates to be created
 * @param dim_count - count of dimensions
 * @param length of templates
 */
void initTestTemplates(int count, int dim_count, int length);

/**
 * @brief clearTestTemplates() - frees memory of templates
 */
void clearTestTemplates();

/**
 * @brief getTemplate(..)
 *
 * @param num - number of template
 * @return template number num
 */
double* getTemplate(int num);

/**
 * @brief getTemplateValueOnPos(..)
 *
 * @param templ_num - number of template
 * @param pos - position of data
 * @return template number num
 */
double* getTemplateValueOnPos(int templ_num, int pos);

/**
 * @brief getTemplateCount()
 * @return count of temlates
 */
const int getTemplateCount();

/**
 * @brief getTemplateLength()
 * @return length of templates
 */
const int getTemplateLength();

/**
 * @brief getDimensionCount()
 * @return count of dimensions
 */
const int getDimensionCount();

/**
 * @brief getTemplateMemoryUsage()
 * @return memory of templates used in program
 */
const unsigned int getTemplateMemoryUsage();

/**
 * @brief getFakeData()
 *
 * @param dim_count - count of dimensions
 * @param length of data to be created
 *
 * @return pointer to created fake data
 */
double* getFakeData(int dim_count, int length);

/**
 * @brief freeFakeData()
 *
 * @param dim_count - count of dimensions
 * @param length of data to be created
 *
 * @return pointer to created fake data
 */
void freeFakeData();

#ifdef __cplusplus
}
#endif
#endif // FAKE_TEMPLATES_H


