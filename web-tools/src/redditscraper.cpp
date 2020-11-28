//
// Created by atlas on 11/26/20.
//

#include "redditscraper/redditscraper.hpp"

void mergeMap(std::map<std::string, int> &map1, std::map<std::string, int> &map2) {
    //Will iterate and merge both maps while also storing the sum of both values
    for ( auto const& [key, val] : map2) {
        auto node = map1.find(key);
        if (node == map1.end()) {
            map1[key] = val;
        } else {
            node->second += val;
        }
    }
}

RedditScraper::RedditScraper() {
    //https://www.reddit.com/dev/api#GET_subreddits_search - used for finding sub reddits about stocks

    //if post not text ignore or maybe use title only
}

std::vector<Post> RedditScraper::get(int epoch_start, int epoch_end, const std::string& subreddits,
                                         const std::string& queries, std::map<std::string, int> &tickers) {

    std::vector<Post> results;

    httplib::Client reddit("https://api.pushshift.io");

    bool new_queries = true;

    while (new_queries) {

        //If too many queries continue time after latest time
        int max_size = 100;
        std::string query = "/reddit/submission/search/?";
        query += "q=" + queries;
        query += "&subreddit=" + subreddits;
        query += "&after=" + std::to_string(epoch_start);
        query += "&before=" + std::to_string(epoch_end);
        query += "&size=" + std::to_string(max_size);

        auto res = reddit.Get(query.c_str());
        json body = json::parse(res->body);

        for (json post : body["data"]) {
            Post new_post;
            new_post.id = post["id"];
            new_post.title = post["title"];
            try {
                new_post.body = post["selftext"];
            }
            catch (std::exception &e) {
                //unknown file failure
                //something to do with reading the selftexts
                new_post.body = "";
                std::cout << "Exception: " << e.what() << std::endl;
            }
            new_post.time = post["created_utc"];
            results.push_back(new_post);

            //Update maps
            auto temp_map = this->get_tickers(new_post.title);
            mergeMap(tickers, temp_map);
            temp_map = this->get_tickers(new_post.body);
            mergeMap(tickers, temp_map);
        }
        if (results.size() % 100 != 0) {
            new_queries = false;
        } else {
            epoch_start = results.back().time;
        }
    }

    return results;
}

std::map<std::string, int> RedditScraper::get_tickers(std::string str) {
    //according to NYSE tickers have up to 4 letters while in NASDAQ there can be up to 5, minimum 3 letters
    //for ease lets make sure theyre all caps so [A-Z] 3 to 5 letters so {3,5}
    // for the moment \s is used to avoid slicing words
    std::regex ticker_rgx("\\s([A-Z]{3,5})\\s");
    std::smatch match;

    std::map<std::string, int> tickers;

    while (regex_search(str, match, ticker_rgx)) {
        // Doesnt work for less than 2 characters but since out ticker is 3 minimum its fine
        std::string ticker = match.str(0).substr(1, match.str(0).size() - 2);

        auto val = tickers.find(ticker);
        if (val == tickers.end()) {
            tickers[ticker] = 1;
        } else {
            val->second += 1;
        }

        //Pos of the match
        //match.position(0)

        // suffix to find the rest of the string.
        str = match.suffix().str();
    }
    return tickers;
}