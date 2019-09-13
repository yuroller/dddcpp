#include "tipi_semplici.h"

namespace meetup
{
auto operator<<(std::ostream &os, Errore const &err)
    -> std::ostream &
{
    return os << err.testo_;
}

} // namespace meetup
