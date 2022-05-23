#include <stdio.h>

int main(int argc, char** argv)
{
	int n, nr;
	printf("n = ");
	scanf_s("%d", &n);
	int s = 0;
	int i;
	for (i = 0; i < n; i++)
	{
		scanf_s("%d", &nr);
		s = s + nr;
	}
	printf("Suma este %d", s);

	return 0;
}