#ifndef PATTERN_RECOGNIZE_CRITERIANODE_H
#define PATTERN_RECOGNIZE_CRITERIANODE_H

#include <vector>
#include <stdint.h>
#include <cmath>

static const int sensivity_koef = 16;
static const double SIMILARITY_THRESHOLD = 0.9;

struct CriteriaNode {
	uint16_t id;
	double coo[3];
	uint16_t RepeatCount;
	std::vector<uint16_t> nextIds;


	const double compareWith(double coordinates[3])
	{
		float squared_diff = 0.0;
		for (int i = 0; i < 3; ++i) {
			squared_diff += ((*this)[i]-coordinates[i])*((*this)[i]-coordinates[i]);
		}
		return exp(-squared_diff/(2*sensivity_koef));
	}

	const bool closeTo(double coordinates[3])
	{
		return this->compareWith(coordinates)>SIMILARITY_THRESHOLD;
	}

	const double& operator[](const unsigned int &i) const {
		switch (i) {
			case 0: return coo[0];
			case 1: return coo[1];
			case 2: return coo[2];
			default:
				throw new std::logic_error("Out of range error: no such index in type");
		}
	}

	double& operator[](const unsigned int &i) {
		return const_cast<double &>(static_cast<const CriteriaNode&>(*this)[i]);
	}

	const uint16_t& childId(const unsigned int &i) const {
		return nextIds[i];
	}

	uint16_t& childId(const unsigned int &i) {
		return nextIds[i];
	}

	static CriteriaNode getEmpty() {
		//A lill' monkey code, but it's needed for now
		CriteriaNode res;
		res.id=0;
		res.coo[0]=0;
		res.coo[1]=0;
		res.coo[2]=0;
		res.RepeatCount = 0;
		return res;
	}

	static CriteriaNode getByDimensions(double data[3]) {
		CriteriaNode res;
		res.coo[0] = data[0];
		res.coo[1] = data[1];
		res.coo[2] = data[2];
		return res;
	}
};

#include <vector>
#include <stdint.h>
#include <stdexcept>

#endif //PATTERN_RECOGNIZE_CRITERIANODE_H
