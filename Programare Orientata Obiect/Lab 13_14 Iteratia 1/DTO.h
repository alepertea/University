#pragma once

using namespace std;

class DTO
{
private:
	int substantaActiva;
	int nrMedicamente;

public:
	DTO(const int& substantaActiva, const int& nrMedicamente) :substantaActiva{ substantaActiva }, nrMedicamente{ nrMedicamente }{}
	~DTO() = default;

	int getSubstantaActiva() const;
	int getNrMedicamente() const;
	void setNrMedicamente(int value);
};