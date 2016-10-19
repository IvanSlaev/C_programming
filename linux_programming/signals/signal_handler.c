typedef void (*sighandler_t)(int)

void B(int) {
}

void C(int) {
}

sighandler_t signal(int, sighandler_t b) {
	
  return b;
}

signal(10, B);
signal(34, C);
