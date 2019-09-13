#include "entita.h"
#include "dto.h"
#include "oggetti_valore.h"
#include "tipi_semplici.h"

#include "optional.hpp"
#include "expected.hpp"
#include "date.h"
#include "utilita.h"

#include <iostream>
#include <string>
#include <vector>

using namespace meetup;

auto main()
    -> int
{
    ////////////////////////////////////////////
    // dipendenze (es. file di configurazione date_meetup.json)
    
    auto dateMeetupDaConfigurazione = std::vector<tl::expected<date::year_month_day, Errore>>{
        date::year{2019} / 9 / 12,
        date::year{2019} / 10 / 10,
        date::year{2019} / 11 / 14,
        date::year{2019} / 12 / 12
    };

    auto dateMeetupValidate = FoldExpected(dateMeetupDaConfigurazione);
    if (!dateMeetupValidate)
    {
        std::cerr << "Errore file di configurazione: " << dateMeetupValidate.error() << std::endl;
        return -1;
    }

    ///////////////////////////////////////////////
    // input da sistema esterno (es. file proposte.json)

    auto relatoriDto = std::vector<RelatoreDto>{
        RelatoreDto("yv", "Yuri Valentini", "yv@example.com", tl::nullopt),
        RelatoreDto("zp", "Zio Paperone", "zp@example.com", "@ziopaperone"),
    };

    auto proposteDto = std::vector<PropostaDto>{
        PropostaDto(1000, "yv", "Esperimenti di DDD in C++",
                                           "Da Event Storming a modello DDD a implementazione in C++17",
                                           TipoDisponibilita::DateSpecifiche,
                                           std::vector<date::year_month_day>{date::year{2019} / 9 / 12, date::year{2019} / 10 / 10},
                                           tl::nullopt),

        PropostaDto(1001, "yv", "Bare metal programming in C++",
                                           "Programmazione di un microcontrollore stm32 in C++",
                                           TipoDisponibilita::DopoUnaData,
                                           tl::nullopt,
                                           date::year{2019} / 10 / 1),

        PropostaDto(2000, "zp", "PaperBitDollar",
                                           "Realizziamo una cryptovaluta con C++",
                                           TipoDisponibilita::SempreDisponibile,
                                           tl::nullopt,
                                           tl::nullopt)};

    ///////////////////////////////////////////////
    // validazione input

    auto relatori = FoldExpected(
        Apply(relatoriDto,
              [](RelatoreDto const &relatore)
                  -> tl::expected<Relatore, Errore> {
                  return Relatore::Crea(relatore);
              }));

    if (!relatori)
    {
        std::cerr << "Errore relatore in input: " << relatori.error() << std::endl;
        return -2;
    }

    auto verificaDataMeetup = [dateMeetup = *dateMeetupValidate](date::year_month_day dataProposta)
    ->bool {
        return std::cend(dateMeetup) != find(
            std::cbegin(dateMeetup),
            std::cend(dateMeetup),
            dataProposta);
    };

    auto proposte = FoldExpected(
        Apply(proposteDto,
              [&verificaDataMeetup](PropostaDto const &proposta)
                  -> tl::expected<Proposta, Errore> {
                  return Proposta::Crea(verificaDataMeetup, proposta);
              }));

    if (!proposte)
    {
        std::cerr << "Errore proposta in input: " << proposte.error() << std::endl;
        return -2;
    }

    ///////////////////////////////////////////////
    // proposte di un relatore


    // TODO: (proposte, relatori) -> Richiesta

    ///////////////////////////////////////////////
    // CalendarioMeetup

    // TODO: Richiesta -> CalendarioMeetUp

    return 0;
}
