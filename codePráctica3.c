//ALEJANDRO LÓPEZ GUERRERO
//PRÁCTICA 3 APARCAMIENTO 
//PARA ACCEDER AL PROGRAMA : USUARIO:administrador CONTRASEÑA 1234

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <string.h>

#define SIZE 26

struct plaza {
	int estado;
	char tipo;
	char matricula[8];
	int hora_entrada;
};

struct user_data {
	char user[50];
	char password[50];
};

void main(void) {
	char user_aux[50], password_aux[50];
	struct plaza plaza1 = { 0, 'C' }, plaza2 = { 0, 'M' };
	struct user_data usuario = { "administrador","1234" };
	
	int i, j, booleana, confirmacion, orden_1, orden_2, precio;
	char opcion_menu1, opcion_menu1_1, tipoauto, aux_matricula[8];
	int opcion_menu2;
	system("color 0B ");

	for (i = 0; i < 50; i++) {
		password_aux[i] = '\0';
	}

	//*****************DESBLOQUEO POR CONTRASEÑA*******************************
	for (i = 0; i < 3; i++) {
		printf("\nGestion de aparcamiento\t\t\t");
		printf("Intentos disponibles: %d", 3 - i);
		printf("\n\nIntroduzca el Usuario: ");
		gets(user_aux);
		printf("\nIntroduzca la Contrase\244a: ");
		j = 0;
		do {	//Este paso permite no hacer visible la contraseña.
			password_aux[j] = _getche();
			if (password_aux[j] == '\b') {
				password_aux[j - 1] = '\0';
				printf(" ");
				printf("\b");
				j--;
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

		if ((strcmp(usuario.password, password_aux) == 0) && (strcmp(usuario.user, user_aux) == 0)) {
			break;
		}
		else {
			printf("\n\n----------------------------------------------------");
			printf("\a\n\nEl Usuario o la Contrase\244a son incorrectos.\n\n");
			system("Pause()");
			system("cls");
		}
		if (i == 2) {
			system("cls");
			printf("\nHa agotado el numero de intentos disponibles. El programa se cerrar\240.\n\n");
			system("Pause()");
			return;
		}
	}

	//*************************ACCESO TRAS DESBLOQUEAR CONTRASEÑA*********************
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
		printf("\t\t\t\t\t\t\tUsuario: %s", usuario.user);
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

			if ((plaza1.estado == 0) || (plaza2.estado == 0)) {
				do {
					printf("\n\nIndique el tipo de vehiculo que desea aparcar: ");
					printf("\n\n\t(C) >> COCHE\n\n\t(M) >> MOTO\n\nOpcion: ");
					scanf_s("%c", &tipoauto,1);
					booleana = 1;

					switch (tipoauto) {
					case 'c':
					case 'C':
						tipoauto = 'C';
						if (plaza1.estado == 1) {
							printf("\nNo quedan plazas disponibles para coche. Disculpe las molestias.\n\n");
							system("Pause()");
							booleana = 0;
							continue;
						}
						break;
					case 'm':
					case'M':
						tipoauto = 'M';
						if (plaza2.estado == 1) {
							printf("\nNo quedan plazas disponibles para moto. Disculpe las molestias.\n\n");
							system("Pause()");
							booleana = 0;
							break;
						}
						break;
					default:
						printf("\nOpcion incorrecta\n");
						system("Pause()");
					}
				} while ((tipoauto != 'C') && (tipoauto != 'M'));
				if (booleana == 1) {
					system("cls");
					getchar();
					printf("\nReservar plaza \n");

					do {
						printf("\n\nIntroduzca su matricula para reservar una plaza: ");

						gets(aux_matricula);
						_strupr(aux_matricula);
						printf("\n\nEsta es su matricula: ");
						puts(aux_matricula);

						printf("\n\nConfirmacion: (S) >> SI\t(N) >> NO\n\nOpcion: ");
						do {
							scanf_s("%c", &opcion_menu1_1, 1);
							switch (opcion_menu1_1) {
							case's':
							case'S':
								opcion_menu1_1 = 'S';
								confirmacion = 1;
								getchar();
								break;
							case 'N':
							case 'n':
								opcion_menu1_1 = 'N';
								confirmacion = 0;
								getchar();
								break;
							default:
								getchar();
								printf("\nOpcion incorrecta");
								printf("\n\nNueva opcion:");
							}
						} while ((opcion_menu1_1 != 'S') && (opcion_menu1_1 != 'N'));

					} while (confirmacion == 0);

					if (tipoauto == 'C') {
						strcpy(plaza1.matricula, aux_matricula);
						plaza1.hora_entrada = (int)ltime;
						plaza1.estado = 1;
					}
					else if (tipoauto = 'M') {
						strcpy(plaza2.matricula, aux_matricula);
						plaza2.hora_entrada = (int)ltime;
						plaza2.estado = 1;
					}
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

			if ((plaza1.estado == 0) && (plaza2.estado == 0)) {
				printf("\n\nActualmente no hay ninguna plaza opupada\n\n");
				system("Pause()");
				continue;
			}
			else {
				printf("\nIndique la plaza a abandonar\n\n");

				if (plaza1.estado == 1) {
					printf(" >> Plaza 1\n\n");
				}
				if (plaza2.estado == 1) {
					printf(" >> Plaza 2\n\n");
				}
				printf("Opcion: ");
				scanf("%d",&opcion_menu2);

				switch (opcion_menu2) {
				case 1:
					if (plaza1.estado == 0) {
						printf("\n\nLa plaza %d actualmente est\240 libre\n\n",opcion_menu2);
						system("Pause()");
						continue;
					}
					else {
						printf("\n\nYa est\240 libre la plaza %d", opcion_menu2);
						precio = (int)(0.25*(ltime - plaza1.hora_entrada));
						printf("\nEl cliente debe abonar %d Euros al retirar el vehiculo", precio);
						plaza1.estado = 0;
					}
					break;
				case 2:
					if (plaza2.estado == 0) {
						printf("\n\nLa plaza %d actualmente est\240 libre\n\n",opcion_menu2);
						system("Pause()");
						continue;
					}
					else {
						printf("\n\nYa est\240 libre la plaza %d", opcion_menu2);
						precio = (int)(0.05*(ltime - plaza2.hora_entrada));
						printf("\nEl cliente debe abonar %d€ al retirar el vehiculo", precio);
						plaza2.estado = 0;	
					}
					break;
				default:
					printf("\nOpcion incorrecta. ");
					system("Pause()");
					continue;
				}

				printf("\n\n");
				system("Pause()");
			}
				break;
		case 'E'://Estado de las plazas
		case 'e':
			opcion_menu1 = 'E';
			printf("\nHa elegido \" Estado del aparcamiento \" \n");

			//Impresion del estado de plazas con matricula
			printf("\n\nPLAZA 1 - ");
			if (plaza1.estado == 0) {
				printf("LIBRE - ");
				printf("COCHE\n");
			}
			else {
				printf("OCUPADA - ");
				printf("%s - COCHE\n", plaza1.matricula);
			}
			printf("\nPLAZA 2 - ");
			if (plaza2.estado == 0) {
				printf("LIBRE - ");
				printf("MOTO\n");
			}
			else {
				printf("OCUPADA - ");
				printf("%s - MOTO\n\n", plaza2.matricula);
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
			gets(aux_matricula);
			_strupr(aux_matricula);
			
			orden_1 = strcmp(aux_matricula, plaza1.matricula);
			orden_2 = strcmp(aux_matricula, plaza2.matricula);
			if ((orden_1==0)||(orden_2==0)) {
				if (orden_1 == 0) {
					printf("\n%s >> Su busqueda se encuentra en la Plaza 1 - Coche", aux_matricula);
				}
				else if (orden_2 == 0) {
					printf("\n%s >> Su busqueda se encuentra en la Plaza 2 - Moto", aux_matricula);
				}
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
			if ((opcion_menu1 != '\n')&&(opcion_menu1 != '\0')) {
				printf("\nEl caracter introducido no esta registrado. \n\nIntroduzca de nuevo su opcion.\n\n");
				system("Pause()");
			}
		}
	}while (opcion_menu1 != 'S');
}