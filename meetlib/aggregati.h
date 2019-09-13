#pragma once

#include "entita.h"
#include "tipi_semplici.h"
#include "expected.hpp"
#include <utility>
#include <vector>

namespace meetup
{

class ProposteDiUnRelatore
{
public:
    static auto Crea(Relatore relatore, std::vector<Proposta> proposte)
        -> tl::expected<ProposteDiUnRelatore, Errore>;

    auto relatore() const
        -> Relatore { return relatore_; }

    auto proposte() const
        -> std::vector<Proposta> { return proposte_; }

private:
    Relatore relatore_;
    std::vector<Proposta> proposte_;

    ProposteDiUnRelatore(Relatore relatore, std::vector<Proposta> proposte)
        : relatore_(std::move(relatore)),
          proposte_(std::move(proposte))
    {
    }
};

} // namespace meetup