#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <corecrt_math_defines.h>

#define _MATH_DEFINES_DEFINED

using namespace std;

double stirling(int n) {
	if (n == 0) {
		return 0;
	}
	else return log(sqrt(2 * M_PI * n)) + n * log(n / M_E);
}

void sleep(int time)
{
	time_t koniec;
	koniec = clock() + time;
	while (koniec > clock())
	{

	}
}

int main()
{
	const int liczba_kostek = 600;
	const int rzuty = 100;
	double entropia;
	int chance, sum = 0, old;
	int kostki[liczba_kostek];
	int wystapienia[6] = { 0,0,0,0,0,600 };
	int i, j, k, oldValue;
	time_t pocz;
	srand(time(NULL));
	pocz = clock();

#pragma omp parallel for private(i)
	for (int i = 0; i < liczba_kostek; i++) {
		kostki[i] = 6;
	}

	for (i = 0; i < rzuty; i++)
	{
#pragma omp parallel for  private(j, chance, oldValue)  shared(kostki, wystapienia) 
		for (j = 0; j < liczba_kostek; j++)
		{
			sleep(1);

			chance = rand() % 20;

			if (chance == 0)
			{
				oldValue = kostki[j];
				kostki[j] = rand() % 6 + 1;

				if (kostki[j] != oldValue)
				{
#pragma omp critical
					wystapienia[kostki[j] - 1]++;
#pragma omp critical
					wystapienia[oldValue - 1]--;
				}
			}
		}

		entropia = stirling(liczba_kostek);
		sum = 0;
#pragma omp parallel for reduction(-:entropia) reduction(+:sum)
		for (k = 0; k < 6; k++)
		{
			entropia -= stirling(wystapienia[k]);
			sum += wystapienia[k];
		}
		cout << "Entropia = " << entropia << endl;
		cout << "Wystapienia: ";
		for (int i = 0; i < 6; i++)
			cout << "[" << i + 1 << "]: " << wystapienia[i] << " ";
		cout << "\nsuma " << sum << endl << endl;
	}

	cout << "Czas " << clock() - pocz << endl;
	_getch();
	return 0;
}