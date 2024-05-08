#pragma once
#include "Core.h"
#include "Data.h"

namespace summit
{
class PolygonAPI
{
public:

private:
	static inline PolygonAPI& Instance()
	{
		static PolygonAPI api{};
		return api;
	}
};
}