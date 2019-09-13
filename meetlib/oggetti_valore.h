
#pragma once

#include "tipi_semplici.h"
#include "expected.hpp"
#include "date.h"
#include <functional>
#include <string>
#include <utility>
#include <vector>
#include <variant>

namespace meetup
{

class IndirizzoEmail : public Valore<std::string>
{
public:
    static auto Crea(std::string str)
        -> tl::expected<IndirizzoEmail, Errore>;

private:
    explicit IndirizzoEmail(std::string str)
        : Valore<std::string>(std::move(str)) {}
};

class IndirizzoTwitter : public Valore<std::string>
{
public:
    static auto Crea(std::string str)
        -> tl::expected<IndirizzoTwitter, Errore>;

private:
    explicit IndirizzoTwitter(std::string str)
        : Valore<std::string>(std::move(str)) {}
};

class NomeRelatore : public Valore<std::string>
{
public:
    static auto Crea(std::string str)
        -> tl::expected<NomeRelatore, Errore>;

private:
    explicit NomeRelatore(std::string nomeRelatore)
        : Valore<std::string>(std::move(nomeRelatore))
    {
    }
};

class CodiceRelatore : public Valore<std::string>
{
public:
    static auto Crea(std::string str)
        -> tl::expected<CodiceRelatore, Errore>;

private:
    explicit CodiceRelatore(std::string codice)
        : Valore<std::string>(std::move(codice))
    {
    }
};

class CodicePresentazione : public Valore<int>
{
public:
    static auto Crea(int codice)
        -> tl::expected<CodicePresentazione, Errore>;

private:
    explicit CodicePresentazione(int codice)
        : Valore<int>(codice)
    {
    }
};

class TitoloPresentazione : public Valore<std::string>
{
public:
    static auto Crea(std::string str)
        -> tl::expected<TitoloPresentazione, Errore>;

private:
    explicit TitoloPresentazione(std::string titoloPresentazione)
        : Valore<std::string>(std::move(titoloPresentazione))
    {
    }
};

class SommarioPresentazione : public Valore<std::string>
{
public:
    static auto Crea(std::string str)
        -> tl::expected<SommarioPresentazione, Errore>;

private:
    explicit SommarioPresentazione(std::string sommarioPresentazione)
        : Valore<std::string>(std::move(sommarioPresentazione))
    {
    }
};

class DateMeetup : public Valore<std::vector<date::year_month_day>>
{
public:
    static auto Crea(std::vector<date::year_month_day> date)
        -> tl::expected<DateMeetup, Errore>;

private:
    explicit DateMeetup(std::vector<date::year_month_day> date)
        : Valore<std::vector<date::year_month_day>>(std::move(date))
    {
    }
};

class DisponibilitaInQualunqueData
{
};

class DisponibilitaInDateSpecifiche : public Valore<std::vector<date::year_month_day>>
{
public:
    static auto Crea(std::function<bool(date::year_month_day)> verificaDataMeetup,
                     std::vector<date::year_month_day> date)
        -> tl::expected<DisponibilitaInDateSpecifiche, Errore>;

private:
    explicit DisponibilitaInDateSpecifiche(std::vector<date::year_month_day> date)
        : Valore<std::vector<date::year_month_day>>(std::move(date))
    {
    }
};

class DisponibilitaDopoUnaData : public Valore<date::year_month_day>
{
public:
    static auto Crea(date::year_month_day data)
        -> tl::expected<DisponibilitaDopoUnaData, Errore>;

private:
    explicit DisponibilitaDopoUnaData(date::year_month_day data)
        : Valore<date::year_month_day>(data)
    {
    }
};

using UnioneDisponibilita = std::variant<DisponibilitaInQualunqueData,
                                         DisponibilitaInDateSpecifiche, DisponibilitaDopoUnaData>;

class DisponibilitaRelatore : public Valore<UnioneDisponibilita>
{
public:
    explicit DisponibilitaRelatore(UnioneDisponibilita disp)
        : Valore<UnioneDisponibilita>(std::move(disp))
    {
    }
};

} // namespace meetup