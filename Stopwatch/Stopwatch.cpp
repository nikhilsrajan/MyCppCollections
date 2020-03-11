#include "Stopwatch.hpp"
#include <iostream>

Stopwatch::TIMEPOINT Stopwatch::Start(const std::string& segment_name, const bool& announce) {
	if(announce) {
		std::cout << segment_name << " starting..." << std::endl;
	}
	TIMEPOINT start_time = std::chrono::high_resolution_clock::now();
	segment_start_map_[segment_name] = start_time;
	return start_time;
}

Stopwatch::TIMEPOINT Stopwatch::Stop(const std::string& segment_name, const bool& announce) {
	auto stop_time = std::chrono::high_resolution_clock::now();
	auto ret = segment_start_map_.find(segment_name);
	if(ret == segment_start_map_.end()) {
		throw std::logic_error((segment_name + "'s start time not recorded.").c_str());
	}
	if(announce) {
		std::cout << segment_name << " done" << std::endl;
	}
	auto start_time = ret->second;
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);
	auto ret2 = segment_duration_map_.find(segment_name);
	if(ret2 == segment_duration_map_.end()) {
		segment_duration_map_.emplace(segment_name, duration);
	} else {
		ret2->second += duration;
	}
	return stop_time;
}

void Stopwatch::Summary() {
	for(auto it = segment_duration_map_.rbegin(); it != segment_duration_map_.rend(); ++it) {
		std::cout << it->first << ": " << (it->second.count() / 1e6) << " seconds" << std::endl; 
	}
}

void Stopwatch::Clear() {
	segment_start_map_.clear();
	segment_duration_map_.clear();
}