#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include "algo_analyzer.h"

static timeval start_time;
static uint64_t m_allocated_memory = 0;

#ifdef __cplusplus
extern "C" {
#endif

void init_test() {
    gettimeofday(&start_time,NULL);
    m_allocated_memory = 0;
}

uint64_t getUsedMemory() {
    return m_allocated_memory;
}

void finish_test() {
    timeval end_time;
    gettimeofday(&end_time,NULL);
    clearTestTemplates();
    freeFakeData();
    fprintf(stderr, "Time elapsed: %.3lf microsec's\n", (end_time.tv_usec - start_time.tv_usec)/1000.0);
    fprintf(stderr, "Memory of templates used %u\n", getTemplateMemoryUsage());
    fprintf(stderr, "Memory allocated by classifier %lu\n", getUsedMemory());
}

void* getMemBlock(uint64_t count) {
    m_allocated_memory += count;
    return malloc(count);
}

#ifdef __cplusplus
}
#endif