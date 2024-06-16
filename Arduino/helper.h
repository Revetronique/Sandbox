#ifndef _HELPER_h
#define _HELPER_h

namespace programming {
	class helper {
	public:
		// https://stackoverflow.com/questions/6457551/hex-character-to-int-in-c
		inline static unsigned char convertHexCharToInt(char c) {
			return (c >= 'A') ? (c >= 'a') ? (c - 'a' + 10) : (c - 'A' + 10) : (c - '0');
		}
		inline static char convertIntToHexChar(unsigned char n) {
			return (n > 9) ? (char)(n - 10 + 'A') : (char)(n + '0');
		}

		template<typename T>
		static T decodeHex(const char* hex, unsigned char digit, bool is_big = true) {
			T ret = 0;
			// conversion
			for (int i = 0; i < digit; i++) {
				// number of shift. each hex data is equal to 4-digit binary
				unsigned int shift = is_big ? 4 * (digit - 1 - i) : 4 * i;
				// logical add
				ret |= (T)((convertHexCharToInt(hex[i]) & 0x0F) << shift);
			}
			return ret;
		}

		//https://arduino.stackexchange.com/questions/13545/using-progmem-to-store-array-of-structs
		template <typename T>
		static void PROGMEM_readAnything(const T* src, T& dst) {
			memcpy_P(&dst, src, sizeof(T));
		}
		template <typename T>
		static T PROGMEM_getAnything(const T* src) {
			static T temp;
			memcpy_P(&temp, src, sizeof(T));
			return temp;
		}

		//https://github.com/RobTillaart/bitHelpers/blob/master/bitHelpers.cpp
		template<typename T>
		static T reverseBits(T value) {
			// number of bits in an argument
			auto num_bits = sizeof(T) * 8;
			// bit reversal
			for (T i = 1; i <= (num_bits >> 2); i <<= 1) {    //1, 2, 4, 8, 16, 32
				// bit mask (lower and higher)
				//0101..., 0011..., 00001111..., 0000000011111111,
				T mask_low = 0, mask_high = 0;
				// digits in mask unit 
				auto digits = 2 * i;
				// generate lower mask
				for (auto j = 0; j < num_bits / digits; j++) {
					// mask bits
					T bits = (1 << i) - 1;  //2 - 1, 4 - 1, 16 - 1, 256 - 1,...
					// logical adding of mask bit
					mask_low |= bits << (j * digits); // added in each n-th digit
				}
				// bitwise to create upper mask
				mask_high = ~mask_low;
				// split the value with the bit masks, and then swap the upper and lower one.
				value = ((value & mask_high) >> i) | ((value & mask_low) << i);
			}
			// split into upper and lower half, and then switch them.
			return (value >> (num_bits >> 1)) | (value << (num_bits >> 1));
		}
	};
}

#endif