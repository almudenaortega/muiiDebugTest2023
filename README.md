# Ejemplo para la depuración de un programa

Utilizando esta plantilla se experimentará con la depuración en circuito de un programa y se buscará reducir lo máximo posible el tiempo de ejecución

El programa consta de dos apartados, en cada uno de ellos habrá que introducir código en una función

# Ejercicio 1

En este ejercicio hay que modificar el código que se encuentra en la función calcularRMS, la función tiene esta definición:

```
    float calcularRMS(uint16_t *datos, int longitud)
```

La función recibe un puntero a un array de datos en formato enteros con sin signo de 16 bits de anchura de palabra.
Los datos que contiene el array provienen de un ADC de 16bits que muestrea una señal comprendida entre -400V y 400V, utilizando offset zero.
Como segundo parámetro recibe la cantidad de elementos que contiene el array.
Lo que la función tiene que devolver es el valor Vrms de la señal en Voltios.

La ecuación para calcular la tensión eficaz es la siguiente:

![](https://latex.codecogs.com/png.image?\inline&space;\dpi{110}{\color{white}&space;V_{rms}=\sqrt{\frac{1}{N}\sum_{0}^{N-1}\left|&space;v\left&space;(&space;n&space;\right&space;)\right|^{2}}{\color{Yellow}&space;}})

El código de la función contiene un pequeño error que hay que localizarlo.
Una vez solventado el error se puede comprobar el tiempo de ejecución, este es muy malo,
Modificar el código para que la función se ejecute lo más rápido que se pueda.

# Ejercicio 2

La segunda función calcula varios parámetros eléctricos de la señal muestreada de la onda de tensión y de la onda de corriente.
La señal de tensión proviene de un ADC de 16bits siendo las tensiones de referencia -400V y 400V, utilizando offset zero.
La señal de corriente proviene de un ADC de 16 bits que mide corrientes entre -2.5A y 2.5A, utilizando offset zero.
Los parámetros que se calculen hay que dejarlos en los campos de la estructura que se pase en la función

```
    void calcularDatos(uint16_t *datosV, uint16_t *datosI, int longitud, estructuraMedidas *medidas)
```
