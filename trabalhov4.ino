//#define Monitor
//#define Plotter
#define GnuPlot
#define VersionTwo
//#define Smoothening
//#define MediaCorrenteCumulativa
//#define MediaMMedicoes

byte greenLED = 13;
byte redLED = 8;

const float w = 1.;

#ifdef VersionTwo
const int n = 3;
#endif

const float a = 0.2;
const float tMin = -10.;
const float tMax = 100.;

const float t0 = 10.;
const float t1 = 80.;

#if (defined(MediaCorrenteCumulativa) || defined(MediaMMedicoes))
int counter = 0;
float tmpMed = 0.;
#endif


float tmpAcumulada = 0.;


#ifdef MediaMMedicoes
const int nMed = 3;
float tmpArray[nMed];

#endif

#ifdef Smoothening
const float smoothScale = 0.5;
float tmpOld = 0.;
float tmpSmooth = 0.;
#endif

const int rMin = -60.;
const int rMax = 60.;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

#if (defined(GnuPlot) || defined(Monitor))
  Serial.println("#Trabalho 1 (v2.0): Arduino & Gerador de Sinais");
  Serial.println("#1º Ano - EI - FAC 2018-19\n");
#endif

#ifdef GnuPlot
  Serial.println("#t(s)\ttMin\ttMax\tT\tT0\tT1");
#endif
}

void loop() {
  // put your main code here, to run repeatedly:
  float t = (float) millis() / 1000.0;
#ifdef VersionTwo
  float mSin = 0.; 
  for(int k = 1; k <= n; k++){
    mSin = mSin + sin(k*w*t);
  }
  mSin = mSin / n;
  float tmpNew = varSinal(mSin) + a * random(rMin, rMax);
#else
  float tmpNew = varSinal(sin(w * t)) + a * random(rMin, rMax);
#endif

#ifdef MediaCorrenteCumulativa
  CalcMedCumulativa(tmpNew);
#endif
#ifdef MediaMMedicoes
  CalcMedM(tmpNew);
#endif
#ifdef Smoothening
  tmpSmooth = tmpOld + ((tmpNew - tmpOld) * smoothScale);
#endif
#ifdef Monitor
  displayMonitor(t, tmpNew);
#endif
#ifdef Plotter
  displayPlotter(tmpNew);
#endif
#ifdef GnuPlot
  displayGnuPlot(t, tmpNew);
#endif
#ifdef Smoothening
  tmpOld = tmpSmooth;
#endif
}

float varSinal(float seno){
  float m = (tMax - tMin) / 2;
  float b = (tMin + tMax) / 2;
  return m * seno + b;
}

#ifdef MediaMMedicoes
void CalcMedM(float temp){
  tmpArray[counter] = temp;
  counter++;
  if(counter == nMed) {
    tmpMed = 0.;
    for(int k = 0; k < nMed; k++){
      tmpMed = tmpMed + tmpArray[k];
    }
    tmpMed = tmpMed / nMed;
    counter = 0;
  }
}
#endif

#ifdef MediaCorrenteCumulativa
void CalcMedCumulativa(float temp){
  tmpAcumulada += temp;
  tmpMed = tmpAcumulada / counter;
  counter++;
  Serial.print("tgggggg = ");
  Serial.print(tmpAcumulada);
}
#endif

#ifdef Monitor
void displayMonitor(float timer, float temp){
  Serial.print("t = ");
  Serial.print(timer);
  Serial.print("\ttMin = ");
  Serial.print(tMin);
  Serial.print("\ttMax = ");
  Serial.print(tMax);
  Serial.print("\tT = ");
  Serial.print(temp);
  Serial.print("\tT0 = ");
  Serial.print(t0);
  Serial.print("\tT1 = ");
  Serial.print(t1);
  colorLEDChecker(temp);
}
#endif

#ifdef Plotter
void displayPlotter(float temperature){
  Serial.print("\ttMin = ");
  Serial.print(tMin);
  Serial.print("\ttMax = ");
  Serial.print(tMax);
#if (defined(MediaCorrenteCumulativa) || defined(MediaMMedicoes))
  Serial.print("\ttMed = ");
  Serial.print(tmpMed);
#endif
#ifdef Smoothening
  Serial.print("\tSmoothened = ");
  Serial.print(tmpSmooth);
#endif
  Serial.print("\tT = ");
  Serial.print(temperature);
  Serial.print("\tT0 = ");
  Serial.print(t0);
  Serial.print("\tT1 = ");
  Serial.println(t1);
  colorLEDChecker(temperature);
}
#endif

void colorLEDChecker(float temperature){
  if (tMin < temperature && temperature <= t0){
    Serial.println("\tLED Green");
    digitalWrite(greenLED, HIGH);     // turns the green LED ON
    digitalWrite(redLED, LOW);     // turns the red LED OFF
  } else {
    if (temperature <= t1){
      Serial.println("\tLED Green+Red");
      digitalWrite(greenLED, HIGH);     // turns the green LED ON
      digitalWrite(redLED, HIGH);     // turns the red LED ON
    } else {
      if (temperature <= tMax){
        Serial.println("\tLED Red");
        digitalWrite(redLED, HIGH);     // turns the red LED ON
        digitalWrite(greenLED, LOW);     // turns the green LED OFF
      } else {
        Serial.println("\t Temperature out of range");
        digitalWrite(greenLED, LOW);     // turns the green LED OFF
        digitalWrite(redLED, LOW);     // turns the green LED OFF
      }
    }
  }
}

#ifdef GnuPlot
void displayGnuPlot(float timer, float temperature){
  Serial.print(timer);
  Serial.print("\t");
  Serial.print(tMin);
  Serial.print("\t");
  Serial.print(tMax);
  Serial.print("\t");
  Serial.print(temperature);
  Serial.print("\t");
  Serial.print(t0);
  Serial.print("\t");
  Serial.println(t1);
}
#endif
