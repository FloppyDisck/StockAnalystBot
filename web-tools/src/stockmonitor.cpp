#include "stockmonitor/stockmonitor.hpp"

StockMonitor::StockMonitor() {
    api_key = std::to_string(std::getenv("ALPACAVANTAGE_API_KEY"));
}

std::map<int, float> StockMonitor::get_historical_data(std::string ticker, int tick_interval, int start_year,
                                                       int start_month, int end_year, int end_month) {

}
