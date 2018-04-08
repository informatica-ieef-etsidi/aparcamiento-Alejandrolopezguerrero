//Alejandro López Guerrero
//PRÁCTICA 4 APARCAMIENTO. Los posibles usuarios y contraseñas están a partir de la línea 60.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define NPLAZAS 10
#define SIZE 26

typedef struct {
	int estado;//0 LIBRE 1 OCUPADA
	char tipo;//'C' COCHE 'M' MOTO
	char matricula[8];
	int hora_entrada;
}plaza;

typedef struct {//Avanzado
	char user[50];
	char password[50];
}usuario;

void main(void) {

	plaza aparcamiento[NPLAZAS];
	usuario administradores[3];
	int i, j, verificacion;
	char user_aux[50], password_aux[50];

	char opcion_menu1, tipoauto, matricula_aux[8];
	char opcion_menu1_1;
	int estado, precio, orden, opcion_menu2;

	system("color 0B ");

	for (i = 0; i < 50; i++) {
		user_aux[i] = '\0';
		password_aux[i] = '\0';
	}

	for (i = 0; i < NPLAZAS; i++) {
		if (i <=(int)NPLAZAS*0.75) {//(int)NPLAZAS*0.75 es el numero de plazas moto en funcion de las totales
			aparcamiento[i].tipo = 'C';
		}
		else {
			aparcamiento[i].tipo = 'M';
		}
	}

	for (i = 0; i < NPLAZAS; i++) {
		aparcamiento[i].estado = 0;
	}

	//Administradores y contraseñas de cada uno (AVANZADO)
	strcpy(administradores[0].user, "administrador");
	strcpy(administradores[0].password, "1234");
	strcpy(administradores[1].user, "alejandro");
	strcpy(administradores[1].password, "1235");
	strcpy(administradores[2].user, "usuario1");
	strcpy(administradores[2].password, "1012");

	//*****************DESBLOQUEO POR CONTRASEÑA*******************************
	i = 0;
	do{
		printf("\nGestion de aparcamiento\t\t\t");
		printf("Intentos disponibles: %d", 3 - i);
		printf("\n\nIntroduzca un Usuario: ");
		gets(user_aux);
		printf("\nIntroduzca la Contrase\244a: ");
		j = 0;
		do {	//Este paso permite no hacer visible la contraseña.
			password_aux[j] = _getche();
			if (password_aux[j] == '\b') {
				if (j > 0) {
					password_aux[j - 1] = '\0';
					password_aux[j] = '\0';
					printf(" ");
					printf("\b");
					j--;
				}
				else
					printf(" ");
				password_aux[j] = '\0';
					continue;
			}
			else if (password_aux[j] == '\r') {
				j++;
			}
			else {
				j++;
				printf("\b*");
			}

		} while (password_aux[j - 1] != '\r');
		password_aux[j - 1] = '\0';
		verificacion = 0;
		for (j = 0; j < 3; j++) {
			if ((strcmp(administradores[j].user, user_aux) == 0) && (strcmp(administradores[j].password, password_aux) == 0)) {
				verificacion = 1;
			}
			if ((j == 2)&&(verificacion!=1)) {
				printf("\n\n----------------------------------------------------");
				printf("\a\n\nEl Usuario o la Contrase\244a son incorrectos.\n\n");
				system("Pause()");
				system("cls");
				verificacion = 0;
				break;
			}
		}
		i++;
	} while ((verificacion == 0) && (i < 3));
		
	if (verificacion == 0) {
		system("cls");
		printf("\nHa agotado el numero de intentos disponibles. El programa se cerrar\240.\n\n");
		system("Pause()");
		return;
	}
	//**************************************
	//ACCESO TRAS DESBLOQUEO

	do {
		time_t ltime;
		wchar_t buf[SIZE];
		errno_t err;

		time(&ltime);

		err = _wctime_s(buf, SIZE, &ltime);

		system("cls");
		printf("\nGestion de aparcamiento\t\t\t");
		if (err != 0) printf("No disponible");
		wprintf_s(L"\tFecha: %s\n", buf);
		printf("\t\t\t\t\t\t\tUsuario: %s", user_aux);
		printf("\nSeleccione una de estas opciones:\n\n\t(R) - Reservar plaza\n\t(A) ");
		printf("- Abandonar plaza\n\t(E) - Estado del aparcamiento\n\t(B) ");
		printf("- Buscar vehiculo por matricula\n\t(S) - Salir del programa\n\nOpcion: ");
		scanf("%c", &opcion_menu1);
		system("cls");

		switch (opcion_menu1) {

		case 'R'://Reservar plaza
		case 'r':

			opcion_menu1 = 'R';
			getchar();
			printf("\nHa elegido \" Reservar plaza \" \n");
			
			for (i = 0; i < NPLAZAS; i++) {
				if (aparcamiento[i].estado == 0) {
					estado = 0;
					break;
				}
				else
					estado = 1;
			}

			if (estado ==0) {
				do {
					printf("\n\nIndique el tipo de vehiculo que desea aparcar: ");
					printf("\n\n\t(C) >> COCHE\n\n\t(M) >> MOTO\n\nOpcion: ");
					scanf_s("%c", &tipoauto, 1);

					switch (tipoauto) {
					case 'c':
					case 'C':
						tipoauto = 'C';

						for (j = 0; j <= (int)NPLAZAS*0.75; j++) {
							if (aparcamiento[j].estado == 0) {
								estado = 0;
								break;
							}
							else
								estado = 1;
						}
						if (estado == 1) {
							printf("\nNo quedan plazas disponibles para coche. Disculpe las molestias.\n\n");
							system("Pause()");
							continue;
						}
						break;
					case 'm':
					case'M':
						tipoauto = 'M';
						for (j = (((int)NPLAZAS*0.75)+1); j < NPLAZAS; j++) {
							if (aparcamiento[j].estado == 0) {
								estado = 0;
								break;
							}
							else
								estado = 1;
						}
						if (estado == 1) {
							printf("\nNo quedan plazas disponibles para moto. Disculpe las molestias.\n\n");
							system("Pause()");
							continue;
						}
						break;
					default:
						printf("\nOpcion incorrecta\n");
						system("Pause()");
						system("cls");
					}
				} while ((tipoauto != 'C') && (tipoauto != 'M'));
				if (estado==0) {
					system("cls");
					getchar();
					printf("\nReservar plaza \n");

					do {
						printf("\n\nIntroduzca su matricula para reservar una plaza: ");

						gets(matricula_aux);
						_strupr(matricula_aux);

						for (i = 0; i < 8; i++) {
							if (i < 4) {
								if ((matricula_aux[i] >= '0') && (matricula_aux[i] <= '9')) {
									verificacion = 1;
								}
								else {
									verificacion = 0;
									break;
								}
							}
							else if ((i >= 4) && (i < 7)) {
								if ((matricula_aux[i] >= 'A') && (matricula_aux[i] <= 'Z')) {
									verificacion = 1;
								}
								else {
									verificacion = 0;
									break;
								}
							}
						}
						if (verificacion == 0) {
							printf("\n\nDebe introducir la matricula con formato NNNNLLL   N: NUMERO   L: LETRA\n\n");
							system("Pause()");
							system("cls");
							continue;
						}
						printf("\n\nEsta es su matricula: ");
						puts(matricula_aux);

						printf("\n\nConfirmacion: (S) >> SI\t(N) >> NO\n\nOpcion: ");
						do {
							scanf_s("%c", &opcion_menu1_1, 1);
							switch (opcion_menu1_1) {
							case's':
							case'S':
								opcion_menu1_1 = 'S';
								verificacion = 1;
								getchar();
								break;
							case 'N':
							case 'n':
								opcion_menu1_1 = 'N';
								verificacion = 0;
								getchar();
								break;
							default:
								getchar();
								printf("\nOpcion incorrecta");
								printf("\n\nNueva opcion:");
							}
						} while ((opcion_menu1_1 != 'S') && (opcion_menu1_1 != 'N'));

					} while (verificacion == 0);

					strcpy(aparcamiento[j].matricula, matricula_aux);
					aparcamiento[j].hora_entrada = (int)ltime;
					aparcamiento[j].estado = 1;
				}
			}
			else {

				printf("\n\nNo quedan plazas libres. Disculpe las molestias.\n\n");
				system("Pause()");
			}
			break;

		case 'A'://Avandonar plaza
		case 'a':
			opcion_menu1 = 'A';
			printf("\nHa elegido \" Abandonar plaza \" \n");

			for (i = 0; i < NPLAZAS; i++) {
				if (aparcamiento[i].estado == 1) {
					estado = 1;
					break;
				}
				else
					estado = 0;
			}
			if(estado==1){
				printf("\nIndique la plaza a abandonar\n\n");

				for (i = 0; i < NPLAZAS; i++) {
					if (aparcamiento[i].estado == 1) {
						printf(" >> Plaza %d\n\n",i+1);
					}
				}
				printf("Opcion: ");
				scanf_s("%d", &opcion_menu2,1);

				if ((opcion_menu2 > 0) && (opcion_menu2 <= NPLAZAS)) {
					if (aparcamiento[opcion_menu2 - 1].estado == 1) {
						aparcamiento[opcion_menu2 - 1].estado = 0;
						printf("\nLa plaza %d ya esta libre\n\n", opcion_menu2);
						if (aparcamiento[opcion_menu2 - 1].tipo == 'C') {
							precio = (int)(0.25*(ltime - aparcamiento[opcion_menu2-1].hora_entrada));//Tarifa para coches
							printf("\nEl cliente debe abonar %d Euros al retirar el vehiculo", precio);
						}
						else if (aparcamiento[opcion_menu2 - 1].tipo == 'M') {
							precio = (int)(0.05*(ltime - aparcamiento[opcion_menu2].hora_entrada));//Tarifa para motos
							printf("\nEl cliente debe abonar %d Euros al retirar el vehiculo", precio);
						}
					}
					else
						printf("La plaza %d ya se encuentra libre",opcion_menu2);
				}
				else {
					printf("Opcíon incorrecta.");
				}				
				printf("\n\n");
				system("Pause()");
			}
			else if (estado == 0) {
				printf("\n\nActualmente todas las plazas estan libres\n\n");
				system("Pause()");
			}
			break;
		case 'E'://Estado de las plazas
		case 'e':
			opcion_menu1 = 'E';
			printf("\nHa elegido \" Estado del aparcamiento \" \n\n\n");

			//Impresion del estado de plazas con matricula
			
			for (i = 0; i < NPLAZAS; i++) {
				printf("PLAZA %d", i + 1);
				if (aparcamiento[i].estado == 1) {
					printf(" - OCUPADA");
					printf(" - %s", aparcamiento[i].matricula);
				}
				else {
					printf(" - LIBRE");
				}

				if (aparcamiento[i].tipo == 'C')
					printf(" - COCHE\n\n");
				else
					printf(" - MOTO\n\n");
			}
			printf("\n\n");
			system("Pause()");

			break;

		case 'B': //Buscar vehiculo por matricula
		case 'b':
			opcion_menu1 = 'B';
			getchar();
			printf("\nHa elegido \" Buscar vehiculo por matricula \" \n");
			printf("\nIntroduzca la matricula del vehiculo que desee buscar.\n\nMatricula: ");
			gets(matricula_aux);
			_strupr(matricula_aux);

			orden = 2;
			for (i = 0; i < NPLAZAS; i++) {
				orden = strcmp(matricula_aux, aparcamiento[i].matricula);
				if (orden == 0)
					break;
			}
			if (orden == 0) {
					printf("\n%s >> Su busqueda se encuentra en la Plaza %d", matricula_aux, i+1);
					if (aparcamiento[i].tipo == 'C')
						printf(" - Coche\n\n");
					else
						printf(" - Moto\n\n");
			}
			else
				printf("\nLa matricula que precisa no esta registrada en este aparcamiento");

			printf("\n\n");
			system("Pause()");
			break;

		case 'S'://Salir del programa
		case 's':
			opcion_menu1 = 'S';
			printf("\nEl programa se cerrara.\n\n");
			system("Pause()");
			break;

		default:
			if ((opcion_menu1 != '\n') && (opcion_menu1 != '\0')) {
				printf("\nEl caracter introducido no esta registrado. \n\nIntroduzca de nuevo su opcion.\n\n");
				system("Pause()");
			}
		}
	} while (opcion_menu1 != 'S');
}