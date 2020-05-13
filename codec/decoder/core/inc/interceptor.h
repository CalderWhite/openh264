/**
 * This code will intercept the outputted values from the CABAC decoder before they are sent off
 * to be decompressed. This can allow developers to test out their own lossless compression algorithms.
 *
 * As a secondary function, this code can also recieve a raw stream of bytes to test the integrity of the
 * data captured by this code. For example, if you were to run this code and capture the bitstream into a file,
 * this code could also be used to turn that file into a raw YUV file. That YUV file can then be encoded back into
 * h264 and tested to make sure the video is still intact.
 */
#pragma once

#include <fstream>
#include <stdint.h>

namespace cwhite {
// Class for capturing the outputted bits from the cabac decoder
class CabacCapture {
public:
  CabacCapture(std::string filename);
  ~CabacCapture();

  // Captures an outputted bit from the cabac decoder.
  // Once 8 bits have been captured, a byte is written to the outgoing file
  void captureCabac(uint32_t val);

private:
  // The number of total bits in the outgoing bitstream
  uint64_t m_bit_size;

  // The next byte to be written to the file which is currently being constructed
  uint8_t m_next_byte;

  std::fstream m_file;
};

// Class for replacing the outputted bits of the decoder with those from a given file
class CabacMock {
public:
  CabacMock(std::string filename);
  ~CabacMock();

  int32_t getNextBit();

private:
  // The current byte that is being read, which will be updated after
  // each of its 8 bits have been read.
  uint8_t m_next_byte;

  // the current bit's index in the entire bitstream
  uint64_t m_bit_index = 0;

  std::fstream m_file;
};
} // namespace cwhite