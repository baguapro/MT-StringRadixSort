
/* Author: Adrian Phung
 * A modified version of the radix sort algorithm given at: https://www.geeksforgeeks.org/radix-sort/
 * Implements a parallel radix sort algorithm for string data types, 
 *
 * Compiler requirements: C++17 compilient compiler and STL
 *
 * License: MIT
 *
 * Flame retardant section
 * It is the clients responsibility to ensure that the range passed to the algorithm and the lower 
 * and upper sorting bounds are valid in terms of both ‘object’ and order.
 *
 * Note: This is the initial sequential version developed for the blog post
 * https://www.themindseye.io/multi-threaded-radix-sort/
 * The post discusses the process of developing and analysing a simple sorting
 * algorithm
*/

#include <algorithm>
#include <future>
#include <vector>
#include <string_view>
#include <iterator>

namespace RadixSortMT_P1
{

// Result type of the bucket calculation process
using BucketDataType = std::tuple<std::vector<uint_fast64_t>,std::size_t>;

// Function object that creates a bucket of the total of the given
// significant bit for the letters at the given index
template<typename RandomItr>
class RadixBucket
{
public:

    RadixBucket(RandomItr begin, 
                RandomItr end,
                uint_fast64_t index, 
                int size, 
                char sigBit)
        :begin_(begin)
        ,end_(end)
        ,index_(index)
        ,bucket_(size, 0)
        ,sig_bit_(sigBit)
        { }
    
    auto operator()()
    {
        std::for_each(begin_, end_, [&](const auto &word) 
        {
            int char_index = (word.size() < index_) ? 0 : ((word[index_-1] - sig_bit_));
            ++bucket_[char_index];

        });
        
        // sum up the values in each subsequent slot in the bucket 
        for(auto i = 1u; i < bucket_.size(); ++i)
            bucket_[i] += bucket_[i-1];

        // return both the bucket and index as these are required for the
        // final sorting section 
        return std::make_tuple(std::move(bucket_), index_);
    }
    
private:
    RandomItr begin_; 
    RandomItr end_;
    const uint_fast64_t index_;
    std::vector<uint_fast64_t> bucket_;
    const char sig_bit_;
         
};

/*
* Performs radix sort on the range between 'begin' and 'end'
* The sort will be in the order 'lower' to 'upper'
* pre-condition:
* begin - end must be valid ranges
* lower - upper must be a valid order 
* (ie. lower must be lower than upper, obvious really!!!)
* All the characters in the range to be sorted (begin,end)
* must be within the lower - upper order
*/
template<typename RandomItr>
void RadixSortMT(RandomItr begin, 
                 RandomItr end,
                 char lower,
                 char upper)
{
    auto container_size = 1u;
    auto max_index = (*(std::max_element(begin,end,
                         [&](const auto &left, const auto &right)
                         {
                             ++container_size;
                             return (left.size() < right.size());
                         })
                       )).size();


    std::vector<std::future<BucketDataType>> futures;

    for(auto index = max_index; index > 0; --index)
    {
        RadixBucket rb{begin, end, index, 
                        (upper - lower)+1, lower};

        futures.push_back(std::async(std::launch::async,rb));
    }
   
    std::vector<typename std::iterator_traits<RandomItr>::value_type
                > temp_container(container_size, "");
   
    std::vector<BucketDataType> bucket_results;
    for(auto &fut : futures)
    {
        bucket_results.emplace_back(fut.get());
    }
   
    const auto sorting_size = container_size - 1; 
    for(auto &[bucket,index] : bucket_results)
    {
        // get the sorting bucket and index for each bucket function object
        // and sort the range according to the calculated significant bit for
        // the letter in the word at the index.
        for(int i=sorting_size;i>=0;--i)
        {
            int char_index = (begin[i].size() < index) ? 0 : 
                             (begin[i][index-1] - lower);
            std::swap(
                temp_container[bucket[char_index]-1], begin[i]
            );
            --bucket[char_index];
        }
        
        std::swap_ranges(begin,end,temp_container.begin());
    }
}

}
