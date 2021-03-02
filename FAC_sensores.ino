/* 
 * Fisica Aplicada a Computacao - Engenharia Informatica
 * Aluno: Hugo Alexandre, Tiago Filipe, Omar Pizon
 * Mestre: Nuno Pereira
 * 2018-19
 * Hardware: Arduino Uno R3
 * Descricao: testa estruturas de programacao, sensor de temperatura.
 * Primeiro trabalho em sala de aula.
 * Versão 20/02/2019
 * Recursos: https://www.arduino.cc/en/Reference/FunctionDeclaration
 *           https://www.arduino.cc/en/Reference/If
 *           https://www.arduino.cc/en/Reference/For
 *           https://www.arduino.cc/en/Reference/SwitchCase
 *           https://www.arduino.cc/en/Reference/While
 *           https://www.arduino.cc/en/Reference/DoWhile
 *           https://www.arduino.cc/en/Reference/Break
 *           https://www.arduino.cc/en/Reference/Continue
 *           https://www.arduino.cc/en/Reference/Return
*/


//variáveis globais que irão mostrar os valores dos sensores e utilização durante a execução do trabalho;
byte Vcc = 11;
byte Trig = 12;
byte Echo = 13;
float distance;               // variavel para receber valor de distancia;
byte triggerDuration = 10;          // us, "conforme citação do mestre nuno e unidade de medida;
unsigned int sampleDelay = 10;      // ms, "conforme citação do mestre nuno e unidade de medida;
unsigned int timeout = 23530;             // tempo correspondente a d > 4m, "conforme citação do mestre nuno e unidade de medida;

//escolhemos a variavél float por receber números decimais que ocupam 32 bits(4 bytes);
//assim não precesariamos usar a variavel double que ocupa o dobro em alguns casos, economizando até mesmo no espaço de memoria;
//essas variaveis podem tomar valores entre -3.4028235E+38 e +3.4028235E+38.

float duration_a = 0.;     // "conforme citação do mestre nuno e unidade de medida. nome variavel. recebe duração;
float distance_a = 0.;
float duration_suav = 0.;   // "conforme citação do mestre nuno e unidade de medida. nome variavel. recebe suavização duração;
float distance_suav = 0.;   // "conforme citação do mestre nuno e unidade de medida. nome variavel. recebe suavização distancia;
int contador = 0;           // contador usado para as formulas, contagem das medições. ideia baseada do primeiro trabalho FAC;
const int valor_media = 3;    // contador usado para as formulas, contagem das medições deslizante, ideia baseada do primeiro trabalho FAC;
const float suavizacao = 0.3; // suavização usado para as formulas, ideia baseada do primeiro trabalho FAC;
float media_a = 0.;           //variavel para medias em geral;
float media_b = 0.;           //variavel para medias em geral;
float duration_media = 0.;    //variavel para media da duração;
float distance_media = 0.;    //variavel para media da distancia;
float duration_mmm = 0.;      //variavel para media acumulativa;
float distance_mmm = 0.;    //variavel para media acumulativa;
float duration_array[valor_media];    //array para valores de duração, ideia baseada do primeiro trabalho FAC;;
float distance_array[valor_media];    //array para valores de distancia, ideia baseada do primeiro trabalho FAC;;


//após a formulação do calculo os acendimentos dos led ocorreram nos seguintes pinos;
//assim como ocorre no trabalho 1 descritivo ao qual utilizamos como base e ideia para as formulas.

 
  const int pino7 = 7; //byte pino7 = 7;
  const int pino6 = 6; //byte pino6 = 6;
  const int pino5 = 5; //byte pino5 = 5;
  const int pino4 = 4; //byte pino4 = 4;
  

#define ultrasom
    //#define mms
    //#define mmc
    //#define mmm
    //#define mmd
    //#define mserial
    //#define mplotter
    #define gnuplot
    
//#define humidade
    // #define mms_humidade
    //#define mmc_humidade
    //#define mmm_humidade
    //#define mmd_humidade
    //#define mserial_humidade
    //#define mplotter_humidade
    //#define gnuplot_humidade

//#define pressao
    //#define mms_pressao
    //#define mmc_pressao
    //#define mmm_pressao
    //#define mmd_pressao
    //#define mserial_pressao
    //#define mplotter_pressao
    //#define gnuplot_pressao
    

#ifdef ultrasom

// Initialization
void setup() {
  pinMode(Vcc, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Vcc, HIGH);
  digitalWrite(Trig, LOW);
  Serial.begin(9600);
  while(!Serial);

#ifdef gnuplot
  Serial.print(F("#Fisica Aplicada Computação | 2018-19"));
  Serial.print(F("#Duration (us)\tDistance (cm)"));
  Serial.print(F("\tSuavização duration (us)\tSuavização distance (cm)"));
  Serial.println(F("\tMedia duration (us)\tMedia distance (cm)"));
#endif gnuplot
}
// Main loop
void loop() {
  delay(sampleDelay);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(triggerDuration);
  digitalWrite(Trig, LOW);
  unsigned long duration = pulseIn(Echo, HIGH, timeout);
  distance = (float)duration/58.8;

#ifdef mmm                              //inicio da media mmm de 3 valores, de ambos valores, distancia e duração.
  duration_array[contador]=duration;    //aqui utiizamos o mesmo seguimento e ação que foi feito no trabalho 1.
  distance_array[contador]=distance;
  contador++;
if(contador == valor_media) {
  duration_media = 0.;
  distance_media = 0.;
for(int k = 0; k < valor_media; k++){
  duration_media=duration_media + duration_array[k];
  distance_media=distance_media + distance_array[k];
}
  duration_media=duration_media / valor_media;
  distance_media=distance_media / valor_media;
  contador = 0;
}
#endif mmm
 
#ifdef mms                              // inicio dos calculos das ações de suavização;
  duration_a = duration_suav;         //duração receber valor de suavização para armazenamento;
  distance_a = distance_suav;
  duration_suav = duration + (duration_a - duration) * suavizacao;  //função de calculo para executar a suavização;
  distance_suav = distance + (distance_a - distance) * suavizacao;
#endif mms

#ifdef mmc                          // inicio do calculos das media correntes ou acumulativas;
  contador++;
  duration_mmm += duration;         // aqui utilizamos as funções e seguimentos conforme trabalho 1, baseando em criar resultados;
  distance_mmm += distance;                   //para distancia e duração conforme valores pretendidos;
  duration_media = duration_mmm / contador;
  distance_media = distance_mmm / contador;
#endif mmc

#ifdef mmd                              //inicio da ação de calculo das medias deslizantes;
if(contador < valor_media) {              //inicio de array para armazenar valores de duração e distancia;
    duration_array[contador]=duration;
    distance_array[contador]=distance;
    contador++;
}
if(contador == valor_media) {              // baseado no descritivo do quadro do mestre nuno, esta formula, 
for(int k = 0; k < valor_media; k++){         //efetua a troca dos valores dos array e traz novas medições trocando a mais antiga;
   if(k < (valor_media - 1)){
     duration_array[k]=duration_array[k + 1];
     distance_array[k]=distance_array[k + 1];
} else {
     duration_array[k]=duration;
     distance_array[k]=distance;
}
}
for(int k = 0; k < valor_media; k++){                   // dentro das medias ja calculadas e armazenadas no array, 
    duration_media=duration_media + duration_array[k];    //iremos receber novo valor de duração medida e armazenar dentro de um array e 
    distance_media=distance_media + distance_array[k];    //utilizar para efetuar o calculo de nova media com valores atualizados;
}
    duration_media=duration_media / valor_media;
    distance_media=distance_media / valor_media;
}
#endif mmd

#ifdef gnuplot
  Serial.print(F("\t"));
  Serial.print(duration_media);             //imprimi a media da duração, media final;
  Serial.print(F("\t"));
  Serial.print(distance_media);           //imprimi a media da distancia, media final;
  Serial.print(F("\t"));
  Serial.print(duration);               //imprimi a duração, "conforme citação do mestre nuno e unidade de medida. nome variavel. recebe duração;
  Serial.print(F("\t"));
  Serial.println(distance);     //imprimi a distancia, "conforme citação do mestre nuno e unidade de medida. nome variavel. recebe distancia;
  Serial.print(F("\t"));
  Serial.print(duration_suav);          //imprimi a suavização da duração;
  Serial.print(F("\t"));
  Serial.print(distance_suav);         //imprimi a suavização da distancia;
#endif gnuplot

#ifdef mplotter
  Serial.print(F("\tSuavização duration(us): "));
  Serial.print(duration_suav);          //imprimi a suavização da duração;
  Serial.print(F("\tSuavização distance(us): "));
  Serial.print(distance_suav);         //imprimi a suavização da distancia;
  Serial.print(F("\tDuration(us): "));
  Serial.print(duration);               //imprimi a duração, "conforme citação do mestre nuno e unidade de medida. nome variavel. recebe duração;
  Serial.print(F("\tDistance(cm): "));
  Serial.println(distance);     //imprimi a distancia, "conforme citação do mestre nuno e unidade de medida. nome variavel. recebe distancia;
#endif mplotter

#ifdef mserial
  Serial.print(F("\tMedia duration(us): "));
  Serial.print(duration_media);             //imprimi a media da duração, media final;
  Serial.print(F("\tMedia distance(cm): "));
  Serial.print(distance_media);           //imprimi a media da distancia, media final;
  Serial.print(F("\tDuration(us): "));
  Serial.print(duration);               //imprimi a duração, "conforme citação do mestre nuno e unidade de medida. nome variavel. recebe duração;
  Serial.print(F("\tDistance(cm): "));
  Serial.println(distance);     //imprimi a distancia, "conforme citação do mestre nuno e unidade de medida. nome variavel. recebe distancia;
  Serial.print(F("\tSuavização duration(us): "));
  Serial.print(duration_suav);          //imprimi a suavização da duração;
  Serial.print(F("\tSuavização distance(us): "));
  Serial.print(distance_suav);         //imprimi a suavização da distancia;
  
if (duration > 0 && duration <= 9000){
   digitalWrite(pino7, HIGH);          // para os valores de if luz de led acessa, estará HIGH;
   Serial.print(F("LED Blue  "));
}
if (duration > 9000 && duration <= 55000){
   digitalWrite(pino6, HIGH);      // para os valores de if luz de led acessa, estará HIGH;
   Serial.print(F("LED Yellow  "));
}
if (distance > 0 && distance <= 1900){
   digitalWrite(pino5, HIGH);     // para os valores de if luz de led acessa, estará HIGH;
   Serial.print(F("LED Green  "));
}
if (distance > 1900 && distance <= 4100){
   digitalWrite(pino4, HIGH);         // para os valores de if luz de led acessa, estará HIGH;
   Serial.print(F("LED Red  "));
}
#endif mserial
}

#endif ultrasom


/*
Sensor de Temperatura do Ar & Humidade Relativa DHT-11
Biblioteca: Adafruit DHT11 + Adafruit Unified Sensor
Código para teste:
*/


#ifdef humidade

#include "DHT.h"
// Declaration of global variables
byte DHTpin = 2;        // Digital pin to connect pin 2 of the sensor 
int delaySample = 200; // delay between measurements in ms
// Definition of the sensor
DHT dht(DHTpin, DHT11);
// Initialization 

void setup() {
  Serial.begin(115200); // Start serial port communications
  dht.begin();  // Initialize sensor
  delay(delaySample); 
  
#ifdef gnuplot_humidade
  Serial.print(F("#Fisica Aplicada Computação | 2018-19"));
  Serial.print(F("#Humidity (%)\tTemperature (ºC))"));
  Serial.print(F("\tSuavização Humidity (%)\tSuavização Temperature (ºC)"));
  Serial.println(F("\tMedia Humidity (%)\tMedia Temperature (ºC)"));
#endif gnuplot_humidade
  
}
    
// Main loop 
  void loop() {   
  delay(delaySample);
  float h = dht.readHumidity();     // Read relative humidity   
  float t = dht.readTemperature();  // Read temperature in Celcius   
  // Check validity of readings   
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Invalid Data!"));
    return;   // Loops to the reading instructions without printing data   
    }

#ifdef mms_humidade                     // inicio dos calculos das ações de suavização;
    duration_a = duration_suav;             //mesma ação e teoria da função da parte do ultrasom, alterando apenas os valores de entrada;
    distance_a = distance_suav;                           //não alteramos os nomes das variaveis para não ter quer ficar criando varias variaveis e 
    duration_suav = h + (duration_a - h) * suavizacao;      //o que importa são os valores de entradas e execeção, sendo assim as variaveis sendo chamadas de
    distance_suav = t + (distance_a - t) * suavizacao;          // a ou b, não interfere no execução e obtenção do resultado correto.
#endif mms_humidade                                                 //sendo assim reslvermos deixar o codigo bem comentado para não gerar duvidas.

#ifdef mmm_humidade
  duration_array[contador] = h;               //inicio da media mmm de 3 valores, de ambos valores, distancia e duração.
  distance_array[contador] = t;                 //aqui utiizamos o mesmo seguimento e ação que foi feito no trabalho 1.
  contador++;
if(contador == valor_media) {
  duration_media = 0.;
  distance_media = 0.;
for(int k = 0; k < valor_media; k++){
  duration_media=duration_media + duration_array[k];
  distance_media=distance_media + distance_array[k];
}
  duration_media=duration_media / valor_media;
  distance_media=distance_media / valor_media;
  contador = 0;
}
#endif mmm_humidade
 
#ifdef mmc_humidade                       // inicio do calculos das media correntes ou acumulativas
  contador++;
  duration_mmm += h;                      // aqui utilizamos as funções e seguimentos conforme trabalho 1, baseando em criar resultados;
  distance_mmm += t;                        //para distancia e duração conforme valores pretendidos;
  duration_media = duration_mmm / contador;
  distance_media = distance_mmm / contador;
#endif mmc_humidade

#ifdef mmd_humidade                         //inicio da ação de calculo das medias deslizantes;
if(contador < valor_media) {
    duration_array[contador] = h;
    distance_array[contador] = t;
    contador++;
}
if(contador == valor_media) {             // baseado no descritivo do quadro do mestre nuno, esta formula, 
for(int k = 0; k < valor_media; k++){          //efetua a troca dos valores dos array e traz novas medições trocando a mais antiga;
   if(k < (valor_media - 1)){
     duration_array[k]=duration_array[k + 1];
     distance_array[k]=distance_array[k + 1];
} else {
     duration_array[k] = h;
     distance_array[k] = t;
}
}
for(int k = 0; k < valor_media; k++){                   // dentro das medias ja calculadas e armazenadas no array, 
    duration_media=duration_media + duration_array[k];    //iremos receber novo valor de duração medida e armazenar dentro de um array e 
    distance_media=distance_media + distance_array[k];    //utilizar para efetuar o calculo de nova media com valores atualizados;
}
    duration_media=duration_media / valor_media;
    distance_media=distance_media / valor_media;
}
#endif mmd_humidade

#ifdef gnuplot_humidade
  Serial.print(F("\t"));
  Serial.print(duration_media);             //imprimi a media da duração, media final;
  Serial.print(F("\t"));
  Serial.print(distance_media);           //imprimi a media da distancia, media final;
  Serial.print(F("\t"));
  Serial.print(h);
  Serial.print(F("\t"));
  Serial.println(t);
  Serial.print(F("\t"));
  Serial.print(duration_suav);          //imprimi a suavização da duração;
  Serial.print(F("\t"));
  Serial.print(distance_suav);         //imprimi a suavização da distancia;
#endif gnuplot_humidade

#ifdef mplotter_humidade
  Serial.print(F("\tSuavização Humidity (%): "));
  Serial.print(duration_suav);          //imprimi a suavização da duração;
  Serial.print(F("\tSuavização Temperature (ºC)): "));
  Serial.print(distance_suav);         //imprimi a suavização da distancia;
Serial.print(F("\tHumidity (%): "));
  Serial.print(h);
  Serial.print(F("\tTemperature (ºC): "));
  Serial.println(t);
#endif mplotter_humidade

#ifdef mserial_humidade
  Serial.print(F("\tMedia Humidity (%): "));
  Serial.print(duration_media);             //imprimi a media da duração, media final;
  Serial.print(F("\tMedia Temperature (ºC): "));
  Serial.print(distance_media);           //imprimi a media da distancia, media final;
  Serial.print(F("\tHumidity (%): "));
  Serial.print(h);
  Serial.print(F("\tTemperature (ºC): "));
  Serial.println(t);
  Serial.print(F("\tSuavização Humidity (%): "));
  Serial.print(duration_suav);          //imprimi a suavização da duração;
  Serial.print(F("\tSuavização Temperature (ºC)): "));
  Serial.print(distance_suav);         //imprimi a suavização da distancia;
  
if (h > 0 && h <= 75){
   digitalWrite(pino7, HIGH);          // para os valores de if luz de led acessa, estará HIGH;
   Serial.print(F("LED Blue  "));
}
if (h > 75 && h <= 150){
   digitalWrite(pino6, HIGH);      // para os valores de if luz de led acessa, estará HIGH;
   Serial.print(F("LED Yellow  "));
}
if (t > 0 && t <= 25){
   digitalWrite(pino5, HIGH);     // para os valores de if luz de led acessa, estará HIGH;
   Serial.print(F("LED Green  "));
}
if (t > 25 && t <= 70){
   digitalWrite(pino4, HIGH);         // para os valores de if luz de led acessa, estará HIGH;
   Serial.print(F("LED Red  "));
}
#endif mserial_humidade
}
#endif humidade


#ifdef pressao
#include <i2c.h>
#include <i2c_BMP280.h>
#include <i2c_Sensor.h>
#include <Wire.h>
#include "i2c.h"
#include "i2c_BMP280.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

//#include <Adafruit_CircuitPlayground.h>  \\ esta biblioteca esta incompativel com alguma função ou com o arduino, sempre apresenta erro de compilação.
// Declaration of global variables 
int delaySample = 20; // delay between measurements in ms
// Definition of the sensor
//Adafruit_BMP280 BMP280; // I2C
BMP280 bmp280;
// Initialization 
void setup() {
  Serial.begin(115200); // Start serial port communications   
  while(!Serial); // Wait for serial communications start

#ifdef gnuplot_humidade
  Serial.print("#Trabalho Fisica Aplicada a Computação - Mestre Nuno");
  Serial.print("#Sensores BMP280 - 1º Ano - FAC 2018-19\n");
  Serial.println(F("Suavização T(ºC)   Suavização P(Pa)    T(ºC)    P(Pa)    Media T(ºC)    Media P(Pa)\n"));
#endif gnuplot_humidade

  if (!bmp280.initialize()) {  // check if sensor is present and initializes sensor
    Serial.println(F("Sensor não encontrado!!\nVerifique ligações"));
    while (1);
  }
}
// Main loop 
void loop() {   
  delay(delaySample);
  float t; bmp280.getTemperature(t); // Read temperature in Celcius   
  float p; bmp280.getPressure(p);    // Read pressure in Pascal
 
#ifdef mms_pressao                        // inicio dos calculos das ações de suavização;
    duration_a = duration_suav;                   //mesma ação e teoria da função da parte do ultrasom, alterando apenas os valores de entrada;
    distance_a = distance_suav;                      //não alteramos os nomes das variaveis para não ter quer ficar criando varias variaveis e
    duration_suav = t + (duration_a - t) * suavizacao;    //o que importa são os valores de entradas e execeção, sendo assim as variaveis sendo chamadas de
    distance_suav = p + (distance_a - p) * suavizacao;        // a ou b, não interfere no execução e obtenção do resultado correto.
#endif mms_pressao                                               //sendo assim reslvermos deixar o codigo bem comentado para não gerar duvidas.

#ifdef mmm_pressao                        //inicio da media mmm de 3 valores, de ambos valores, distancia e duração.
  duration_array[contador] = t;           //aqui utiizamos o mesmo seguimento e ação que foi feito no trabalho 1.
  distance_array[contador] = p;
  contador++;
if(contador == valor_media) {
  duration_media = 0.;
  distance_media = 0.;
for(int k = 0; k < valor_media; k++){
  duration_media=duration_media + duration_array[k];
  distance_media=distance_media + distance_array[k];
}
  duration_media=duration_media / valor_media;
  distance_media=distance_media / valor_media;
  contador = 0;
}
#endif mmm_pressao
 
#ifdef mmc_pressao                      // inicio do calculos das media correntes ou acumulativas
  contador++;
  duration_mmm += t;                          // aqui utilizamos as funções e seguimentos conforme trabalho 1, baseando em criar resultados;
  distance_mmm += p;                              //para distancia e duração conforme valores pretendidos;
  duration_media = duration_mmm / contador;
  distance_media = distance_mmm / contador;
#endif mmc_humidade

#ifdef mmd_pressao                  //inicio da ação de calculo das medias deslizantes;
if(contador < valor_media) {
    duration_array[contador] = t;
    distance_array[contador] = p;
    contador++;
}
if(contador == valor_media) {            // baseado no descritivo do quadro do mestre nuno, esta formula, 
for(int k = 0; k < valor_media; k++){          //efetua a troca dos valores dos array e traz novas medições trocando a mais antiga;
   if(k < (valor_media - 1)){
     duration_array[k]=duration_array[k + 1];
     distance_array[k]=distance_array[k + 1];
} else {
     duration_array[k] = t;
     distance_array[k] = p;
}
}
for(int k = 0; k < valor_media; k++){                   // dentro das medias ja calculadas e armazenadas no array, 
    duration_media=duration_media + duration_array[k];    //iremos receber novo valor de duração medida e armazenar dentro de um array e 
    distance_media=distance_media + distance_array[k];    //utilizar para efetuar o calculo de nova media com valores atualizados;
}
    duration_media=duration_media / valor_media;
    distance_media=distance_media / valor_media;
}
#endif mmd_pressao

#ifdef gnuplot_pressao
  Serial.print(duration_suav);          //imprimi a suavização da duração;
  Serial.print(F("\t\t "));
  Serial.print(distance_suav);         //imprimi a suavização da distancia;
  Serial.print(F("\t\t "));
  Serial.print(t);
  Serial.print(F("\t\t "));
  Serial.print(p);
  Serial.print(F("\t\t "));
  Serial.print(duration_media);             //imprimi a media da duração, media final;
  Serial.print(F("\t\t "));
  Serial.println(distance_media);           //imprimi a media da distancia, media final;
#endif gnuplot_pressao

#ifdef mplotter_pressao
  Serial.print(F("\tSuavização T (ºC): "));
  Serial.print(duration_suav);          //imprimi a suavização da duração;
  Serial.print(F("\tSuavização P (Pa): "));
  Serial.print(distance_suav);         //imprimi a suavização da distancia;
  Serial.print(F("\tT (ºC): "));
  Serial.print(t);
  Serial.print(F("\tP (Pa): "));
  Serial.println(p);
#endif mplotter_pressao

#ifdef mserial_pressao
  Serial.print(F("\tMedia T (ºC): "));
  Serial.print(duration_media);             //imprimi a media da duração, media final;
  Serial.print(F("\tMedia P (Pa): "));
  Serial.print(distance_media);           //imprimi a media da distancia, media final;
  Serial.print(F("T (ºC) = "));
  Serial.print(t);
  Serial.print("\t\tP (Pa) = ");
  Serial.println(p);
  
if (t > 0 && t <= 75){
   digitalWrite(pino7, HIGH);          // para os valores de if luz de led acessa, estará HIGH;
   Serial.print(F("LED Blue  "));
}
if (t > 75 && t <= 150){
   digitalWrite(pino6, HIGH);      // para os valores de if luz de led acessa, estará HIGH;
   Serial.print(F("LED Yellow  "));
}
if (p > 0 && p <= 25){
   digitalWrite(pino5, HIGH);     // para os valores de if luz de led acessa, estará HIGH;
   Serial.print(F("LED Green  "));
}
if (p > 25 && p <= 70){
   digitalWrite(pino4, HIGH);         // para os valores de if luz de led acessa, estará HIGH;
   Serial.print(F("LED Red  "));
}
#endif mserial_pressao 
}
#endif pressao


/*
Autor: Nuno Pereira  Departamento: Matemática e Ciências Físicas 
Mudanças, incremento e adaptação: Hugo Alexandre Silva
Ano lectivo: 2018-19  Edição: 03
UCs / Cursos: Física Aplicada à Computação / Eng. Informática  
*/ 
