#pragma once

namespace meetup {

enum class dias_semana {
    lunes,
    martes,
    miercoles,
    jueves,
    viernes,
    sabado,
    domingo
};

enum class ocurrencia {
    primero,
    segundo,
    tercero,
    cuarto,
    ultimo,
    teenth
};

class scheduler {
public:
    scheduler(int anio, int mes);
    int dia(ocurrencia semana_buscada, dias_semana dia_buscado) const;

private:
    int anio_reunion;
    int mes_reunion;

    bool es_bisiesto(int anio) const;
    int dias_del_mes(int anio, int mes) const;
    int calcular_dia_semana(int anio, int mes, int dia) const;
};

}  // namespace meetup
