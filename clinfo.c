#include "config.h"
#include <stdio.h>
#include <string.h>

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

void print_platform_info(cl_platform_id platform_id)
{
    char name[128];
    char vendor[128];
    char profile[128];
    char version[128];
 
    clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, 128, name, NULL);
    clGetPlatformInfo(platform_id, CL_PLATFORM_VENDOR, 128, vendor, NULL);
    clGetPlatformInfo(platform_id, CL_PLATFORM_PROFILE, 128, profile, NULL);
    clGetPlatformInfo(platform_id, CL_PLATFORM_VERSION, 128, version, NULL);

    printf("  %-13s %s\n"
	   "  %-13s %s\n"
	   "  %-13s %s\n"
	   "  %-13s %s\n",
	   "Name:", name,
	   "Vendor:", vendor,
	   "Profile:", profile,
	   "Version:", version);
	   
}

void print_device_info(cl_device_id device)
{
    char name[128], vendor[128], profile[128], extensions[1024];
    cl_uint n_compute_units, max_clock_freq;
    cl_ulong mem_size;
 
    clGetDeviceInfo(device, CL_DEVICE_NAME, 128, name, NULL);
    clGetDeviceInfo(device, CL_DEVICE_VENDOR, 128, vendor, NULL);
    clGetDeviceInfo(device, CL_DEVICE_PROFILE, 128, profile, NULL);
    clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, 1024, extensions, NULL);
    clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &n_compute_units, NULL);
    clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_uint), &max_clock_freq, NULL);
    clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &mem_size, NULL);
      
    printf("  %-13s %s\n"
	   "  %-13s %s\n"
	   "  %-13s %s\n"
	   "  %-13s %u\n"
	   "  %-13s %u MHz\n"
	   "  %-13s %lu MB\n",
	   "Name:", name,
	   "Vendor:", vendor,
	   "Profile:", profile,
	   "OpenCL CU:", n_compute_units,
	   "Clock speed:", max_clock_freq,
	   "Memory:", (long)(mem_size/(1<<20))
	   );
    if (strlen(extensions) > 0) {
      const char *sep = " ";
      char *word, *brkt;

      printf("  Extensions:\n");
      for (word = strtok_r(extensions, sep, &brkt);
	   word;
	   word = strtok_r(NULL, sep, &brkt)) {
	printf("    %s\n", word);
      }
    }
}

const char *opencl_error_strings[] = {
  "CL_SUCCESS",
  "CL_INVALID_PLATFORM",
  "CL_INVALID_CONTEXT",
  "CL_INVALID_VALUE",
  "CL_DEVICE_NOT_AVAILABLE",
  "CL_DEVICE_NOT_FOUND",
  "CL_OUT_OF_HOST_MEMORY",
  "CL_INVALID_DEVICE_TYPE",
  "CL_PLATFORM_NOT_FOUND_KHR",
  "UNKNOWN",
};

const char *opencl_error_string(cl_int err)
{
  switch (err) {
  case CL_SUCCESS:
    return opencl_error_strings[0];
  case CL_INVALID_PLATFORM:
    return opencl_error_strings[1];
  case CL_INVALID_CONTEXT:
    return opencl_error_strings[2];
  case CL_INVALID_VALUE:
    return opencl_error_strings[3];
  case CL_DEVICE_NOT_AVAILABLE:
    return opencl_error_strings[4];
  case CL_DEVICE_NOT_FOUND:
    return opencl_error_strings[5];
  case CL_OUT_OF_HOST_MEMORY:
    return opencl_error_strings[6];
  case CL_INVALID_DEVICE_TYPE:
    return opencl_error_strings[7];
  //case CL_PLATFORM_NOT_FOUND_KHR:
  case -1001:
    return opencl_error_strings[8];
  default:
    return opencl_error_strings[9];
  }
}
 
void print_all_devices_info(cl_platform_id platform_id)
{
    int i;
    cl_context context;
    size_t length;
    cl_device_id devices[16];
    cl_int ret;

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

void print_all_platforms_info()
{
    int i;
    cl_platform_id *platforms;
    cl_int ret;
    cl_uint num_platforms;

    ret = clGetPlatformIDs(0, NULL, &num_platforms);
    if (ret != CL_SUCCESS) {
      printf("clGetPlatformIds: %s\n", opencl_error_string(ret));
      return;
    }
    printf("The number of OpenCL platforms available: %u\n", num_platforms);
    if (num_platforms <= 0) {
      return;
    }

    platforms = calloc(num_platforms, sizeof(cl_platform_id));
    if (platforms == NULL) {
      return;
    }

    ret = clGetPlatformIDs(num_platforms, platforms, 0);
    if (ret != CL_SUCCESS) {
      printf("clGetPlatformIds: %s\n", opencl_error_string(ret));
      return;
    }

    printf("The following devices are available for use:\n");

    for (i = 0; i < num_platforms; i++) {
      printf("Platform #%d\n", i+1);
      print_platform_info(platforms[i]);
      print_all_devices_info(platforms[i]);
    }

    free(platforms);
}


int main(int argc, const char* argv[]) {
    print_all_platforms_info();
    return 0;
}
