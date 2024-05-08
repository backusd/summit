#include "pch.h"
#include "Data.h"


namespace summit
{
	// ===========================================================================
	// Ticker Type
	const TickerType TickerType::CS = TickerType(TickerType::Type::CS);
	const TickerType TickerType::ADRC = TickerType(TickerType::Type::ADRC);
	const TickerType TickerType::ADRP = TickerType(TickerType::Type::ADRP);
	const TickerType TickerType::ADRR = TickerType(TickerType::Type::ADRR);
	const TickerType TickerType::UNIT = TickerType(TickerType::Type::UNIT);
	const TickerType TickerType::RIGHT = TickerType(TickerType::Type::RIGHT);
	const TickerType TickerType::PFD = TickerType(TickerType::Type::PFD);
	const TickerType TickerType::FUND = TickerType(TickerType::Type::FUND);
	const TickerType TickerType::SP = TickerType(TickerType::Type::SP);
	const TickerType TickerType::WARRANT = TickerType(TickerType::Type::WARRANT);
	const TickerType TickerType::INDEX = TickerType(TickerType::Type::INDEX);
	const TickerType TickerType::ETF = TickerType(TickerType::Type::ETF);
	const TickerType TickerType::ETN = TickerType(TickerType::Type::ETN);
#pragma push_macro("OS")
#undef OS
	const TickerType TickerType::OS = TickerType(TickerType::Type::OS);
#pragma pop_macro("OS")
	const TickerType TickerType::GDR = TickerType(TickerType::Type::GDR);
	const TickerType TickerType::OTHER = TickerType(TickerType::Type::OTHER);
	const TickerType TickerType::NYRS = TickerType(TickerType::Type::NYRS);
	const TickerType TickerType::AGEN = TickerType(TickerType::Type::AGEN);
	const TickerType TickerType::EQLK = TickerType(TickerType::Type::EQLK);
	const TickerType TickerType::BOND = TickerType(TickerType::Type::BOND);
	const TickerType TickerType::ADRW = TickerType(TickerType::Type::ADRW);
	const TickerType TickerType::BASKET = TickerType(TickerType::Type::BASKET);
	const TickerType TickerType::LT = TickerType(TickerType::Type::LT);
	const TickerType TickerType::_ERROR = TickerType(TickerType::Type::_ERROR);
}