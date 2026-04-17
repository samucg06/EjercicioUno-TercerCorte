#include <string>
#include <unordered_map>
using namespace std;

class UndergroundSystem {
private:
    struct DatosEntrada {
        string estacionEntrada;
        int tiempoEntrada;
    };

    struct EstadisticasRuta {
        double tiempoTotal = 0;
        int cantidadViajes = 0;
    };

    unordered_map<int, DatosEntrada> pasajerosEnViaje;
    unordered_map<string, EstadisticasRuta> estadisticasPorRuta;

    string construirClaveRuta(const string& estacionInicio, const string& estacionFin) {
        return estacionInicio + "->" + estacionFin;
    }

public:
    UndergroundSystem() {
    }

    void checkIn(int id, string stationName, int t) {
        pasajerosEnViaje[id] = {stationName, t};
    }

    void checkOut(int id, string stationName, int t) {
        DatosEntrada datosEntrada = pasajerosEnViaje[id];
        pasajerosEnViaje.erase(id);

        string claveRuta = construirClaveRuta(datosEntrada.estacionEntrada, stationName);
        int duracionViaje = t - datosEntrada.tiempoEntrada;

        estadisticasPorRuta[claveRuta].tiempoTotal += duracionViaje;
        estadisticasPorRuta[claveRuta].cantidadViajes++;
    }

    double getAverageTime(string startStation, string endStation) {
        string claveRuta = construirClaveRuta(startStation, endStation);
        EstadisticasRuta datosRuta = estadisticasPorRuta[claveRuta];

        return datosRuta.tiempoTotal / datosRuta.cantidadViajes;
    }
};
