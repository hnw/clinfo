#include "config.h"
#include <stdio.h>

# if defined(HAVE_WINDOWS_H) && defined(_WIN32)
#   include <windows.h>
# endif
# ifdef HAVE_CL_CL_H
#   include <CL/cl.h>
# elif defined(HAVE_OPENCL_OPENCL_H)
#   include <OpenCL/opencl.h>
# else
#   error no cl.h nor opencl.h
# endif

static void print_device_info(cl_device_id device) {
    char name[128];
    char vendor[128];
    cl_uint n_compute_unit, max_clock_freq;
    cl_ulong mem_size;
 
    clGetDeviceInfo(device, CL_DEVICE_NAME, 128, name, NULL);
    clGetDeviceInfo(device, CL_DEVICE_VENDOR, 128, vendor, NULL);
    clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &n_compute_unit, NULL);
    clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_uint), &max_clock_freq, NULL);
    clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &mem_size, NULL);

    printf("  %-14s %s\n  %-14s %s\n  %-14s %u\n  %-14s %u MHz\n  %-14s %llu MB\n", "Name:", name, "Vendor:", vendor, "Compute unit:", n_compute_unit, "Clock freq.:", max_clock_freq, "Mem. size:", mem_size/(1<<20));
}
 
static void print_all_devices_info()
{
    int i;
    cl_context context;
    size_t length;
    cl_device_id devices[16];

    context = clCreateContextFromType(0, CL_DEVICE_TYPE_ALL, NULL, NULL, NULL);
    clGetContextInfo(
         context, CL_CONTEXT_DEVICES, sizeof(devices), devices, &length);
 
    printf("The following devices are available for use:\n");
    int num_devices = (int)(length / sizeof(cl_device_id));
    for (i = 0; i < num_devices; i++) {
      printf("#%d\n", i+1);
        print_device_info(devices[i]);
    }
}

int main(int argc, const char* argv[]) {
    print_all_devices_info();
}
