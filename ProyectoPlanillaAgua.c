#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cordova.h"
#define N 100

typedef struct{
	int anio;
    int mes;
    int dia;
}fechaNac;

typedef struct{
	int diaemision;
	int mesemision;
	int yearemision;
	int diavencimiento;
	int mesvencimiento;
	int yearvencimiento;
}fecha;

typedef struct{ //Erick Cordova
	char numeromedidor[7]; //campo unico del agua que no se repite
	char cedula[11]; //campo que se repite	
	char nombre[50];
	int edad;
	float m3;//consumo
	float costoXm3;//Costo de cada metro cubico 
	float valorTotal;
	int Cantidadpersonas;//personas que habitan
	int estado;
	fecha fechafact;
}agua; // la palinlla de agua con todos los datos recogidos 



int registrar(agua *planillas,fecha *fechas,int n);
void presentar(agua *planillas,fecha *fechas,int n);
void verCiudadano(agua x);
int buscar(char *medidorn,agua *planillas, int n);
int buscarb(char *nombren,float *pago,agua *planillas, int n);

int main(){	
	agua *planillas=NULL;
	fecha *fechas=NULL;
	char msj[]="\nElija la opcion \n1:Registrar \n2:Presentar \n3:Buscar por numero de medidor \n4:Buscar por cliente y valor a pagar \n5:Actualizar \n6:Eliminar \n7:Acerca de \n0:Salir \n\nINSERTE SU OPCION: ";//Actualizar,eliminar,acerca de,salir(0)
	char op=' ',ope=' ';
	int busquedame=0, digito=0,rt=1;
	int bandera=0;//0 no encontrada, 1 si encontrdda
	int n=0,i=0,h=0,p=0,posicion=0;
	char medidorn[7];
	char nombren[50];
	char edit [0];
	float pago;
	setlocale(LC_CTYPE, "Spanish");
do{
	printf("ingrese la cantidad de personas a registrar: ");
	scanf("%d",&n);fflush(stdin);
}while(n<=0);
	
	planillas=(agua *)malloc(n*sizeof(agua)); //arreglo dinamico
	h=0;
	do{
		printf("%s", msj);
		scanf("%c",&op);fflush(stdin);
		switch(op){
			case '1': if(p<n){ //registrar 
  			p= registrar(planillas,fechas, p);				
					}else{
						printf("\nYa no hay cupos disponibles :(\n");
				}
			break;
	
			case '2': //presentar todo
			presentar(planillas, fechas, p);						
			break;
	
			case '3': //buscar por medidor
			printf("\nIngrese el numero de medidor para buscar: ");
			scanf("%s",&medidorn);fflush(stdin);
			posicion=buscar(medidorn,planillas,p);	
			if(posicion!=-1){
				verCiudadano(planillas[posicion]);
				}	else
				printf("\nEl numero de medidor no fue encontrado\n")	;
			break;
	
			case '4': //buscar por nombre y valor a pagar
			printf("\nIngrese el nombre del cliente a buscar: ");
			scanf("%s",&nombren);fflush(stdin);
			printf("Ingrese el valor a pagar del cliente: ");
			scanf("%f",&pago);fflush(stdin);
			posicion=buscarb(nombren,&pago,planillas,p);
			if(posicion!=-1){
				verCiudadano(planillas[posicion]);	
				}			
			break;			
	
			case '5': //editar o actualizar
			printf("\nIngrese el numero de medidor para actualizar los datos:  ");
			scanf("%s",&medidorn);fflush(stdin);
			posicion=buscar(medidorn,planillas,p);
			do{
			printf("\nSeleccione el campo que desea actualizar:\n 1:Nombre\n 2.Cedula\n 3:Edad\n 4:Metros cubicos usados\n 0:Regresar\nIngrese su opcion: ");
			scanf("%c",&ope);fflush(stdin);							
				switch(ope){
					case '1': 
					printf("Si quiere actualizar el nombre, presione la tecla 'S' si no presionar cualquiere tecla: ");
					scanf("%s",&edit);fflush(stdin);
					if((strcmp(edit,"S")==0)||(strcmp(edit,"s")==0)){
						printf("\nActualizar nombre: ");
						scanf("%s",planillas[posicion].nombre);fflush(stdin);							
					}else printf("\nSOLICITUD CANCELADA\n");	
					break;
					case '2':
					printf("Si quiere actualizar la cedula, presione la tecla 'S' si no, presionar cualquiere tecla: ");
					scanf("%s",&edit);fflush(stdin);
					if((strcmp(edit,"S")==0)||(strcmp(edit,"s")==0)){
						printf("\nActualizar cedula: ");
						scanf("%s",planillas[posicion].cedula);fflush(stdin);								
					}else printf("\nSOLICITUD CANCELADA\n");								
					break;
					case '3':
					printf("Si quiere actualizar la edad, presione la tecla 'S' si no, presionar cualquiere tecla: ");
					scanf("%s",&edit);fflush(stdin);
					if((strcmp(edit,"S")==0)||(strcmp(edit,"s")==0)){
						printf("\nActualizar edad: ");
						scanf("%d",&planillas[posicion].edad);fflush(stdin);										
					}else printf("\nSOLICITUD CANCELADA\n");																	
					break;
					case '4':
					printf("Si quiere actualizar los metros cubicos usados, presione la tecla 'S' si no, presionar cualquiere tecla: ");
					scanf("%s",&edit);fflush(stdin);
					if((strcmp(edit,"S")==0)||(strcmp(edit,"s")==0)){
						printf("\nActaulizar los metros cubicos usados: ");
						scanf("%f",&planillas[posicion].m3);fflush(stdin);
						planillas[posicion].valorTotal=0.72*planillas[posicion].m3;											
					}else printf("\nSOLICITUD CANCELADA\n");												
					break;	
					case '0':	//cerrar ciclo de actualizacion					
					rt=0;					
					break;																		
				}
			}while(rt>0);	
			break;			
			case '6':  //eliminar 
				printf("Ingrese el numero de medidor a dar de baja: ");
				scanf("%s",&medidorn);fflush(stdin);
				posicion=buscar(medidorn,planillas,p);
				if(posicion!=-1){
					verCiudadano(planillas[posicion]);
					do{
						printf("\n¿Desea eliminar a este cliente? 1-Si 2-No: ");
						scanf("%i",&digito);fflush(stdin);
					}while(digito!=1&&digito!=2);
					if(digito==1){
						planillas[posicion].estado=0;//Cambio de estado
						printf("\nCliente con nombre %s eliminado.\n",planillas[posicion].nombre);
					}
				}else{
					printf("\nCliente con numero de medidor %s no encontrado.\n",medidorn);
					}
			break;
			
			case '7': //info
			info();
			break;					
	
			case '0': //cerrar programa
			n=-1;
			break;												
		}
	}while(n>0);
	printf("\nGracias por preferirnos :)\n");
	free(planillas);
	return 0;
}
int registrar(agua *planillas, fecha *fechas,int n){
	
	float total=0;
	float m3=0;
	int diaemi=0, mesemi=0, yearemi=0;
	int diaven=0, mesven=0, yearven=0;
	printf("\nIngrese el numero de medidor: ");
	scanf("%s",&planillas[n].numeromedidor);fflush(stdin);
	printf("Ingrese su numero de cedula: ");
	scanf("%s",planillas[n].cedula);fflush(stdin);
	printf("Ingrese su nombre: ");
	scanf("%s",planillas[n].nombre);fflush(stdin);	
	printf("Ingrese su edad: ");
	scanf("%d",&planillas[n].edad);fflush(stdin);		
	printf("Ingrese el consumo en metros cubicos: "); //proceso para sacar el valor a pagar
	scanf("%f",&planillas[n].m3);fflush(stdin);
	planillas[n].costoXm3=0.72;//el costo por metro cubico es de 0.72 ctv 
	planillas[n].valorTotal=planillas[n].costoXm3*planillas[n].m3;
	printf("Costo de cada metro cubico: $%.2f ",planillas[n].costoXm3);
	printf("\nValor total a pagar: $%.2f \n",planillas[n].valorTotal);
	printf("Cantidad de personas habitando la vivienda: ");
	scanf("%d",&planillas[n].Cantidadpersonas);
	printf("Ingrese la fecha de emision\n");
	do{
		printf("-Dia: ");	
		scanf("%i",&diaemi);fflush(stdin);	
	}while(diaemi<1||diaemi>30);
	planillas[n].fechafact.diaemision=diaemi;
	do{	
		printf("-Mes: ");	
		scanf("%i",&mesemi);fflush(stdin);	
	}while(mesemi<1||mesemi>12);
	planillas[n].fechafact.mesemision=mesemi;
	do{	
		printf("-Anio: ");	
		scanf("%i",&yearemi);fflush(stdin);	
	}while(yearemi<1900||yearemi>2022);
	planillas[n].fechafact.yearemision=yearemi;
	mesven=mesemi+2;
	planillas[n].fechafact.mesvencimiento=mesven;	
	planillas[n].fechafact.yearvencimiento=	planillas[n].fechafact.yearemision;
	
	if(mesven==13){
		planillas[n].fechafact.mesvencimiento=1;
		planillas[n].fechafact.yearvencimiento=yearemi+1;
	}
	else if (mesven==14){
		planillas[n].fechafact.mesvencimiento=2;
		planillas[n].fechafact.yearvencimiento=yearemi+1;
	}
	planillas[n].estado=1;//activo
	n++;
	return n;
}
void presentar(agua *planillas,fecha *fechas,int n){
	int i=0;
	for(i=0;i<n;i++){
		if(planillas[i].estado==1){
			verCiudadano(planillas[i]);
		}		
	}
}
void verCiudadano(agua x){

	printf("\nNumero de medidor: %s",x.numeromedidor);
	printf("\nNumero de cedula: %s",x.cedula);
	printf("\nNombre: %s",x.nombre);	
	printf("\nEdad: %d",x.edad);
	printf("\nConsumo en metros cubicos: %.2f",x.m3);
	printf("\nValor total a pagar: $%.2f ",x.valorTotal);
	printf("\nFecha de emision: %i / %i / %i  \n",x.fechafact.diaemision,x.fechafact.mesemision,x.fechafact.yearemision);	
	printf("Fecha de vencimiento: %i / %i / %i \n",x.fechafact.diaemision,	x.fechafact.mesvencimiento,x.fechafact.yearvencimiento);
	printf("Cantidad de personas habitando el hogar: %i\n",x.Cantidadpersonas);
	if(x.estado==0){
		printf("\nCiudadano dado de baja\n");	
	}			
}
int buscar(char *medidorn,agua *planillas, int n){
	int i=0, bandera=0, posicion=-1;
	for(i=0;i<n&&bandera==0;i++){
		if(strcmp(medidorn, planillas[i].numeromedidor)==0){
			posicion=i;
			bandera=1;
		}
	}
	return posicion;
}
int buscarb(char *nombren,float *pago,agua *planillas, int n){
	int i=0, bandera=0, posicion=-1;
	for(i=0;i<n&&bandera==0;i++){
		if((strcmp(nombren, planillas[i].nombre)==0)&&(*pago=planillas[i].valorTotal)){
			posicion=i;
			bandera=1;				
		}else printf("Campo no encontrado en los datos\n");
	}
	return posicion;
}