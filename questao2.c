#include <at89x52.h>

int counter = 0;		//CONTADOR DE REPETI��ES
int id_cam = 0;			//ID DA CAMERA QUE EST� GRAVANDO
int ultimo_id = 0;	

//P2_0 AT� P2_3 = CAMERAS
//P2_4 AT� P2_7 = SENSOR DAS CAMERAS

void atendeTimer() interrupt 1{
	TR0 = 0;
	TH0 = 0x3C;
	TL0 = 0xAF;
	TR0 = 1;
	
	counter++;
	if(counter==60){				// A CADA 3 SEGUNDOS ATUALIZA A CAMERA QUE EST� GRAVANDO
		
		if(P2_4==0 && P2_5==0 && P2_6==0 && P2_7==0){ // SE TODAS AS CAMERAS EST�O DESATIVADAS
			ultimo_id = id_cam;	//SALVA A ULTIMA POSI��O
			id_cam = 4;					//ESTADO DE PAUSE
		}
		else{
			if(id_cam==4){			//SE AO MENOS UMA EST� ATIVADA, VOLTA A GRAVAR
				id_cam = ultimo_id;
				P2_1=1;
			}
			//DEPOIS DE 3 SEGUNDOS QUAL � A POSI��O DO ID DA CAMERA
			//SE � DA CAMERA ANTERIOR DA SEQUENCIA, ATUALIZA PARA A SEGUINTE
			if(id_cam==3){			//VERIFICA O ID DA CAMERA
				if(P2_4==1){			//VERIFICA SE O SENSOR DE PRESEN�A EST� ATIVO
					id_cam=0;				//ATUALIZA A CAMERA NA GRAVA��O
				}
				else{
					id_cam=1;				//SE N�O ESTIVER ATIVO, ATUALIZA PARA O PROXIMO
				}
			}
			else if(id_cam==0){
				if(P2_5==1){
					id_cam=1;
				}
				else{
					id_cam=2;
				}
			}
			else if(id_cam==1){
				if(P2_6==1){
					id_cam=2;
				}
				else{
					id_cam=3;
				}
			}
			else if(id_cam==2){
				if(P2_7==1){
					id_cam=3;
				}
				else{
					id_cam=0;
				}
			}
		}
		
		counter = 0;
	}
}

void main(){
	EA = 1;
	ET0 = 1;
	TMOD = 1;
	TH0 = 0x3C;
	TL0 = 0xAF;
	TR0 = 1;
	
	while(1){
		switch(id_cam){
			case 0:
				P2_0 = 1;
				P2_1 = 0;
				P2_2 = 0;
				P2_3 = 0;
				break;
			
			case 1:
				P2_0 = 0;
				P2_1 = 1;
				P2_2 = 0;
				P2_3 = 0;
				break;
			
			case 2:
				P2_0 = 0;
				P2_1 = 0;
				P2_2 = 1;
				P2_3 = 0;
				break;
			
			case 3:
				P2_0 = 0;
				P2_1 = 0;
				P2_2 = 0;
				P2_3 = 1;
				break;
			
			case 4:
				P2_0 = 0;
				P2_1 = 0;
				P2_2 = 0;
				P2_3 = 0;
				break;
		}
	}
}