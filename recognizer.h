#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdio.h>

#define min(x,y) (x>y)?y:x

static double* recognition_table;

const double DWTCompare(double* first, int f_index,
                        double* sec, int s_index,
                        int dim_count);
const double CompareData(double* first_sequence, int first_size,
                         double* sec_sequence,  int sec_size,
                         int dim_count);


const double CompareData(double* first_sequence, int first_size,
                         double* sec_sequence,  int sec_size,
                         int dim_count)
{
    recognition_table = (double*)
                        malloc(sizeof(double) * first_size * sec_size + 1);
    for (int i = 0 ; i < first_size * sec_size; i++) {
        *(recognition_table + i) = -1.0;
    }
    // return 0.0;
    double result = DWTCompare(first_sequence, first_size - 1,
                               sec_sequence, sec_size - 1,
                               dim_count);
    free(recognition_table);
    return result;
}

const double DWTCompare(double* first, int f_index,
                        double* sec, int s_index,
                        int dim_count) {
    if (f_index < 0  || s_index < 0) {
        return 0.0f;
    }
    double modulus = 0.0;

    for (int i = 0; i < dim_count; i++) {
        modulus += fabs(*(first + (f_index * dim_count + dim_count - 1)) *
                        *(first + (f_index * dim_count + dim_count - 1)) -
                        * (sec + (s_index * dim_count + dim_count - 1)) *
                        *(sec + (s_index * dim_count + dim_count - 1)));
    }
    if (f_index == 0  && s_index == 0) {
        *(recognition_table + f_index * s_index + s_index) = modulus;
    } else if (f_index < 1) {
        if (*(recognition_table + f_index * s_index + s_index) < 0)
            *(recognition_table + f_index * s_index + s_index) =
                modulus + DWTCompare(first, f_index, sec, s_index - 1, dim_count);
    } else if (s_index < 1) {
        if (*(recognition_table + f_index * s_index + s_index) < 0)
            *(recognition_table + f_index * s_index + s_index) =
                modulus + DWTCompare(first, f_index - 1, sec, s_index, dim_count);
    }
    else {
        if (*(recognition_table + f_index * s_index + s_index) < 0) {
            uint32_t w[3];
            w[0] = DWTCompare(first, f_index - 1, sec, s_index, dim_count);
            w[1] = DWTCompare(first, f_index, sec, s_index - 1, dim_count);
            w[2] = DWTCompare(first, f_index - 1, sec, s_index - 1, dim_count);
            *(recognition_table + f_index * s_index * (dim_count) + s_index) =
                modulus + min(min(w[0], w[1]), w[2]);
        }
    }
    return *(recognition_table + f_index * s_index + s_index);
}

#ifdef __cplusplus
}
#endif

#endif // RECOGNIZER_H
