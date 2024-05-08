#pragma once
#include "Core.h"

namespace summit
{
struct OHLC
{
	float Open;
	float High;
	float Low;
	float Close;
};
struct OHLCV
{
	float Open;
	float High;
	float Low;
	float Close;
	unsigned int Volume;
};

#pragma push_macro("OS")
#undef OS
class TickerType
{
private:
	enum class Type
	{
		CS		= 0,
		ADRC	= 1,
		ADRP	= 2,
		ADRR	= 3,
		UNIT	= 4,
		RIGHT	= 5,
		PFD		= 6,
		FUND	= 7,
		SP		= 8,
		WARRANT = 9,
		INDEX	= 10,
		ETF		= 11,
		ETN		= 12,
		OS		= 13,
		GDR		= 14,
		OTHER	= 15,
		NYRS	= 16,
		AGEN	= 17,
		EQLK	= 18,
		BOND	= 19,
		ADRW	= 20,
		BASKET	= 21,
		LT		= 22,
		_ERROR	= 23
	};

public:
	static const TickerType CS;
	static const TickerType ADRC;
	static const TickerType ADRP;
	static const TickerType ADRR;
	static const TickerType UNIT;
	static const TickerType RIGHT;
	static const TickerType PFD;
	static const TickerType FUND;
	static const TickerType SP;
	static const TickerType WARRANT;
	static const TickerType INDEX;
	static const TickerType ETF;
	static const TickerType ETN;
	static const TickerType OS;
	static const TickerType GDR;
	static const TickerType OTHER;
	static const TickerType NYRS;
	static const TickerType AGEN;
	static const TickerType EQLK;
	static const TickerType BOND;
	static const TickerType ADRW;
	static const TickerType BASKET;
	static const TickerType LT;
	static const TickerType _ERROR;

	constexpr TickerType(Type type) noexcept : m_type(type) {}
	constexpr TickerType(std::string_view type) noexcept : m_type(FromString(type)) {}
	constexpr TickerType(const TickerType&) noexcept = default;
	constexpr TickerType(TickerType&&) noexcept = default;
	constexpr TickerType& operator=(TickerType tt) noexcept { m_type = tt.m_type; return *this; }
	constexpr TickerType& operator=(TickerType&&) noexcept = default;
	constexpr TickerType& operator=(std::string_view str) noexcept { m_type = FromString(str); return *this; }

	constexpr bool operator==(TickerType rhs) const noexcept { return m_type == rhs.m_type; }
	constexpr bool operator==(std::string_view rhs) const noexcept { return m_type == FromString(rhs); }
	constexpr bool operator!=(TickerType rhs) const noexcept { return m_type != rhs.m_type; }
	constexpr bool operator!=(std::string_view rhs) const noexcept { return m_type != FromString(rhs); }

	ND constexpr std::string ToString() const noexcept { return m_typeStrings[static_cast<unsigned int>(m_type)]; }

	ND constexpr bool IsCS() const noexcept { return m_type == Type::CS; }
	ND constexpr bool Is_ERROR() const noexcept { return m_type == Type::_ERROR; }

private:
	static constexpr std::array m_typeStrings = 
	{ 
		"CS", "ADRC", "ADRP" "ADRR", "UNIT", "RIGHT", "PFD", "FUND", "SP", "WARRANT",
		"INDEX", "ETF", "ETN", "OS", "GDR", "OTHER", "NYRS", "AGEN", "EQLK", "BOND",
		"ADRW", "BASKET", "LT", "_ERROR" 
	};
	static constexpr Type FromString(std::string_view str) noexcept
	{
		for (size_t iii = 0; iii < m_typeStrings.size(); ++iii)
		{
			if (str.compare(m_typeStrings[iii]) == 0)
				return static_cast<Type>(iii);
		}
		return Type::_ERROR;
	}

	Type m_type;
};
#pragma pop_macro("OS")

enum class ExchangeType
{
	XNYS
};
enum class CurrencyType
{
	USD
};
enum class MarketType
{
	STOCKS
};
struct TickerInfo
{
	std::string Ticker;
	std::string Name;
	TickerType Type;
	MarketType Market;
	ExchangeType PrimaryExchange;
	CurrencyType Currency;
	std::string CIK;
	std::string CompositeFigi;
	std::string ShareClassFigi;
	bool Active;
};

} // namespace summit



template <>
struct std::formatter<summit::TickerType> : std::formatter<std::string> {
	auto format(summit::TickerType tt, format_context& ctx) const
	{
		return formatter<string>::format(tt.ToString(), ctx);
	}
};