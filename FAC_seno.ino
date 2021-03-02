/* 
 * Fisica Aplicada a Computacao - Engenharia Informatica
 * Aluno: Hugo Alexandre, Tiago Filipe, Omar Pizon
 * Mestre: Nuno Pereira
 * 2018-19
 * Hardware: Arduino Uno R3
 * Descricao: testa estruturas de programacao, sensor de temperatura.
 * Primeiro trabalho em sala de aula.
 * Versão 10/11/2019
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
//variáveis globais que nos irão mostrar a temperatura, ruido, base de analise e calculo para o seno;
//pino onde poderemos ligar o sensor por exemplo para captar a temperatura;float t=0;
  int sensor = 2;
//após a formulação do calculo os acendimentos dos led ocorreram nos seguintes pinos;
  const int pino4 = 4; 
  const int pino5 = 5;
  const int pino6 = 6;
  const int pino7 = 7;
/* escolhemos a variavél float por receber números decimais que ocupam 32 bits(4 bytes);
* assim não precesariamos usar a variavel double que ocupa o dobro em alguns casos, economizando até mesmo no espaço de memoria;
* essas variaveis podem tomar valores entre -3.4028235E+38 e +3.4028235E+38.
*/

//#define parteum                  //contém marcadores, if, calculo seno, ruido, led's;
//#define partedois               //contém a função 7 senos;
#define partetres             //contém as medias, mcm, mmm, smoothing ou suavização;
//#define mediac              //contém a media corrente acumulativa;
#define mmmedia              //leitura das temperaturas, divida por 3; 
//#define suav                 //suavização das leituras em media;
#define gnuplot               //seleção para impressão dentro do gnuplot;
//#define mserial              //seleção para impressão apenas dentro do serial monitor;
//#define mplotter            //seleção para impressão apenas dentro do monitor plotter;

        float t = 0.;            // executa o operação em millis;
        float y = 0.;            // variavel rcebe o calculo da função seno;
        float tmin = -40.;          // valor temperatura minima;
        float tmax = 120.;          // valor temperatura maxima;
        float f = 0.;            // variavel recebe o calculo da função temperatura;
        float temp = 0.;             // variavel de calculo da função mais o ruido;
        float w = 2.;               // variavel para periodo seno;
        int contador = 0;           //variavel para contar numero de vezes, junto a temperatura, usada na função para calculo da media;
        float temperaturas = 0.;       // irá receber a leituras das temp e irá soma-las;
        float mms = 0.;                    //suavização final ou mais recente;
        float mmsI = 0.;               //suavização inicial;
        float media = 0.;                // recebe a média;
        float mmm = 0.;                 // recebe a media calculada de tres temp divido por 3;
        const int quant = 0;              //recebe a quantidade de valores a ser divido na media;
        const int contLeitura = 3;        // quantidade de valores guardado da temperatura; como o valores são gerados aleatorios em temp, utilizamos array 10 para ir guardando de 10 em 10 os valores e que depois será somado em leitura_a;
        float tempContLeitura[contLeitura];   //array usado para a formula do calculo da media e leitura de 3 em 3;
        
      
//inicialização do codigo para execução
void setup() { 
// put your setup code here, to run once:
    Serial.begin(9600);           // Sincronizar a porta serial a 9600 bits por segundo;
    pinMode(sensor, INPUT);       // Defini o nosso sensor como INPUT;
    randomSeed(analogRead(1));    // Esta instrução é necessária, para que o nosso sensor possa estar pronto para ser utilizado;
#ifdef gnuplot        
        Serial.println("#Trabalho Fisica Aplicada a Computação - Mestre Nuno\n");
        Serial.println("#Gerador de Seno - 1º Ano - FAC 2018-19\n");
        Serial.println("#\tt\tTmin\tT0\tT1\tTmax\tT\tMedia\tMMM\tMMS");
#endif gnuplot
} //fim da void setup

void loop() { //inicio da operação loop
    
// put your main code here, to run repeatedly:
    delay(100);       // leitura do programa durante 1000 milissegundos que equivale a 1 segundo;
    
#ifdef parteum 
/* variaveis para calculo e elaboração da função de leitura da temperatura, assim como calculo
* e regras a serem seguidas na estrutura de ação do codigo;
*/   
    float ruido = 0.8 * random(-3,3); // calculo para o ruido;
    t = t + 0.09;               // acrescenta sempre o valor somado de + 0.09;
    y = calculation (temp);       //retorno do calculo da função f = ((tmax - tmin) / 2.0) * y + (tmax - (tmax - tmin) / 2.0);
    temp = func(y) + ruido;        // calculo completo da função seno com ruido;
#ifdef mplotter
       Serial.print(F("Tmax = "));
       Serial.print(120);// marcação da linha de maior temperatura;
       Serial.print(F("Tmin = "));
       Serial.print(-40); // marcação da linha de menor temperatura;
       Serial.print(F("t = ")); 
       Serial.println(temp);    //imprima na tela o resultado da função completa;
       Serial.print(F("T0 = "));
       Serial.print(10); // marcação da linha de valor aleatorio da tempertura;
       Serial.print(F("T1 = "));
       Serial.print(80); // marcação da linha de valor aleatorio da tempertura;
#endif mplotter
#ifdef mserial
        Serial.print(F("\tTmin ="));
        Serial.print(-40); // marcação da linha de menor temperatura;
        Serial.print(F("\tT0 ="));
        Serial.print(10); // marcação da linha de valor aleatorio da tempertura;
        Serial.print(F("\tT1 ="));
        Serial.print(80); // marcação da linha de valor aleatorio da tempertura;
        Serial.print(F("\tTmax ="));
        Serial.print(120);// marcação da linha de maior temperatura;
        Serial.print(F("\tt =")); 
        Serial.println(temp);   //imprima na tela o resultado da função completa;
        Serial.print(F("\tT =")); 
        Serial.print(t,2);  //imprimi o resultado t com acrescimo 0.09;
//Condição para resultados de temperaturas, com seleção dos pinos escolhidos e cores para representar a temperatura;
if (temp < -40){
      digitalWrite(pino7, HIGH); // para os valores de if luz de led acessa, estará HIGH;
        Serial.print(F("\t Led Marrom"));
}
if (temp >= -40 && temp < -20){
      digitalWrite(pino4, HIGH); // para os valores de if luz de led acessa, estará HIGH;
      digitalWrite(pino5, LOW); // para os valores de if luz de led apagada, estará LOW;
      digitalWrite(pino6, LOW);
        Serial.print(F("\t Led Azul"));
}
if (temp >= -20 && temp < 0){
      digitalWrite(pino4, LOW);
      digitalWrite(pino5, HIGH);
      digitalWrite(pino6, LOW);
        Serial.print(F("\t Led Verde"));
}
if (temp >= 0 && temp < 25){
      digitalWrite(pino4, LOW);
      digitalWrite(pino5, LOW);
      digitalWrite(pino6, HIGH);
        Serial.print(F("\t Led Laranja"));
}
if (temp >= 25 && temp < 50){
      digitalWrite(pino4, HIGH);
      digitalWrite(pino5, HIGH);
      digitalWrite(pino6, LOW);
        Serial.print(F("\t Led Vermelho"));
} 
if (temp >= 50 && temp <= 120){
      digitalWrite(pino4, HIGH);
      digitalWrite(pino5, HIGH);
      digitalWrite(pino6, HIGH);
        Serial.print(F("\t Led Violeta"));
}
if (temp > 120){
      digitalWrite(pino7, HIGH); // para os valores de if luz de led acessa, estará HIGH;
        Serial.print(F("\t Led Marrom"));
}
#endif mserial
#ifdef gnuplot 
        Serial.print(F("\t"));
        Serial.print(-40); // marcação da linha de menor temperatura;
        Serial.print(F("\t"));
        Serial.print(10); // marcação da linha de valor aleatorio da tempertura;
        Serial.print(F("\t"));
        Serial.print(80); // marcação da linha de valor aleatorio da tempertura;
        Serial.print(F("\t"));
        Serial.print(120);// marcação da linha de maior temperatura;
        Serial.print(F("\t")); 
        Serial.println(temp);   //imprima na tela o resultado da função completa;
        Serial.print(F("\t")); 
        Serial.print(t,2);  //imprimi o resultado t com acrescimo 0.09;
#endif gnuplot
} //fim da void loop;
      float func (float y){ 
        f = (tmax - tmin) / 2.0 * y + tmax - (tmax - tmin) / 2.0;
return f;       // dividimos a equação de calculo e a variavel func esta recebendo y e a parte do calculo em variavel f;
}
      float calculation(float temp){ 
        y = sin(w*t);
return y;       // recebe o y e executa o calculo do seno;
}   
#endif parteum

//-------------------------------

#ifdef partedois
      float ruido = 0.3 * random(-10,10); // calculo para o ruido;
      t = (float) millis()/1000.; // acrescenta o calculo/contagem em millis;
      y = calculation (temp);     //retorno do calculo da função f = ((tmax - tmin) / 2.0) * y + (tmax - (tmax - tmin) / 2.0);
      temp = func(y) + ruido;     // calculo completo da função seno com ruido;
#ifdef mplotter
       Serial.print(F("Tmax = "));
       Serial.print(120);// marcação da linha de maior temperatura;
       Serial.print(F("Tmin = "));
       Serial.print(-40); // marcação da linha de menor temperatura;
       Serial.print(F("t = ")); 
       Serial.println(temp);    //imprima na tela o resultado da função completa;
       Serial.print(F("T0 = "));
       Serial.print(10); // marcação da linha de valor aleatorio da tempertura;
       Serial.print(F("T1 = "));
       Serial.print(80); // marcação da linha de valor aleatorio da tempertura;
#endif mplotter
#ifdef mserial
         Serial.print(F("\tt= ")); //imprima na tela o resultado da função completa;
         Serial.println(temp);
         Serial.print(F("\tTmin= "));
         Serial.print(-40); // marcação da linha de menor temperatura;
         Serial.print(F("\tT0= "));
         Serial.print(10); // marcação da linha de valor aleatorio da tempertura;
         Serial.print(F("\tT1= "));
         Serial.print(80); // marcação da linha de valor aleatorio da tempertura;
         Serial.print(F("\tTmax= "));
         Serial.print(120);// marcação da linha de maior temperatura;
         Serial.print(F("\tT= "));  
         Serial.print(t,2);   //imprimi o resultado t com millis;
#endif mserial
#ifdef gnuplot
        Serial.print(F("\t"));
        Serial.print(-40); // marcação da linha de menor temperatura;
        Serial.print(F("\t"));
        Serial.print(10); // marcação da linha de valor aleatorio da tempertura;
        Serial.print(F("\t"));
        Serial.print(80); // marcação da linha de valor aleatorio da tempertura;
        Serial.print(F("\t"));
        Serial.print(120);// marcação da linha de maior temperatura;
        Serial.print(F("\t")); 
        Serial.println(temp);   //imprima na tela o resultado da função completa;
        Serial.print(F("\t")); 
        Serial.print(t,2);  //imprimi o resultado t com acrescimo em millis;
#endif gnuplot         
} //fim da void loop;
      float func (float y){
        f = ((tmax - tmin) / 2.0) * y + (tmax - (tmax - tmin) / 2.0);
return f;       // dividimos a equação de calculo e a variavel func esta recebendo y e a parte do calculo em variavel f;
}
      float calculation(float temp){  
        y = 0.;
for( int k = 1; k < 8; k++){        //regra para seno de 7 valores;
        y += (sin(k*w*t));
}
return y;       // recebe o y e executa o calculo do seno;
}
#endif partedois

//-------------------------------

#ifdef partetres
      float ruido = 1 * random(-10,10);     // calculo para o ruido;
      t = (float) millis()/1000.0;        // acrescenta o calculo/contagem em millis;
      y = calculation (temp);  //retorno do calculo da função f = ((tmax - tmin) / 2.0) * y + (tmax - (tmax - tmin) / 2.0);
    temp = func(y) + ruido; // calculo completo da função seno com ruido;
#ifdef mediac               //media acumulada, soma todos os valores apresentados em temp e depois divide pelo numero do contador;
     temperaturas += temp;
     media = temperaturas/contador;
     contador++;
#endif mediac
#ifdef mmmedia                    //media corrente, soma 3 valores apresentados em temp e depois divide por 3;
     tempContLeitura[contador] = temp;
        contador++;
if(contador == contLeitura) {
     mmm = 0.;
for(int k = 0; k < contLeitura; k++){       //condição e contador para a apresentação da media em 3 em 3;
     mmm = mmm + tempContLeitura[k];
}
     mmm = mmm / contLeitura;
        contador = 0;
}  
#endif mmmedia
#ifdef suav
      mms = temp;  
      mmsI = mms + ((temp - mms) * 0.5); //suavização parte superior;
#endif suav
#ifdef mplotter
       Serial.print(F(" "));
       Serial.print(10); // marcação da linha de valor aleatorio da tempertura;
       Serial.print(F(" "));
       Serial.print(80); // marcação da linha de valor aleatorio da tempertura;
       Serial.print(F(" "));
       Serial.print(120);// marcação da linha de maior temperatura;
       Serial.print(F(" "));
       Serial.print(-40); // marcação da linha de menor temperatura;
       Serial.print(F(" ")); 
       Serial.println(temp); //imprima na tela o resultado da função completa;
       Serial.print(F(" "));
       Serial.print(media);   // imprimi media mcm acumulativa;
       Serial.print(F(" "));
       Serial.print(mmm);   // imprimi media mmm;
#endif mplotter
#ifdef mserial
        Serial.print(F("\tT0= "));
        Serial.print(y); // marcação da linha de valor aleatorio da tempertura;
        Serial.print(F("\tT1= "));
        Serial.print(80); // marcação da linha de valor aleatorio da tempertura;
        Serial.print(F("\tt= "));     
        Serial.println(temp);   //imprima na tela a função completa;
        Serial.print(F("\tTmin= "));
        Serial.print(-40); // marcação da linha de menor temperatura;
        Serial.print(F("\tTmax= "));
        Serial.print(120);// marcação da linha de maior temperatura;
        Serial.print(F("\tT= "));   
        Serial.print(t,2);    //imprimi o resultado T com millis;
        Serial.print(F("\tContador= "));  
        Serial.print(contador);                 // imprimi a contagem;
        Serial.print(F("\tMedia= "));
        Serial.print(media);                 // imprimi media mcm acumulativa;
        Serial.print(F("\tMMM= "));
        Serial.print(mmm);   // imprimi media mmm;
        Serial.print(F("\tMMS= "));
        Serial.print(mmsI);     // imprimi suavização;
//Condição para resultados de temperaturas, com seleção dos pinos escolhidos e cores para representar a temperatura;
if (temp < -40){
      digitalWrite(pino7, HIGH); // para os valores de if luz de led acessa, estará HIGH;
        Serial.print(F("\t  Led Marrom"));
}
if (temp >= -40 && temp < -20){
      digitalWrite(pino4, HIGH); // para os valores de if luz de led acessa, estará HIGH;
      digitalWrite(pino5, LOW); // para os valores de if luz de led apagada, estará LOW;
      digitalWrite(pino6, LOW);
        Serial.print(F("\t  Led Azul"));
}
if (temp >= -20 && temp < 0){
      digitalWrite(pino4, LOW);
      digitalWrite(pino5, HIGH);
      digitalWrite(pino6, LOW);
        Serial.print(F("\t  Led Verde"));
}
if (temp >= 0 && temp < 25){
      digitalWrite(pino4, LOW);
      digitalWrite(pino5, LOW);
      digitalWrite(pino6, HIGH);
        Serial.print(F("\t  Led Laranja"));
}
if (temp >= 25 && temp < 50){
      digitalWrite(pino4, HIGH);
      digitalWrite(pino5, HIGH);
      digitalWrite(pino6, LOW);
        Serial.print(F("\t  Led Vermelho"));
} 
if (temp >= 50 && temp <= 120){
      digitalWrite(pino4, HIGH);
      digitalWrite(pino5, HIGH);
      digitalWrite(pino6, HIGH);
        Serial.print(F("\t  Led Violeta"));
}
if (temp > 120){
      digitalWrite(pino7, HIGH); // para os valores de if luz de led acessa, estará HIGH;
        Serial.print(F("\t  Led Marrom"));
}
#endif mserial
#ifdef gnuplot
        Serial.print(F("\t "));
        Serial.print(-40); // marcação da linha de menor temperatura;
        Serial.print(F("\t "));
        Serial.print(10); // marcação da linha de valor aleatorio da tempertura;
        Serial.print(F("\t "));
        Serial.print(80); // marcação da linha de valor aleatorio da tempertura;
        Serial.print(F("\t "));
        Serial.print(120);// marcação da linha de maior temperatura;
        Serial.print(F("\t ")); 
        Serial.println(temp);   //imprima na tela o resultado da função completa;
        Serial.print(F("\t ")); 
        Serial.print(t,2);  //imprimi o resultado t com acrescimo em millis;
        Serial.print(F("\t "));
        Serial.print(media);  // imprimi media mcm acumulativa;
        Serial.print(F("\t "));
        Serial.print(mmm);   // imprimi media mmm;
        Serial.print(F("\t "));
        Serial.print(mmsI);   // imprimi media mms;
#endif gnuplot
} //fim da void loop;
      float func (float y){ 
        f = ((tmax - tmin) / 2.0) * y + (tmax - (tmax - tmin) / 2.0);
return f;                           // dividimos a equação de calculo e a variavel func esta recebendo y e a parte do calculo em variavel f;
}
      float calculation(float temp){ 
        y = sin(w*t);
return y;                           // recebe o y e executa o calculo do seno;
}
#endif partetres
