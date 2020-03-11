#pragma once

#include <chrono>
#include <string>
#include <map>

class Stopwatch {
public:
#ifdef _WIN32
    using TIMEPOINT = std::chrono::steady_clock::time_point;
#endif
#ifdef __linux__
	using TIMEPOINT = std::chrono::system_clock::time_point;
#endif

public:
    Stopwatch() = default;
    ~Stopwatch() = default;

    /**
     * @brief Notes the start time against segment_name
     */ 
    TIMEPOINT Start(const std::string& segement_name, const bool& announce = true);

    /**
     * @brief Notes the stop time and store the duration using the start time
     *        against the same segment_name. If the start_time against the
     *        segment_name doesn't exist, error is throw. If duration has already
     *        been previous noted, then the new duration is added to the previous
     *        one - storing the cummulative duration.
     */ 
    TIMEPOINT Stop(const std::string& segment_name, const bool& announce = true);

    /**
     * @brief Prints all the segment_names and the cummulative durations recorded.
     */ 
    void Summary();

    /**
     * @brief Clears all the recorded start times and durations.
     */ 
    void Clear();

private:
    std::map<std::string, TIMEPOINT> segment_start_map_;
    std::map<std::string, std::chrono::microseconds> segment_duration_map_;
};