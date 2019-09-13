#include "entita.h"
#include "dto.h"
#include "catch.hpp"

using namespace meetup;

auto SezioneRelatore = "[Relatore]";

TEST_CASE("Contiene informazioni valide senza account twitter", SezioneRelatore)
{
    auto dto = RelatoreDto("yv", "Yuri Valentini", "yv@example.com", tl::nullopt);
    auto r = Relatore::Crea(dto);
    REQUIRE(r);
    REQUIRE(r->codice().valore() == "yv");
    REQUIRE(r->nome().valore() == "Yuri Valentini");
    REQUIRE(r->email().valore() == "yv@example.com");
    REQUIRE(!r->twitter());
}

TEST_CASE("Contiene informazioni valide con account twitter", SezioneRelatore)
{
    auto dto = RelatoreDto("yv", "Yuri Valentini", "yv@example.com", "@yvexample");
    auto r = Relatore::Crea(dto);
    REQUIRE(r);
    REQUIRE(r->codice().valore() == "yv");
    REQUIRE(r->nome().valore() == "Yuri Valentini");
    REQUIRE(r->email().valore() == "yv@example.com");
    auto twitter = r->twitter();
    REQUIRE(twitter);
    REQUIRE(twitter->valore() == "@yvexample");
}