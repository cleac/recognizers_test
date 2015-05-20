#include <chrono>
#include <unistd.h>
#include <iostream>
#include <signal.h>

//User includes
#include "recognizer.h"


namespace program_timer {
static auto start_time = std::chrono::high_resolution_clock::now();

inline static void start() {
	program_timer::start_time = std::chrono::high_resolution_clock::now();
}

inline void finish() {
	auto end_time = std::chrono::high_resolution_clock::now();
	fprintf(stderr, "Time elapsed: %lu nanosec's\n",
	        std::chrono::duration_cast
	        <std::chrono::nanoseconds>(end_time - start_time).count());
}
};//TIMER

void signal_callback_handler(int signum) {
	if (signum == SIGTERM || signum == SIGINT) {
		program_timer::finish();
		exit(0);
	}
}

int main(int argc, char const *argv[])
{
	signal(SIGINT, signal_callback_handler);
	signal(SIGTERM, signal_callback_handler);
	FRecognizer recognizer;

	int first_size = 1000, sec_size = 1000;
	double *first_seq = new double[first_size],
	*sec_seq = new double[sec_size];
	for ( int i = 0 ; i < first_size; i++) {
		*(first_seq + i) = 1;
	}
	for ( int i = 0 ; i < first_size; i++) {
		*(sec_seq + i) = 20;
	}
	program_timer::start();
	double res = recognizer.
	             CompareData(first_seq, first_size, sec_seq, sec_size, 1);
	fprintf(stderr, "Result %lf\n", res);

	program_timer::finish();
	return 0;
}
