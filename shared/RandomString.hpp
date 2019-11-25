#ifndef __RANDOM_STRING_HPP__
#define __RANDOM_STRING_HPP__

#include <random>

namespace shared
{

class randomString
{
public:
    static randomString& instance()
    {
        static randomString instance_{};
        return instance_;
    }

    randomString()
        :characters_{"abcdefghijklmnopqrstuvwxyz"}
    {
    }

    void generate(std::size_t len = 50u, std::size_t amount = 500'000u)
    {
        std::random_device rdevice;
        std::mt19937 randon_generator(rdevice());
        std::uniform_int_distribution<> rdistribution(0, characters_.size() - 1);
        random_strings_vec.clear();
        random_strings_vec.reserve(amount);

        while(random_strings_vec.size() < amount)
        {
            std::string rand_str;
            rand_str.reserve(len);
            while(rand_str.size() < len)
                rand_str.push_back(characters_[rdistribution(randon_generator)]);

            random_strings_vec.emplace_back(rand_str);
        }
    }

    auto randomStrings() { return random_strings_vec; }

private:
    std::string_view characters_;
    std::vector<std::string> random_strings_vec;
};

}

#endif // __RANDOM_STRING_HPP__

