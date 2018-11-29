#include <cstdio>
#include <hip/hip_runtime_api.h>
#ifdef __HIP_PLATFORM_HCC__
#include <hiprand/hiprand.h>
#else
#include <curand.h>
#endif

// Workspace
extern void* workspace;
// RNG generator
#ifdef __HIP_PLATFORM_HCC__
extern hiprandGenerator_t rng;
#else
extern curandGenerator_t rng;
#endif

#define HIP_CHECK(err)                                              \
{                                                                   \
    if(err != hipSuccess)                                           \
    {                                                               \
        fprintf(stderr, "HIP ERROR %s (%d) in file %s ; line %d\n", \
                hipGetErrorString(err),                             \
                err,                                                \
                __FILE__,                                           \
                __LINE__);                                          \
                                                                    \
        size_t free_mem;                                            \
        size_t total_mem;                                           \
        hipMemGetInfo(&free_mem, &total_mem);                       \
                                                                    \
        fprintf(stderr, "%lu (%lu) MByte\n",                        \
                free_mem >> 20, total_mem >> 20);                   \
                                                                    \
        exit(1);                                                    \
    }                                                               \
}

#define RETURN_IF_HPCG_ERROR(err)   \
{                                   \
    if(err != 0)                    \
    {                               \
        return err;                 \
    }                               \
}
