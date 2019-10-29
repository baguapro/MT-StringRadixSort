
#include <RadixSort.hpp>

#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <iterator>
//#include <execution>


int main (int argc, char **argv)
{
    namespace RS = RadixSort;

    std::ifstream infile("words_alpha.txt");
    std::vector<std::string> dictionary_txt;
    dictionary_txt.reserve(370102);

    std::string word;
    while(std::getline(infile, word))
    {
        word.pop_back();
        dictionary_txt.push_back(word);
    }

    std::random_device rdevice;
    std::mt19937 randon_generator(rdevice());
 
    std::shuffle(std::begin(dictionary_txt), std::end(dictionary_txt), randon_generator);

    RS::RadixSort(std::begin(dictionary_txt), std::end(dictionary_txt),
                      'a','z');
}

