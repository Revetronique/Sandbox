#ifndef _HELPER_h
#define _HELPER_h

namespace programming {
  class helper {
    public:
      // https://stackoverflow.com/questions/6457551/hex-character-to-int-in-c
      inline static uint8_t convertHexCharToInt(char c) {
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
  };
}

#endif