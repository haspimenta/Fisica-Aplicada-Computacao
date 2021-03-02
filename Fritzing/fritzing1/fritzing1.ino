 int sensor = 2;

  const int pino4; 
  const int pino5;
  const int pino6;

  float t = 0;
  float y = 0;
  float tmin = -40;
  float tmax = 120;
  float w = 1;
  float k = 0;
  float r = 0;


  void setup() {

  Serial.begin(9600);
  pinMode(sensor, INPUT); 
  randomSeed(analogRead(1)); 
       } 

  void loop() {

 delay(10);

  if (t > -41 && t <= -20){
      digitalWrite(pino4, HIGH);
      digitalWrite(pino5, LOW);
      digitalWrite(pino6, LOW);
      //Serial.print(t,2);
      //Serial.println(F("Led Azul"));
      }
  
  if (t > -20 && t <= 0){
      digitalWrite(pino4, LOW);
      digitalWrite(pino5, HIGH);
      digitalWrite(pino6, LOW);
      //Serial.print(t,2);
      //Serial.print(F("Led Verde"));
      }
  
  if (t > 0 && t <= 25){
      digitalWrite(pino4, LOW);
      digitalWrite(pino5, LOW);
      digitalWrite(pino6, HIGH);
      //Serial.print(t,2);
      //Serial.print(F("Led Laranja"));
      }
  
  if (t > 25 && t <= 50){
      digitalWrite(pino4, HIGH);
      digitalWrite(pino5, HIGH);
      digitalWrite(pino6, LOW);
      //Serial.print(t,2);
      //Serial.print(F("Led Vermelho"));
      }
  
  if (t > 50 && t <= 120){
      digitalWrite(pino4, HIGH);
      digitalWrite(pino5, HIGH);
      digitalWrite(pino6, HIGH);
      //Serial.print(t,2);
      //Serial.print(F("Led Violeta"));
      }
    
  float ruido = 0.4 * random(-10,10);
  t += 0.09;
  y = calculation (t);
  r = func(y) + ruido;
  Serial.println(r); 
  Serial.print(" ");
  Serial.print(-20);
  Serial.print(" "); 
  Serial.print(10);
  Serial.print(" ");
  //Serial.print(0);
  //Serial.print(" ");
  Serial.print(80);
  Serial.print(" ");
  Serial.print(100);
  Serial.print(" ");
      } 
  
  float func (float y){
  k = (tmax - tmin) / 2.0 * y + tmax - (tmax - tmin) / 2.0 ;
  return k;
  
      }

  float calculation(float t){
  y = sin(w*t);
  return y;  
  
      }
