
#ifndef TEST_MOCKS_RUNTIME_ERROR_STUB_H_
#define TEST_MOCKS_RUNTIME_ERROR_STUB_H_

#include "util/runtime_error.h"

#if defined(__cplusplus)
extern "C" {
#endif

void RuntimeErrorStub_Reset(void);
const char* RuntimeErrorStub_GetLastError(void);
int RuntimeErrorStub_GetLastParameter(void);

#ifdef __cplusplus
}
#endif

#endif  // TEST_MOCKS_RUNTIME_ERROR_STUB_H_

