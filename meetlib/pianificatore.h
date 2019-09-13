#pragma once

#include "dto.h"
#include "entita.h"
#include "oggetti_valore.h"
#include "tipi_semplici.h"
#include "expected.hpp"
#include <functional>
#include <vector>

namespace meetup
{
class Pianificatore
{
public:
    // side-effect
    static auto LeggiDateMeetup()
        -> tl::expected<std::vector<DataMeetupDto>, Errore>;
    static auto RiceviRelatori()
        -> tl::expected<std::vector<RelatoreDto>, Errore>; // Async<tl::expected<vector<RelatoreDto>, Errore>>
    static auto RiceviProposte()
        -> tl::expected<std::vector<PropostaDto>, Errore>; // Async<tl::expected<std::vector<PropostaDto>, Errore>

    // pure
    static auto ValidaDateMeetup(std::vector<DataMeetupDto> const &dateMeetupDto)
        -> tl::expected<DateMeetup, Errore>;
    static auto ValidaRelatori(std::vector<RelatoreDto> const &relatoriDto)
        -> tl::expected<std::vector<Relatore>, Errore>;
    static auto ValidaProposte(std::function<bool(CodiceRelatore)> verificaCodiceRelatore,
                               std::vector<PropostaDto> const &proposteDto)
        -> tl::expected<std::vector<Proposta>, Errore>;

#if 0
    static auto VotaProposte(std::vector<Proposta> const &proposte)
        -> tl::expected<std::vector<PropostaVotata>, Errore>; // Async<tl::expected<std::vector<PropostaVotata>, Errore>>
    static auto CreaCalendatrioMeetup(const DateMeetup &dateMeetup,
                                std::vector<PropostaVotata> const &proposteVotate)
        -> tl::expected<Calendario, Errore>;
    static auto SerializzaCalendario(Calendario const &calendario)
        -> CalendarioDto;
    // side-effect
    static auto PubblicaCalendario(CalendarioDto const &calendarioDto)
        -> Errore; // Async<tl::optional<Errore>>
    static auto NotificaRelatori(Calendario const &calendario)
        -> Errore; // Async<tl::optional<Errore>>
#endif
};
} // namespace meetup