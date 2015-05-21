#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdio.h>
#include "fake_templates.h"

#define min(x,y)    (x>y)?y:x

const double DWTCompare(const double* first, const int f_index,
                        const double* sec, const int s_index,
                        const int dim_count);
const double CompareData(const double* first_sequence, const int first_size,
                         const double* sec_sequence,  const int sec_size,
                         const int dim_count);
const int findMatch(const double* data, int len);


static double* recognition_table;


const double CompareData(const double* first_sequence, const int first_size,
                         const double* sec_sequence,  const int sec_size,
                         const int dim_count)
{
    for (int i = 0 ; i < first_size * sec_size; i++)
        *(recognition_table + i) = -1.0;
    return DWTCompare(first_sequence, first_size - 1,
                      sec_sequence, sec_size - 1,
                      dim_count);
}

const double DWTCompare(const double* first, const int f_index,
                        const double* sec, const int s_index,
                        const int dim_count) {
    if (f_index < 0  || s_index < 0)
        return 0.0f;
    double* iterator = recognition_table + f_index * s_index + s_index;

    double modulus = 0.0;
    for (int i = 0; i < dim_count; i++) {
        modulus += fabs((*(first + (f_index * dim_count + dim_count - 1))) -
                        (*(sec + (s_index * dim_count + dim_count - 1))));
    }
    if (f_index > -1  && s_index > -1)
        *iterator = modulus;
    if (f_index < 1 && *iterator < 0) {
        *iterator += DWTCompare(first, f_index, sec, s_index - 1, dim_count);
    } else if (s_index < 1 && *iterator < 0) {
        *iterator += DWTCompare(first, f_index - 1, sec, s_index, dim_count);
    }
    else if (*(recognition_table + f_index * s_index + s_index) < 0) {
        uint32_t w0 = DWTCompare(first, f_index - 1, sec, s_index, dim_count),
                 w1 = DWTCompare(first, f_index, sec, s_index - 1, dim_count),
                 w2 = DWTCompare(first, f_index - 1, sec, s_index - 1, dim_count);
        *iterator += min(min(w0, w1), w2);
    }
    return *iterator;
}

const int findMatch(const double* data, int len) {
    int result = -1;
    double impossibility = 1e+300;
    recognition_table = (double*)
                        malloc((sizeof(double) * templates_length * len));
    for (int i = 0 ; i < templates_count ; i++) {
        double cur_impos = CompareData(
                               data, len,
                               getTemplate(i), templates_length,
                               dimension_count);
        if (impossibility > cur_impos) {
            impossibility = cur_impos;
            result = i;
        }
    }
    free(recognition_table);
    return result;
}

#ifdef __cplusplus
}
#endif

#endif // RECOGNIZER_H
