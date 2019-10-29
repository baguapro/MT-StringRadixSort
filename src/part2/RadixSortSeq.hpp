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
*/

#include <vector>
#include <algorithm>
#include <string_view>
#include <iterator>

namespace RadixSortSeq_P2
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
*
* Note: this version uses string_view to prevent coping of the
* strings when reordering
*/
template<typename RandomItr>
void RadixSortSeq(RandomItr begin, RandomItr end,char lower,char upper)
{
    using iterator_category = typename std::iterator_traits<RandomItr>::iterator_category();
    static_assert(!std::is_same_v<iterator_category, std::random_access_iterator_tag>,
                  "radix sort requires random access iterators");
   
    std::vector<std::string_view> sv_vec(begin, end); 

    auto max_index = (*(std::max_element(std::begin(sv_vec),std::end(sv_vec),
                                        [&](const auto &left, const auto &right)
                                        {
                                            return (left.size() < right.size());
                                        })
                       )).size();

    const auto sorting_size = sv_vec.size() - 1; 
    const auto bucket_size = ((upper - lower) + 1);
    std::vector<int> indexing_bucket(bucket_size, 0);
    std::vector<std::string_view> temp_container(sv_vec.size(),"");
   
    // its basically counting sort from this point onwards
   for(auto index=max_index;index>0u;--index) 
   {
        std::for_each(std::begin(sv_vec), std::end(sv_vec), [&](const auto &word) 
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
            int char_index = (sv_vec[i].size() < index) ? 0 : (sv_vec[i][index-1] - lower);
            temp_container[indexing_bucket[char_index]-1].swap(sv_vec[i]);
            --indexing_bucket[char_index];
        };
    
        temp_container.swap(sv_vec);
        std::fill(indexing_bucket.begin(), indexing_bucket.end(), 0);
   }

    // Give the appearence of inplace sorting
    std::vector<std::string> convert;
    convert.reserve(sv_vec.size());
    for(auto &str : sv_vec)
        convert.emplace_back(str);

    std::swap_ranges(begin,end,convert.begin());


}

}
