//
// Created by atlas on 11/26/20.
//

#ifndef WEBSCRAPER_HPP
#define WEBSCRAPER_HPP
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <map>

using json = nlohmann::json;

enum apis { reddit };

struct Post {
    std::string id;
    std::string title;
    std::string body;
    apis api;
    int time;
};

class WebScraper {
public:
    WebScraper();
    std::vector<Post> get(apis api, int epoch_start, int epoch_end, const std::string& subreddits, const std::string& queries, std::map<std::string, int> &tickers);
private:
    static std::map<std::string, int> get_tickers(std::string str);
};


#endif //WEBSCRAPER_HPP
