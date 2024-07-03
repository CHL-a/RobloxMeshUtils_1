#include "StopWatch.h"

using namespace std;

// CONSTRUCTORS
StopWatch::StopWatch(): begin(nullptr){}

// DESTRUCTORS
StopWatch::~StopWatch(){delete begin;}

// STATICS
chrono::high_resolution_clock::time_point* StopWatch::now(){
	return new chrono::high_resolution_clock::time_point(
		chrono::high_resolution_clock::now());
}

// METHODS
void StopWatch::start(){delete begin;begin = now();}

/**
 * Returns delta time while setting start;
 */
double StopWatch::hop(){
	if (begin == nullptr) {
		start();
		return 0;
	}
	
	auto later = now();
	auto result = chrono::duration_cast<
		chrono::duration<double>
	>(*later - *begin).count();
	delete begin;
	begin = later;

	return result;
}