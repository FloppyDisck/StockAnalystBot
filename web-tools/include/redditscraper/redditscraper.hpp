//
// Created by atlas on 11/26/20.
//

#ifndef REDDITSCRAPER_HPP
#define REDDITSCRAPER_HPP
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <map>

using json = nlohmann::json;

struct Post {
    std::string id;
    std::string title;
    std::string body;
    int time;
};

class RedditScraper {
public:
    RedditScraper();
    std::vector<Post> get(int epoch_start, int epoch_end, const std::string& subreddits, const std::string& queries, std::map<std::string, int> &tickers);
private:
    static std::map<std::string, int> get_tickers(std::string str);
};


#endif //WEBSCRAPER_HPP
