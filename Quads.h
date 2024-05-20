#pragma once

#include "Primitive.h"


class Quad : public Primitive
{
public:
	Quad();
	bool operator==(const Quad& other) const;
};




