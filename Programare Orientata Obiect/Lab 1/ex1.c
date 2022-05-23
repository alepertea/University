#include <stdio.h>
#include <math.h>
#include <float.h>

typedef struct
{
	float x, y;
}pair;

void menu()
{
	printf("1: afiseaza toate numerele prime mai mici decat un numar dat. \n");
	printf("2: afiseaza primele n numere prime. \n");
	printf("3: scrie un numar ca suma de numere consecutive. \n");
	printf("4: determina primele n cifre din scrierea zecimala a unei fractii SUBUNITARE \n");
	printf("5: afiseaza un numar precizat de termeni din sirul  1, 2,1, 3,2,1, 4,2,2, 5,4,3,2,1, 6,2,2,3,3,3, 7,6,... \n");
	printf("6: afiseaza primele n linii din triunghiul lui Pascal \n");
	printf("7: calculeaza radacina patrata cu aproximatie epsilon. \n");
	printf("8: tipareste exponentul la care numarul prim p apare in descompunerea in factori primi a numarului N = 1 * 2 *... * n \n");
	printf("9: citeste un sir de numere naturale nenule terminat cu 0 si determina numarul cifrelor 0 in care se termina numarul produs al numerelor citite. \n");
	printf("10: tipareste un numar precizat de sume partiale din sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ... \n");
	printf("11: gaseste intersectia a doua segmente date prin coordonatele carteziene \n");
	printf("12: calculeaza valoarea x^n \n");
	printf("13: descompune in factori primi un numar natural nenul dat \n");
	printf("14: descompune un numar natural par, mai mare strict ca 2, intr-o suma de doua numere prime (verificarea ipotezei lui Goldbach) \n");
	printf("15: determina primele n perechi de numere prime gemene, unde n este un numar natural nenul dat \n");
	printf("16: determina toate numerele naturale mai mici decat un numar naturtal nenul dat n si care sunt relativ prime cu n \n");
	printf("17: determina primele 10 numere naturale strict mai mari ca 2, care au proprietatea ca toate numerele naturale strict mai mici decat ele si care sunt prime cu ele sunt numere prime \n");
	printf("Introduceti 0 pentru a parasi programul! \n");
}

int prim(int n)
{
	if (n == 0 || n == 1)
	{
		return 1;
	}
	int d;
	for (d = 2; d * d <= n; d++)
	{
		if (n % d == 0)
		{
			return 1;
		}
	}
	return 0;
}

int cmmdc(int a, int b)
{
	if (b == 0)
		return a;
	return cmmdc(b, a % b);
}

void ex1(int n)
{
	int i;
	for (i = 1; i < n; i++)
	{
		if (prim(i) == 1)
			printf("%d ", i);
	}
	printf("\n");
}

void ex2(int n)
{
	int nr = 2;
	while (n != 0)
	{
		if (prim(nr) == 1)
		{
			n = n - 1;
			printf("%d ", nr);
		}
		nr = nr + 1;
	}
	printf("\n");
}

void ex3(int n)
{
	int i, j, s = 0;
	for (i = 0; i < n / 2 + 1; i++)
	{
		s = i;
		for (j = i + 1; j <= n / 2 + 1; j++)
		{
			s = s + j;
			if (n == s)
			{
				int t;
				for (t = i; t < j; t++)
					printf("%d + ", t);
				printf("%d", j);
				printf("\n");
			}
		}
	}
}

void ex4(int n, int k, float m)
{
	if (k >= m)
	{
		printf("Fractia este supraunitara. \n");
	}
	else
	{
		int i;
		long float fract = 0;
		fract = k / m;
		printf("0.");
		for (i = 1; i <= n; i++)
		{
			fract = fract * 10;
			int fract2 = (int)fract;
			printf("%d", fract2);
			fract = fract - fract2;
		}
		printf("\n");
	}

}

void ex5(int n)
{
	int nr = 1;
	int elem_curent = 2;
	printf("1 ");
	while (nr <= n)
	{
		if (prim(elem_curent) == 1)
		{
			nr = nr + 1;
			if (nr > n)
				return;
			printf("%d ", elem_curent);
			int i;
			for (i = elem_curent - 1; i >= 1; i--)
			{
				nr = nr + 1;
				if (nr > n)
					return;
				printf("%d ", i);
			}
			elem_curent += 1;
		}
		else
		{
			int i;
			nr = nr + 1;
			if (nr > n)
				return;
			printf("%d ", elem_curent);
			for (i = 2; i <= elem_curent / 2; i++)
			{
				if (elem_curent % i == 0)
				{
					int j = 1;
					for (j = 1; j <= i; j++)
					{
						nr = nr + 1;
						if (nr > n)
							return;
						printf("%d ", i);
					}
				}
			}
			elem_curent += 1;
		}
	}
}

void ex6(int n)
{
	int v[505], nr = 2, nivel = 2;
	v[1] = 1;
	printf("1\n");
	while (nivel <= n)
	{
		int i;
		v[nr] = 1;
		for (i = nr - 1; i >= 2; i--)
			v[i] = v[i] + v[i - 1];
		for (i = 1; i <= nr; i++)
			printf("%d ", v[i]);
		printf("\n");
		nivel = nivel + 1;
		nr = nr + 1;
	}
}

float ex7(int n, float eps)
{
	float st, dr, m;
	st = 0;
	dr = n;
	while (dr - st > eps)
	{
		m = (st + dr) / 2;
		if (m * m == n)
			return m;
		else if (m * m < n)
		{
			st = m;
		}
		else
		{
			dr = m;
		}
	}
	return st;
}

int ex8(int n, int p)
{
	int nr = 0, i;
	for (i = 1; i <= n; i++)
	{
		int t = i;
		while (t % p == 0)
		{
			t = t / p;
			nr += 1;
		}
	}
	return nr;
}

int ex9()
{
	int x, p2, p5;
	p2 = 0;
	p5 = 0;
	printf("Numerele dumneavoastra sunt: ");
	scanf_s("%d", &x);
	while (x != 0)
	{
		while (x % 2 == 0)
		{
			x = x / 2;
			p2 += 1;
		}
		while (x % 5 == 0)
		{
			x = x / 5;
			p5 += 1;
		}
		scanf_s("%d", &x);
	}
	if (p2 < p5)
		return p2;
	else return p5;
}

int ex10(n)
{
	int nr = 3;
	printf("x");
	int i;
	for (i = 2; i <= n; i++)
	{
		if (i % 2 == 0)
		{
			printf("-x^%d/%d!", nr, nr);
			nr = nr + 2;
		}
		else
		{
			printf("+x^%d/%d!", nr, nr);
			nr = nr + 2;
		}
	}
	printf("\n");
}

pair ex11(pair A, pair B, pair C, pair D)
{
	float a1, b1, c1, a2, b2, c2;

	//AB: a1*x + b1*y = c1
	a1 = A.y - B.y;
	b1 = B.x - A.x;
	c1 = B.x * A.y - A.x * B.y;

	//CD: a2*x + b2*y = c2
	a2 = C.y - D.y;
	b2 = D.x - C.x;
	c2 = D.x * C.y - C.x * D.y;

	float det = a1 * b2 - a2 * b1;
	pair rez;
	if (det == 0)
	{
		rez.x = FLT_MAX;
		rez.y = FLT_MAX;
	}
	else
	{
		float x = (b2 * c1 - b1 * c2) / det;
		float y = (a1 * c2 - a2 * c1) / det;
		rez.x = x;
		rez.y = y;
	}
	return rez;
}

long ex12(int x, int n)
{
	if (n == 0)
		return 1;

	int putere = ex12(x, n / 2);

	if (n % 2 == 0)
		return putere * putere;
	else
		return putere * putere * x;
}

void ex13(int n)
{
	int d;
	for (d = 2; d * d <= n; d++)
	{
		int p = 0;
		while (n % d == 0)
		{
			p++;
			n = n / d;
		}
		printf("%d^%d * ", d, p);
	}
	printf("\n");
}

void ex14(int n)
{
	int nr = 2;
	while (prim(n - nr) != 0 || prim(nr) != 0)
		nr++;
	printf("%d + %d \n", nr, n - nr);
}

void ex15(int n)
{
	int p = 3;
	int q = 5;
	while (n != 0)
	{
		if (prim(p) == 0 && prim(q) == 0)
		{
			printf("%d %d \n", p, q);
			n--;
		}
		p++;
		q++;
	}
}

void ex16(int n)
{
	int i;
	for (i = 1; i < n; i++)
	{
		if (cmmdc(n, i) == 1)
		{
			printf("%d ", i);
		}
	}
	printf("\n");
}

void ex17()
{
	int i = 10;
	int nr = 3;
	int j;
	while (i != 0 && nr < 999)
	{
		int ok = 0;
		for (j = 2; j < nr; j++)
			if (cmmdc(nr, j) == 1)
				if(prim(j) == 1)
					ok = 1;
		if (ok == 0)
		{
			printf("%d ", nr);
			i--;
		}
		nr++;
	}
	printf("\n");
}

int main(int argc, char** argv)
{
	menu();
	int opt;
	do
	{
		scanf_s("%d", &opt);
		switch (opt)
		{
			case 1:
			{
				int n;
				printf("Introduceti numarul dorit: ");
				scanf_s("%d", &n);

				ex1(n);
				break;
			}

			case 2:
			{
				int n;
				printf("Introduceti numarul dorit: ");
				scanf_s("%d", &n);

				ex2(n);
				break;
			}

			case 3:
			{
				int n;
				printf("Introduceti numarul dorit: ");
				scanf_s("%d", &n);

				ex3(n);
				break;
			}

			case 4:
			{
				int n;
				printf("Introduceti numarul de zecimale dorit: ");
				scanf_s("%d", &n);

				printf("Introduceti numaratorul: ");
				int k;
				float m;
				scanf_s("%d", &k);

				printf("Introduceti numitorul: ");
				scanf_s("%f", &m);

				ex4(n, k, m);
				break;
			}

			case 5:
			{
				int n;
				printf("Introduceti numarul de termeni dorit: ");
				scanf_s("%d", &n);

				ex5(n);
				printf("\n");
				break;
			}

			case 6:
			{
				int n;
				printf("Introduceti numarul de linii dorit: ");
				scanf_s("%d", &n);

				ex6(n);
				break;
			}

			case 7:
			{
				int n;
				printf("Introduceti numarul dorit: ");
				scanf_s("%d", &n);

				float eps, rez7;
				printf("Introduceti precizia epsilon: ");
				scanf_s("%f", &eps);

				rez7 = ex7(n, eps);
				printf("%f\n", rez7);
				break;
			}

			case 8:
			{
				int n;
				printf("Introduceti numarul dorit: ");
				scanf_s("%d", &n);

				printf("Introduceti numarul prim: ");
				int p, rez8;
				scanf_s("%d", &p);

				rez8 = ex8(n, p);
				printf("Rezultatul este : %d \n", rez8);
				break;
			}

			case 9:
			{
				int rez9;
				rez9 = ex9();
				printf("Rezultatul este : %d\n", rez9);
				break;
			}

			case 10:
			{
				int n;
				printf("Introduceti numarul de sume partiale dorit: ");
				scanf_s("%d", &n);

				ex10(n);
				break;
			}

			case 11:
			{
				pair A, B, C, D, rez11;

				printf("Introduceti coordonatele lui A: ");
				scanf_s("%f%f", &A.x, &A.y);

				printf("Introduceti coordonatele lui B: ");
				scanf_s("%f%f", &B.x, &B.y);

				printf("Introduceti coordonatele lui C: ");
				scanf_s("%f%f", &C.x, &C.y);

				printf("Introduceti coordonatele lui D: ");
				scanf_s("%f%f", &D.x, &D.y);

				rez11 = ex11(A, B, C, D);
				printf("%f %f\n", rez11.x, rez11.y);
				break;
			}

			case 12:
			{
				int x, n;
				printf("Introduceti x: ");
				scanf_s("%d", &x);

				printf("Introduceti n: ");
				scanf_s("%d", &n);

				int rez12 = ex12(x, n);
				printf("%d\n", rez12);

				break;
			}

			case 13:
			{
				int n;
				printf("Introduceti numarul: ");
				scanf_s("%d ", &n);

				ex13(n);
				break;
			}

			case 14:
			{
				int n;
				printf("Introduceti numarul: ");
				scanf_s("%d", &n);

				if (n % 2 != 0 || n < 2)
				{
					printf("Numarul trebuie sa fie par, mai mare decat 2. \n");
					break;
				}

				ex14(n);
				break;
			}

			case 15:
			{
				int n;
				printf("Introduceti n: ");
				scanf_s("%d", &n);

				ex15(n);
				break;
			}

			case 16:
			{
				int n;
				printf("Introduceti n: ");
				scanf_s("%d", &n);

				ex16(n);
				break;
			}

			case 17:
			{
				ex17();
				break;
			}
		}
	} while (opt != 0);
}