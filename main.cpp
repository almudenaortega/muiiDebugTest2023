#include "mbed.h"
#include "datos.h"
#include "math.h"


#define longitudTrama 200
#define fs (50*20)

Timer timer;
float resultado;
int tiempo;

struct estructuraMedidas {
  float vrms;
  float irms;
  float potenciaActiva;
  float potenciaReactiva;
  float potenciaAparente;
  float factorDePotencia;
  float energiaConsumida;
};

float calcularRMS(uint16_t *datos, int longitud);

void calcularDatos(uint16_t *datosV, uint16_t *datosI, int longitud,
                   estructuraMedidas *medidas);

int main() {

  timer.reset();
  timer.start();
  resultado = calcularRMS(datos, longitudTrama);
  timer.stop();
  printf("\n****El valor Vrms es %f calculado en %lld us ****\n\n", resultado,
         timer.elapsed_time().count());

  estructuraMedidas medidas;
  medidas.energiaConsumida = 0;

  timer.reset();
  timer.start();
  calcularDatos(datosV, datosI, longitudTrama, &medidas);
  timer.stop();
  printf("**** Datos calculados en %lld us ****\n",
         timer.elapsed_time().count());
  printf("**** El valor Vrms es %f ****\n", medidas.vrms);
  printf("**** El valor Irms es %f ****\n", medidas.irms);
  printf("**** La potencia activa es %f ****\n", medidas.potenciaActiva);
  printf("**** La potencia reactiva es %f ****\n", medidas.potenciaReactiva);
  printf("**** La potencia aparente es %f ****\n", medidas.potenciaAparente);
  printf("**** La energia consumida es %f ****\n", medidas.energiaConsumida);
  printf("**** El factor de potencia es es %f ****\n",
         medidas.factorDePotencia);

  while (true) {
  }
}

// Esta función calcula el valor RMS
float calcularRMS(uint16_t *datos, int longitud) {
  float rms = 0;
  
  for (int i = 0; i < longitud; i++) {
    float datoV = (((float)datos[i]) / 65536 * 800.0) - 400.0;
    rms += datoV * datoV;
  }
  rms = sqrt(rms / longitud);
  return rms;
}

void calcularDatos(uint16_t *datosV, uint16_t *datosI, int longitud,
                   estructuraMedidas *medidas) {
  int Vrms = 0;
  float datoV; 
  float Irms = 0;
  float datoI;
  float P = 0;
  float S, Q, FA, E;
  for (int i = 0; i < longitud; i++) {
    datoV = (((float)datosV[i]) / 65536 * 800.0) - 400.0;
    datoI = (((float)datosI[i]) / 65536 * 5.0) - 2.5;

    Vrms += datoV * datoV;
    Irms += datoI * datoI;
    P += datoV * datoI;
  }

  Vrms = sqrt(Vrms / longitud);
  Irms = sqrt(Irms / longitud);
  P = P / longitud;
  S = Vrms * Irms;
  Q = sqrt(S*S - P*P);
  FA = P / S;
  E = P/fs*longitudTrama/60/60/1000;
  medidas->vrms = Vrms;
  medidas->irms = Irms;
  medidas->potenciaActiva = P;
  medidas->potenciaAparente = S;
  medidas->potenciaReactiva = Q;
  medidas->factorDePotencia = FA;
  medidas->energiaConsumida+=E;
}
