//Alejandro López Guerrero
//Práctica 5 del aparcamiento (FUNCIONES I)

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define NPLAZAS 5
#define NUM_USUARIOS 4
#define SIZE 26

char menu();
int esDigitoValido(char caracter);
int esLetraValida(char caracter);
int esMatriculaValida(char matricula[]);
int existeUsuario(struct usuario usuarioValido, char username[], char password[]);

typedef struct {
	int estado;//0 LIBRE 1 OCUPADA
	char tipo;//'C' COCHE 'M' MOTO
	char matricula[8];
	int hora_entrada;
}plaza;

struct usuario {
	char username[50];
	char password[50];
};

void main(void) {

	plaza aparcamiento[NPLAZAS];
	struct usuario administradores[NUM_USUARIOS];
	int i, j, verificacion;
	char user_aux[50], password_aux[50], auxiliar[50];

	char opcion_menu1, tipoauto, matricula_aux[8];
	char opcion_menu1_1;
	int estado, precio, orden, opcion_menu2;

	system("color 0B ");

	for (i = 0; i < 50; i++) {
		user_aux[i] = '\0';
		password_aux[i] = '\0';
		auxiliar[i] = '\0';
	}

	for (i = 0; i < NPLAZAS; i++) {
		if (i <= (int)NPLAZAS*0.75) {//(int)NPLAZAS*0.75 es el numero de plazas moto en funcion de las totales
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
	strcpy(administradores[0].username, "administrador");
	strcpy(administradores[0].password, "1234");
	strcpy(administradores[1].username, "alejandro");
	strcpy(administradores[1].password, "1235");
	strcpy(administradores[2].username, "usuario1");
	strcpy(administradores[2].password, "1012");
	strcpy(administradores[3].username, "admin");
	strcpy(administradores[3].password, "1234");

	//*****************DESBLOQUEO POR CONTRASEÑA*******************************
	i = 0;
	do {
		printf("\nGestion de aparcamiento\t\t\t");
		printf("Intentos disponibles: %d", 3 - i);
		printf("\n\nIntroduzca un Usuario: ");
		gets(user_aux);
		printf("\nIntroduzca la Contrase\244a: ");
		j = 0;
		do {	//Este paso permite no hacer visible la contraseña.
			auxiliar[j] = _getche();
			if (auxiliar[j] == '\b') {
				if (j > 0) {
					auxiliar[j - 1] = '\0';
					auxiliar[j] = '\0';
					printf(" ");
					printf("\b");
					j--;
				}
				else {
					printf(" ");
					
				}
				auxiliar[j] = '\0';
				strcpy(password_aux, auxiliar);
				continue;
			}
			else if (auxiliar[j] == 'à') {
				printf("\b \b");
				auxiliar[j+1]= _getche();
				strcpy(auxiliar, password_aux);
				
			}
			else if (auxiliar[j] == '\r') {
				break;
			}
			else {
				j++;
				printf("\b*");
				strcpy(password_aux, auxiliar);
			}

		} while (1);

		verificacion = 0;
		for (j = 0; j < NUM_USUARIOS; j++) {
			if (existeUsuario(administradores[j],user_aux,password_aux)==1) {
				verificacion = 1;
				break;
			}
			else {
				verificacion = 0;
				continue;
			}
		}
		i++;

		if (verificacion == 1) {
			printf("\n\n----------------------------------------------------");
			printf("\n\nDatos correctos.\n\n");
			system("Pause()");
			system("cls");
		}
		else {
			printf("\n\n----------------------------------------------------");
			printf("\a\n\nEl Usuario o la Contrase\244a son incorrectos.\n\n");
			system("Pause()");
			system("cls");
		}
	} while ((verificacion == 0) && (i < 3));

	if (verificacion == 0) {
		system("cls");
		printf("\nHa agotado el numero de intentos disponibles. El programa se cerrar\240.\n\n");
		system("Pause()");
		return;
	}
	//**************************************
	//ACCESO TRAS DESBLOQUEO

	while((opcion_menu1=menu())!='S'){
		
		system("cls");

		time_t ltime;
		wchar_t buf[SIZE];
		time(&ltime);

		switch (opcion_menu1) {
		case 'R'://Reservar plaza

			printf("\nHa elegido \" Reservar plaza \" \n");

			for (i = 0; i < NPLAZAS; i++) {
				if (aparcamiento[i].estado == 0) {
					estado = 0;
					break;
				}
				else
					estado = 1;
			}

			if (estado == 0) {
				do {
					system("cls");
					printf("\nHa elegido \" Reservar plaza \" \n");
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
						for (j = (((int)NPLAZAS*0.75) + 1); j < NPLAZAS; j++) {
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
						getchar();
						system("Pause()");
						system("cls");
					}
				} while ((tipoauto != 'C') && (tipoauto != 'M'));
				if (estado == 0) {
					system("cls");
					getchar();

					do {
						system("cls");
						printf("\nReservar plaza \n");
						printf("\n\nIntroduzca su matricula para reservar una plaza: ");

						gets(matricula_aux);
						_strupr(matricula_aux);
						
						if (esMatriculaValida(matricula_aux) == 0) {
							printf("\n\nDebe introducir la matricula con un formato correcto\n\n");
							verificacion = 0;
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

					} while (verificacion== 0);

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

			printf("\nHa elegido \" Abandonar plaza \" \n");

			for (i = 0; i < NPLAZAS; i++) {
				if (aparcamiento[i].estado == 1) {
					estado = 1;
					break;
				}
				else
					estado = 0;
			}
			if (estado == 1) {
				printf("\nIndique la plaza a abandonar\n\n");

				for (i = 0; i < NPLAZAS; i++) {
					if (aparcamiento[i].estado == 1) {
						printf(" >> Plaza %d\n\n", i + 1);
					}
				}
				printf("Opcion: ");
				scanf_s("%d", &opcion_menu2);

				if ((opcion_menu2 > 0) && (opcion_menu2 <= NPLAZAS)) {
					if (aparcamiento[opcion_menu2 - 1].estado == 1) {
						aparcamiento[opcion_menu2 - 1].estado = 0;
						printf("\nLa plaza %d ya esta libre\n\n", opcion_menu2);
						if (aparcamiento[opcion_menu2 - 1].tipo == 'C') {
							precio = (int)(0.25*(ltime - aparcamiento[opcion_menu2 - 1].hora_entrada));//Tarifa para coches
							printf("\nEl cliente debe abonar %d Euros al retirar el vehiculo", precio);
						}
						else if (aparcamiento[opcion_menu2 - 1].tipo == 'M') {
							precio = (int)(0.05*(ltime - aparcamiento[opcion_menu2 -1].hora_entrada));//Tarifa para motos
							printf("\nEl cliente debe abonar %d Euros al retirar el vehiculo", precio);
						}
					}
					else
						printf("La plaza %d ya se encuentra libre", opcion_menu2);
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
				printf("\n%s >> Su busqueda se encuentra en la Plaza %d", matricula_aux, i + 1);
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

			printf("\nEl programa se cerrara.\n\n");
			system("Pause()");
			break;

		}
	}
}

char menu() {
	
	while (1) {
		char opcion_menu1;
		time_t ltime;
		wchar_t buf[SIZE];
		errno_t err;

		time(&ltime);

		err = _wctime_s(buf, SIZE, &ltime);

		system("cls");
		printf("\nGestion de aparcamiento\t\t\t");
		if (err != 0) printf("No disponible");
		wprintf_s(L"\tFecha: %s\n", buf);
		printf("\nSeleccione una de estas opciones:\n\n\t(R) - Reservar plaza\n\t(A) ");
		printf("- Abandonar plaza\n\t(E) - Estado del aparcamiento\n\t(B) ");
		printf("- Buscar vehiculo por matricula\n\t(S) - Salir del programa\n\nOpcion: ");
		scanf_s("%c", &opcion_menu1);
		system("cls");

		switch (opcion_menu1) {

		case 'R'://Reservar plaza
		case 'r':
			getchar();
			return 'R';
		case 'A'://Avandonar plaza
		case 'a':
			getchar();
			return 'A';
		case 'E'://Estado de las plazas
		case 'e':
			getchar();
			return 'E';
		case 'B': //Buscar vehiculo por matricula
		case 'b':
			getchar();
			return 'B';
		case 'S'://Salir del programa
		case 's':
			getchar();
			return 'S';
		default:
			if ((opcion_menu1 != '\n') && (opcion_menu1 != '\0')) {
				getchar();
				printf("\nEl caracter introducido no esta registrado. \n\nIntroduzca de nuevo su opcion.\n\n");
				system("Pause()");
			}
		}
	}
}

int esMatriculaValida(char matricula[]) { //AVANZADO
	
	int i, tipo_matricula;
	
	//tipo_matricula = 1 >>> NNNNL LL
	//tipo_matricula = 2 >>> L NNNN LL
	//tipo_matricula = 3 >>> LL NNNN L
	
	if (esDigitoValido(matricula[0]) == 1) {
		tipo_matricula = 1;
	}
	else if (esLetraValida(matricula[0]) == 1) {
		if ((matricula[1]>='A')&&(matricula[1]<='Z')) {
			tipo_matricula = 3;
		}
		else {
			tipo_matricula = 2;
		}
	}
	else {
		return 0;
	}
	
	switch (tipo_matricula) {
	case 1:
		for (i = 1; i < 8; i++) {
			if (i < 4) {
				if (esDigitoValido(matricula[i]) == 1) {
					continue;
				}
				else {
					return 0;
				}
			}
			else if ((i >= 4) && (i < 7)) {
				if (esLetraValida(matricula[i]) == 1) {
					continue;
				}
				else {
					return 0;
				}
			}
		}
		return 1;
	case 2:
		for (i = 1; i < 8; i++) {
			if (i < 5) {
				if (esDigitoValido(matricula[i]) == 1) {
					continue;
				}
				else {
					return 0;
				}
			}
			else if ((i >= 5) && (i < 7)) {
				if (esLetraValida(matricula[i]) == 1) {
					continue;
				}
				else {
					return 0;
				}
			}
		}
		return 1;
	case 3:
		for (i = 2; i < 8; i++) {
			if (i < 6) {
				if (esDigitoValido(matricula[i]) == 1) {
					continue;
				}
				else {
					return 0;
				}
			}
			else if ((i >= 6) && (i < 7)) {
				if (esLetraValida(matricula[i]) == 1) {
					continue;
				}
				else {
					return 0;
				}
			}
		}
		return 1;
	}
	
	return 1;
}

int esDigitoValido(char caracter) {

	if ((caracter >= '0') && (caracter <= '9')) {
		return 1;
	}
	else {
		return 0;
	}
}

int esLetraValida(char caracter) {

	if ((caracter >= 'B') && (caracter <= 'Z')) {
		if ((caracter != 'E') && (caracter != 'I') && (caracter != 'O') && (caracter != 'U')) {
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
	
}

int existeUsuario(struct usuario usuarioValido, char username[], char password[]) {

	if ((strcmp(usuarioValido.username, username) == 0) && (strcmp(usuarioValido.password, password) == 0)) {
		return 1;
	}
	else {
		return 0;
	}
}