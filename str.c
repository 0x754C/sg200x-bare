#include "str.h"
#include "types.h"

uint64_t num32tohexstr(uint32_t n) {
  uint64_t ret = 0;
  uint8_t shi, sho;
  uint64_t tmp;
  shi = 28;
  sho = 0;

  while (sho <= 56) {
    tmp = (n & (0xF << shi)) >> shi;
    if (tmp < 10) {
      tmp += '0';
    } else {
      tmp -= 10;
      tmp += 'A';
    }
    ret |= tmp << sho;
    shi -= 4;
    sho += 8;
  }
  return ret;
}
