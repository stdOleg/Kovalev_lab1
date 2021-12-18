#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


int main(void) {
	system("cls");
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int g = 0, m = 0, e = 0, tmp_g, N;
	float eps = 0, b = 0;
	int counter_g = 0, counter_m = 0, COUNTER = 0, check;
	int ARRg[40], ARRm[40], residue[40], ARRe[40], bx[40];

	printf("Введите пораждающий многочлен: ");
	scanf_s("%d", &g);
	printf("\nВведите сообщение: ");
	scanf_s("%d", &m);
	printf("\nВведите вероятность ошибки на бит: ");
	scanf_s("%f", &b);
	printf("\nВведите точность: ");

	scanf_s("%f", &eps);
	while(eps > 1.5 || eps < 0){
		printf("Отрицательное значение, либо Слишком большое значение точности, введите значение меньше 1.5 : ");
		scanf_s("%f", &eps);
	}
	printf("g(x) = %d	m(x) = %d	eps = %f	Pb = %f\n", g, m, eps, b);
	
	N = 9 / (4 * eps * eps);
	tmp_g = g;
	int i = 0;
	while (tmp_g != 0) {
		ARRg[i] = tmp_g % 2;
		i++;
		tmp_g >>= 1;
		counter_g++;
	}

	

	int tmp_m = m;
	i = 0;
	while (tmp_m != 0) {
		ARRm[i] = tmp_m % 2;
		i++;
		tmp_m >>= 1;
		counter_m++;
	}
	for (int i = counter_m - 1; i >= 0; i--) {
		ARRm[i + counter_g - 1] = ARRm[i];
		ARRm[i] = 0;
	}
	
	printf("Сообщение: ");
	for (int i = counter_m + counter_g - 2; i >= 0; i--) {
		printf("%d ", ARRm[i]);
	}
	printf("\nПорождающий многочлен: ");
	for (int i = counter_g - 1; i >= 0; i--) {
		printf("%d ", ARRg[i]);
	}
	printf("\n");

	/*for (int i = counter_m - 1; i >= 0; i--) {
		ARRm[i + counter_g - 1] = ARRm[i];
		ARRm[i] = 0;
	}*/

	for (i = counter_m + counter_g - 2; i >= 0; i--) {
		residue[i] = ARRm[i];
	}

	for (i = counter_m + counter_g - 2; i >= 0; i--) {
		if (residue[i] == 0) {
			continue;
		}
		if (i < counter_g - 1) {
			break;
		}
		int i_tmp = i;
		for (int j = counter_g - 1; j >= 0; j--) {
			//printf("\n%d %d", residue[i_tmp], ARRg[j]);
			if (residue[i_tmp] == ARRg[j]) {
				residue[i_tmp] = 0;
			}
			else { residue[i_tmp] = 1; }
			i_tmp--;
		}
	}

	/*for (i = counter_m - 1; i >= 0; i--) {
		residue[i] = ARRm[i];
	}*/

	printf("Остаток от деления:  ");
	for (int i = counter_g - 1; i >= 0; i--) {
		printf("%d ", residue[i]);
	}


	/*for (int i = counter_m - 1; i >= 0; i--) {
		ARRm[i + counter_g - 1] = ARRm[i];
		ARRm[i] = 0;
	}*/

	printf("\nax: ");

	for (int i = counter_g - 2; i >= 0; i--) {
		ARRm[i] = residue[i];
	}

	for (int i = counter_m + counter_g - 2; i >= 0; i--) { //получили a(x)
		printf("%d ", ARRm[i]);
	}

	for (float j_tmp = 0.099; j_tmp <= 1; j_tmp += 0.1) {

		for (int k = 0; k < N; k++) {
			check = 0;
			//e = generate_e(counter_g, counter_m, b);
			for (int i = 0; i <= (counter_m + counter_g - 2); i++) {
				//if (ARRm[i - counter_g] == 0) {//ДОП ЗАДАНИЕ
				//	continue;
				//}
				int a = (rand() % 10001);
				float y = j_tmp * 10000;
				if (y >= (float)a) {
					e = e + (1 << i);
				}
			}

			int counter_e = 0;
			for (int i = 0; i <= (counter_m + counter_g - 2); i++) {
				ARRe[i] = e % 2;
				e >>= 1;
				counter_e++;
			}

			/*printf("\ne: ");
			for (i = counter_m + counter_g - 2; i >= 0; i--) {
				printf("%d ", ARRe[i]);
			}*/

			//printf("\nbx: ");
			for (i = counter_m + counter_g - 2; i >=0; i--) {
				bx[i] = ARRe[i] ^ ARRm[i];
				//printf("%d ", bx[i]);
			}

			

			for (int i = counter_m + counter_g - 2; i >= 0; i--) {
				residue[i] = bx[i];
			}
			
			for (int i = counter_m + counter_g - 2; i >= 0; i--) {
				if (residue[i] == 0) {
					continue;
				}
				if (i < counter_g - 1) {
					break;
				}
				int i_tmp = i;
				for (int j = counter_g - 1; j >= 0; j--) {
					//printf("\n%d %d", residue[i_tmp], ARRg[j]);
					if (residue[i_tmp] == ARRg[j]) {
						residue[i_tmp] = 0;
					}
					else { residue[i_tmp] = 1; }
					i_tmp--;
				}
			}

			for (int i = 0; i <= counter_g - 1; i++) {
				if (residue[i] == 1) {
					check = 1;
					break;
				}
			}

			/*printf("\nOstatok:  ");
			for (int i = counter_e - 1; i >= 0; i--) {
				printf("%d ", residue[i]);
			}*/
			int check_e = 0;
			for (int i = counter_e - 1; i >= 0; i--) {
				if (ARRe[i] == 1) {
					check_e = 1;
					break;
				}
			}

			if (check == 0 && check_e == 1) {
				COUNTER += 1;
			}
		}

		/*for (float j = 0; j = 1; j += 0.1) {

		}*/

		float P = (float)COUNTER / (float)N;
		printf("\n\nКолличество опытов: %d Колличество ошибочных решений декодера: %d \nВероятность ошибки Pe = Ne/N = %f при вероятности ошибки на бит %f", N, COUNTER, P, j_tmp);
		COUNTER = 0;
	}
}
