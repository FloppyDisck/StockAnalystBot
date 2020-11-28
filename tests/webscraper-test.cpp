#include <iostream>
#include <gtest/gtest.h>
#include "redditscraper/redditscraper.hpp"
#include <map>

TEST(WEBSCRAPER, REDDIT_GET) {
    RedditScraper scraper;
    std::map<std::string, int> tickers;
    //1606489200
    //1606507200
    auto posts = scraper.get(1606485600, 1606507200, "wallstreetbets,investing,smallstreetbets", "", tickers);
    std::cout << posts.size() << std::endl;
    for (const auto& post : posts) {
        std::cout << post.title << std::endl;
        std::cout << post.body << std::endl;
        std::cout << std::endl;
    }

    std::cout << "Found stocks:" << std::endl;
    int ignores = 5;
    for ( auto const& [key, val] : tickers) {
        if (val > ignores) {
            std::cout << key << " was mentioned " << val << " times." << std::endl;
        }
    }

    EXPECT_TRUE(1);
}