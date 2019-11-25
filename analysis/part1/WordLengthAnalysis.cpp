
#include <shared/RandomString.hpp>

#include <part1/RadixSortMT.hpp>

#include <iostream>
#include <iterator>
#include <string>

using namespace shared;

int main (int argc, char **argv)
{
    if(argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " WORD LENGTH" << std::endl;
        return 1;
    }

    const auto length = std::stoul(argv[1],nullptr);

    namespace RM = RadixSortMT_P1;

    randomString::instance().generate(length,500'000u);
    auto dictionary_txt = randomString::instance().randomStrings();

    RM::RadixSortMT(std::begin(dictionary_txt), std::end(dictionary_txt),
                    'a','z');

    return 0;
}

