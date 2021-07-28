#pragma once

#include <cstdint>

// The fundamental types our emulator will use.

namespace emulatte
{
	// Simple typedefs so things are more readable.
	// The 6502 being mainly 8-bit means we're built
	// around bytes, and words are a bit more rare.
	using byte = uint8_t;
	using word = uint16_t;

	// Simple wrapper for a word that will handle
	// CPU memory mapping automatically when it is
	// converted.
	struct address
	{
		word value = 0x0000;

		address(word value) :
			value{ value }
		{};
		// Helper constructor for making an address
		// from a Lo-Hi byte pair.
		address(byte lo, byte hi) :
			value{ (word(hi) << 8) + lo }
		{};

		// Having an impliict constructor from word
		// and a conversion operator will allow us
		// to treat an address almost exactly like
		// a word, while letting us have this extra
		// functionality.
		operator word()
		{
			if (value >= 0x0800 && value < 0x2000)
			{
				return value % 0x0800;
			}
			else if (value >= 0x2008 && value < 0x4000)
			{
				return value % 8 + 0x2000;
			}
			else
			{
				return value;
			}
		};
	};
};