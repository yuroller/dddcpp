#include "entita.h"
#include "utilita.h"

namespace meetup
{

auto Relatore::Crea(RelatoreDto const &relatore)
    -> tl::expected<Relatore, Errore>
{
    auto expCodice = CodiceRelatore::Crea(relatore.codice());
    if (!expCodice)
    {
        return tl::make_unexpected(expCodice.error());
    }

    auto expNome = NomeRelatore::Crea(relatore.nome());
    if (!expNome)
    {
        return tl::make_unexpected(expNome.error());
    }

    auto expEmail = IndirizzoEmail::Crea(relatore.email());
    if (!expEmail)
    {
        return tl::make_unexpected(expEmail.error());
    }

    auto optTwitter = relatore.twitter();
    if (!optTwitter)
    {
        return Relatore(*expCodice, *expNome, *expEmail, tl::nullopt);
    }

    auto twitter = IndirizzoTwitter::Crea(*optTwitter);
    if (!twitter)
    {
        return tl::make_unexpected(twitter.error());
    }

    return Relatore(*expCodice, *expNome, *expEmail, *twitter);
}

auto Proposta::Crea(std::function<bool(date::year_month_day)> verificaDataMeetup,
                                   PropostaDto const &proposta)
    -> tl::expected<Proposta, Errore>
{
    auto expCodice = CodicePresentazione::Crea(proposta.codice());
    if (!expCodice)
    {
        return tl::make_unexpected(expCodice.error());
    }

    auto expCodiceRelatore = CodiceRelatore::Crea(proposta.codiceRelatore());
    if (!expCodiceRelatore)
    {
        return tl::make_unexpected(expCodiceRelatore.error());
    }

    auto expTitolo = TitoloPresentazione::Crea(proposta.titolo());
    if (!expTitolo)
    {
        return tl::make_unexpected(expTitolo.error());
    }

    auto expSommario = SommarioPresentazione::Crea(proposta.sommario());
    if (!expSommario)
    {
        return tl::make_unexpected(expSommario.error());
    }

    auto expDisponibilitaRelatore = [&verificaDataMeetup, &proposta]()
        -> tl::expected<DisponibilitaRelatore, Errore> {
        switch (proposta.tipoDisponibilita())
        {
        case TipoDisponibilita::SempreDisponibile:
            return DisponibilitaRelatore(DisponibilitaInQualunqueData());
        case TipoDisponibilita::DateSpecifiche:
            return Required(proposta.dateDisponibilita())
                .and_then([&verificaDataMeetup](std::vector<date::year_month_day> const &date)
                              -> tl::expected<DisponibilitaInDateSpecifiche, Errore> {
                    return DisponibilitaInDateSpecifiche::Crea(verificaDataMeetup, date);
                })
                .and_then([](DisponibilitaInDateSpecifiche const &dateSpecifiche)
                              -> tl::expected<DisponibilitaRelatore, Errore> {
                    return DisponibilitaRelatore(dateSpecifiche);
                });
            break;
        case TipoDisponibilita::DopoUnaData:
            return Required(proposta.dataInizioDisponibilita())
                .and_then([](date::year_month_day data)
                              -> tl::expected<DisponibilitaDopoUnaData, Errore> {
                    return DisponibilitaDopoUnaData::Crea(data);
                })
                .and_then([](DisponibilitaDopoUnaData const &dopoUnaData)
                              -> tl::expected<DisponibilitaRelatore, Errore> {
                    return DisponibilitaRelatore(dopoUnaData);
                });
        default:
            break;
        }

        return tl::make_unexpected(Errore("Tipo disponibilita' non supportato"));
    }();

    if (!expDisponibilitaRelatore)
    {
        return tl::make_unexpected(expDisponibilitaRelatore.error());
    }

    return Proposta(*expCodice, *expCodiceRelatore,
                                   *expTitolo, *expSommario, *expDisponibilitaRelatore);
}

} // namespace meetup