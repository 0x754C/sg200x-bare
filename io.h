#ifndef _IO_H_
#define _IO_H_

#include "types.h"

static inline __attribute__((__always_inline__)) uint8_t read8(uint64_t addr) {
  return (*((volatile uint8_t *)(addr)));
}

static inline __attribute__((__always_inline__)) uint16_t
read16(uint64_t addr) {
  return (*((volatile uint16_t *)(addr)));
}

static inline __attribute__((__always_inline__)) uint32_t
read32(uint64_t addr) {
  return (*((volatile uint32_t *)(addr)));
}

static inline __attribute__((__always_inline__)) uint64_t
read64(uint64_t addr) {
  return (*((volatile uint64_t *)(addr)));
}

static inline __attribute__((__always_inline__)) void write8(uint64_t addr,
                                                             uint8_t value) {
  *((volatile uint8_t *)(addr)) = value;
}

static inline __attribute__((__always_inline__)) void write16(uint64_t addr,
                                                              uint16_t value) {
  *((volatile uint16_t *)(addr)) = value;
}

static inline __attribute__((__always_inline__)) void write32(uint64_t addr,
                                                              uint32_t value) {
  *((volatile uint32_t *)(addr)) = value;
}

static inline __attribute__((__always_inline__)) void write64(uint64_t addr,
                                                              uint64_t value) {
  *((volatile uint64_t *)(addr)) = value;
}

#endif
