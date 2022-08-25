//===================================================================================================//
// Projeto: Garra Automatizada IFPB - Cajazeiras; 08/2018                                                    //
// Estrutura: Braço e Garra em MDF;                                                                  //
// Hardware: 4 Micro servos 9g, Placa Arduino Uno, Protoboard;                                       //
// Objetivo: Pegar 3 objetos diferentes em 120º, 150º e 180º e colocalos no local especificado a 0º; //
// Versão: 0.1.8;                                                                                    //
//===================================================================================================//

#include <Servo.h> // INCLUSÃO DA BIBLIOTECA DE CONTROLE DOS SERVOS;

  // DEFINE CONSTANTES 
#define MAX_BASE 180
#define MIN_BASE 0
#define MAX_B_ESQUERDO 50
#define MIN_B_ESQUERDO 20
#define B_ESQUERDO_EX_MAX 60 
#define MAX_B_DIREITO 110
#define MIN_B_DIREITO 50
#define B_DIREITO_EX_MAX 80   // ESSA PARTE SERVE PARA FACILITAR ALTERAÇÕES FUTURAS, UMA VEZ QUE SÓ PRECISA 
#define Garra_abre 80               // ALTERAR OS DADOS NO DEFINE E TODAS AS CONSTANTES NO CODIGO SÃO ALTERADAS
#define Garra_fecha 40
#define Pos_First 115
#define Pos_Second 140
#define Pos_Third 165
#define tempoDelay 5
#define tempoDelayEx 20
#define tempPause 1000

  // Define os servos na biblioteca (SEPARADOS POR VIRGULA E EM UNICA LINHA PARA ECONOMIA DE ESPAÇO NO CODIGO) 
Servo servo_base, servo_bracoD, servo_bracoE, servo_garra;
  
  //Define variavies e atribui valores iniciais 
int posBase=90;
int posGarra = 50;
int posBDireito = 50; 
int posBEsquerdo = 30; 
int count = 0;

  //Prototipos das funções
void moveBase_Min(void);
void moveBase_First(void);
void moveBase_Second(void);
void moveBase_Third(void);
void moveBase_Max(void);
void moveGarra_Abre(void);
void moveGarra_Fecha(void);
void moveBracoD_Ampliar(void);
void moveBracoD_Retrair(void);
void moveBracoE_Ampliar(void);
void moveBracoE_Retrair(void);
void moveBracoE_Retrair_Third(void);
void moveBracoD_EX(void);
void moveBracoE_EX(void);

void setup()
{ // Define portas OUTPUT do arduino que controlam os servos
    servo_base.attach(9);
    servo_bracoD.attach(8);
    servo_bracoE.attach(5);
    servo_garra.attach(6);  
    Serial.begin(9600);
}

void loop()
{//==================== MOVIMENTO TESTE, CALIBRADO SE ESTIVER OK // POSIÇÃO DE REPOUSO INICIAL ============================
  if(count != 1)
   {                    //--- CALIBRAÇÃO SAI DO LOOP, ACONTECE APENAS NESSE MOMENTO 
    count = 1;
    
          moveBracoD_Retrair();
          moveBracoE_Retrair();
          moveGarra_Fecha();
          moveGarra_Abre();
    
      Serial.println("\t======================");
      Serial.println("\tAguardando Comando...");
      Serial.println("\tTecla 's', start");
      Serial.println("\tTecla 'p', pausar");
      Serial.println("\t=======================");
      delay(tempPause);  // Tempo em que o braço fica em repouso após o movimento de teste e calibração
  }
 
//  Espera comando de inicio 
  if(Serial.available())
  {
    switch(Serial.read())
    {
      case 's':{
      Serial.println("\tRotina Iniciada");
      Serial.println("\t===============");
      //================Inicia Rotina Chamando cada função =====================
          moveBase_First();
          moveBracoE_Ampliar();
          moveBracoD_Ampliar();
          moveGarra_Fecha();
          moveBracoD_Retrair();
          moveBracoE_Retrair();
          moveBase_Min();
          moveBracoE_Ampliar();
          moveBracoD_Ampliar();
          moveGarra_Abre();
          moveBracoD_Retrair();
          moveBracoE_Retrair();
          moveBase_Second();
          moveBracoD_EX();
          moveBracoE_EX();
          moveGarra_Fecha();
          moveBracoD_Retrair();
          moveBracoE_Retrair();
          moveBase_Min();
          moveBracoE_Ampliar();
          moveBracoD_Ampliar();
          moveGarra_Abre();
          moveBracoD_Retrair();
          moveBracoE_Retrair();
          moveBase_Third();
          moveBracoE_Ampliar();
          moveBracoD_Ampliar();
          moveGarra_Fecha();
          moveBracoD_Retrair();
          moveBracoE_Retrair();
          moveBase_Min();
          moveBracoE_Ampliar();
          moveBracoD_Ampliar();
          moveGarra_Abre();
          moveBracoD_Retrair();
          moveBracoE_Retrair();
          moveBase_Max();
          moveBracoE_Ampliar();
          moveBracoD_Ampliar();
          moveGarra_Fecha();
          moveBracoD_Retrair();
          moveBracoE_Retrair();
          moveBase_Min();
          moveBracoE_Ampliar();
          moveBracoD_Ampliar();
          moveGarra_Abre();
    }
    case 'p':{
      Serial.println("\tRotina Encerrada");
      Serial.println("\t===============");
          moveBracoD_Retrair();
          moveBracoE_Retrair();
          moveGarra_Fecha();
          moveGarra_Abre();  
    }
    default:{  
      Serial.println("\t======================");
      Serial.println("\tAguardando Comando...");
      Serial.println("\t=======================");
      delay(tempPause); break; // Tempo em que o braço fica em repouso 
    }
    }
  }
  
}
  // ===== Escopo de Funções ====
void moveBase_First(void) // função não retorna nada 
{
  for (posBase; posBase <= Pos_First; posBase ++) // BASE SE MOVE DA POSIÇÃO ATUAL ATÉ A POSIÇÃO DO PRIMEIRO OBJETO
   { 
    servo_base.write(posBase);              
    delay(tempoDelay);
  }
}
void moveBase_Min(void) // Função não retorna nada
{
  for (posBase; posBase >= MIN_BASE; posBase --) // BASE SE MOVE DA POSIÇÃO ATUAL PARA A POSIÇÃO DE ENTREGA DO OBJETO 
   { 
    servo_base.write(posBase);              
    delay(tempoDelay);
  }
}
void moveBase_Second(void)// função não retorna nada
{
  for (posBase; posBase <= Pos_Second; posBase ++) // BASE SE MOVE DA POSIÇÃO ATUAL ATÉ A POSIÇÃO DO SEGUNDO OBJETO
   { 
    servo_base.write(posBase);              
    delay(tempoDelay);
  }  
}
void moveBase_Third(void)// função não retorna nada
{
  for (posBase; posBase <= Pos_Third; posBase ++) // BASE SE MOVE DA POSIÇÃO ATUAL ATÉ A POSIÇÃO DO terceiro OBJETO
   { 
    servo_base.write(posBase);              
    delay(tempoDelay);
  }  
}
void moveBase_Max(void)// Função não retorna nada
{ 
  for (posBase; posBase <= MAX_BASE; posBase ++) // BASE SE MOVE DA POSIÇÃO ATUAL ATÉ A POSIÇÃO DO ULTIMO OBJETO
   { 
    servo_base.write(posBase);              
    delay(tempoDelay);
  }
}
void moveGarra_Abre(void)// Função não retorna nada
{
  for (posGarra; posGarra <= Garra_abre; posGarra ++)          // GARRA ABRE LIBERANDO O OBJETO
    { 
    servo_garra.write(posGarra);              
    delay(tempoDelay);                      
  }                          
}
void moveGarra_Fecha(void)// Função não retorna nada 
{
  for (posGarra; posGarra >= Garra_fecha; posGarra --)// GARRA FECHA PEGANDO OBJETO
   { 
   servo_garra.write(posGarra);              
   delay(tempoDelayEx);                     
  }                          
}
void moveBracoD_Retrair(void)// Função não retorna nada 
{
  for (posBDireito; posBDireito >= MIN_B_DIREITO; posBDireito --)
   {                                                    // BRAÇO DIREITO PUXADO PARA TRAS
    servo_bracoD.write(posBDireito);              
    delay(tempoDelay);
  }                          
}
void moveBracoD_Ampliar(void)// Função não retorna nada
{
  for (posBDireito ; posBDireito <= MAX_B_DIREITO; posBDireito ++)// BRAÇO DIREITO PUXADO PARA FRENTE
    {
    servo_bracoD.write(posBDireito);              
    delay(tempoDelayEx); 
    }
}
void moveBracoD_EX(void)// Função não retorna nada
{
  for (posBDireito ; posBDireito <= B_DIREITO_EX_MAX; posBDireito ++)// BRAÇO DIREITO PUXADO PARA FRENTE
    {
    servo_bracoD.write(posBDireito);              
    delay(tempoDelayEx); 
    }
}
void moveBracoE_Retrair(void)// Função não retorna nada
{
  for (posBEsquerdo; posBEsquerdo >= MIN_B_ESQUERDO; posBEsquerdo --)
   {                                              // BRAÇO ESQUERDO DIMINUI O ANGULO PARA VALOR MINIMO, VAI PRA TRÁS
    servo_bracoE.write(posBEsquerdo);              
    delay(tempoDelay);                       
  }                          
}

void moveBracoE_Ampliar(void)// Função não retorna nada
{
  for (posBEsquerdo; posBEsquerdo <= MAX_B_ESQUERDO; posBEsquerdo ++)
    {                                                      // BRAÇO ESQUERDO VAI PARA FRENTE (ANGULO MAXIMO)
    servo_bracoE.write(posBEsquerdo);              
    delay(tempoDelayEx);                       
  }
}
void moveBracoE_EX(void)// Função não retorna nada
{
  for (posBEsquerdo; posBEsquerdo <= B_ESQUERDO_EX_MAX; posBEsquerdo ++)
    {                                                      // BRAÇO ESQUERDO VAI PARA FRENTE (ANGULO MAXIMO)
    servo_bracoE.write(posBEsquerdo);              
    delay(tempoDelayEx);                       
  }
}
