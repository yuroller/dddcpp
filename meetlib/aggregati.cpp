#include "aggregati.h"
#include <algorithm>

namespace meetup
{
auto ProposteDiUnRelatore::Crea(Relatore relatore, std::vector<Proposta> proposte)
    -> tl::expected<ProposteDiUnRelatore, Errore>
{
    if (proposte.empty())
    {
        return tl::make_unexpected(Errore("Deve esserci almeno una proposta di un relatore"));
    }

    auto stessoCodice = std::find_if_not(
                            std::cbegin(proposte),
                            std::cend(proposte),
                            [codice = relatore.codice().valore()](Proposta const &p) {
                                return p.codiceRelatore().valore() == codice;
                            }) == std::cend(proposte);

    if (!stessoCodice)
    {
        return tl::make_unexpected(Errore("Il codice relatore di tutte le proposte"
                                          " deve corripondere a quello del relatore"));
    }

    return ProposteDiUnRelatore(std::move(relatore), std::move(proposte));
}
} // namespace meetup