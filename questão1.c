#include <at89x52.h>

int counter = 0; //CONTADOR DOS PRODUTOS
//P3_2 = SENSOR DOS PRODUTOS
//P2_0 = ESTEIRA DOS PRODUTOS
//P2_1 = ESTEIRA DAS CAIXAS

void atendeInterrupcao() interrupt 0{
	counter++;
	if(counter==5){		//SE PASSOU 5 PRODUTOS
			P2_0 = 0;			//DESLIGA A ESTEIRA DOS PRODUTOS
			P2_1 = 1;			//LIGA A ESTEIRA DAS CAIXAS
			//delay(3000)	//ESPERA 3 SEGUNDOS PARA MOVER AS CAIXAS
			counter=0;		//ZERA O CONTADOR
			P2_1 = 0;			//DESLIGA A ESTEIRA DAS CAIXAS
			P2_0 = 1;			//LIGA A ESTEIRA DOS PRODUTOS
			
		}
}

void main(){
	EA = 1;
	EX0 = 1;
	P2 = 0;
	P2_0 = 1;				//LIGA A ESTEIRA DOS PRODUTOS
	P3_2 = 0;				//ACIONA O PINO 3_2 PARA DETECTAR OS PRODUTOS
	while(1){}
}