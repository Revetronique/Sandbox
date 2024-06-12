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
      template <typename T> void PROGMEM_readAnything (const T* src, T& dst){
        memcpy_P(&dst, src, sizeof(T));
      }
      template <typename T> T PROGMEM_getAnything (const T* src){
        static T temp;
        memcpy_P(&temp, src, sizeof(T));
        return temp;
      }
  };
}

#endif