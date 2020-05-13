/**
 * Refer to the interceptor.h file for all documentation.
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <stdint.h>

#include "../inc/interceptor.h"

namespace cwhite {
// CabacCapture functions
CabacCapture::CabacCapture(std::string filename) {
  m_file = std::fstream(filename, std::ios::out | std::ios::binary);
}

CabacCapture::~CabacCapture() {
  // the last byte will never be written, so flush it to the file.
  m_file << m_next_byte;

  m_file.close();
}

void CabacCapture::captureCabac(uint32_t val) {
  m_next_byte |= val << (m_bit_size%8);

  if ((++m_bit_size)%8 == 0) {
    m_file << m_next_byte;
    m_next_byte = 0;
  }
}

// CabacMock functions
CabacMock::CabacMock(std::string filename) {
  m_file = std::fstream(filename, std::ios::in | std::ios::binary);
}

CabacMock::~CabacMock() {
  m_file.close();
}

int32_t CabacMock::getNextBit() {
  if (m_bit_index%8 == 0) {
    m_file >> m_next_byte;
  }

  uint32_t ret = (m_next_byte >> (m_bit_index%8)) & 1;
  ++m_bit_index;

  return ret;
}

} // namespace cwhite