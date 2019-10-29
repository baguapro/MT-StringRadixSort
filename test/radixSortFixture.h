#ifndef __RADIX_SORT_FIXTURE_H__
#define __RADIX_SORT_FIXTURE_H__

#include <gtest/gtest.h>

#include <vector>
#include <string>

namespace radix_sort_fixture
{

class TestRadixSort : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        test_data_lc_.insert(test_data_lc_.end(), {
                            "the",
                            "quick",
                            "brown",
                            "fox",
                            "jumped",
                            "over",
                            "the",
                            "lazy",
                            "dog"
                        });

        test_data_uc_.insert(test_data_uc_.end(), {
                            "THE",
                            "QUICK",
                            "BROWN",
                            "FOX",
                            "JUMPED",
                            "OVER",
                            "THE",
                            "LAZY",
                            "DOG"
                        });

        test_data_mix_.insert(test_data_mix_.end(), {
                            "tHe",
                            "QuIck",
                            "brOWN",
                            "FOX",
                            "jumped",
                            "oVEr",
                            "ThE",
                            "LaZy",
                            "doG"
                        });
    }

    virtual void TearDown() { }

public:
    std::vector<std::string> test_data_lc_;
    std::vector<std::string> test_data_uc_;
    std::vector<std::string> test_data_mix_;
};

}

#endif // __RADIX_SORT_FIXTURE_H__
