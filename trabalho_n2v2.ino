//#define DispositivoUltraSons
#define SensorTempAr_HumidadeRel
//#define SensorTempAr_PressaoAtm

//#define Smoothening
//#define MediaCorrenteCumulativa
//#define MediaMMedicoes
#define MediaMDeslizante

#if defined(DispositivoUltraSons)
byte Vcc = 11;
#endif
#ifdef DispositivoUltraSons
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
  #elif defined(SensorTempAr_HumidadeRel) || defined(MediaMDeslizante)
    float oldValOne = 0.;
    float oldValTwo = 0.;
    float valOneSmooth = 0.;
    float valTwoSmooth = 0.;
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
  #elif defined(SensorTempAr_HumidadeRel) || defined(SensorTempAr_PressaoAtm)
    float valOneMed = 0.;
    float valTwoMed = 0.;
    #ifdef MediaCorrenteCumulativa
      float valOneAcumulado = 0.;
      float valTwoAcumulado = 0.;
    #elif defined(MediaMMedicoes) || defined(MediaMDeslizante)
      float valOneArray[nMed];
      float valTwoArray[nMed];
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
    durSmooth = SmoothUpValue(duration, oldDur);
    distSmooth = SmoothUpValue(distance, oldDist);
  #elif (defined(MediaCorrenteCumulativa) || defined(MediaMMedicoes) || defined(MediaMDeslizante))
    CalcMed(duration);
  #endif
  displayData(duration);
  #ifdef Smoothening
    oldDur = durSmooth;
    oldDist = distSmooth;
  #endif

// Parte do sensor tempAr e humidadeRel
#elif defined(SensorTempAr_HumidadeRel)
  delay(delaySample);
  float h = dht.readHumidity(); // Read relative humidity
  float t = dht.readTemperature(); // Read temperature in Celcius
  // Check validity of readings
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Invalid Data!"));
    return; // Loops to the reading instructions without printing data
  }

  #ifdef Smoothening
    valOneSmooth = SmoothUpValue(h, oldValOne);
    valTwoSmooth = SmoothUpValue(t, oldValTwo);
  #elif (defined(MediaCorrenteCumulativa) || defined(MediaMMedicoes) || defined(MediaMDeslizante))
    CalcMed(h, t);
  #endif
  // Write to serial port
  displayData(h, t);
  
  #ifdef Smoothening
    oldValOne = valOneSmooth;
    oldValTwo = valTwoSmooth;
  #endif
#endif
}

#ifdef Smoothening
float SmoothUpValue(float v, float oldV){
  return oldV + (v - oldV) * smoothScale;
}
#endif

#ifdef MediaCorrenteCumulativa
  #ifdef DispositivoUltraSons
void CalcMed(float dur){
  counter++;
  durAcumulada += dur;
  distAcumulada += distance;
  durMed = durAcumulada / counter;
  distMed = distAcumulada / counter;
}
  #elif defined(SensorTempAr_HumidadeRel)
void CalcMed(float valOne, float valTwo){
  counter++;
  valOneAcumulado += valOne;
  valTwoAcumulado += valTwo;
  valOneMed = valOneAcumulado / counter;
  valTwoMed = valTwoAcumulado / counter;
}
  #endif
#endif

#ifdef MediaMMedicoes
  #ifdef DispositivoUltraSons
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
  #elif defined(SensorTempAr_HumidadeRel)
void CalcMed(float valOne, float valTwo){
  valOneArray[counter] = valOne;
  valTwoArray[counter] = valTwo;
  counter++;
  if(counter == nMed) {
    valOneMed = 0.;
    valTwoMed = 0.;
    for(int k = 0; k < nMed; k++){
      valOneMed = valOneMed + valOneArray[k];
      valTwoMed = valTwoMed + valTwoArray[k];
    }
    valOneMed = valOneMed / (float) nMed;
    valTwoMed = valTwoMed / (float) nMed;
    counter = 0;
  }
}
  #endif
#endif

#ifdef MediaMDeslizante
  #ifdef DispositivoUltraSons
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
  #elif defined(SensorTempAr_HumidadeRel)
void CalcMed(float valOne, float valTwo){
  if(counter < nMed) {
    // Se as casas dos arrays correspondentes não estiverem preenchidos, preenche uma casa vazia de cada array
    valOneArray[counter] = valOne;
    valTwoArray[counter] = valTwo;
    counter++;
  }
  
  // Se as casas de cada array estão todas preenchidas, atualiza a media
  if(counter == nMed) {
    /* Se, quando cada array receber um novo valor correspondente e já tiver as casas todas preenchidas, então 
       descarta o valor da casa de cada array mais antiga e adiciona um novo valor correspondente ao array */
    for(int k = 0; k < nMed; k++){
      if(k < (nMed - 1)){
        valOneArray[k] = valOneArray[k + 1];
        valTwoArray[k] = valTwoArray[k + 1];
      } else {
        /* Como o valor da variavel k é correspondente à ultima casa de todos os arrays, então a ultima casa de
           cada array recebe o novo valor*/
        valOneArray[k] = valOne;
        valTwoArray[k] = valTwo;
      }
    }

    /* Faz reset às variáveis que recebem os resultados das médias correspondentes para não serem considerados 
       cálculos anteriores*/
    valOneMed = 0.;
    valTwoMed = 0.;

    /* Faz a parte da soma de todos os valores correspondentes dos arrays para de pois fazer a parte da divisão das médias*/
    for(int k = 0; k < nMed; k++){
      valOneMed = valOneMed + valOneArray[k];
      valTwoMed = valTwoMed + valTwoArray[k];
    }
    // Faz a parte da divisão das médias correspondentes a cada array
    valOneMed = valOneMed / ((float) nMed);
    valTwoMed = valTwoMed / ((float) nMed);
  }
}
  #endif
#endif

#ifdef DispositivoUltraSons
void displayData(float dur){
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
#elif defined(SensorTempAr_HumidadeRel) || defined(SensorTempAr_PressaoAtm)
void displayData(float valOne, float valTwo){
  Serial.print(F("Humidity (%): "));
  Serial.print(valOne);
  Serial.print(F("\tTemperature (ºC): "));
  Serial.print(valTwo);
#ifdef Smoothening
  Serial.print(F("\tsmoothened humidity(%)= "));
  Serial.print(valOneSmooth);
  Serial.print(F("\tsmoothened temperature(ºC)= "));
  Serial.println(valTwoSmooth);
#elif (defined(MediaCorrenteCumulativa) || defined(MediaMMedicoes) || defined(MediaMDeslizante))
  Serial.print(F("\taverage humidity(%)= "));
  Serial.print(valOneMed);
  Serial.print(F("\taverage temperature(ºC)= "));
  Serial.println(valTwoMed);
#else
  Serial.print("\n");
#endif
}
#endif
