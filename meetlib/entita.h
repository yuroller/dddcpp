#pragma once

#include "tipi_semplici.h"
#include "dto.h"
#include "oggetti_valore.h"
#include "expected.hpp"
#include "optional.hpp"
#include <functional>
#include <vector>

namespace meetup
{

class Relatore
{
public:
    static auto Crea(RelatoreDto const &relatore)
        -> tl::expected<Relatore, Errore>;

    Relatore(CodiceRelatore codice, NomeRelatore nome, IndirizzoEmail email,
             tl::optional<IndirizzoTwitter> twitter)
        : codice_(std::move(codice)),
          nome_(std::move(nome)),
          email_(std::move(email)),
          twitter_(std::move(twitter))
    {
    }

    auto codice() const
        -> CodiceRelatore { return codice_; }

    auto nome() const
        -> NomeRelatore { return nome_; }

    auto email() const
        -> IndirizzoEmail { return email_; }

    auto twitter() const
        -> tl::optional<IndirizzoTwitter> { return twitter_; }

private:
    CodiceRelatore codice_;
    NomeRelatore nome_;
    IndirizzoEmail email_;
    tl::optional<IndirizzoTwitter> twitter_;
};

class Proposta
{
public:
    static auto Crea(std::function<bool(date::year_month_day)> verificaDataMeetup,
                     PropostaDto const &proposta)
        -> tl::expected<Proposta, Errore>;

    auto codice() const
        -> CodicePresentazione { return codice_; }

    auto codiceRelatore() const
        -> CodiceRelatore { return codiceRelatore_; }

    auto titolo() const
        -> TitoloPresentazione { return titolo_; }

    auto sommario() const
        -> SommarioPresentazione { return sommario_; }

    auto disponibilitaRelatore() const
        -> DisponibilitaRelatore { return disponibilitaRelatore_; }

private:
    CodicePresentazione codice_;
    CodiceRelatore codiceRelatore_;
    TitoloPresentazione titolo_;
    SommarioPresentazione sommario_;
    DisponibilitaRelatore disponibilitaRelatore_;

    Proposta(CodicePresentazione codice,
                            CodiceRelatore codiceRelatore,
                            TitoloPresentazione titolo,
                            SommarioPresentazione sommario,
                            DisponibilitaRelatore disponibilitaRelatore)
        : codice_(std::move(codice)),
          codiceRelatore_(std::move(codiceRelatore)),
          titolo_(std::move(titolo)),
          sommario_(std::move(sommario)),
          disponibilitaRelatore_(std::move(disponibilitaRelatore))
    {
    }
};

} // namespace meetup