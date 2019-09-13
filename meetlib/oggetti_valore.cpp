#include "oggetti_valore.h"
#include "utilita.h"
#include <algorithm>
#include <iterator>
#include <regex>
#include <set>

namespace meetup
{

int constexpr NomeRelatoreLunghezzaMax = 50;
int constexpr CodiceRelatoreLunghezzaMax = 2;
int constexpr TitoloPresentazioneLunghezzaMax = 80;
int constexpr SommarioPresentazioneLunghezzaMax = 1000;
int constexpr CodicePresentazioneMinimo = 0;
int constexpr CodicePresentazioneMassimo = 999999;

template <size_t lunghezzaMax>
auto CreaStringaConLunghezzaMax(std::string str)
    -> tl::expected<std::string, Errore>
{
    if (str.empty())
    {
        return tl::make_unexpected(
            Errore("la stringa non puo' essere vuota"));
    }

    if (str.length() > lunghezzaMax)
    {
        return tl::make_unexpected(
            Errore("la stringa supera la lunghezza massima consentita"));
    }

    return str;
}

template <int minimo, int massimo>
auto CreaInteroInIntervallo(int i)
    -> tl::expected<int, Errore>
{
    if (i < minimo)
    {
        return tl::make_unexpected(
            Errore("intero troppo piccolo"));
    }

    if (i > massimo)
    {
        return tl::make_unexpected(
            Errore("intero troppo grande"));
    }

    return i;
}

static auto CreaDataValida(date::year_month_day data)
    -> tl::expected<date::year_month_day, Errore>
{
    if (!data.ok())
    {
        return tl::make_unexpected(
            Errore("data non valida"));
    }

    return data;
}

static auto CreaElencoDate(std::vector<date::year_month_day> date)
    -> tl::expected<std::vector<date::year_month_day>, Errore>
{
    if (date.empty())
    {
        return tl::make_unexpected(
            Errore("Occorre specificare almeno una data"));
    }

    auto totaleElementiUnici = std::set<date::year_month_day>(
                                   std::cbegin(date), std::cend(date))
                                   .size();
    if (date.size() != totaleElementiUnici)
    {
        return tl::make_unexpected(
            Errore("Le date non possono essere duplicate"));
    }

    return FoldExpected(Apply(date, CreaDataValida));
}

auto IndirizzoEmail::Crea(std::string str)
    -> tl::expected<IndirizzoEmail, Errore>
{
    std::regex const regex("^\\S+@\\S+$");
    if (!std::regex_match(str, regex))
    {
        return tl::make_unexpected(
            Errore("formato indirizzo email non valido"));
    }

    return IndirizzoEmail(std::move(str));
}

auto IndirizzoTwitter::Crea(std::string str)
    -> tl::expected<IndirizzoTwitter, Errore>
{
    std::regex const regex("^@?(\\w){1,15}$");
    if (!std::regex_match(str, regex))
    {
        return tl::make_unexpected(
            Errore("formato indirizzo twitter non valido"));
    }

    return IndirizzoTwitter(std::move(str));
}

auto NomeRelatore::Crea(std::string str)
    -> tl::expected<NomeRelatore, Errore>
{
    return CreaStringaConLunghezzaMax<NomeRelatoreLunghezzaMax>(std::move(str))
        .and_then([](std::string val)
                      -> tl::expected<NomeRelatore, Errore> {
            return NomeRelatore(std::move(val));
        });
}

auto CodiceRelatore::Crea(std::string str)
    -> tl::expected<CodiceRelatore, Errore>
{
    return CreaStringaConLunghezzaMax<CodiceRelatoreLunghezzaMax>(std::move(str))
        .and_then([](std::string val)
                      -> tl::expected<CodiceRelatore, Errore> {
            return CodiceRelatore(std::move(val));
        });
}

auto CodicePresentazione::Crea(int codice)
    -> tl::expected<CodicePresentazione, Errore>
{
    return CreaInteroInIntervallo<CodicePresentazioneMinimo, CodicePresentazioneMassimo>(codice)
        .and_then([](int val)
                      -> tl::expected<CodicePresentazione, Errore> {
            return CodicePresentazione(val);
        });
}

auto TitoloPresentazione::Crea(std::string str)
    -> tl::expected<TitoloPresentazione, Errore>
{
    return CreaStringaConLunghezzaMax<TitoloPresentazioneLunghezzaMax>(std::move(str))
        .and_then([](std::string val)
                      -> tl::expected<TitoloPresentazione, Errore> {
            return TitoloPresentazione(std::move(val));
        });
}

auto SommarioPresentazione::Crea(std::string str)
    -> tl::expected<SommarioPresentazione, Errore>
{
    return CreaStringaConLunghezzaMax<SommarioPresentazioneLunghezzaMax>(std::move(str))
        .and_then([](std::string val)
                      -> tl::expected<SommarioPresentazione, Errore> {
            return SommarioPresentazione(std::move(val));
        });
}

auto DateMeetup::Crea(std::vector<date::year_month_day> date)
    -> tl::expected<DateMeetup, Errore>
{
    return CreaElencoDate(std::move(date))
        .and_then([](std::vector<date::year_month_day> date)
                      -> tl::expected<DateMeetup, Errore> {
            return DateMeetup(std::move(date));
        });
}

auto DisponibilitaInDateSpecifiche::Crea(
    std::function<bool(date::year_month_day)> verificaDataMeetup,
    std::vector<date::year_month_day> date)
    -> tl::expected<DisponibilitaInDateSpecifiche, Errore>
{
    return CreaElencoDate(date)
        .and_then([&verificaDataMeetup](std::vector<date::year_month_day> dateEsistenti)
                      -> tl::expected<DisponibilitaInDateSpecifiche, Errore> {
            if (std::cend(dateEsistenti) != find_if_not(
                                                std::cbegin(dateEsistenti),
                                                std::cend(dateEsistenti),
                                                [&verificaDataMeetup](date::year_month_day dataDisponibilita) {
                                                    return verificaDataMeetup(dataDisponibilita);
                                                }))
            {
                return tl::make_unexpected(Errore("Una data di disponibilita' non e' in una data di meetup"));
            }

            return DisponibilitaInDateSpecifiche(std::move(dateEsistenti));
        });
}

auto DisponibilitaDopoUnaData::Crea(date::year_month_day data)
    -> tl::expected<DisponibilitaDopoUnaData, Errore>
{
    return CreaDataValida(data)
        .and_then([](date::year_month_day dataValida)
                      -> tl::expected<DisponibilitaDopoUnaData, Errore> {
            return DisponibilitaDopoUnaData(dataValida);
        });
}

} // namespace meetup