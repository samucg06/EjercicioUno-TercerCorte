#pragma once
#include <string>

namespace date_independent {

class clock {
public:
    clock(int horas, int minutos);

    std::string to_string() const;

    clock plus(int minutos_a_sumar) const;
    clock minus(int minutos_a_restar) const;

    bool operator==(const clock& otro_reloj) const;

private:
    int minutos_totales_del_dia;

    static int normalizar_minutos(int total_minutos);
};

}  // namespace date_independent
