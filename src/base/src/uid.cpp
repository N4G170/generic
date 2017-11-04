#include "uid.hpp"
#include <functional>
#include <mutex>
#include <chrono>
#include <sstream>
#include <ctime>
#include <iomanip>//put_time

UID GenerateUID()
{
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);//lock will release at the end of the function (out of scope)

    static size_t counter{0};//used to "avoid" equal string for use in the hash
    static std::string last_string{};

    //read current date time
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    //format datetime and convert it to a string
    ss << std::put_time(std::localtime(&now_time_t), "%X %d-%m-%Y");
    // ss << std::put_time(std::localtime(&now_time_t), "%Y-%m-%d %X");

    std::string new_string{ss.str()};

    if(last_string != new_string)//we moved to a new second
    {
        counter = 0;//reset counter
        last_string = new_string;
    }
    ++counter;

    //add counter to string
    new_string = std::to_string(counter) + new_string + std::to_string(counter);

    std::hash<std::string> std_hash;
    UID uid{std_hash(new_string)};

    return uid;
}
