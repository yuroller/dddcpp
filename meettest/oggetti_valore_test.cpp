#include "oggetti_valore.h"
#include "catch.hpp"
#include <sstream>

using namespace meetup;

auto SezioneNomeRelatore = "[NomeRelatore]";

TEST_CASE("Contiene un nome di lunghezza valido", SezioneNomeRelatore)
{
    auto s = NomeRelatore::Crea("Yuri Valentini");
    REQUIRE(s);
    REQUIRE(s->valore() == "Yuri Valentini");
}

TEST_CASE("Non contiene un nome di lunghezza nulla", SezioneNomeRelatore)
{
    auto s = NomeRelatore::Crea("");
    REQUIRE(!s);
}

TEST_CASE("Non contiene un nome di lunghezza eccessiva", SezioneNomeRelatore)
{
    // cit. Fantozzi alla Riscossa
    auto s = NomeRelatore::Crea("Direttore Naturale, Gran Mascalzon., Lup. Man., Pezz. di Merd., Dottor Barambani");
    REQUIRE(!s);
}

auto SezioneIndirizzoEmail = "[IndirizzoEmail]";

TEST_CASE("Contiene un indirizzo email con formato valido", SezioneIndirizzoEmail)
{
    auto e = IndirizzoEmail::Crea("yv@example.com");
    REQUIRE(e);
    REQUIRE(e->valore() == "yv@example.com");
}

TEST_CASE("Non contiene un indirizzo email con formato non valido", SezioneIndirizzoEmail)
{
    auto e = IndirizzoEmail::Crea("yv at example.com");
    REQUIRE(!e);
}

auto SezioneIndirizzoTwitter = "[IndirizzoTwitter]";

TEST_CASE("Contiene un indirizzo twitter con formato valido", SezioneIndirizzoTwitter)
{
    auto e = IndirizzoTwitter::Crea("@yvexample");
    REQUIRE(e);
    REQUIRE(e->valore() == "@yvexample");
}

TEST_CASE("Non contiene un indirizzo twitter con formato non valido", SezioneIndirizzoTwitter)
{
    auto e = IndirizzoTwitter::Crea("@@invalid");
    REQUIRE(!e);
}

auto SezioneCodiceRelatore = "[CodiceRelatore]";

TEST_CASE("Contiene un codice relatore con formato valido", SezioneCodiceRelatore)
{
    auto id = CodiceRelatore::Crea("yv");
    REQUIRE(id);
    REQUIRE(id->valore() == "yv");
}

TEST_CASE("Non contiene un codice relatore con formato non valido", SezioneCodiceRelatore)
{
    auto id = CodiceRelatore::Crea("yuriv");
    REQUIRE(!id);
}

auto SezioneCodicePresentazione = "[CodicePresentazione]";

TEST_CASE("Contiene un codice con limiti validi", SezioneCodicePresentazione)
{
    auto i = CodicePresentazione::Crea(5);
    REQUIRE(i);
    REQUIRE(i->valore() == 5);
}

TEST_CASE("Non contiene un codice eccessivamente piccolo", SezioneCodicePresentazione)
{
    auto i = CodicePresentazione::Crea(-1);
    REQUIRE(!i);
}

TEST_CASE("Non contiene un codice eccessivamente grande", SezioneCodicePresentazione)
{
    auto i = CodicePresentazione::Crea(1000000);
    REQUIRE(!i);
}

auto SezioneDateMeetup = "[DateMeetup]";

TEST_CASE("Contiene una data valida", SezioneDateMeetup)
{
    auto d = DateMeetup::Crea({date::year(2019) / 9 / 12});
    REQUIRE(d);
    REQUIRE(d->valore().size() == 1);
    auto v0 = d->valore().at(0);
    REQUIRE(v0.year() == date::year(2019));
    REQUIRE(v0.month() == date::month(9));
    REQUIRE(v0.day() == date::day(12));
}

TEST_CASE("Non contiene una data non valida", SezioneDateMeetup)
{
    auto d = DateMeetup::Crea({date::year(2019) / 2 / 30});
    REQUIRE(!d);
}

TEST_CASE("Non contiene un elenco vuoto", SezioneDateMeetup)
{
    auto d = DateMeetup::Crea({});
    REQUIRE(!d);
}

auto SezioneDateSpecifiche = "[DateSpecifiche]";

TEST_CASE("Contiene l'unica data disponbile", SezioneDateSpecifiche)
{
    auto verificaDataMeetup = [](date::year_month_day dataDisponibilita) {
        return dataDisponibilita == date::year_month_day(date::year(2019), date::month(9), date::day(12));
    };

    auto expDataSpecifica = DisponibilitaInDateSpecifiche::Crea(
        verificaDataMeetup,
        std::vector<date::year_month_day>{date::year(2019) / 9 / 12});
    REQUIRE(expDataSpecifica);
    REQUIRE(expDataSpecifica->valore().size() == 1);
    REQUIRE(expDataSpecifica->valore().at(0) == date::year(2019) / 9 / 12);
}

TEST_CASE("Non contiene una data non disponbile", SezioneDateSpecifiche)
{
    auto verificaDataMeetup = [](date::year_month_day dataDisponibilita) {
        return false;
    };

    auto expDataSpecifica = DisponibilitaInDateSpecifiche::Crea(
        verificaDataMeetup,
        std::vector<date::year_month_day>{date::year(2019) / 9 / 12});
    REQUIRE(!expDataSpecifica);
}
