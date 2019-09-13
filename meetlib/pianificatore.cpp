#include "pianificatore.h"

namespace meetup
{

auto Pianificatore::LeggiDateMeetup()
    -> tl::expected<std::vector<DataMeetupDto>, Errore>
{
    // TODO: leggere da file json
    // dati di esempio
    return std::vector<DataMeetupDto>{
        DataMeetupDto("12/9/2019"),
        DataMeetupDto("10/10/2019"),
        DataMeetupDto("14/11/2019"),
        DataMeetupDto("12/12/2019")};
}

auto Pianificatore::RiceviRelatori()
    -> tl::expected<std::vector<RelatoreDto>, Errore>
{
    // TODO: leggere da file json
    // dati di esempio
    return std::vector<RelatoreDto>{
        RelatoreDto("yv", "Yuri Valentini", "yv@example.com", tl::nullopt),
        RelatoreDto("zp", "Zio Paperone", "zp@example.com", "@ziopaperone")};
}

auto Pianificatore::RiceviProposte()
    -> tl::expected<std::vector<PropostaDto>, Errore>
{
    // TODO: leggere da file json
    // dati di esempio
    return std::vector<PropostaDto>{
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
}

auto Pianificatore::ValidaDateMeetup(std::vector<DataMeetupDto> const &dateMeetupDto)
    -> tl::expected<DateMeetup, Errore>
{
    // TODO: match con regex -> date::year_month_day -> controllare duplicati
    return tl::make_unexpected(Errore("TODO"));
}
auto Pianificatore::ValidaRelatori(std::vector<RelatoreDto> const &relatoriDto)
    -> tl::expected<std::vector<Relatore>, Errore>
{
    // TODO: controllare codici relatori duplicati
    return tl::make_unexpected(Errore("TODO"));
}

auto Pianificatore::ValidaProposte(std::function<bool(CodiceRelatore)> verificaCodiceRelatore,
                                   std::vector<PropostaDto> const &proposteDto)
    -> tl::expected<std::vector<Proposta>, Errore>
{
    // TODO: controllare codici relatori esistenti, controllare codici duplicati
    return tl::make_unexpected(Errore("TODO"));
}

} // namespace meetup
