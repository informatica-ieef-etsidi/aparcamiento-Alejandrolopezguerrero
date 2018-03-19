//Alejandro López Guerrero - - Páctica_2
//Las plazas están distribuidas de forma que un 25% de las plazas son de moto. Aunque si hay menos de cuatro plazas, también habrá al menos una plaza.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <string.h>
#define num_plazas 4



void main(void) {

	//Variables generales
	unsigned char opcion_menu1[1], vector_matricula_buscar[1][8];
	unsigned char matrizplazas[num_plazas][8];
	int vector_boolean_plazas_libres[num_plazas], plazasmotolibre,plazascochelibre,
		vector_boolean_tipo_vehiculo[num_plazas];
	char tipo_vehiculo[2][6],char_aux1[6]="Coche",char_aux2[6]="Moto";
	
	//Contadores y booleanos
	int i = 0, j, opcion2,  booleana, booleana2, confirmacion, booleana3,
		booleana_tipo_auto=0;
	
	//Selectores menus
	int opcion3;
	char n,tipoauto; 

	//Formato de la interfaz de la consola
	system("color 0B ");

    //Inicilaizamos la matriz de las plazas como vacías

	for (i = 0; i < num_plazas; i++) {
		for (j = 0; j < 8; j++) {

			matrizplazas[i][j] = '\0';

		}

	}

	//Tipos de vehiculos
	strcpy(tipo_vehiculo[0], char_aux1);
	strcpy(tipo_vehiculo[1], char_aux2);
	
	
	//Reparto de las plazas entre coche y moto.
	plazasmotolibre = (int)num_plazas / 4;
	
	if ((num_plazas < 4) && (num_plazas>1)) {
		plazasmotolibre = 1;
	}
	else if (num_plazas == 1) {
		plazasmotolibre = 0;
		plazascochelibre = 1;
	}
	
	plazascochelibre = (num_plazas - plazasmotolibre);
	
	for (i = 0; i < num_plazas; i++) {
		vector_boolean_tipo_vehiculo[i] = 0;
	}
	do {

			//Menú principal
			system("cls");
			opcion_menu1[0] = '\0';//Inicialización para evitar errores tras varios bucles
			
			//Enviar por pantalla la hora
			struct _timeb timebuffer;
			char timeline[26];
			errno_t err;
			time_t time1;
			unsigned short millitm1;
			short timezone1;
			short dstflag1;

			_ftime_s(&timebuffer); 								    

			time1 = timebuffer.time;
			millitm1 = timebuffer.millitm;
			timezone1 = timebuffer.timezone;
			dstflag1 = timebuffer.dstflag;

			err = ctime_s(timeline, 26, &(timebuffer.time));

			
			printf("\nGestion de aparcamiento\t\t\t"); 
			printf("FECHA: %.19s.%hu %s\n\n", timeline, timebuffer.millitm,	&timeline[20]);
			printf("\nSeleccione una de estas opciones:\n\n\t(R) - Reservar plaza\n\t(A) ");
			printf("- Abandonar plaza\n\t(E) - Estado del aparcamiento\n\t(B) ");
			printf("- Buscar vehiculo por matricula\n\t(S) - Salir del programa\n\nOpcion: ");
			gets(opcion_menu1);
			system("cls");

			_strupr_s(opcion_menu1,20);

			switch (opcion_menu1[0]) {
			
			case 'R'://Reservar plaza

				printf("\nHa elegido \" Reservar plaza \" \n");
				
				booleana = 0;

				for (i = 0; i < num_plazas; i++) {

					if (matrizplazas[i][0] == '\0') {
						//En este if se revisa si hay alguna plaza libre, en cuyo caso, booleana cambia a 1
						booleana = 1;
						break;

					}
				}

				if (booleana == 1) {

					do {
						printf("\n\nIndique el tipo de vehiculo que desea aparcar: ");
						printf("\n\n\t(C) >> COCHE\n\n\t(M) >> MOTO\n\nOpcion: ");
						scanf_s("%c", &tipoauto, 2);

						switch (tipoauto) {
						case 'c':
						case 'C':
							tipoauto = 'C';
							if (plazascochelibre <= 0) {
								printf("\nNo quedan plazas disponibles para coche. Disculpe las molestias.\n\n");
								system("Pause()");
								booleana2 = 0;
								continue;
							}
							else {
								booleana_tipo_auto = 0;
								booleana2 = 1;
								vector_boolean_tipo_vehiculo[i] = 0;//Plaza tipo coche
							}

							break;
						case 'm':
						case'M':
							tipoauto = 'M';
							if (plazasmotolibre <= 0) {
								printf("\nNo quedan plazas disponibles para moto. Disculpe las molestias.\n\n");
								system("Pause()");
								booleana2 = 0;
								continue;
							}
							else {
								booleana_tipo_auto = 1;
								booleana2 = 1;
								vector_boolean_tipo_vehiculo[i] = 1;//Indica que esta plaza es tipo moto
								
							}
							break;
						default:
							printf("\nOpcion incorrecta\n");
							system("Pause()");
						}
					} while ((tipoauto != 'C') && (tipoauto != 'M'));

					if (booleana2 == 1) {
						//Impresion del estado de plazas sin matricula
						system("cls");
						getchar();
						printf("\nReservar plaza \n");
						for (i = 0; i < num_plazas; i++) {
							printf("\n\n Plaza %d - ", (i + 1));

							if (matrizplazas[i][0] == '\0') {
								printf("Libre");
							}
							else {
								printf("Ocupada");

							}
						}

						for (i = 0; i < num_plazas; i++) {

							if (matrizplazas[i][0] == '\0') {
								//En este if se revisa si hay alguna plaza libre, en cuyo caso, booleana cambia a 1
								booleana = 1;
								break;

							}
						}
						do {
							printf("\n\nIntroduzca su matricula para reservar una plaza: ");
							gets(matrizplazas[i]);
							_strupr(matrizplazas[i]);

							printf("\n\nEsta es su matricula: ");
							puts(matrizplazas[i]);


							printf("\n\nConfirmacion: (S) >> SI\t(N) >> NO\n\nOpcion: ");
							do {
								scanf_s("%c", &n);
								switch (n) {
								case's':
								case'S':
									n = 'S';
									confirmacion = 1;
									getchar();

									break;
								case 'N':
								case 'n':
									n = 'N';
									confirmacion = 0;
									getchar();

									break;
								default:
									getchar();
									printf("\nOpcion incorrecta");
									printf("\n\nNueva opcion:");

								}
							} while ((n != 'S') && (n != 'N'));

						} while (confirmacion == 0);

						//Se elimina una plaza libre de coche o moto
						if (booleana_tipo_auto == 0) {
							plazascochelibre = (plazascochelibre - 1);
						}
						else if (booleana_tipo_auto == 1) {
							plazasmotolibre = (plazasmotolibre - 1);
						}
					}
					
				}
				else {

					printf("\n\nNo quedan plazas libres. Disculpe las molestias.\n\n");
					system("Pause()");
				}
				break;
			
			case 'A'://Avandonar plaza

				printf("\nHa elegido \" Abandonar plaza \" \n");
				
				booleana = 0;
				for (i = 0; i < num_plazas; i++) {
					 
					if (matrizplazas[i][0] != '\0') {
						booleana = 1;
						break;
					}
						
				}
				switch (booleana) {
					case 0: 
						printf("\n\nNo hay ninguna plaza ocupada.\n\n");
						system("Pause()");
						continue;
					case 1:
						printf("\nSeleccione la plaza que desea abandonar: \n\n");

						for (i = 0; i < num_plazas; i++) {
							
							if (matrizplazas[i][0] != '\0') {
								printf("\nPlaza - %d \n",(i+1));
								vector_boolean_plazas_libres[i] = 0;//Declara que esta plaza está libre
							}
							else {
								vector_boolean_plazas_libres[i] = 1;//Declara que esta plaza está ocupada

							}

						}

						printf("\nNumero de plaza: ");
						scanf_s("%d", &opcion3);
						if ((opcion3 > 0) && opcion3 <= num_plazas) {
							if (vector_boolean_plazas_libres[(opcion3 - 1)] == 0) {

								for (j = 0; j < 8; j++) {

									matrizplazas[(opcion3 - 1)][j] = '\0';//Vacía la plaza

								}
								if (vector_boolean_tipo_vehiculo[opcion3 - 1] == 0) {
									plazascochelibre++;
								}
								else
									plazasmotolibre++;
								printf("\nLa plaza %d ya esta libre.\n", opcion3);
							}
							else
								printf("\nLa plaza que ha indicado ya esta libre.\n");
						}
						else
							printf("\nOpcion incorrecta.");
				}
				printf("\n\n");
				system("Pause()");

				break;
			
			case 'E'://Estado de las plazas

				printf("\nHa elegido \" Estado del aparcamiento \" \n");

				//Impresion del estado de plazas con matricula

				for (i = 0; i < num_plazas; i++) {
					printf("\n\n Plaza %d - ", (i + 1));

					if (matrizplazas[i][0] != '\0') {
						if (vector_boolean_tipo_vehiculo[i]==1) {
							printf("Ocupada - Moto");
						}
						else {
							printf("Ocupada - Coche");
						}
					}
					else {
						printf("Libre");

					}
				}
				printf("\n\n");
				system("Pause()");
				break;
			
			case 'B': //Buscar vehiculo por matricula

				printf("\nHa elegido \" Buscar vehiculo por matricula \" \n");
				printf("\nIntroduzca la matricula del vehiculo que desee buscar.\n\nMatricula: ");
				gets(vector_matricula_buscar);
				_strupr(vector_matricula_buscar);

				booleana3 = 0;
				
				for (i = 0; i < num_plazas; i++) {
					if (strcmp(matrizplazas[i], vector_matricula_buscar) == 0) {
						booleana3 = 1;
						break;
					}

				}
				if (booleana3 == 1) {
					printf("\n%s >> Su busqueda se encuentra en: \n\n\t Plaza %d - %s\n\n",
						vector_matricula_buscar, (++i),tipo_vehiculo[booleana_tipo_auto]);
				}
				else
					printf("\nLa matricula que precisa no esta registrada en este aparcamiento\n\n");

					system("Pause()");
				break;

			case 'S'://Salir del programa
				
				printf("\nEl programa se cerrara.\n\n");
				system("Pause()");
				break;
		
			default:

				if (opcion_menu1[0] != '\0') {
					printf("\nEl caracter introducido no esta registrado. \n\nIntroduzca de nuevo su opcion.\n\n");
					system("Pause()");
				}
			}
		
	}while (opcion_menu1[0] != 'S');

	exit(0);
}