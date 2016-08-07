#pragma once

#include "core/types.h"
#include "core/fixed.h"
#include "util/MathFunctions.h"

namespace System
{
	struct TimeSpan
	{
	public:

		TimeSpan(int64 ticks = 0);

		TimeSpan(int hours, int minutes, int seconds);

		TimeSpan(int days, int hours, int minutes, int seconds);

		TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds);

		TimeSpan Add(const TimeSpan &other);

		static int64 CalculateTicks(int days, int hours, int minutes, int seconds, int milliseconds);

		int Days() const;

		int Hours() const;

		int Milliseconds() const;

		int Minutes() const;

		int Seconds() const;

		int64 Ticks() const;

		float TotalDays() const;

		float TotalHours() const;

		float TotalMilliseconds() const;

		float TotalMinutes() const;

		float TotalSeconds() const;

		static TimeSpan FromDays(float value);

		static TimeSpan FromHours(float value);

		static TimeSpan FromMinutes(float value);

		static TimeSpan FromSeconds(float value);

		static TimeSpan FromMilliseconds(float value);

		static TimeSpan FromTicks(int64 ticks);

	public:

		TimeSpan operator+(const TimeSpan &other) const;

		TimeSpan operator-(const TimeSpan &other) const;

		TimeSpan operator+=(const TimeSpan &other);

		TimeSpan operator-=(const TimeSpan &other);

		bool operator==(const TimeSpan &other) const;

		bool operator!=(const TimeSpan &other) const;

		bool operator<(const TimeSpan &other) const;

		bool operator>(const TimeSpan &other) const;

		bool operator<=(const TimeSpan &other) const;

		bool operator>=(const TimeSpan &other) const;

	private:

		static TimeSpan From(float value, int64 tickMultiplicator);

	public:

		static const int64 TicksPerDay         = 8640000000000L;
		static const int64 TicksPerHour        =  360000000000L;
		static const int64 TicksPerMinute      =    6000000000L;
		static const int64 TicksPerSecond      =     100000000L;
		static const int64 TicksPerMillisecond =        100000L;
		static const TimeSpan Zero;

	private:
		
		int64 ticks;
	};

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan::TimeSpan(int64 ticks)
	{
		this->ticks = ticks;
	}

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan::TimeSpan(int hours, int minutes, int seconds)
	{
		ticks = CalculateTicks(0, hours, minutes, seconds, 0);
	}

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan::TimeSpan(int days, int hours, int minutes, int seconds)
	{
		ticks = CalculateTicks(days, hours, minutes, seconds, 0);
	}

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan::TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds)
	{
		ticks = CalculateTicks(days, hours, minutes, seconds, milliseconds);
	}

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan TimeSpan::Add(const TimeSpan &other)
	{
		return TimeSpan(ticks + other.ticks);
	}

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan TimeSpan::FromTicks(int64 ticks)
	{
		return TimeSpan(ticks);
	}

	//-------------------------------------------------------------------------------------------------
	finline int TimeSpan::Days() const
	{
		return (int) (ticks / TicksPerDay);
	}

	//-------------------------------------------------------------------------------------------------
	finline int TimeSpan::Hours() const 
	{
		return (int) (ticks % TicksPerDay / TicksPerHour);
	}

	//-------------------------------------------------------------------------------------------------
	finline int TimeSpan::Milliseconds() const
	{
		return (int) (ticks % TicksPerSecond / TicksPerMillisecond);
	}

	//-------------------------------------------------------------------------------------------------
	finline int TimeSpan::Minutes() const
	{
		return (int) (ticks % TicksPerHour / TicksPerMinute);
	}

	//-------------------------------------------------------------------------------------------------
	finline int TimeSpan::Seconds() const
	{
		return (int) (ticks % TicksPerMinute / TicksPerSecond);
	}

	//-------------------------------------------------------------------------------------------------
	finline int64 TimeSpan::Ticks() const
	{
		return ticks;
	}

	//-------------------------------------------------------------------------------------------------
	finline float TimeSpan::TotalDays() const
	{
		return (float)ticks / TicksPerDay;
	}

	//-------------------------------------------------------------------------------------------------
	finline float TimeSpan::TotalHours() const
	{
		return (float)ticks / TicksPerHour;
	}

	//-------------------------------------------------------------------------------------------------
	finline float TimeSpan::TotalMilliseconds() const
	{
		return (float)ticks / TicksPerMillisecond;
	}

	//-------------------------------------------------------------------------------------------------
	finline float TimeSpan::TotalMinutes() const
	{
		return (float)ticks / TicksPerMinute;
	}

	//-------------------------------------------------------------------------------------------------
	finline float TimeSpan::TotalSeconds() const
	{
		return (float)ticks / TicksPerSecond;
	}

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan TimeSpan::operator+(const TimeSpan &other) const
	{
		return TimeSpan(ticks + other.Ticks());
	}

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan TimeSpan::operator-(const TimeSpan &other) const
	{
		return TimeSpan(ticks - other.Ticks());
	}

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan TimeSpan::operator+=(const TimeSpan &other)
	{
		ticks += other.Ticks();
		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan TimeSpan::operator-=(const TimeSpan &other)
	{
		ticks -= other.Ticks();
		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	finline bool TimeSpan::operator==(const TimeSpan &other) const
	{
		return ticks == other.Ticks();
	}

	//-------------------------------------------------------------------------------------------------
	finline bool TimeSpan::operator!=(const TimeSpan &other) const
	{
		return !(*this == other);
	}

	//-------------------------------------------------------------------------------------------------
	finline bool TimeSpan::operator<(const TimeSpan &other) const
	{
		return ticks < other.Ticks();
	}

	//-------------------------------------------------------------------------------------------------
	finline bool TimeSpan::operator>(const TimeSpan &other) const
	{
		return ticks > other.Ticks();
	}

	//-------------------------------------------------------------------------------------------------
	finline bool TimeSpan::operator<=(const TimeSpan &other) const
	{
		return !(*this > other);
	}

	//-------------------------------------------------------------------------------------------------
	finline bool TimeSpan::operator>=(const TimeSpan &other) const
	{
		return !(*this < other);
	}

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan TimeSpan::FromDays(float value)
	{
		return From(value, TicksPerDay);
	}

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan TimeSpan::FromHours(float value)
	{
		return From(value, TicksPerHour);
	}

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan TimeSpan::FromMinutes(float value)
	{
		return From(value, TicksPerMinute);
	}

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan TimeSpan::FromSeconds(float value)
	{
		return From(value, TicksPerSecond);
	}

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan TimeSpan::FromMilliseconds(float value)
	{
		return From(value, TicksPerMillisecond);
	}

	//-------------------------------------------------------------------------------------------------
	finline TimeSpan TimeSpan::From(float value, int64 tickMultiplicator) 
	{
		value = (value * (tickMultiplicator / TicksPerMillisecond));
		int64 val = (int64) Math::Round(value);
		return TimeSpan (val * TicksPerMillisecond);
	}
}
