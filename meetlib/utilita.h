#pragma once
#include "tipi_semplici.h"
#include "expected.hpp"
#include "optional.hpp"
#include <algorithm>
#include <iterator>
#include <vector>

namespace meetup
{
template <typename T>
auto FoldExpected(std::vector<tl::expected<T, Errore>> const &ary)
    -> tl::expected<std::vector<T>, Errore>
{
    std::vector<T> result;
    for (auto &exp : ary)
    {
        if (!exp)
        {
            return tl::make_unexpected(exp.error());
        }

        result.push_back(*exp);
    }

    return result;
}

template <typename T>
auto Required(tl::optional<T> const &opt)
    -> tl::expected<T, Errore>
{
    if (!opt)
    {
        return tl::make_unexpected(Errore("Valore obbligatorio non disponibile"));
    }

    return *opt;
}

template <typename T, typename F>
auto Apply(std::vector<T> const &ary, F func)
    -> std::vector<decltype(func(ary[0]))>
{
    auto result = std::vector<decltype(func(ary[0]))>();
    for (auto const &val : ary)
    {
        std::transform(std::cbegin(ary), std::cend(ary),
                       std::back_inserter(result), func);
    }

    return result;
}

} // namespace meetup