
#ifndef UTIL_RUNTIME_ERROR_H_
#define UTIL_RUNTIME_ERROR_H_

#define RUNTIME_ERROR(description, parameter) \
  RuntimeError(description, parameter, __FILE__, __LINE__)

#if defined(__cplusplus)
extern "C" {
#endif

void RuntimeError(const char* message, int parameter,
                  const char* file, int line);

#ifdef __cplusplus
}
#endif

#endif  // UTIL_RUNTIME_ERROR_H_
