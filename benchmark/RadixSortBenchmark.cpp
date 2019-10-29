
#include <benchmark/benchmark.h>

#include <part1/RadixSortMT.hpp>
#include <part1/RadixSortSeq.hpp>

#include <part2/RadixSortMT.hpp>
#include <part2/RadixSortSeq.hpp>

#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <iterator>

/*
 * Part1 benchmark
*/
static void RadixSortSeqPart1_wordsDictionary_BM(benchmark::State &state)
{
    namespace RS = RadixSortSeq_P1;

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

    for(auto _ : state)
    {
        RS::RadixSortSeq(std::begin(dictionary_txt), std::end(dictionary_txt),
                      'a','z');
    }
}

static void RadixSortMTPart1_wordsDictionary_BM(benchmark::State &state)
{
    namespace RM = RadixSortMT_P1;

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

    for(auto _ : state)
    {
        RM::RadixSortMT(std::begin(dictionary_txt), std::end(dictionary_txt),
                      'a','z');
    }
}

/*
 * Part 2 benchmark
*/
static void RadixSortSeqPart2_wordsDictionary_BM(benchmark::State &state)
{
    namespace RS = RadixSortSeq_P2;

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

    for(auto _ : state)
    {
        RS::RadixSortSeq(std::begin(dictionary_txt), std::end(dictionary_txt),
                      'a','z');
    }
}

static void RadixSortMTPart2_wordsDictionary_BM(benchmark::State &state)
{
    namespace RM = RadixSortMT_P2;

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

    for(auto _ : state)
    {
        RM::RadixSortMT(std::begin(dictionary_txt), std::end(dictionary_txt),
                      'a','z');
    }
}

/*
 * std sort algorithm benchmarks
*/
static void StdStableSort_wordsDictionary_BM(benchmark::State &state)
{

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

    for(auto _ : state)
    {
        std::stable_sort(std::begin(dictionary_txt), std::end(dictionary_txt),
                  std::less<std::string>());
    }
}


static void StdSort_wordsDictionary_BM(benchmark::State &state)
{

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

    for(auto _ : state)
    {
        std::sort(std::begin(dictionary_txt), std::end(dictionary_txt),
                  std::less<std::string>());
    }
}

BENCHMARK(RadixSortSeqPart1_wordsDictionary_BM);
BENCHMARK(RadixSortMTPart1_wordsDictionary_BM);
BENCHMARK(RadixSortSeqPart2_wordsDictionary_BM);
BENCHMARK(RadixSortMTPart2_wordsDictionary_BM);

BENCHMARK(StdStableSort_wordsDictionary_BM);
BENCHMARK(StdSort_wordsDictionary_BM);

BENCHMARK_MAIN();
