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

const char *opencl_error_string(cl_int err)
{
  const char *strings[] = {
    "CL_SUCCESS",
    "CL_INVALID_PLATFORM",
    "CL_INVALID_CONTEXT",
    "CL_INVALID_VALUE",
    "CL_DEVICE_NOT_AVAILABLE",
    "CL_DEVICE_NOT_FOUND",
    "CL_OUT_OF_HOST_MEMORY",
    "CL_INVALID_DEVICE_TYPE",
    "UNKNOWN",
  };

  switch (err) {
  case CL_SUCCESS:
    return strings[0];
  case CL_INVALID_PLATFORM:
    return strings[1];
  case CL_INVALID_CONTEXT:
    return strings[2];
  case CL_INVALID_VALUE:
    return strings[3];
  case CL_DEVICE_NOT_AVAILABLE:
    return strings[4];
  case CL_DEVICE_NOT_FOUND:
    return strings[5];
  case CL_OUT_OF_HOST_MEMORY:
    return strings[6];
  case CL_INVALID_DEVICE_TYPE:
    return strings[7];
  default:
    return strings[8];
  }
}
 
static void print_all_devices_info(cl_platform_id platform_id)
{
    int i;
    cl_context context;
    size_t length;
    cl_platform_id platforms[16];
    cl_device_id devices[16];
    cl_int ret;
    cl_uint num_platforms;

    cl_context_properties prop[]
        = {CL_CONTEXT_PLATFORM, (cl_context_properties)platform_id, 0};

    context = clCreateContextFromType(prop, CL_DEVICE_TYPE_ALL, NULL, NULL, &ret);
    if (context == NULL) {
      printf("clCreateContextFromType: %s\n", opencl_error_string(ret));
      return;
    }

    ret = clGetContextInfo(context, CL_CONTEXT_DEVICES,
			   sizeof(devices), devices, &length);
    if (ret != CL_SUCCESS) {
      printf("clGetContextInfo: %s\n", opencl_error_string(ret));
      return;
    }
 
    int num_devices = (int)(length / sizeof(cl_device_id));
    for (i = 0; i < num_devices; i++) {
      printf("Device #%d\n", i+1);
        print_device_info(devices[i]);
    }
}

static void print_all_platforms_info()
{
    int i;
    cl_context context;
    size_t length;
    cl_platform_id platforms[16];
    cl_device_id devices[16];
    cl_int ret;
    cl_uint num_platforms;

    ret = clGetPlatformIDs(sizeof(platforms), platforms, &num_platforms);
    if (ret != CL_SUCCESS) {
      printf("clGetPlatformIds: %s\n", opencl_error_string(ret));
      return;
    }
    printf("The number of OpenCL platforms available: %u\n", num_platforms);
    if (num_platforms <= 0) {
      return;
    }

    printf("The following devices are available for use:\n");

    for (i = 0; i < num_platforms; i++) {
      printf("Platform #%d\n", i+1);
      print_all_devices_info(platforms[i]);
    }
}

int main(int argc, const char* argv[]) {
    print_all_platforms_info();
}
