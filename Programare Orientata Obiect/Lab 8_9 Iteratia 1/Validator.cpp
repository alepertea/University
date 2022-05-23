#include "Validator.h"
#include <string.h>
#include <sstream>

using std::string;
using std::ostream;

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

void Validator::validate(const Medicament& m)
{
	vector<string> erori;
	if (m.getDenumire().size() == 0)
	{
		erori.push_back("Denumire invalida! \n");
	}
	if (m.getProducator().size() == 0)
	{
		erori.push_back("Producator invalid! \n");
	}
	if (m.getPret() <= 0)
	{
		erori.push_back("Pret invalid! \n");
	}
	if (m.getSubstantaActiva() <= 0)
	{
		erori.push_back("Cantitate de substanta activa invalida! \n");
	}

	if (erori.size() > 0)
		throw ValidateException(erori);
}