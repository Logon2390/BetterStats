#pragma once
#include <string>

int64_t getCurrentTimestamp();
std::string formatDuration(double time);
std::string formatDate(int64_t timestamp);
std::string formatRelativeTime(int64_t timestamp);