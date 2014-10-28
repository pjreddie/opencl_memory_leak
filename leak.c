#include <CL/cl.h>
#include <stdio.h>

#define MAX_DEVICES 10

typedef struct {
    cl_int error;
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
}cl_info;

cl_info info;

void check_error(cl_info info)
{
    if (info.error != CL_SUCCESS) {
        printf("\n Error number %d", info.error);
        exit(1);
    }
}

cl_info cl_init()
{
    cl_uint num_platforms, num_devices;
    cl_device_id devices[MAX_DEVICES];
    info.error=clGetPlatformIDs(1, &info.platform, &num_platforms);
    check_error(info);
    info.error=clGetDeviceIDs(info.platform, CL_DEVICE_TYPE_ALL, MAX_DEVICES, devices, &num_devices);
    info.device = devices[0];
    check_error(info);
    cl_context_properties properties[]={CL_CONTEXT_PLATFORM, (cl_context_properties)info.platform,0};
    info.context=clCreateContext(properties, 1, &info.device, 0, 0, &info.error);
    check_error(info);
    info.queue = clCreateCommandQueue(info.context, info.device, 0, &info.error);
    check_error(info);
    return info;
}

cl_mem cl_sub_array(cl_mem src, int offset, int size)
{
    cl_buffer_region r;
    r.origin = offset*sizeof(float);
    r.size = size*sizeof(float);
    cl_mem sub = clCreateSubBuffer(src, CL_MEM_READ_WRITE, CL_BUFFER_CREATE_TYPE_REGION, &r, &info.error);
    check_error(info);
    return sub;
}

cl_mem cl_make_array(float *x, int n)
{
    cl_mem mem = clCreateBuffer(info.context,
            CL_MEM_READ_WRITE|CL_MEM_COPY_HOST_PTR,
            sizeof(float)*n, x, &info.error);
    check_error(info);
    return mem;
}

int main()
{
    float *a = calloc(10000, sizeof(float));
    printf("Initializing\n");
    info = cl_init();
    cl_mem mem = cl_make_array(a, 10000);
    printf("Let's make some sub arrays...\n");
    while(1){
        cl_mem sub = cl_sub_array(mem, 0, 100);
        cl_int status = clReleaseMemObject(sub);
        if (status != CL_SUCCESS) printf("Failed to release\n");
    }
    return 0;
}


