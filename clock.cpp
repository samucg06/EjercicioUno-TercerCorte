#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

int clock::normalizar_minutos(int total_minutos) {
    const int minutos_por_dia = 24 * 60;

    total_minutos %= minutos_por_dia;

    if (total_minutos < 0) {
        total_minutos += minutos_por_dia;
    }

    return total_minutos;
}

clock::clock(int horas, int minutos) {
    minutos_totales_del_dia = normalizar_minutos(horas * 60 + minutos);
}

std::string clock::to_string() const {
    int horas = minutos_totales_del_dia / 60;
    int minutos = minutos_totales_del_dia % 60;

    std::ostringstream salida;
    salida << std::setw(2) << std::setfill('0') << horas
           << ":"
           << std::setw(2) << std::setfill('0') << minutos;

    return salida.str();
}

clock clock::plus(int minutos_a_sumar) const {
    return clock(0, minutos_totales_del_dia + minutos_a_sumar);
}

clock clock::minus(int minutos_a_restar) const {
    return clock(0, minutos_totales_del_dia - minutos_a_restar);
}

bool clock::operator==(const clock& otro_reloj) const {
    return minutos_totales_del_dia == otro_reloj.minutos_totales_del_dia;
}

}
