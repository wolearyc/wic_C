// ------------------------------------------------------------------------------------------------
// File:			Pair.h
// Author:			Will O'Leary
// Documentation:
//-------------------------------------------------------------------------------------------------

#ifndef PAIR_H
#define PAIR_H
#include <math.h>
#include "Pairf.h"
namespace wick
{
	class Pair
	{
	public:

		int x_;
		int y_;

		// Constructors.
		Pair(int x, int y);
		Pair(const Pair& other);
		Pair(const Pairf& pairf);
		Pair();

		// Methods determining distance and angle.
		double distance(const Pair& other);
		double angle(const Pair& other);
		double angleInDegrees(const Pair& other);

		// Operator overloads.
		Pair operator+(const Pair& other) const;
		Pair operator-(const Pair& other) const;
		Pair operator*(const Pair& other) const;
		Pair operator/(const Pair& other) const;
		Pair operator%(const Pair& other) const;
		bool operator==(const Pair& other);
		bool operator!=(const Pair& other) const;
		Pair operator+(const int i) const;
		Pair operator-(const int i) const;
		Pair operator*(const int i) const;
		Pair operator/(const int i) const;
		Pair operator%(const int i) const;

		Pairf operator+(const Pairf& other) const;
		Pairf operator-(const Pairf& other) const;
		Pairf operator*(const Pairf& other) const;
		Pairf operator/(const Pairf& other) const;
        Pair operator+(const float i) const;
		Pair operator-(const float i) const;
		Pair operator*(const float i) const;
		Pair operator/(const float i) const;
	};
}
#endif
