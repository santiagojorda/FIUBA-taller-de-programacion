#ifdef wrapsocks
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

ssize_t __real_send(int sockfd, const void* buf, size_t len, int flags);
ssize_t __real_recv(int sockfd, void* buf, size_t len, int flags);

static size_t _random(size_t max) {
    static bool is_random_initialized = false;

    if (!is_random_initialized) {
        srand(time(NULL));
        is_random_initialized = true;
    }

    return 1 + (rand() % max);
}

// cppcheck-suppress unusedFunction
ssize_t __wrap_send(int sockfd, const void* buf, size_t len, int flags) {
    size_t modified_len = len;
    if (len != 0) {
        modified_len = _random(len);
    }
    return __real_send(sockfd, buf, modified_len, flags);
}

// cppcheck-suppress unusedFunction
ssize_t __wrap_recv(int sockfd, void* buf, size_t len, int flags) {
    size_t modified_len = len;
    if (len != 0) {
        modified_len = _random(len);
    }
    return __real_recv(sockfd, buf, modified_len, flags);
}

#ifdef __cplusplus
}
#endif

#endif  // end ifdef
