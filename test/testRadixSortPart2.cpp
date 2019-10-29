#include <gtest/gtest.h>

#include <part2/RadixSortSeq.hpp>
#include <part2/RadixSortMT.hpp>
#include "radixSortFixture.h"

#include <iterator>

using namespace radix_sort_fixture;
namespace RS = RadixSortSeq_P2;
namespace RM = RadixSortMT_P2;

// Test radix sort over the lower and upper case latters in the alphabet


TEST_F(TestRadixSort, testLowerCaseSort_part2)
{
    auto compare_data{test_data_lc_};
    auto seq_test_data{test_data_lc_};

    RM::RadixSortMT(std::begin(test_data_lc_), std::end(test_data_lc_),
                 'a','z');

    RS::RadixSortSeq(std::begin(seq_test_data),std::end(seq_test_data),
                'a','z');

    std::sort(std::begin(compare_data),std::end(compare_data),
                         std::less<std::string>());

    EXPECT_TRUE(std::equal(std::begin(test_data_lc_), 
                           std::end(test_data_lc_),
                           std::begin(compare_data)));

    EXPECT_TRUE(std::equal(std::begin(seq_test_data),
                           std::end(seq_test_data),
                           std::begin(compare_data)));
}

TEST_F(TestRadixSort, testUpperCaseSort_part2)
{
    auto compare_data{test_data_uc_};
    auto seq_test_data{test_data_uc_};

    RM::RadixSortMT(std::begin(test_data_uc_), std::end(test_data_uc_),
                 'A','Z');

    RS::RadixSortSeq(std::begin(seq_test_data), std::end(seq_test_data),
                'A','Z');

    std::sort(std::begin(compare_data),std::end(compare_data),
                         std::less<std::string>());

    EXPECT_TRUE(std::equal(std::begin(test_data_uc_), 
                           std::end(test_data_uc_),
                           std::begin(compare_data)));

    EXPECT_TRUE(std::equal(std::begin(seq_test_data),
                           std::end(seq_test_data),
                           std::begin(compare_data)));

}

TEST_F(TestRadixSort, testMixCaseSort_part2)
{
    auto compare_data{test_data_mix_};
    auto seq_test_data{test_data_mix_};

    RM::RadixSortMT(std::begin(test_data_mix_), std::end(test_data_mix_),
                 'A','z');

    RS::RadixSortSeq(std::begin(seq_test_data), std::end(seq_test_data),
                'A','z');

    std::sort(std::begin(compare_data),std::end(compare_data),
                         std::less<std::string>());

    EXPECT_TRUE(std::equal(std::begin(test_data_mix_), 
                           std::end(test_data_mix_),
                           std::begin(compare_data)));

    EXPECT_TRUE(std::equal(std::begin(seq_test_data),
                           std::end(seq_test_data),
                           std::begin(compare_data)));
}
