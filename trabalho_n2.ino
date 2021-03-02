#define DispositivoUltraSons
//#define SensorTempAr_HumidadeRel
//#define SensorTempAr_PressaoAtm

//#define Smoothening
//#define MediaCorrenteCumulativa
//#define MediaMMedicoes
//#define MediaMDeslizante

#ifdef DispositivoUltraSons
byte Vcc = 11;
byte Trig = 12;
byte Echo = 13;
float distance;
byte triggerDuration = 10; // us
unsigned int sampleDelay = 1000; // ms
unsigned int timeout = 23530; // tempo correspondente a d > 4m
#elif defined(SensorTempAr_HumidadeRel)
#include<DHT.h>
// Declaration of global variables
byte DHTpin = 2; // Digital pin to connect pin 2 of the sensor
int delaySample = 2000; // delay between measurements in ms
// Definition of the sensor
DHT dht(DHTpin, DHT11);
#endif


#ifdef Smoothening
  const float smoothScale = 0.3;
  #ifdef DispositivoUltraSons
    float oldDur = 0.;
    float oldDist = 0.;
    float durSmooth = 0.;
    float distSmooth = 0.;
  #endif
#endif

#if (defined(MediaCorrenteCumulativa) || defined(MediaMMedicoes) || defined(MediaMDeslizante))
  int counter = 0;
  #if defined(MediaMMedicoes) || defined(MediaMDeslizante)
  const int nMed = 3;
  #endif
  #ifdef DispositivoUltraSons
    float durMed = 0.;
    float distMed = 0.;
    #ifdef MediaCorrenteCumulativa
      float durAcumulada = 0.;
      float distAcumulada = 0.;
    #elif defined(MediaMMedicoes) || defined(MediaMDeslizante)
      float durArray[nMed];
      float distArray[nMed];
    #endif
  #endif
#endif

// Initialization
void setup() {
#ifdef DispositivoUltraSons
  pinMode(Vcc, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Vcc, HIGH);
  digitalWrite(Trig, LOW);
  Serial.begin(9600);
  while(!Serial);
#elif defined(SensorTempAr_HumidadeRel)
  Serial.begin(115200); // Start serial port communications
  Serial.println(F("FAC - EI (v1.0) | 2018-19\nDHT11 test\n"));
  dht.begin(); // Initialize sensor
  delay(delaySample);
#endif
}
// Main loop
void loop(){
#ifdef DispositivoUltraSons
  delay(sampleDelay);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(triggerDuration);
  digitalWrite(Trig, LOW);
  unsigned long duration = pulseIn(Echo, HIGH, timeout);
  distance = (float)duration/58.8;
    #ifdef Smoothening
      durSmooth = oldDur + (duration - oldDur) * smoothScale;
      distSmooth = oldDist + (distance - oldDist) * smoothScale;
    #elif (defined(MediaCorrenteCumulativa) || defined(MediaMMedicoes) || defined(MediaMDeslizante))
      CalcMed(duration);
    #endif
 displayUltraSound(duration);
    #ifdef Smoothening
      oldDur = durSmooth;
      oldDist = distSmooth;
    #endif
#endif
}

#ifdef MediaCorrenteCumulativa
void CalcMed(float dur){
  counter++;
  durAcumulada += dur;
  distAcumulada += distance;
  durMed = durAcumulada / counter;
  distMed = distAcumulada / counter;
}
#endif

#ifdef MediaMMedicoes
void CalcMed(float dur){
  durArray[counter] = dur;
  distArray[counter] = distance;
  counter++;
  if(counter == nMed) {
    durMed = 0.;
    distMed = 0.;
    for(int k = 0; k < nMed; k++){
      durMed = durMed + durArray[k];
      distMed = distMed + distArray[k];
    }
    durMed = durMed / (float) nMed;
    distMed = distMed / (float) nMed;
    counter = 0;
  }
}
#endif

#ifdef MediaMDeslizante
void CalcMed(float dur){
  if(counter < nMed) {
    // Se as casas dos arrays correspondentes não estiverem preenchidos, preenche uma casa vazia de cada array
    durArray[counter] = dur;
    distArray[counter] = distance;
    counter++;
  }
  
  // Se as casas de cada array estão todas preenchidas, atualiza a media
  if(counter == nMed) {
    /* Se, quando cada array receber um novo valor correspondente e já tiver as casas todas preenchidas, então 
       descarta o valor da casa de cada array mais antiga e adiciona um novo valor correspondente ao array */
    for(int k = 0; k < nMed; k++){
      if(k < (nMed - 1)){
        durArray[k] = durArray[k + 1];
        distArray[k] = distArray[k + 1];
      } else {
        /* Como o valor da variavel k é correspondente à ultima casa de todos os arrays, então a ultima casa de
           cada array recebe o novo valor*/
        durArray[k] = dur;
        distArray[k] = distance;
      }
    }

    /* Faz reset às variáveis que recebem os resultados das médias correspondentes para não serem considerados 
       cálculos anteriores*/
    durMed = 0.;
    distMed = 0.;

    /* Faz a parte da soma de todos os valores correspondentes dos arrays para de pois fazer a parte da divisão das médias*/
    for(int k = 0; k < nMed; k++){
      durMed = durMed + durArray[k];
      distMed = distMed + distArray[k];
    }
    // Faz a parte da divisão das médias correspondentes a cada array
    durMed = durMed / ((float) nMed);
    distMed = distMed / ((float) nMed);
  }
}
#endif

void displayUltraSound(float dur){
  Serial.print(F("duration(us)= "));
  Serial.print(dur);
  Serial.print(F("\tdistance(cm)= "));
  Serial.print(distance);
#ifdef Smoothening
  Serial.print(F("\tsmoothened duration(us)= "));
  Serial.print(durSmooth);
  Serial.print(F("\tsmoothened distance(us)= "));
  Serial.println(distSmooth);
#elif (defined(MediaCorrenteCumulativa) || defined(MediaMMedicoes) || defined(MediaMDeslizante))
  Serial.print(F("\taverage duration(us)= "));
  Serial.print(durMed);
  Serial.print(F("\taverage distance(cm)= "));
  Serial.println(distMed);
#else  
  Serial.print("\n");
#endif
}
