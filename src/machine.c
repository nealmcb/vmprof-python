#include "machine.h"

#include "vmprof.h"
#include <stdio.h>

int vmp_machine_bits(void)
{
    return sizeof(void*)*8;
}

const char * vmp_machine_os_name(void)
{
#ifdef _WIN32
   #ifdef _WIN64
      return "win64";
   #endif
  return "win32";
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_MAC
        return "mac os x";
    #endif
#elif __linux__
    return "linux";
#else
    #error "Unknown compiler"
#endif
}

long vmp_fd_to_path(int fd, char * buffer, long buffer_len)
{
#ifdef VMPROF_LINUX
    char proffs[24];
    (void)snprintf(proffs, 24, "/proc/self/fd/%d", fd);
    return readlink(proffs, buffer, buffer_len);
#endif
    return -1;
}
