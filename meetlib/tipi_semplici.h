#pragma once

#include "expected.hpp"
#include <ostream>
#include <string>
#include <utility>

namespace meetup
{
class Errore
{
public:
    explicit Errore(std::string testo)
        : testo_(std::move(testo)) {}

    auto testo() const
        -> std::string { return testo_; }

private:
    std::string testo_;

    friend auto operator<<(std::ostream &os, Errore const &err)
        -> std::ostream &;
};

template <typename T>
class Valore
{
public:
    auto valore() const
        -> T { return val_; }

protected:
    T val_;

    explicit Valore(T const &val)
        : val_(val)
    {
    }

    explicit Valore(T &&val)
        : val_(std::forward<T>(val))
    {
    }
};

} // namespace meetup