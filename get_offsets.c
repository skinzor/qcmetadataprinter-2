#include <stdlib.h>
#include <dlfcn.h>
#include <cam_intf.h>

#define CAM_LIB "libmmcamera2_mct.so"
#define PRINT(PARAM_ID, table_ptr)  \
	blob_pointer = (char*)(get_pointer_of(PARAM_ID, table_ptr))-(char*)(table_ptr); \
	oss_pointer = (char*)(POINTER_OF_META(PARAM_ID, table_ptr))-(char*)(table_ptr); \
	blob_size=get_size_of(PARAM_ID); \
	oss_size=SIZE_OF_PARAM(PARAM_ID, table_ptr); \
	if ((blob_pointer != oss_pointer) || (blob_size != oss_size) ) \
		printf("FIXME!!!\n"); \
	printf("BLOB: %s index=%d pointer=%d size=%d\n", #PARAM_ID, PARAM_ID, blob_pointer, blob_size); \
        printf("OSS : %s index=%d pointer=%d size=%d\n", #PARAM_ID, PARAM_ID, oss_pointer, oss_size); 

#include "print_intf.h"

typedef void* (*get_pointer_of_t)(cam_intf_parm_type_t, metadata_buffer_t*);
typedef uint32_t (*get_size_of_t)(cam_intf_parm_type_t);

int main() {
    void *handle;
    get_pointer_of_t get_pointer_of;
    get_size_of_t get_size_of;
    metadata_buffer_t *pMetadata=malloc(sizeof(metadata_buffer_t));

    handle = dlopen(CAM_LIB, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    get_pointer_of = (get_pointer_of_t) dlsym(handle, "get_pointer_of");
    if (!get_pointer_of)  {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }
    get_size_of = (get_size_of_t) dlsym(handle, "get_size_of");
    if (!get_size_of)  {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }
    int blob_pointer = 0;
    int oss_pointer = 0;
    int blob_size = 0;
    int oss_size = 0;

    printit();

    dlclose(handle);
    return 0;
}