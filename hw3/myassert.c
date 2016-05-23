int failed = 0;

int myassert(int b) {
  if (b == 0) {
    failed = 1;
    return failed;
  }
  return 0;
}

void checkasserts() {
  if (!failed) {
    printf ("TEST SUCCESSFULLY COMPLETED.\n");
  }
}