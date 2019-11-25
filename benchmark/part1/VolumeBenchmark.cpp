#ifndef __VOLUME_BENCHMARK_H__
#define __VOLUME_BENCHMARK_H__

#include <benchmark/benchmark.h>
#include <../shared/RandomString.hpp>

#include <part1/RadixSortMT.hpp>
#include <part1/RadixSortSeq.hpp>

using namespace shared;

static void RadixSortSeqPart1_wordsDictionary_BM(benchmark::State &state)
{
    namespace RS = RadixSortSeq_P1;
    
    randomString::instance().generate(50u, state.range(0));
    auto dictionary_txt = randomString::instance().randomStrings();

    for(auto _ : state)
    {
        RS::RadixSortSeq(std::begin(dictionary_txt), std::end(dictionary_txt),
                      'a','z');
    }
}

static void RadixSortMTPart1_wordsDictionary_BM(benchmark::State &state)
{
    namespace RM = RadixSortMT_P1;

    randomString::instance().generate(50u, state.range(0));
    auto dictionary_txt = randomString::instance().randomStrings();

    for(auto _ : state)
    {
        RM::RadixSortMT(std::begin(dictionary_txt), std::end(dictionary_txt),
                    'a','z');
    }
}

static void StdStableSort_wordsDictionary_BM(benchmark::State &state)
{
    randomString::instance().generate(50u, state.range(0));
    auto dictionary_txt = randomString::instance().randomStrings();

    for(auto _ : state)
    {
        std::stable_sort(std::begin(dictionary_txt), std::end(dictionary_txt),
                  std::less<std::string>());
    }
}


static void StdSort_wordsDictionary_BM(benchmark::State &state)
{
    randomString::instance().generate(50u, state.range(0));
    auto dictionary_txt = randomString::instance().randomStrings();

    for(auto _ : state)
    {
        std::sort(std::begin(dictionary_txt), std::end(dictionary_txt),
                  std::less<std::string>());
    }
}

BENCHMARK(RadixSortSeqPart1_wordsDictionary_BM)->DenseRange(100'000u, 1'500'000u, 100'000u);
BENCHMARK(RadixSortMTPart1_wordsDictionary_BM)->DenseRange(100'000u, 1'500'000u, 100'000u);

BENCHMARK(StdStableSort_wordsDictionary_BM)->DenseRange(100'000u, 1'500'000u, 100'000u);
BENCHMARK(StdSort_wordsDictionary_BM)->DenseRange(100'000u, 1'500'000u, 100'000u);

int main (int argc, char ** argv) {
    benchmark::Initialize (& argc, argv);
    benchmark::RunSpecifiedBenchmarks ();
    return 0;
}

#endif // __VOLUME_BENCHMARK_H__

