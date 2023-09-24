#ifdef __cplusplus
extern "C" int readfile(char *file_address, char *buf, size_t buf_size);
#else
extern int readfile(char *file_address, char *buf, size_t buf_size);
#endif