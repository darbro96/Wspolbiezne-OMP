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
	int number;
	const int liczba_kostek = 600;
	const int rzuty = 100;
	double entropia;
	int chance, sum = 0;
	int kostki[liczba_kostek];
	int one = 0, two = 0, three = 0, four = 0, five = 0, six = 600;
	int i, j, oldValue;
	time_t pocz;
	srand(time(NULL));
	pocz = clock();

	double N = stirling(liczba_kostek);
	double n1, n2, n3, n4, n5, n6;

#pragma omp parallel for private(i)
	for (int i = 0; i < liczba_kostek; i++) {
		kostki[i] = 6;
	}

	for (i = 0; i < rzuty; i++)
	{
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

#pragma omp parallel shared(one, two, three, four, five, six)
					{
#pragma omp sections 
						{
#pragma omp section 
							{
								switch (kostki[j])
								{
								case 1:
									one++;
									break;
								case 2:
									two++;
									break;

								case 3:
									three++;
									break;

								case 4:
									four++;
									break;

								case 5:
									five++;
									break;

								case 6:
									six++;
									break;
								}
							}
#pragma omp section
							{
								switch (oldValue)
								{
								case 1:
									one--;
									break;
								case 2:
									two--;
									break;

								case 3:
									three--;
									break;

								case 4:
									four--;
									break;

								case 5:
									five--;
									break;

								case 6:
									six--;
									break;
								}
							}
						}
					}
				}
			}
		}


#pragma omp parallel
		{
#pragma omp sections 
			{
#pragma omp section
				{
					n1 = stirling(one);
				}
#pragma omp section
				{
					n2 = stirling(two);
				}
#pragma omp section
				{
					n3 = stirling(three);
				}
#pragma omp section
				{
					n4 = stirling(four);
				}
#pragma omp section
				{
					n5 = stirling(five);
				}
#pragma omp section
				{
					n6 = stirling(six);
				}
			}
		}


		entropia = N - n1 - n2 - n3 - n4 - n5 - n6;
		sum = one + two + three + four + five + six;

		for (int i = 1; i < 7; i++) {
			switch (i)
			{
			case 1:
				number = one;
				break;
			case 2:
				number = two;
				break;

			case 3:
				number = three;
				break;

			case 4:
				number = four;
				break;

			case 5:
				number = five;
				break;

			case 6:
				number = six;
				break;
			}
			cout << "[" << i << "]: " << number << " ";
		}

		cout << "Entropia = " << entropia << endl;
		cout << "\nsuma " << sum << endl;
	}

	cout << "Czas " << clock() - pocz << endl;
	_getch();
	return 0;
}