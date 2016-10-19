typedef void (*bptr_t)(int)

void B(int) {
}

void C(int) {
}

bptr_t A(int, bptr_t b) {
  b(10);

  return b;
}

A(10, B);
A(34, C);
