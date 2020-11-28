#ifndef STOCKMONITOR_HPP
#define STOCKMONITOR_HPP
#include <map>
#include <httplib.h>
#include <nlohmann/json.hpp>
// Alpha Vantage, 5 calls per minute, 500 calls per day

using json = nlohmann::json;

class StockMonitor {
public:
    StockMonitor() : api("https://www.alphavantage.co/query?");
    std::map<int, float> get_historical_data(std::string ticker, int tick_interval, int start_year, int start_month, int end_year, int end_month);
private:
    httplib::Client api;
    std::string api_key;
};

#endif //STOCKMONITOR_HPP