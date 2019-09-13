#include "dto.h"

namespace meetup
{

auto DataMeetupDto::CreaElenco(std::string const &json)
    -> tl::expected<std::vector<DataMeetupDto>, Errore>
{
    return tl::make_unexpected(Errore("TODO"));
}

auto RelatoreDto::CreaElenco(std::string const &json)
    -> tl::expected<std::vector<RelatoreDto>, Errore>
{
    return tl::make_unexpected(Errore("TODO"));
}

auto PropostaDto::CreaElenco(std::string const &json)
    -> tl::expected<std::vector<PropostaDto>, Errore>
{
    return tl::make_unexpected(Errore("TODO"));
}

} // namespace meetup