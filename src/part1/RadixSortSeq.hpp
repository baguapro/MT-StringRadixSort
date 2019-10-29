/* Author: Adrian Phung
 * A modified version of the radix sort algorithm given at: https://www.geeksforgeeks.org/radix-sort/
 * Implements a sequential radix sort algorithm for string data types, 
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

#include <vector>
#include <algorithm>
#include <string_view>
#include <iterator>

namespace RadixSortSeq_P1
{

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
void RadixSortSeq(RandomItr begin, RandomItr end,char lower,char upper)
{
    using iterator_category = typename std::iterator_traits<RandomItr>::iterator_category();
    static_assert(!std::is_same_v<iterator_category, std::random_access_iterator_tag>,
                  "radix sort requires random access iterators");
   
    auto container_size = 1u;
    auto max_index = (*(std::max_element(begin,end,
                                        [&](const auto &left, const auto &right)
                                        {
                                            ++container_size;
                                            return (left.size() < right.size());
                                        })
                       )).size();

    const auto sorting_size = container_size - 1; 
    const auto bucket_size = ((upper - lower) + 1);
    std::vector<int> indexing_bucket(bucket_size, 0);
    std::vector<typename std::iterator_traits<RandomItr>::value_type> 
                temp_container(container_size + 1, "");
   
    // its basically counting sort from this point onwards
   for(auto index=max_index;index>0u;--index) 
   {
        std::for_each(begin, end, [&](const auto &word) 
        {
            int char_index = (word.size() < index) ? 0 : ((word[index-1] - lower));
            ++indexing_bucket[char_index];
        });
    
        // sum up indexing_bucket; indexing_bucket will hold last 
        // index for the char at each strings index
        for(auto i=1;i<bucket_size;i++)
        {
            indexing_bucket[i] += indexing_bucket[i-1];
        }
    
        for(int i=sorting_size;i>=0;--i) 
        {
            int char_index = (begin[i].size() < index) ? 0 : (begin[i][index-1] - lower);
            temp_container[indexing_bucket[char_index]-1].swap(begin[i]);
            --indexing_bucket[char_index];
        };
    
        std::swap_ranges(begin,end,temp_container.begin());
        std::fill(indexing_bucket.begin(), indexing_bucket.end(), 0);
   }

}

}
