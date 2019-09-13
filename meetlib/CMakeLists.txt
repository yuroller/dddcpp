add_library(meetlib
    tipi_semplici.cpp
    oggetti_valore.cpp
    entita.cpp
    aggregati.cpp
    dto.cpp
    pianificatore.cpp
)
target_link_libraries(meetlib
    tlexpected
    tloptional
    hhdate
)
target_include_directories(meetlib INTERFACE .)