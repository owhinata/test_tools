
#include "runtime_error_stub.h"

static const char* message_ = "No Error";
static int parameter_ = 0;
static const char* file_ = 0;
static int line_ = 0;

void RuntimeErrorStub_Reset(void) {
  message_ = "No Error";
  parameter_ = 0;
}

const char* RuntimeErrorStub_GetLastError(void) {
  return message_;
}

int RuntimeErrorStub_GetLastParameter(void) {
  return parameter_;
}

void RuntimeError(const char* m, int p, const char* f, int l) {
  message_ = m;
  parameter_ = p;
  file_ = f;
  line_ = l;
}
