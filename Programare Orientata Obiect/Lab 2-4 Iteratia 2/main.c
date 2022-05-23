#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "ui.h"
#include "teste.h"
#include "service.h"

int main()
{
	{
		Repo* r = (Repo*)malloc(sizeof(Repo));
		Srv* s = (Srv*)malloc(sizeof(Srv));
		s->r = r;

		r->elems = creareVector();
		runTeste(s);
		distrugeVector(r->elems);
		free(r->elems);

		r->elems = creareVector();
		Ui* cons = (Ui*)malloc(sizeof(Ui));
		cons->s = s;

		run(cons);

		distrugeVector(r->elems);
		free(r->elems);

		free(r);
		free(s);
		free(cons);
	}
	_CrtDumpMemoryLeaks();
	return 0;
}