#include "meetup.h"
#include <vector>

namespace meetup {

scheduler::scheduler(int anio, int mes) : anio_reunion(anio), mes_reunion(mes) {}

bool scheduler::es_bisiesto(int anio) const {
    if (anio % 400 == 0) return true;
    if (anio % 100 == 0) return false;
    return anio % 4 == 0;
}

int scheduler::dias_del_mes(int anio, int mes) const {
    if (mes == 2) {
        return es_bisiesto(anio) ? 29 : 28;
    }

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        return 30;
    }

    return 31;
}

// Devuelve:
// 0 = domingo
// 1 = lunes
// 2 = martes
// 3 = miércoles
// 4 = jueves
// 5 = viernes
// 6 = sábado
int scheduler::calcular_dia_semana(int anio, int mes, int dia) const {
    if (mes < 3) {
        mes += 12;
        anio--;
    }

    int siglo = anio / 100;
    int anio_del_siglo = anio % 100;

    int valor = dia
              + (13 * (mes + 1)) / 5
              + anio_del_siglo
              + (anio_del_siglo / 4)
              + (siglo / 4)
              + (5 * siglo);

    int resultado_zeller = valor % 7;

    if (resultado_zeller == 0) return 6; // sábado
    if (resultado_zeller == 1) return 0; // domingo
    if (resultado_zeller == 2) return 1; // lunes
    if (resultado_zeller == 3) return 2; // martes
    if (resultado_zeller == 4) return 3; // miércoles
    if (resultado_zeller == 5) return 4; // jueves
    return 5; // viernes
}

int scheduler::dia(ocurrencia semana_buscada, dias_semana dia_buscado) const {
    std::vector<int> dias_que_coinciden;
    int total_dias = dias_del_mes(anio_reunion, mes_reunion);

    int valor_dia_buscado;
    switch (dia_buscado) {
        case dias_semana::domingo:   valor_dia_buscado = 0; break;
        case dias_semana::lunes:     valor_dia_buscado = 1; break;
        case dias_semana::martes:    valor_dia_buscado = 2; break;
        case dias_semana::miercoles: valor_dia_buscado = 3; break;
        case dias_semana::jueves:    valor_dia_buscado = 4; break;
        case dias_semana::viernes:   valor_dia_buscado = 5; break;
        case dias_semana::sabado:    valor_dia_buscado = 6; break;
    }

    for (int dia_actual = 1; dia_actual <= total_dias; dia_actual++) {
        if (calcular_dia_semana(anio_reunion, mes_reunion, dia_actual) == valor_dia_buscado) {
            dias_que_coinciden.push_back(dia_actual);
        }
    }

    switch (semana_buscada) {
        case ocurrencia::primero:
            return dias_que_coinciden[0];

        case ocurrencia::segundo:
            return dias_que_coinciden[1];

        case ocurrencia::tercero:
            return dias_que_coinciden[2];

        case ocurrencia::cuarto:
            return dias_que_coinciden[3];

        case ocurrencia::ultimo:
            return dias_que_coinciden.back();

        case ocurrencia::teenth:
            for (int dia_encontrado : dias_que_coinciden) {
                if (dia_encontrado >= 13 && dia_encontrado <= 19) {
                    return dia_encontrado;
                }
            }
    }

    return -1;
}

}  // namespace meetup
