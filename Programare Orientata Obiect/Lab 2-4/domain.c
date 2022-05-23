#include "domain.h"
#include <stdio.h>
#include <string.h>

void initializare()
{
	len = 0;
	int i;
	for (i = 1; i <= 30; i++)
	{
		strcpy_s(p[i].nume, 1, "");
		strcpy_s(p[i].prenume, 1, "");
		p[i].scor = 0;
	}
}