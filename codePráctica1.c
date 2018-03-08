#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

void main() {
	
	int i = 0, opcion2;
	char option, n;
	char plaza1[8] = { '\0' }, plaza2[8] = { '\0' };
	
	system("color 0B ");

	while (1) {
		do {
			
			system("cls");
			
			//Menú principal
			printf("\nGestion de aparcamiento\n\n");
			printf("\nSeleccione una de estas opciones:\n\n\t(R) - Reservar plaza\n\t(A) - Abandonar plaza\n\t(E) - Estado del aparcamiento\n\nOpcion: ");
			scanf_s("%c", &option,1);
			getchar();
			system("cls");
			

			switch (option) {
			case 'R':
			case 'r':
				printf("\nHa elegido \" Reservar plaza \" \n");
				option = 'R';
				break;
			case 'A':
			case 'a':
				printf("\nHa elegido \" Abandonar plaza \" \n");
				option = 'A';
				break;
			case 'E':
			case 'e':
				printf("\nHa elegido \" Estado del aparcamiento \" \n");
				option = 'E';
				break;
			default:
				printf("\nEl caracter introducido no esta registrado. Introduzca de nuevo su opcion.\n");
			}
		} while ((option != 'R') && (option != 'A') && (option != 'E'));

		//Selector del menú
		if (option == 'R') {
			//Impresion del estado de plazas sin matricula
				printf("\n\n Plaza 1 - ");

				if (plaza1[0] == '\0') {
					printf("Libre");
				}
				else {
					printf("Ocupada");
					
				}

				printf("\n\n Plaza 2 - ");

				if (plaza2[0] == '\0') {
					printf("Libre\n\n");
				}
				else {
					printf("Ocupada");
					
				}

				if (plaza1[0] == '\0') {//Ocupar plazas
					do {

						printf("\n\nIntroduzca su matricula para reservar una plaza: ");
						i = 0;
						do {
							plaza1[i] = _getche();
							i++;
						} while (i < 7);
						printf("\n\nEsta es su matricula: ");
						for (i = 0; i < 7; i++) {
							printf("%c", plaza1[i]);
							if (i == 3)
								printf("-");
						}
						
						printf("\n\n¿Desea modificarla?: (S) >> SI\t(N) >> NO\n\nOpcion: ");
						do {
							scanf_s("%c", &n);
							switch (n) {
							case's':
							case'S':
								n = 'S';
								break;
							case 'N':
							case 'n':
								n = 'N';
								break;
							default:
								getchar();
								printf("\nOpcion incorrecta");
								printf("\n\nNueva opcion:");
								
							}
						} while ((n != 'S') && (n != 'N'));
					}while (n=='S');
				}
				else if (plaza2[0] == '\0') {
					do {

						printf("\n\nIntroduzca su matricula para reservar una plaza: ");
						i = 0;
						do {
							plaza2[i] = _getche();
							i++;
						} while (i < 7);
						printf("\n\nEsta es su matricula: ");
						for (i = 0; i < 7; i++) {
							printf("%c", plaza2[i]);
							if (i == 3)
								printf("-");
						}
						getchar();
						printf("\n\n¿Desea modificarla?: (S) >> SI\t(N) >> NO\n\nOpcion: ");
						do {
							scanf_s("%c", &n);
							switch (n) {
							case's':
							case'S':
								n = 'S';
								break;
							case 'N':
							case 'n':
								n = 'N';
								break;
							default:
								getchar();
								printf("\nOpcion incorrecta");
								printf("\n\nNueva opcion:");

							}
						} while ((n != 'S') && (n != 'N'));
					} while (n == 'S');
				}
				else
					printf("\n\nNo quedan plazas libres. Disculpe las molestias.\n\n");
		/*else if (option == 'A') {


		}*/
				getchar();
		}
		else if (option == 'A') {
			if ((plaza1[0] == '\0') && (plaza2[0] == '\0')) {
				printf("\n¿Que plaza desea abandonar?: ");
				scanf_s("%d", &opcion2);
				if ((opcion2 == 1) || (opcion2 == 2)) {
					printf("\nLa plaza %d esta ahora libre", opcion2);
					if (opcion2 == 1) {
						do {
							plaza1[i] = '\0';
							i++;
						} while (i < 7);
					}
					else {
						do {
							plaza2[i] = '\0';
							i++;
						} while (i < 7);
					}
					continue;
					}
					
				}
				else
					printf("\nOpcion incorrecta.");

			}
			
		
		else if (option == 'E') {

			printf("\n\n Plaza 1 - ");

			if (plaza1[0] == '\0') {
				printf("Libre");
			}
			else {
				printf("Ocupada - Matricula: ");
				printf(plaza1);
			}

			printf("\n\n Plaza 2 - ");

			if (plaza2[0] == '\0') {
				printf("Libre\n\n");
			}
			else {
				printf("Ocupada - Matricula: ");
				printf(plaza2);
			}
		}
		printf("\n\n");
		system("Pause()");
		
	}

}
