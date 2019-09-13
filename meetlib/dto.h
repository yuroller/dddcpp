#pragma once

#include "tipi_semplici.h"
#include "expected.hpp"
#include "optional.hpp"
#include "date.h"
#include <string>
#include <vector>
#include <utility>

namespace meetup
{

class DataMeetupDto
{
public:
    static auto CreaElenco(std::string const &json)
        -> tl::expected<std::vector<DataMeetupDto>, Errore>;

    explicit DataMeetupDto(std::string data)
        : data_(std::move(data))
    {
    }

    auto data() const
        -> std::string { return data_; }

private:
    std::string data_;
};

class RelatoreDto
{
public:
    static auto CreaElenco(std::string const &json)
        -> tl::expected<std::vector<RelatoreDto>, Errore>;

    RelatoreDto(std::string codice, std::string nome, std::string email,
                tl::optional<std::string> twitter)
        : codice_(std::move(codice)),
          nome_(std::move(nome)),
          email_(std::move(email)),
          twitter_(std::move(twitter))
    {
    }

    auto codice() const
        -> std::string { return codice_; }

    auto nome() const
        -> std::string { return nome_; }

    auto email() const
        -> std::string { return email_; }

    auto twitter() const
        -> tl::optional<std::string> { return twitter_; }

private:
    std::string codice_;
    std::string nome_;
    std::string email_;
    tl::optional<std::string> twitter_;
};

enum class TipoDisponibilita
{
    SempreDisponibile,
    DateSpecifiche,
    DopoUnaData
};

class PropostaDto
{
public:
    static auto CreaElenco(std::string const &json)
        -> tl::expected<std::vector<PropostaDto>, Errore>;

    PropostaDto(int codice,
                std::string codiceRelatore,
                std::string titolo, std::string sommario,
                TipoDisponibilita tipoDisponibilita,
                tl::optional<std::vector<date::year_month_day>> dateDisponibilita,
                tl::optional<date::year_month_day> dataInizioDisponbilita)
        : codice_(codice),
          codiceRelatore_(codiceRelatore),
          titolo_(std::move(titolo)),
          sommario_(std::move(sommario)),
          tipoDisponibilita_(tipoDisponibilita),
          dateDisponibilita_(std::move(dateDisponibilita)),
          dataInizioDisponibilita_(std::move(dataInizioDisponbilita))
    {
    }

    auto codice() const
        -> int { return codice_; }

    auto codiceRelatore() const
        -> std::string { return codiceRelatore_; }

    auto titolo() const
        -> std::string { return titolo_; }

    auto sommario() const
        -> std::string { return sommario_; }

    auto tipoDisponibilita() const
        -> TipoDisponibilita { return tipoDisponibilita_; }

    auto dateDisponibilita() const
        -> tl::optional<std::vector<date::year_month_day>> { return dateDisponibilita_; }

    auto dataInizioDisponibilita() const
        -> tl::optional<date::year_month_day> { return dataInizioDisponibilita_; }

private:
    int codice_;
    std::string codiceRelatore_;
    std::string titolo_;
    std::string sommario_;
    TipoDisponibilita tipoDisponibilita_;
    tl::optional<std::vector<date::year_month_day>> dateDisponibilita_;
    tl::optional<date::year_month_day> dataInizioDisponibilita_;
};

} // namespace meetup