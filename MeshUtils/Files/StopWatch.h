#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class StopWatch {
	private:
		std::chrono::high_resolution_clock::time_point *begin;
	public:
		StopWatch();
		~StopWatch();
		
		void start();
		double hop();
		static std::chrono::high_resolution_clock::time_point* now();
};

#endif