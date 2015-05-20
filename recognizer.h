#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <cmath>
#include "stdint.h"
#include <cstdio>
#include <stdlib.h>

#define min(x,y) (x>y)?y:x

class FRecognizer
{
public:
    explicit FRecognizer();
    ~FRecognizer();

    const double CompareData(double* first_sequence, int first_size,
                             double* sec_sequence,  int sec_size,
                             int dim_count)
    {
        double* table = (double*)malloc(sizeof(double) * first_size * sec_size);
        for (int i = 0 ; i < first_size * sec_size; i++) {
            *(table + i) = -1.0;
            // fprintf(stderr, "init table: %lf\n", *(table + i));
        }
        // return 0.0;
        double result = DWTCompare(first_sequence, first_size - 1,
                                   sec_sequence, sec_size - 1,
                                   dim_count,
                                   table);
        // free(table);
        return result;
    }

    const double DWTCompare(double* first, int f_index,
                            double* sec, int s_index,
                            int dim_count, double* table) {
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
            *(table + f_index * s_index + s_index) = modulus;
        } else if (f_index < 1) {
            if (*(table + f_index * s_index + s_index) < 0)
                *(table + f_index * s_index + s_index) =
                    modulus + DWTCompare(first, f_index, sec, s_index - 1, dim_count, table);
        } else if (s_index < 1) {
            if (*(table + f_index * s_index + s_index) < 0)
                *(table + f_index * s_index + s_index) =
                    modulus + DWTCompare(first, f_index - 1, sec, s_index, dim_count, table);
        }
        else {
            if (*(table + f_index * s_index + s_index) < 0) {
                uint32_t w[3];
                w[0] = DWTCompare(first, f_index - 1, sec, s_index, dim_count, table);
                w[1] = DWTCompare(first, f_index, sec, s_index - 1, dim_count, table);
                w[2] = DWTCompare(first, f_index - 1, sec, s_index - 1, dim_count, table);
                *(table + f_index * s_index * (dim_count) + s_index) =
                    modulus + min(min(w[0], w[1]), w[2]);
            }
        }
        return *(table + f_index * s_index + s_index);
    }

};

#endif // RECOGNIZER_H
