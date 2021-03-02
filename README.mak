Arduino UNO R3: Seno 
Física Aplicada à Computação - Licenciatura em Engenharia Informática 

Hugo Alexandre Silva


Beja - Portugal
 	 

Sumário


Introdução 

Este trabalho visa executar tarefas em Arduino que é uma plataforma de prototipagem eletrônica de hardware em placa única, projetada inicialmente com um microcontrolador Atmel AVR, trabalhando com periféricos com conexões de entrada e saída constituído por 14 pinos, assim como circuitos eletrônicos e manipuláveis em uma linguagem de programação padrão. A linguagem tem origem em Wiring e é essencialmente C/C++.  A visão do projeto é criar ferramentas acessíveis, com baixo custo, flexíveis e fáceis de se usar por principiantes e profissionais, aqueles que não teriam alcance aos controladores mais sofisticados e ferramentas mais complicadas. Em relação a pinagem são: 6 podem ser usados como saídas PWM, 6 entradas analógicas, uma conexão USB, uma entrada de alimentação com conexão ICSP e um botão de reset. Cada um dos 14 pinos digitais do UNO podem ser utilizados como uma entrada ou saída utilizando-se as funções pinMode(), digitalWrite() e digitalRead(). Eles operam a 5.0V e cada pino pode fornecer ou receber um máximo de 40mA. 
Neste trabalho utilizamos o Arduino UNO R3 como sistema de aquisição de dados de sensores nomeadamente sensores da temperatura com cálculos e formulas de seno, temperatura, ruído, somatório de série de 7 senos, as quais são: T=f (sin(wt))+ A∗random(Rmin,Rmax),  T=f (∑ k=1 N sin(kwt))+ A∗random(Rmin,Rmax ). Posteriormente, o tratamento do código com o intuito de desenvolver competências de programação de sistema de dados e tratamento elementar. 
Ao Arduino UNO R3 podemos complementar vários sensores como, por exemplo, sensores ambientais, ópticos, força e flexão, som e temperatura e humidade relativa. 

O presente trabalho estruturar-se-á do seguinte modo: 

“Primeiro será uma variação sinusoidal entre valores arbitrários Tmin e Tmax, definidos como constantes, com ruído obtido a partir do gerador de números pseudo aleatórios, random(), de acordo com a formula citada acima.
Definição de dois níveis de alerta T0 e T1 correspondentes às seguintes situações: ◦ Se Tmin < T ≤ To mensagem “LED Green” / acende LED verde ◦ Se To < T ≤ T1 mensagem “LED Green+Red” / acende LED verde e vermelho ◦ Se T1 < T ≤ Tmax mensagem “LED Red” / acende LED vermelho.
Segundo, será uma versão do programa o sinal deverá ser gerado não apenas por uma função seno, mas através de uma soma de N funções de acordo com a citada acima. O parâmetro N, que define o número de termos do somatório, é definido pelo utilizador. A figura 5 mostra um exemplo do sinal gerado a partir de uma série de 7 senos.
Média corrente cumulativa (MCM): Tmed = (T1 + T2 + … + Tk) / k, em que k é o número de medições realizadas; • Média corrente de M medições (MMM): TM = (Tk + Tk+1 + … + Tk+M-1) / M, em que M é número medições que entram no cálculo; • Smoothening: Ts = Tk + (Tk+1 – Tk) x fs , em que Ts é a medição suavizada calculada a partir de duas medições consecutivas, e fs o factor de suavização ( 0 < fs ≤ 1)”.   
Citação do manual projeto FAC – Mestre Nuno.


Objetivo 

O trabalho tem de dar resposta a dois objetivos, que devem constar no relatório: 
1)	Fazer o levantamento das características técnicas mais importantes como, por exemplo, os limites de corrente de input/output dos pinos do Arduino e alimentação apropriada.
2)	Desenvolvimento do programa onde são aplicados os conhecimentos já adquiridos relativamente à linguagem de programação do Arduino (C/C++), de acordo com os requisitos listados no guia prático. 


Aparato Experimental 
•	Arduino UNO R3; 
•	Sensor temperatura; 
•	Led’s;
•	Breadboard1;
•	Resistores;
•	Wires;

Sensor de temperatura

Mesmo se tratando de uma variação automática onde os valores e formulas foram inseridas a simular um valor e medições aleatórios, dentro da elaboração do circuito optamos por colocar o sensor para realização dos testes em modo de valores e medição reais se fosse o caso.
Usamos o sensor LM35 que é um sensor de precisão que apresenta uma saída de tensão linear proporcional à temperatura em que ele se encontrar no momento, tendo em sua saída um sinal de 10mV para cada grau Célsius de temperatura. Verificamos que o sensor não necessita de qualquer calibração externa para fornecer com exatidão os valores de temperatura com variações de ¼ºC ou até mesmo ¾ºC dentro da faixa de temperatura entre –55ºC e 150ºC, que está dentro da faixa de medição proposta inicialmente no projeto que é entre –40ºC e 120ºC.
  
Breadboard

Podemos traduzir por “tábua de pão”, esta “tábua” é usada como uma matriz de contatos que permite a elaboração e construção de circuitos para testes experimentais sem precisar de solda neste momento, permitindo fazer mudanças e organizações com rapidez e segurança partindo de uma alteração de posição de um determinado componente ou substituição, ainda podendo acrescentar ou retirar componentes para melhor funcionamento e obter resultados conforme o esperado.
A breadboard nos permite conectar uma série de dispositivos e componentes assim como: Circuitos integrados (CIs); Capacitores; Diodos; Led; Sensores; Resistores; Transistores.
Levando em consideração que seu funcionamento é por linha e colunas, observando as laterais onde são linhas positivas e negativas para transitar esses valores pela placa afim de facilitar e organizar os circuitos elaborados, assim como a montagem na placa dos circuitos devem seguir no meio a orientação das colunas e linhas para o funcionamento e conexão da corrente e do circuito.

Resistores

Baseando em informações de pesquisa sobre Resistores podemos encontrar inúmeros tipos e modelos, assim como também há uma grande diversidade para suas atualizações, eles são componentes eletrônicos que tem como principal característica sua resistência elétrica, cuja ação é por limite ao fluxo de elétrons. 
 
R = Resistência elétrica (medida em Ohm);
I = Corrente (medida em Amperes);
V = Diferença de potencial (medida em Volts);
A equação é de suma importância pois através dela muitas outras equações podem ser obtidas.
Citação robocore tecnologias
 
Seno

Ao elaborar o dispositivo conectamos a uma tensão de 5.0 V, o pino GND como negativo do Arduino para o circuito. O alinhamento dos pinos do dispositivo permite que usássemos os pinos GND, 2, como input do sensor, 4, 5, 6 e 7, para os led’s do Arduino para o conectarmos diretamente esses periféricos no circuito. 

 “Variação sinusoidal entre valores arbitrários Tmin e Tmax, definidos como constantes, com ruído obtido a partir do gerador de números pseudo aleatórios, random(), de acordo com a seguinte expressão:
T=f (sin(wt))+ A∗random(Rmin ,Rmax)
em que f() e a função que permite variar o sinal entre os limites Tmin e Tmax (uma transformação linear), w=(2π)/P, e a frequência angular ( P o período), A a amplitude do ruído e Rmin , Rmax são os limites do gerador de números pseudo aleatórios (entre Rmin e Rmax-1, no caso da implementação da função random()no Arduino) . Estes parâmetros são constantes definidas pelo utilizador. “
Citação trabalho Física Aplicada, Mestre Nuno.

O parâmetro Value pode assumir valor HIGH, LOW, o que significa que se os valores enquadrarem dentro da regra definida o pino passa para estado HIGH ou LOW, respectivamente onde foram selecionados 3 pinos, a saber digitalWrite (pino4); digitalWrite (pino5); digitalWrite (pino6), digitalWrite (pino7).    
Dentro do parágrafo citado acima, onde podemos ver a função e os valor dado pelo professor para execução do trabalho temos a variável ruído onde temos o mínimo e máximo. Assim como teste de verificação apenas e isoladamente do ruído inserimos os valores de -3 e 3. Para verificação e obtenção de resultado e sua funcionalidade como poderá observar abaixo:

Código parte um

Esse é o código utilizado juntamente com a função para elaboração da primeira parte do projeto. A saber RUIDO e SENO.

#ifdef parteum 
/* variáveis para cálculo e elaboração da função de leitura da temperatura, assim como calculo
* e regras a serem seguidas na estrutura de ação do código;
*/   
    float ruido = 0.8 * random(-3,3); // cálculo para o ruido;
    t += 0.09; // acrescenta sempre o valor somado de + 0.09;
    y = calculation (temp);  //retorno do cálculo da função f = ((tmax - tmin) / 2.0) * y + (tmax - (tmax - tmin) / 2.0);
    temp = func(y) + ruido; // calculo completo da função seno com ruido;
#ifdef mplotter
       Serial.print(F("  Tmax = "  ));
       Serial.print(120);// marcação da linha de maior temperatura;
       Serial.print(F("  Tmin = "  ));
       Serial.print(-40); // marcação da linha de menor temperatura;
       Serial.print(F("  t = ")); 
       Serial.println(temp);    //imprima na tela o resultado da função completa;
       Serial.print(F("  T0 = "  ));
       Serial.print(10); // marcação da linha de valor aleatório da temperatura;
       Serial.print(F("  T1 = "  ));
       Serial.print(80); // marcação da linha de valor aleatório da temperatura;
#endif mplotter
#ifdef mserial
        Serial.print(F("\tTmin ="));
        Serial.print(-40); // marcação da linha de menor temperatura;
        Serial.print(F("\tT0 ="));
        Serial.print(10); // marcação da linha de valor aleatório da temperatura;
        Serial.print(F("\tT1 ="));
        Serial.print(80); // marcação da linha de valor aleatório da temperatura;
        Serial.print(F("\tTmax ="));
        Serial.print(120);// marcação da linha de maior temperatura;
        Serial.print(F("\tt =")); 
        Serial.println(temp);   //imprima na tela o resultado da função completa;
        Serial.print(F("\tT =")); 
        Serial.print(t,2);  //imprimi o resultado t com acréscimo 0.09;
//Condição para resultados de temperaturas, com seleção dos pinos escolhidos e cores para representar a temperatura;
if (temp < -40){   digitalWrite(pino7, HIGH); // para os valores de if luz de led acessa, estará HIGH;
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
if (temp > 120){      digitalWrite(pino7, HIGH); // para os valores de if luz de led acessa, estará HIGH;
        Serial.print(F("\t Led Marrom"));
}
#endif mserial
#ifdef gnuplot
        Serial.println("#Trabalho Física Aplicada a Computação - Mestre Nuno\n");
        Serial.println("#Gerador de Seno - 1º Ano - FAC 2018-19\n");
        Serial.println("#tTmin\tTmax\tt\tT0\tT1\tT");
        Serial.print(F("\tTmin ="));
        Serial.print(-40); // marcação da linha de menor temperatura;
        Serial.print(F("\tT0 ="));
        Serial.print(10); // marcação da linha de valor aleatório da temperatura;
        Serial.print(F("\tT1 ="));
        Serial.print(80); // marcação da linha de valor aleatório da temperatura;
        Serial.print(F("\tTmax ="));
        Serial.print(120);// marcação da linha de maior temperatura;
        Serial.print(F("\tt =")); 
        Serial.println(temp);   //imprima na tela o resultado da função completa;
        Serial.print(F("\tT =")); 
        Serial.print(t,2);  //imprimi o resultado t com acréscimo 0.09;
#endif gnuplot
} //fim da void loop;
      float func (float y){ 
        f = (tmax - tmin) / 2.0 * y + tmax - (tmax - tmin) / 2.0;
return f;       // dividimos a equação de cálculo e a variável func está recebendo y e a parte do cálculo em variável f;
}
      float calculation(float temp){ 
        y = sin(w*t);
return y;       // recebe o y e executa o cálculo do seno;
}   
#endif parteum          //-------------------------------

Nesta segunda parte do projeto, segue o resultado de um somatório de 7 (sete) senos. Utilizamos recursos conforme enunciado e adequamos o mesmo para função do programa para o sinal ser gerado.
Será gerado não por uma função seno mas por uma soma de N funções; a saber 7 (sete) de acordo com a seguinte expressão:
T=f (Σk = 1N sin (kwt)) + A ∗  random (Rmin , Rmax)
O parâmetro N, 7 (sete), que define o número de termos do somatório, e definido pelo utilizador. 
A figura 9.1 mostra um exemplo do sinal gerado a partir de uma série de 7 senos.
Citação trabalho Física Aplicada, Mestre Nuno, com pequenas adequações.

Segue o código descrito para execução da segunda parte do projeto, conforme solicitação de valores 7 seno.

#ifdef partedois
      float ruido = 0.3 * random(-10,10); // cálculo para o ruido;
      t = (float) millis()/1000.; // acrescenta o cálculo/contagem em millis;
      y = calculation (temp);     //retorno do cálculo da função f = ((tmax - tmin) / 2.0) * y + (tmax - (tmax - tmin) / 2.0);
      temp = func(y) + ruido;     // calculo completo da função seno com ruido;
#ifdef mplotter
       Serial.print(F("  Tmax = "  ));
       Serial.print(120);	// marcação da linha de maior temperatura;
       Serial.print(F("  Tmin = "  ));
       Serial.print(-40); // marcação da linha de menor temperatura;
       Serial.print(F("  t = ")); 
       Serial.println(temp);    //imprima na tela o resultado da função completa;
       Serial.print(F("  T0 = "  ));
       Serial.print(10); // marcação da linha de valor aleatório da temperatura;
       Serial.print(F("  T1 = "  ));
       Serial.print(80); // marcação da linha de valor aleatório da temperatura;
#endif mplotter
#ifdef mserial
         Serial.print(F("\tt= ")); //imprima na tela o resultado da função completa;
         Serial.println(temp);
         Serial.print(F("\tTmin= "));
         Serial.print(-40); // marcação da linha de menor temperatura;
         Serial.print(F("\tT0= "));
         Serial.print(10); // marcação da linha de valor aleatório da temperatura;
         Serial.print(F("\tT1= "));
         Serial.print(80); // marcação da linha de valor aleatório da temperatura;
         Serial.print(F("\tTmax= "));
         Serial.print(120);// marcação da linha de maior temperatura;
         Serial.print(F("\tT= "));  
         Serial.print(t,2);   //imprimi o resultado t com millis;
#endif mserial
#ifdef gnuplot
        Serial.println("#Trabalho Física Aplicada a Computação - Mestre Nuno\n");
        Serial.println("#Gerador de Seno - 1º Ano - FAC 2018-19\n");
        Serial.println("#tTmin\tTmax\tt\tT0\tT1\tT");
        Serial.print(F("\tTmin ="));
        Serial.print(-40); // marcação da linha de menor temperatura;
        Serial.print(F("\tT0 ="));
        Serial.print(10); // marcação da linha de valor aleatório da temperatura;
        Serial.print(F("\tT1 ="));
        Serial.print(80); // marcação da linha de valor aleatório da temperatura;
        Serial.print(F("\tTmax ="));
        Serial.print(120);// marcação da linha de maior temperatura;
        Serial.print(F("\tt =")); 
        Serial.println(temp);   //imprima na tela o resultado da função completa;
        Serial.print(F("\tT =")); 
        Serial.print(t,2);  //imprimi o resultado t com acréscimo em millis;
#endif gnuplot         
} //fim da void loop;
      float func (float y){
        f = ((tmax - tmin) / 2.0) * y + (tmax - (tmax - tmin) / 2.0);
return f;       // dividimos a equação de cálculo e a variável func está recebendo y e a parte do cálculo em variável f;
}
      float calculation(float temp){  
        y = 0.;
for( int k = 1; k < 8; k++){        //regra para seno de 7 valores;
        y += (sin(k*w*t));
}
return y;       // recebe o y e executa o cálculo do seno;
}
#endif partedois

//-------------------------------

Media final MCM

O objetivo das médias a seguir é ir somando todos os valores apresentados ou gerados em temperatura, após resultados das funções, valores inseridos ou determinados para o ruído por exemplo e depois dividir pelo número de contador de medições realizada. 
Sendo assim podemos obter os seguintes resultados com a formula, código.

Acima usamos a função para o cálculo da média corrente e da média das últimas M medições. 
• Media (MCM): Tmed = (T1 + T2 + … + Tk) / k, k e o número de medições realizadas;
A seguir utilizaremos a função para o cálculo da média acumulativa e da média das últimas M medições. 
• Media (MMM): TM = (Tk + Tk+1 + … + Tk+M-1) / M, M e número medições que entram no cálculo.
Citação trabalho Física Aplicada, Mestre Nuno.

Media final MMM

 Nesta parte do projeto teremos que calculara mmm que é a média somando 3 em 3 temperaturas e dando o resultado subsequente em seguida e assim correndo de forma continua enquanto a temperatura está sendo media.
Com isso obtemos os seguintes resultados abaixo demonstrados, através do código em seguida e da formula citada acima em quadro anterior.

Segue o código descrito para execução da terceira parte do projeto, conforme solicitação de valores de media MCM, MMM, SUAVIZAÇÃO.

#ifdef partetres
      float ruido = 1 * random(-10,10);     // cálculo para o ruido;
      t = (float) millis()/1000.0;        // acrescenta o cálculo/contagem em millis;
      y = calculation (temp);  //retorno do cálculo da função f = ((tmax - tmin) / 2.0) * y + (tmax - (tmax - tmin) / 2.0);
    temp = func(y) + ruido; // calculo completo da função seno com ruido;
#ifdef mediac               //média acumulada, soma todos os valores apresentados em temp e depois divide pelo número do contador;
     temperaturas += temp;
     media = temperaturas/contador;
     contador++;
#endif mediac
#ifdef mmmedia                    //media corrente, soma 3 valores apresentados em temp e depois divide por 3;
     tempContLeitura[contador] = temp;
        contador++;
if(contador == contLeitura) {
     mmm = 0.;
for(int k = 0; k < contLeitura; k++){       //condição e contador para a apresentação da média em 3 em 3;
     mmm = mmm + tempContLeitura[k];
}
     mmm = mmm / contLeitura;
        contador = 0;
}  
#endif mmmedia
#ifdef suav  
if (temp > 100){
      mms = temp * 0.5; //suavização parte superior;
}
if (temp <-20){
      mms = temp * 0.25; //suavização parte inferior;
} 
#endif suav
#ifdef mplotter
       Serial.print(F("  T0 = "  ));
       Serial.print(10); // marcação da linha de valor aleatório da temperatura;
       Serial.print(F("  T1 = "  ));
       Serial.print(80); // marcação da linha de valor aleatório da temperatura;
       Serial.print(F("  Tmax = "  ));
       Serial.print(120);// marcação da linha de maior temperatura;
       Serial.print(F("  Tmin = "  ));
       Serial.print(-40); // marcação da linha de menor temperatura;
       Serial.print(F("  t = ")); 
       Serial.println(temp); //imprima na tela o resultado da função completa;
       Serial.print(F(" Media = "));
       Serial.print(media);   // imprimi media mcm acumulativa;
       Serial.print(F("\tMMM= "));
       Serial.print(mmm);   // imprime media mmm;
#endif mplotter
#ifdef mserial
        Serial.print(F("\tT0= "));
        Serial.print(y); // marcação da linha de valor aleatório da temperatura;
        Serial.print(F("\tT1= "));
        Serial.print(80); // marcação da linha de valor aleatório da temperatura;
        Serial.print(F("\tt= "));     
        Serial.println(temp);   //imprima na tela a função completa;
        Serial.print(F("\tTmin= "));
        Serial.print(-40); // marcação da linha de menor temperatura;
        Serial.print(F("\tTmax= "));
        Serial.print(120);// marcação da linha de maior temperatura;
        Serial.print(F("\tT= "));   
        Serial.print(t,2);    //imprimi o resultado T com millis;
        //Serial.print(F("\tContador= "));  
        //Serial.print(contador);                 // imprimi a contagem;
        //Serial.print(F("\tMedia= "));
        //Serial.print(media);                 // imprimi media mcm acumulativa;
        Serial.print(F("\tMMM= "));
        Serial.print(mmm);   // imprimi media mmm;
        //Serial.print(F("\tMMS= "));
        //Serial.print(mms);     // imprimi suavização;
#ifdef gnuplot
        Serial.println("#Trabalho Física Aplicada a Computação - Mestre Nuno\n");
        Serial.println("#Gerador de Seno - 1º Ano - FAC 2018-19\n");
        Serial.println("#tTmin\tTmax\tt\tT0\tT1\tT");
        Serial.print(F("\tTmin ="));
        Serial.print(-40); // marcação da linha de menor temperatura;
        Serial.print(F("\tT0 ="));
        Serial.print(10); // marcação da linha de valor aleatório da temperatura;
        Serial.print(F("\tT1 ="));
        Serial.print(80); // marcação da linha de valor aleatório da temperatura;
        Serial.print(F("\tTmax ="));
        Serial.print(120);// marcação da linha de maior temperatura;
        Serial.print(F("\tt =")); 
        Serial.println(temp);   //imprima na tela o resultado da função completa;
        Serial.print(F("\tT =")); 
        Serial.print(t,2);  //imprimi o resultado t com acréscimo em millis;
        Serial.print(F("\tMedia= "));
        Serial.print(media);                 // imprimi media mcm acumulativa;
        Serial.print(F("\tMMM= "));
        Serial.print(mmm);   // imprimi media mmm;
#endif gnuplot
//Condição para resultados de temperaturas, com seleção dos pinos escolhidos e cores para representar a temperatura;
if (temp < -40){      digitalWrite(pino7, HIGH); // para os valores de if luz de led acessa, estará HIGH;
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
if (temp > 120){      digitalWrite(pino7, HIGH); // para os valores de if luz de led acessa, estará HIGH;
        Serial.print(F("\t  Led Marrom"));
}
#endif mserial
} //fim da void loop;
      float func (float y){         f = ((tmax - tmin) / 2.0) * y + (tmax - (tmax - tmin) / 2.0);
return f;                           // dividimos a equação de cálculo e a variável func está recebendo y e a parte do cálculo em variável f;
}      float calculation(float temp){         y = sin(w*t);
return y;                           // recebe o y e executa o cálculo do seno;
}
#endif partetres

TESTES DE EXECUÇÃO 

Durante o processo de elaboração e desenvolvimento tivemos vários testes de execução em todas as áreas do projeto e código onde aos poucos fomos corrigindo os erros encontrados e melhorando tanto o aspecto estrutural como a adaptação do funcionamento das funções, cálculos e variáveis para as devidas impressões e resultados em serial monitor, plotter e gnuplot. Sendo assim efetuamos os print’s para visualização e guardar o histórico do processo de desenvolvimento.
Demonstramos a seguir por algumas telas/print o desenvolvimento e testes/erros no decorrer do processo de elaboração do código.

Conclusão

Visando os resultados obtidos concluímos tanto a plataforma Arduino em geral e também a parte dos sensores, led e circuito em si, do programa podem ser usadas em áreas de pesquisas, estudos, aplicação de conhecimentos adquiridos com relevância e relacionadas em pesquisas futuras para um melhor resultado, apesar dos resultados satisfatórios obtidos, sempre podemos continuar melhorando e adequando os códigos de uma maneira mais integra e enxuta assim como ampliar as ações e execução do projeto.
Todos os conceitos estudados nesse projeto podem ser utilizados em outras aplicações e projetos similares, esse estudo utiliza o Arduino, considerado equipamento de baixo custo, torna-se viável e facilmente replicável em projetos futuros.
De uma forma simples e com todos os resultados obtidos, buscamos demonstrar em geral todos os passos executados para a elaboração do projeto, assim como o código e suas impressões em serial monitor, plotter, permitindo assim sua reprodução até com certas modificações de valores, especificações e melhorias tanto na parte de programação e elaboração do circuito.
Concluímos o presente trabalho com o sentimento de ter alcançado resultados satisfatórios, proposto pelo objetivo e manual de elaboração entregue pelo mestre Nuno Pereira e que não existe limite para a aplicação neste modelo de funcionamento e melhoria de qualquer parte do projeto, incluindo com novos modelos de placa e sensores como o de sequência WIFI que esteja relacionado ao desenvolvimento similar do projeto e que o limite das execuções está somente relacionado ao pensamento e conhecimento presente dos seres humanos, conforme várias vezes dito pelo mestre Nuno Pereira. Conforme formos estudando os novos projetos e novos equipamentos e podemos usar essa plataforma Arduino que é muito importante para o controle de vários outros sensores e equipamentos além de criar o conhecimento facilitado com o acoplamento mecânico, robótico e elétrico neste equipamento chamado ARDUINO.


Referências

https://cms.ipbeja.pt/pluginfile.php/192653/mod_resource/content/6/Trab.Lab01_Arduino%2BSeno_Ed.03_2018-19.pdf
hardware: Arduino Uno R3
programa: Arduino IDE
programa: Fritizing
https://pt.wikipedia.org/wiki/Arduino
http://forum.arduino.cc/index.php
http://labdegaragem.com/forum/topics
http://playground.arduino.cc//Referencia/Extendida
https://www.arduino.cc/en/Reference/FunctionDeclaration
https://www.arduino.cc/en/Reference/If
https://www.arduino.cc/en/Reference/For
https://www.robocore.net
https://www.arduino.cc/en/Reference/SwitchCase
https://www.arduino.cc/en/Reference/While
https://www.arduino.cc/en/Reference/DoWhile
https://www.arduino.cc/en/Reference/Break
https://www.arduino.cc/en/Reference/Continue
https://www.arduino.cc/en/Reference/Return

