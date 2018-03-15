#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <string.h>
#define num_plazas 2



void main(void) {

	int i = 0, j, opcion2, opcion3, booleana, booleana2;
	int vector_boolean_plazas_libres[num_plazas];
	unsigned char opcion_menu1[1], n;
	unsigned char matrizplazas[num_plazas][8];

	system("color 0B ");


	//Inicilaizamos la matriz de las plazas como vacías

	for (i = 0; i < num_plazas; i++) {
		for (j = 0; j < 8; j++) {

			matrizplazas[i][j] = '\0';

		}

	}


	while (1) {

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
			printf("- Abandonar plaza\n\t(E) - Estado del aparcamiento\n\nOpcion: ");
			gets(opcion_menu1);
			system("cls");

			_strupr_s(opcion_menu1,20);

			switch (opcion_menu1[0]) {
			case 'R':
				printf("\nHa elegido \" Reservar plaza \" \n");
				//Impresion del estado de plazas sin matricula

				for (i = 0; i < num_plazas; i++) {
					printf("\n\n Plaza %d - ", (i + 1));

					if (matrizplazas[i][0] == '\0') {
						printf("Libre");
					}
					else {
						printf("Ocupada");

					}
				}
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
						printf("\n\nIntroduzca su matricula para reservar una plaza: ");
						gets_s(matrizplazas[i],8);
						_strupr(matrizplazas[i]);

						printf("\n\nEsta es su matricula: ");
						puts(matrizplazas[i]);


						printf("\n\n¿Desea modificarla?: (S) >> SI\t(N) >> NO\n\nOpcion: ");
						do {
							scanf_s("%c", &n);
							switch (n) {
							case's':
							case'S':
								n = 'S';
								booleana2 = 1;
								getchar();
								
								break;
							case 'N':
							case 'n':
								n = 'N';
								booleana2 = 0;
								getchar();

								break;
							default:
								getchar();
								printf("\nOpcion incorrecta");
								printf("\n\nNueva opcion:");

							}
						} while ((n != 'S') && (n != 'N'));
					} while (booleana2 == 1);
				}
				
				else {

					printf("\n\nNo quedan plazas libres. Disculpe las molestias.\n\n");
					system("Pause()");
				}

				break;
			case 'A':

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
			case 'E':

				printf("\nHa elegido \" Estado del aparcamiento \" \n");

				//Impresion del estado de plazas con matricula

				for (i = 0; i < num_plazas; i++) {
					printf("\n\n Plaza %d - ", (i + 1));

					if (matrizplazas[i][0] != '\0') {
						printf("Ocupada - ");
						puts(matrizplazas[i]);
					}
					else {
						printf("Libre");

					}
				}
				printf("\n\n");
				system("Pause()");
				break;
			default:
				if (opcion_menu1[0] != '\0') {
					printf("\nEl caracter introducido no esta registrado. \n\nIntroduzca de nuevo su opcion.\n\n");
					system("Pause()");
				}
			}
		} while ((opcion_menu1[0] != 'R') && (opcion_menu1[0] != 'A') && (opcion_menu1[0] != 'E'));
	}
}