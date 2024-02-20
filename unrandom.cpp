#include <cassert>
#include <cstring>

#include <random>
#include <dlfcn.h>

void (*orig_srand)(unsigned int seed);

std::mt19937_64 gen64{};
std::independent_bits_engine<std::mt19937_64, 8, unsigned short> genbyte{gen64};

extern "C" {

// https://github.com/whitequark/unrandom

void srand(unsigned int seed) {
  if(!orig_srand) {
    orig_srand = reinterpret_cast<decltype(orig_srand)>(dlsym(RTLD_NEXT, "srand"));
    assert(orig_srand);
  }
  orig_srand(0);
}

ssize_t getrandom(void* buf, size_t buflen, unsigned int flags) {

  unsigned char* cbuf = reinterpret_cast<unsigned char*>(buf);

  for (size_t i = 0; i < buflen; i++) {
    cbuf[i] = genbyte();

    if (i == 0 && buflen >= 8) {
      cbuf[i] &= 0b00000011;
      // 'z' in b64
      // https://en.wikipedia.org/wiki/Base64#Base64_table_from_RFC_4648
      cbuf[i] |= 0b110011 << 2;
    }
  }

  return buflen;
}

}
