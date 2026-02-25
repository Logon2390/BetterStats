#include "Formatters.hpp"
#include "../managers/StatsManager.hpp"
#include <chrono>

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>


int64_t getCurrentTimestamp()
{
    return static_cast<int64_t>(std::time(nullptr));
}

std::string formatDuration(double secondsInput)
{
    std::chrono::seconds totalSeconds(
        static_cast<long long>(secondsInput)
    );

    auto hours = std::chrono::duration_cast<std::chrono::hours>(totalSeconds);
    totalSeconds -= hours;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(totalSeconds);
    totalSeconds -= minutes;

    auto seconds = totalSeconds;

    std::string result;

    if (hours.count() > 0)
        result += std::to_string(hours.count()) + "h ";

    if (minutes.count() > 0)
        result += std::to_string(minutes.count()) + "m ";

    result += std::to_string(seconds.count()) + "s";

	return result; 
}

std::string formatDate(int64_t timestamp)
{
    std::time_t time = static_cast<std::time_t>(timestamp);

    std::tm* tm = std::localtime(&time);

    std::stringstream ss;
    ss << std::put_time(tm, "%d/%m/%Y %H:%M");

    return ss.str();
}

std::string formatRelativeTime(int64_t timestamp)
{
    int64_t now = getCurrentTimestamp();
    int64_t diff = now - timestamp;

    if (diff < 60)
        return "Just now";

    if (diff < 3600)
    {
        int64_t minutes = diff / 60;
        return std::to_string(minutes) +
            (minutes == 1 ? " minute ago" : " minutes ago");
    }

    if (diff < 86400)
    {
        int64_t hours = diff / 3600;
        return std::to_string(hours) +
            (hours == 1 ? " hour ago" : " hours ago");
    }

    if (diff < 604800)
    {
        int64_t days = diff / 86400;
        return std::to_string(days) +
            (days == 1 ? " day ago" : " days ago");
    }

    return formatDate(timestamp);
}