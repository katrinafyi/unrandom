#include <stdlib.h>
#include <stdio.h>

#include <sys/random.h>

#undef NDEBUG
#include <assert.h>

#define assert2(cond) \
{\
  assert(cond);\
  printf("%s : ok\n", #cond);\
}

int main() {
  srand(1);
  int x = rand();
  srand(2);
  int y = rand();
  assert2(x == y);

  unsigned long data, x1, x2;
  getrandom(&data, sizeof(data), 0);
  x1 = data;
  getrandom(&data, sizeof(data), 0);
  x2 = data;

  printf("%0lx %0lx\n", x1, x2);

  assert2(x1 == 0x8621d6cc92f81cce);
  assert2(x2 == 0x902ccb701fd13acc);

  unsigned char uuid[16];
  for (unsigned i = 0; i < 5; i++) {
    getrandom(&uuid, sizeof(uuid), 0);
    assert2(uuid[0] >> 2 == 0b110011);
  }

  return 0;
}
