# 1 "test/example.c"
# 1 "/home/user/workspace/embox/third-party/lib/zlib-1.2.8//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "test/example.c"







# 1 "./zlib.h" 1
# 34 "./zlib.h"
# 1 "./zconf.h" 1
# 368 "./zconf.h"
typedef unsigned char Byte;

typedef unsigned int uInt;
typedef unsigned long uLong;





   typedef Byte Bytef;

typedef char charf;
typedef int intf;
typedef uInt uIntf;
typedef uLong uLongf;


   typedef void const *voidpc;
   typedef void *voidpf;
   typedef void *voidp;







# 1 "/home/user/workspace/embox/./src/include/limits.h" 1
# 396 "./zconf.h" 2
# 406 "./zconf.h"
   typedef unsigned z_crc_t;
# 421 "./zconf.h"
# 1 "/home/user/workspace/embox/./src/compat/posix/include/sys/types.h" 1
# 14 "/home/user/workspace/embox/./src/compat/posix/include/sys/types.h"
# 1 "/home/user/workspace/embox/./src/arch/x86/include/asm/types.h" 1
# 12 "/home/user/workspace/embox/./src/arch/x86/include/asm/types.h"
# 1 "/home/user/workspace/embox/./src/include/asm-generic/types32.h" 1
# 16 "/home/user/workspace/embox/./src/include/asm-generic/types32.h"
typedef signed char __s8;
typedef unsigned char __u8;
typedef signed short __s16;
typedef unsigned short __u16;
typedef signed int __s32;
typedef unsigned int __u32;
typedef long long __s64;
typedef unsigned long long __u64;
# 32 "/home/user/workspace/embox/./src/include/asm-generic/types32.h"
typedef unsigned int __size_t;
typedef signed int __ptrdiff_t;
# 13 "/home/user/workspace/embox/./src/arch/x86/include/asm/types.h" 2
# 15 "/home/user/workspace/embox/./src/compat/posix/include/sys/types.h" 2



typedef unsigned int size_t;






typedef int ssize_t;


typedef unsigned long clock_t;


typedef unsigned long useconds_t;


typedef long suseconds_t;

typedef unsigned long spinlock_t;

typedef __u32 gfp_t;

typedef struct {
 volatile int counter;
} atomic_t;

typedef long time_t;

typedef int id_t;

typedef int pid_t;

typedef int dev_t;

typedef int clockid_t;

typedef unsigned int ino_t;

typedef unsigned short nlink_t;

typedef unsigned int mode_t;

typedef unsigned short uid_t;
typedef unsigned short gid_t;

typedef unsigned int blkno_t;

typedef int off_t;

typedef long long loff_t;

typedef unsigned long fsblkcnt_t;
typedef unsigned long fsfilcnt_t;
# 422 "./zconf.h" 2





# 1 "/home/user/workspace/embox/./src/include/stdarg.h" 1
# 45 "/home/user/workspace/embox/./src/include/stdarg.h"
typedef __builtin_va_list va_list;
# 428 "./zconf.h" 2
# 452 "./zconf.h"
# 1 "/home/user/workspace/embox/./src/compat/posix/include/unistd.h" 1
# 15 "/home/user/workspace/embox/./src/compat/posix/include/unistd.h"
# 1 "/home/user/workspace/embox/./src/compat/posix/include/sys/stat.h" 1
# 13 "/home/user/workspace/embox/./src/compat/posix/include/sys/stat.h"
# 1 "/home/user/workspace/embox/./src/include/sys/cdefs.h" 1
# 14 "/home/user/workspace/embox/./src/compat/posix/include/sys/stat.h" 2



# 82 "/home/user/workspace/embox/./src/compat/posix/include/sys/stat.h"
typedef struct stat {
 int st_dev;
 int st_ino;
 int st_mode;
 int st_nlink;
 int st_uid;
 int st_gid;
 int st_rdev;
 size_t st_size;
 size_t st_blksize;
 int st_blocks;
 unsigned st_atime;
 unsigned st_mtime;
 unsigned st_ctime;
} stat_t;
# 114 "/home/user/workspace/embox/./src/compat/posix/include/sys/stat.h"
static inline int chmod(const char *path, mode_t mode) {
 return -1;
}

extern int stat(const char *, struct stat *);
extern int lstat(const char *, struct stat *);
extern int fstat(int fd, struct stat *);
extern int mkfifo(const char *, mode_t);
extern int mknod(const char *, mode_t, dev_t);
extern int mkdir (const char *, mode_t );
static inline mode_t umask(mode_t mode) {
 return 0;
}


# 16 "/home/user/workspace/embox/./src/compat/posix/include/unistd.h" 2


# 1 "/home/user/workspace/embox/./src/compat/posix/include/posix_environ.h" 1
# 12 "/home/user/workspace/embox/./src/compat/posix/include/posix_environ.h"
# 1 "/home/user/workspace/embox/./src/include/kernel/task/env.h" 1
# 12 "/home/user/workspace/embox/./src/include/kernel/task/env.h"
# 1 "/home/user/workspace/embox/./src/include/framework/mod/options.h" 1
# 13 "/home/user/workspace/embox/./src/include/framework/mod/options.h"
# 1 "/home/user/workspace/embox/./src/include/util/macro.h" 1
# 14 "/home/user/workspace/embox/./src/include/framework/mod/options.h" 2
# 13 "/home/user/workspace/embox/./src/include/kernel/task/env.h" 2
# 1 "/home/user/workspace/embox/./src/include/stddef.h" 1
# 40 "/home/user/workspace/embox/./src/include/stddef.h"
typedef unsigned short wchar_t;





typedef __ptrdiff_t ptrdiff_t;
# 14 "/home/user/workspace/embox/./src/include/kernel/task/env.h" 2


# 1 "/home/user/workspace/embox/./src/include/kernel/task.h" 1
# 12 "/home/user/workspace/embox/./src/include/kernel/task.h"
# 1 "/home/user/workspace/embox/./src/include/util/dlist.h" 1
# 20 "/home/user/workspace/embox/./src/include/util/dlist.h"
# 1 "/home/user/workspace/embox/./build/base/src-gen/include/module/embox/util/DList.h" 1






# 1 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h" 1
# 22 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h"
# 1 "/home/user/workspace/embox/./src/include/assert.h" 1
# 14 "/home/user/workspace/embox/./src/include/assert.h"
# 1 "/home/user/workspace/embox/./build/base/src-gen/include/module/embox/lib/LibCDiagnostic.h" 1






# 1 "/home/user/workspace/embox/./src/include/../lib/assert_impl.h" 1
# 12 "/home/user/workspace/embox/./src/include/../lib/assert_impl.h"
# 1 "/home/user/workspace/embox/./src/include/util/location.h" 1
# 13 "/home/user/workspace/embox/./src/include/util/location.h"
struct location {
 const char *file;
 int line;
};

struct location_func {
 struct location at;
 const char *func;
};
# 13 "/home/user/workspace/embox/./src/include/../lib/assert_impl.h" 2
# 1 "/home/user/workspace/embox/./src/compat/linux/include/linux/compiler.h" 1
# 14 "/home/user/workspace/embox/./src/include/../lib/assert_impl.h" 2
# 31 "/home/user/workspace/embox/./src/include/../lib/assert_impl.h"
struct __assertion_point {
 struct location_func location;
 const char *expression;
};




extern

void __attribute__ ((noreturn)) __assertion_handle_failure(
  const struct __assertion_point *point);
# 8 "/home/user/workspace/embox/./build/base/src-gen/include/module/embox/lib/LibCDiagnostic.h" 2
# 15 "/home/user/workspace/embox/./src/include/assert.h" 2
# 23 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h" 2






struct dlist_head {
 struct dlist_head *next;
 struct dlist_head *prev;




 struct dlist_head *list_id;
};





static inline void __dlist_add(struct dlist_head *_new, struct dlist_head *next,
  struct dlist_head *prev) {
 _new->prev = prev;
 _new->next = next;
 next->prev = _new;
 prev->next = _new;
}




static inline int __is_linked(struct dlist_head *head) {
 return (((void *)0) != head->list_id);
}





static inline struct dlist_head *dlist_head_init(struct dlist_head *head) {
 head->next = head->prev = head;
 head->list_id = (struct dlist_head *)((void *)0);

 return head;
}
# 77 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h"
static inline struct dlist_head *dlist_init(struct dlist_head *list_head) {

 list_head->list_id = list_head;
 list_head->next = list_head->prev = list_head;

 return list_head;
}
# 92 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h"
static inline void dlist_add_next(struct dlist_head *_new,
  struct dlist_head *list) {


 ({do { if (!((__builtin_constant_p(!__is_linked(_new)) ? !!(!__is_linked(_new)) : __builtin_expect(!!(!__is_linked(_new)), 1)))) { extern char __assertion_message_buff[]; static const struct __assertion_point __assertion_point = { .location = { .at = { .file = "/home/user/workspace/embox/./src/include/../util/dlist_debug.h", .line = 96, }, .func = __func__, }, .expression = "!__is_linked(_new)", }; extern int sprintf(char *s, const char *format, ...); sprintf(__assertion_message_buff, "" ); __assertion_handle_failure(&__assertion_point); } } while(0);});



 ({do { if (!((__builtin_constant_p(__is_linked(list)) ? !!(__is_linked(list)) : __builtin_expect(!!(__is_linked(list)), 1)))) { extern char __assertion_message_buff[]; static const struct __assertion_point __assertion_point = { .location = { .at = { .file = "/home/user/workspace/embox/./src/include/../util/dlist_debug.h", .line = 100, }, .func = __func__, }, .expression = "__is_linked(list)", }; extern int sprintf(char *s, const char *format, ...); sprintf(__assertion_message_buff, "" ); __assertion_handle_failure(&__assertion_point); } } while(0);});

 _new->list_id = list->list_id;





 __dlist_add(_new, list->next, list);
}
# 119 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h"
static inline void dlist_add_prev(struct dlist_head *_new,
  struct dlist_head *list) {


 ({do { if (!((__builtin_constant_p(!__is_linked(_new)) ? !!(!__is_linked(_new)) : __builtin_expect(!!(!__is_linked(_new)), 1)))) { extern char __assertion_message_buff[]; static const struct __assertion_point __assertion_point = { .location = { .at = { .file = "/home/user/workspace/embox/./src/include/../util/dlist_debug.h", .line = 123, }, .func = __func__, }, .expression = "!__is_linked(_new)", }; extern int sprintf(char *s, const char *format, ...); sprintf(__assertion_message_buff, "" ); __assertion_handle_failure(&__assertion_point); } } while(0);});



 ({do { if (!((__builtin_constant_p(__is_linked(list)) ? !!(__is_linked(list)) : __builtin_expect(!!(__is_linked(list)), 1)))) { extern char __assertion_message_buff[]; static const struct __assertion_point __assertion_point = { .location = { .at = { .file = "/home/user/workspace/embox/./src/include/../util/dlist_debug.h", .line = 127, }, .func = __func__, }, .expression = "__is_linked(list)", }; extern int sprintf(char *s, const char *format, ...); sprintf(__assertion_message_buff, "" ); __assertion_handle_failure(&__assertion_point); } } while(0);});

 _new->list_id = list->list_id;





 __dlist_add(_new, list, list->prev);
}
# 145 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h"
static inline void dlist_del(struct dlist_head *head) {
 ({do { if (!((__builtin_constant_p(__is_linked(head)) ? !!(__is_linked(head)) : __builtin_expect(!!(__is_linked(head)), 1)))) { extern char __assertion_message_buff[]; static const struct __assertion_point __assertion_point = { .location = { .at = { .file = "/home/user/workspace/embox/./src/include/../util/dlist_debug.h", .line = 146, }, .func = __func__, }, .expression = "__is_linked(head)", }; extern int sprintf(char *s, const char *format, ...); sprintf(__assertion_message_buff, "" ); __assertion_handle_failure(&__assertion_point); } } while(0);});




 head->prev->next = head->next;
 head->next->prev = head->prev;

 head->list_id = (struct dlist_head *)((void *)0);
}
# 8 "/home/user/workspace/embox/./build/base/src-gen/include/module/embox/util/DList.h" 2
# 21 "/home/user/workspace/embox/./src/include/util/dlist.h" 2






struct dlist_head;
# 60 "/home/user/workspace/embox/./src/include/util/dlist.h"
extern struct dlist_head *dlist_init(struct dlist_head *list_head);
# 73 "/home/user/workspace/embox/./src/include/util/dlist.h"
extern struct dlist_head *dlist_head_init(struct dlist_head *item_head);
# 84 "/home/user/workspace/embox/./src/include/util/dlist.h"
extern void dlist_add_next(struct dlist_head *_new, struct dlist_head *list);
# 94 "/home/user/workspace/embox/./src/include/util/dlist.h"
extern void dlist_add_prev(struct dlist_head *_new, struct dlist_head *list);







extern void dlist_del(struct dlist_head *item_head);







static inline void dlist_move(struct dlist_head *head, struct dlist_head *list) {
 dlist_del(head);
 dlist_add_next(head, list);
}







static inline int dlist_empty(struct dlist_head *head) {
 return head == head->next;
}
# 13 "/home/user/workspace/embox/./src/include/kernel/task.h" 2
# 1 "/home/user/workspace/embox/./src/include/util/array.h" 1
# 34 "/home/user/workspace/embox/./src/include/util/array.h"
# 1 "/home/user/workspace/embox/./build/base/src-gen/include/module/embox/util/Array.h" 1






# 1 "/home/user/workspace/embox/./src/include/../util/array_impl.h" 1
# 8 "/home/user/workspace/embox/./build/base/src-gen/include/module/embox/util/Array.h" 2
# 35 "/home/user/workspace/embox/./src/include/util/array.h" 2
# 14 "/home/user/workspace/embox/./src/include/kernel/task.h" 2




# 1 "/home/user/workspace/embox/./src/include/kernel/task/task_priority.h" 1
# 18 "/home/user/workspace/embox/./src/include/kernel/task/task_priority.h"
typedef short task_priority_t;
# 19 "/home/user/workspace/embox/./src/include/kernel/task.h" 2





struct task_signal_table;
struct task_idx_table;
struct thread;
struct emmap;
struct task_u_area;
struct task_env;
struct sleepq;





struct task {
 struct dlist_head task_link;

 int tid;

 char task_name[20];

 struct task *parent;

 struct dlist_head children_tasks;

 struct thread *main_thread;

 struct task_idx_table *idx_table;

 struct task_signal_table *signal_table;

 struct emmap *mmap;



 struct task_u_area *u_area;

 struct task_env *env;

 task_priority_t priority;

 void *security;

 int err;

 clock_t per_cpu;

 struct wait_queue *waitq;

 unsigned int affinity;
};

struct task_resource_desc {
 void (*init)(struct task *task, void *resource_space);
 int (*inherit)(struct task *task, struct task *parent_task);
 void (*deinit)(struct task *task);
 size_t resource_size;
};

typedef int (*task_notifing_resource_hnd)(struct thread *prev, struct thread *next);

extern const struct task_resource_desc *task_resource_desc_array[];

extern const task_notifing_resource_hnd task_notifing_resource[];
# 99 "/home/user/workspace/embox/./src/include/kernel/task.h"
static inline struct task_idx_table *task_idx_table(struct task *task) {
 return task->idx_table;
}


extern int new_task(const char *name, void *(*run)(void *), void *arg);


extern int task_add_thread(struct task *, struct thread *);

extern int task_remove_thread(struct task *, struct thread *);






extern struct task *task_self(void);


static inline int task_getid(void) {
 return task_self()->tid;
}


extern int task_set_priority(struct task *task, task_priority_t priority);


extern task_priority_t task_get_priority(struct task *task);


static inline void task_set_affinity(struct task *task, unsigned int affinity) {
 task->affinity = affinity;
}
static inline unsigned int task_get_affinity(struct task *task) {
 return task->affinity;
}

static inline void *task_self_security(void) {
 return task_self()->security;
}






extern void __attribute__((noreturn)) task_exit(void *res);






extern struct task *task_kernel_task(void);

extern int task_notify_switch(struct thread *prev, struct thread *next);

extern int task_waitpid(pid_t pid);


# 17 "/home/user/workspace/embox/./src/include/kernel/task/env.h" 2

# 1 "/home/user/workspace/embox/./build/base/src-gen/include/module/embox/kernel/task/env.h" 1
# 19 "/home/user/workspace/embox/./src/include/kernel/task/env.h" 2









struct task_env {
 char **envs;
 size_t next;
 char *vals[8 + 1];
 char storage[8][32];
 char buff[32];
};

static inline struct task_env * task_self_env(void) {
 return task_self()->env;
}

static inline char *** task_self_environ_ptr(void) {
 return &task_self()->env->envs;
}


# 13 "/home/user/workspace/embox/./src/compat/posix/include/posix_environ.h" 2
# 19 "/home/user/workspace/embox/./src/compat/posix/include/unistd.h" 2




# 39 "/home/user/workspace/embox/./src/compat/posix/include/unistd.h"
extern int sleep(unsigned int seconds);






extern int usleep(useconds_t useconds);

extern ssize_t write(int fd, const void *buf, size_t nbyte);

extern ssize_t read(int fd, void *buf, size_t nbyte);

extern off_t lseek(int fd, off_t offset, int origin);

extern int close(int fd);

extern int fsync(int);

extern pid_t fork(void);

extern int nice(int incr);

extern int execv(const char *path, char *const argv[]);
extern int execve(const char *filename, char *const argv[], char *const envp[]);

extern int unlink(const char *pathname);

extern int rmdir(const char *pathname);

static inline pid_t getpid(void) {
 return task_getid();
}

extern int isatty(int fd);

extern int dup(int flides);
extern int dup2(int flides, int flides2);

extern int pipe(int pipefd[2] );
extern void _exit(int status);

extern uid_t getuid(void);
extern uid_t geteuid(void);

extern uid_t getgid(void);
extern uid_t getegid(void);

extern int setreuid(uid_t ruid, uid_t euid);
extern int setuid(uid_t uid);
extern int seteuid(uid_t uid);

extern int setregid(gid_t rgid, gid_t egid);
extern int setgid(gid_t gid);
extern int setegid(gid_t gid);

extern int truncate(const char *path, off_t length);
extern int ftruncate(int fd, off_t length);

extern char * getcwd(char *buff, size_t size);
extern int chdir(const char *path);





static inline int access(const char *path, int amode) { return 0; }







extern int getopt(int argc, char **argv, const char *opts);

extern char *optarg;
extern int optind;
extern int optopt;
extern int opterr;


extern void getopt_init(void);
# 132 "/home/user/workspace/embox/./src/compat/posix/include/unistd.h"
extern char *getpass(const char *prompt);

int gethostname(char *name, size_t len);


# 453 "./zconf.h" 2
# 35 "./zlib.h" 2
# 80 "./zlib.h"
typedef voidpf (*alloc_func) (voidpf opaque, uInt items, uInt size);
typedef void (*free_func) (voidpf opaque, voidpf address);

struct internal_state;

typedef struct z_stream_s {
    Bytef *next_in;
    uInt avail_in;
    uLong total_in;

    Bytef *next_out;
    uInt avail_out;
    uLong total_out;

    char *msg;
    struct internal_state *state;

    alloc_func zalloc;
    free_func zfree;
    voidpf opaque;

    int data_type;
    uLong adler;
    uLong reserved;
} z_stream;

typedef z_stream *z_streamp;





typedef struct gz_header_s {
    int text;
    uLong time;
    int xflags;
    int os;
    Bytef *extra;
    uInt extra_len;
    uInt extra_max;
    Bytef *name;
    uInt name_max;
    Bytef *comment;
    uInt comm_max;
    int hcrc;
    int done;

} gz_header;

typedef gz_header *gz_headerp;
# 216 "./zlib.h"
extern const char * zlibVersion (void);
# 246 "./zlib.h"
extern int deflate (z_streamp strm, int flush);
# 353 "./zlib.h"
extern int deflateEnd (z_streamp strm);
# 392 "./zlib.h"
extern int inflate (z_streamp strm, int flush);
# 508 "./zlib.h"
extern int inflateEnd (z_streamp strm);
# 587 "./zlib.h"
extern int deflateSetDictionary (z_streamp strm, const Bytef *dictionary, uInt dictLength)

                                                               ;
# 631 "./zlib.h"
extern int deflateCopy (z_streamp dest, z_streamp source)
                                                      ;
# 649 "./zlib.h"
extern int deflateReset (z_streamp strm);
# 660 "./zlib.h"
extern int deflateParams (z_streamp strm, int level, int strategy)

                                                    ;
# 681 "./zlib.h"
extern int deflateTune (z_streamp strm, int good_length, int max_lazy, int nice_length, int max_chain)



                                                   ;
# 698 "./zlib.h"
extern uLong deflateBound (z_streamp strm, uLong sourceLen)
                                                        ;
# 713 "./zlib.h"
extern int deflatePending (z_streamp strm, unsigned *pending, int *bits)

                                                  ;
# 728 "./zlib.h"
extern int deflatePrime (z_streamp strm, int bits, int value)

                                                ;
# 745 "./zlib.h"
extern int deflateSetHeader (z_streamp strm, gz_headerp head)
                                                          ;
# 819 "./zlib.h"
extern int inflateSetDictionary (z_streamp strm, const Bytef *dictionary, uInt dictLength)

                                                               ;
# 842 "./zlib.h"
extern int inflateGetDictionary (z_streamp strm, Bytef *dictionary, uInt *dictLength)

                                                                ;
# 857 "./zlib.h"
extern int inflateSync (z_streamp strm);
# 876 "./zlib.h"
extern int inflateCopy (z_streamp dest, z_streamp source)
                                                      ;
# 892 "./zlib.h"
extern int inflateReset (z_streamp strm);
# 902 "./zlib.h"
extern int inflateReset2 (z_streamp strm, int windowBits)
                                                      ;
# 914 "./zlib.h"
extern int inflatePrime (z_streamp strm, int bits, int value)

                                                ;
# 935 "./zlib.h"
extern long inflateMark (z_streamp strm);
# 963 "./zlib.h"
extern int inflateGetHeader (z_streamp strm, gz_headerp head)
                                                          ;
# 1025 "./zlib.h"
typedef unsigned (*in_func) (void *, unsigned char * *)
                                                                   ;
typedef int (*out_func) (void *, unsigned char *, unsigned);

extern int inflateBack (z_streamp strm, in_func in, void *in_desc, out_func out, void *out_desc)

                                                                      ;
# 1099 "./zlib.h"
extern int inflateBackEnd (z_streamp strm);







extern uLong zlibCompileFlags (void);
# 1160 "./zlib.h"
extern int compress (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen)
                                                                       ;
# 1174 "./zlib.h"
extern int compress2 (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen, int level)

                                             ;
# 1190 "./zlib.h"
extern uLong compressBound (uLong sourceLen);






extern int uncompress (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen)
                                                                         ;
# 1224 "./zlib.h"
typedef struct gzFile_s *gzFile;
# 1264 "./zlib.h"
extern gzFile gzdopen (int fd, const char *mode);
# 1287 "./zlib.h"
extern int gzbuffer (gzFile file, unsigned size);
# 1304 "./zlib.h"
extern int gzsetparams (gzFile file, int level, int strategy);
# 1313 "./zlib.h"
extern int gzread (gzFile file, voidp buf, unsigned len);
# 1341 "./zlib.h"
extern int gzwrite (gzFile file, voidpc buf, unsigned len)
                                                          ;






extern int gzprintf (gzFile file, const char *format, ...);
# 1364 "./zlib.h"
extern int gzputs (gzFile file, const char *s);







extern char * gzgets (gzFile file, char *buf, int len);
# 1385 "./zlib.h"
extern int gzputc (gzFile file, int c);





extern int gzgetc (gzFile file);
# 1400 "./zlib.h"
extern int gzungetc (int c, gzFile file);
# 1412 "./zlib.h"
extern int gzflush (gzFile file, int flush);
# 1447 "./zlib.h"
extern int gzrewind (gzFile file);
# 1475 "./zlib.h"
extern int gzeof (gzFile file);
# 1490 "./zlib.h"
extern int gzdirect (gzFile file);
# 1511 "./zlib.h"
extern int gzclose (gzFile file);
# 1524 "./zlib.h"
extern int gzclose_r (gzFile file);
extern int gzclose_w (gzFile file);
# 1536 "./zlib.h"
extern const char * gzerror (gzFile file, int *errnum);
# 1552 "./zlib.h"
extern void gzclearerr (gzFile file);
# 1569 "./zlib.h"
extern uLong adler32 (uLong adler, const Bytef *buf, uInt len);
# 1600 "./zlib.h"
extern uLong crc32 (uLong crc, const Bytef *buf, uInt len);
# 1633 "./zlib.h"
extern int deflateInit_ (z_streamp strm, int level, const char *version, int stream_size)
                                                                           ;
extern int inflateInit_ (z_streamp strm, const char *version, int stream_size)
                                                                           ;
extern int deflateInit2_ (z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char *version, int stream_size)


                                                       ;
extern int inflateInit2_ (z_streamp strm, int windowBits, const char *version, int stream_size)
                                                                            ;
extern int inflateBackInit_ (z_streamp strm, int windowBits, unsigned char *window, const char *version, int stream_size)


                                                          ;
# 1670 "./zlib.h"
struct gzFile_s {
    unsigned have;
    unsigned char *next;
    off_t pos;
};
extern int gzgetc_ (gzFile file);
# 1725 "./zlib.h"
   extern gzFile gzopen (const char *, const char *);
   extern off_t gzseek (gzFile, off_t, int);
   extern off_t gztell (gzFile);
   extern off_t gzoffset (gzFile);
   extern uLong adler32_combine (uLong, uLong, off_t);
   extern uLong crc32_combine (uLong, uLong, off_t);
# 1742 "./zlib.h"
    struct internal_state {int dummy;};



extern const char * zError (int);
extern int inflateSyncPoint (z_streamp);
extern const z_crc_t * get_crc_table (void);
extern int inflateUndermine (z_streamp, int);
extern int inflateResetKeep (z_streamp);
extern int deflateResetKeep (z_streamp);






extern int gzvprintf (gzFile file, const char *format, va_list va)

                                                              ;
# 9 "test/example.c" 2
# 1 "/home/user/workspace/embox/./src/include/stdio.h" 1
# 16 "/home/user/workspace/embox/./src/include/stdio.h"
# 1 "/home/user/workspace/embox/./src/include/kernel/printk.h" 1
# 12 "/home/user/workspace/embox/./src/include/kernel/printk.h"
extern int printk(const char *format, ...) __attribute__ ((format
    (printf, 1, 2)));
# 17 "/home/user/workspace/embox/./src/include/stdio.h" 2
# 36 "/home/user/workspace/embox/./src/include/stdio.h"
typedef struct file_struct {
 int fd;
 char has_ungetc;
 int ungetc;
} FILE;


struct stat;





extern int putc(int c, FILE *f);
extern int fputc(int c, FILE *f);

extern int getc(FILE *f);
extern int fgetc(FILE *f);




extern int puts(const char *s);
extern int fputs(const char *s, FILE *f);

extern int putchar(int c);





extern char *gets(char *s);

extern char *fgets(char *s, int n, FILE *stream);

extern int getchar(void);

extern int ungetc(int c, FILE *stream);


int ungetchar(int ch);

extern void perror(const char *s);




extern int printf(const char *format, ...);

extern int vprintf(const char *format, va_list args);




extern int fprintf(FILE *f, const char *format, ...);

extern int vfprintf(FILE *f, const char *format, va_list args);




extern int sprintf(char *s, const char *format, ...);

extern int vsprintf(char *s, const char *format, va_list args);




extern int snprintf(char *s, size_t n, const char *format, ...);

extern int vsnprintf(char *s, size_t n, const char *format, va_list args);




extern int scanf(const char *format, ...);

extern int fscanf(FILE *stream, const char *format, ...);




extern int sscanf(const char *out, const char *format, ...);





extern FILE *fopen(const char *path, const char *mode);






extern FILE *fdopen(int fd, const char *mode);





extern FILE *freopen(const char *path, const char *mode, FILE *stream);





extern size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);





extern size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);





extern int fclose(FILE *fp);

static inline int fflush(FILE *fp) { return (-1); }




extern int remove(const char *pathname);
# 171 "/home/user/workspace/embox/./src/include/stdio.h"
extern int fseek(FILE *stream, long int offset, int origin);

extern long int ftell(FILE *stream);

typedef long int fpos_t;

extern int fgetpos(FILE *stream, fpos_t *pos);

extern int fsetpos(FILE *stream, const fpos_t *pos);




extern void rewind(FILE *stream);




extern int rename(const char *oldpath, const char *newpath);




extern int fioctl(FILE *fp, int request, ...);

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;



extern void clearerr(FILE *stream);

extern int feof(FILE *stream);

extern int ferror(FILE *stream);

static inline int fileno(FILE *stream) {

 return stream->fd;
}


# 10 "test/example.c" 2


# 1 "/home/user/workspace/embox/./src/include/string.h" 1
# 22 "/home/user/workspace/embox/./src/include/string.h"

# 33 "/home/user/workspace/embox/./src/include/string.h"
extern size_t strlen(const char *str);
# 47 "/home/user/workspace/embox/./src/include/string.h"
extern char *strcpy(char *dst, const char *src);
# 66 "/home/user/workspace/embox/./src/include/string.h"
extern char *strncpy(char *dst, const char *src, size_t n);
# 78 "/home/user/workspace/embox/./src/include/string.h"
extern char *strcat(char *dst, const char *src);
# 94 "/home/user/workspace/embox/./src/include/string.h"
extern char *strncat(char *dst, const char *src, size_t n);
# 114 "/home/user/workspace/embox/./src/include/string.h"
extern int strcmp(const char *str1, const char *str2);
# 137 "/home/user/workspace/embox/./src/include/string.h"
extern int strncmp(const char *str1, const char *str2, size_t n);
# 152 "/home/user/workspace/embox/./src/include/string.h"
extern char *strchr(const char *str, int ch);
# 169 "/home/user/workspace/embox/./src/include/string.h"
extern char *strrchr(const char *str, int ch);
# 185 "/home/user/workspace/embox/./src/include/string.h"
extern char *strstr(const char *haystack, const char *needle);
# 195 "/home/user/workspace/embox/./src/include/string.h"
extern char *strerror(int err);
# 215 "/home/user/workspace/embox/./src/include/string.h"
extern void *memcpy(void *dst, const void *src, size_t n);
# 230 "/home/user/workspace/embox/./src/include/string.h"
extern void *memmove(void *dst, const void *src, size_t n);
# 245 "/home/user/workspace/embox/./src/include/string.h"
extern void *memset(void *ptr, int c, size_t n);
# 266 "/home/user/workspace/embox/./src/include/string.h"
extern int memcmp(const void *ptr1, const void *ptr2, size_t n);
# 282 "/home/user/workspace/embox/./src/include/string.h"
extern void *memchr(const void *s, int c, size_t n);
# 292 "/home/user/workspace/embox/./src/include/string.h"
extern char *strlwr(char *str);
# 302 "/home/user/workspace/embox/./src/include/string.h"
extern char *strupr(char *str);
# 315 "/home/user/workspace/embox/./src/include/string.h"
extern size_t strspn(const char *s, const char *accept);
# 328 "/home/user/workspace/embox/./src/include/string.h"
extern size_t strcspn(const char *s, const char *reject);
# 342 "/home/user/workspace/embox/./src/include/string.h"
extern char *strpbrk(const char *s, const char *accept);
# 352 "/home/user/workspace/embox/./src/include/string.h"
extern char *strdup(const char *s);


# 13 "test/example.c" 2
# 1 "/home/user/workspace/embox/./src/include/stdlib.h" 1
# 18 "/home/user/workspace/embox/./src/include/stdlib.h"
# 1 "/home/user/workspace/embox/./src/compat/posix/include/sys/wait.h" 1
# 15 "/home/user/workspace/embox/./src/compat/posix/include/sys/wait.h"
extern pid_t waitpid(pid_t pid, int *status, int options);
# 19 "/home/user/workspace/embox/./src/include/stdlib.h" 2

typedef struct ldiv {
   long int quot;
   long int rem;
} ldiv_t;

typedef struct div {
   int quot;
   int rem;
} div_t;




# 62 "/home/user/workspace/embox/./src/include/stdlib.h"
extern long int strtol(const char *nptr, char **endptr, int base);

extern unsigned long int strtoul(const char *nptr, char **endptr, int base);

extern double strtod(const char *nptr, char **endptr);
# 77 "/home/user/workspace/embox/./src/include/stdlib.h"
extern char *itoa( int num, char *buf, unsigned short int base );


extern void *calloc(size_t nmemb, size_t size);
extern void *malloc(size_t size);
extern void free(void *ptr);
extern void *realloc(void *ptr, size_t size);
extern void *memalign(size_t boundary, size_t size);


extern void qsort(void *base, size_t nmemb, size_t size,
  int(*compar)(const void *, const void *));

extern void *bsearch(const void *key, const void *base,
              size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));


extern void *lower_bound(const void *key, const void *base,
              size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));


extern void *upper_bound(const void *key, const void *base,
              size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));


extern int rand(void);
extern int rand_r(unsigned int *seedp);
extern void srand(unsigned int seed);

extern ldiv_t ldiv(long num, long denom);
extern div_t div(int num, int denom);


extern double atof(const char *nptr);
extern int atoi(const char *nptr);
extern long atol(const char *nptr);
extern long long atoll(const char *nptr);
extern long long atoq(const char *nptr);
extern double strtod(const char *nptr, char **endptr);
extern float strtof(const char *nptr, char **endptr);
extern long double strtold(const char *nptr, char **endptr);
extern void abort(void);



extern void exit(int status);
# 136 "/home/user/workspace/embox/./src/include/stdlib.h"
static inline int abs(int x) { return x < 0 ? -x : x; }
static inline long labs(long x) { return x < 0 ? -x : x; }


extern char * getenv(const char *name);
extern int putenv(char *string);
extern int setenv(const char *envname, const char *envval, int overwrite);
extern int unsetenv(const char *name);
extern int clearenv(void);
extern int system(const char *command);

static inline int mkstemp(char *path_template) { return -1; }
static inline int mbtowc(wchar_t *pwc, const char *s, size_t n) { return 0; }
static inline int wctomb(char *s, wchar_t wchar) { return 0; }


# 14 "test/example.c" 2
# 29 "test/example.c"
 char hello[] = "hello, hello!";




const char dictionary[] = "hello";
uLong dictId;

void test_deflate (Byte *compr, uLong comprLen);
void test_inflate (Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
                                                             ;
void test_large_deflate (Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
                                                             ;
void test_large_inflate (Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
                                                             ;
void test_flush (Byte *compr, uLong *comprLen);
void test_sync (Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
                                                             ;
void test_dict_deflate (Byte *compr, uLong comprLen);
void test_dict_inflate (Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
                                                             ;
int main (int argc, char *argv[]);
# 77 "test/example.c"
static alloc_func zalloc = (alloc_func)0;
static free_func zfree = (free_func)0;

void test_compress (Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
                                                             ;
void test_gzio (const char *fname, Byte *uncompr, uLong uncomprLen)
                                                             ;




void test_compress(compr, comprLen, uncompr, uncomprLen)
    Byte *compr, *uncompr;
    uLong comprLen, uncomprLen;
{
    int err;
    uLong len = (uLong)strlen(hello)+1;

    err = compress(compr, &comprLen, (const Bytef*)hello, len);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "compress", err); exit(1); } };

    strcpy((char*)uncompr, "garbage");

    err = uncompress(uncompr, &uncomprLen, compr, comprLen);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "uncompress", err); exit(1); } };

    if (strcmp((char*)uncompr, hello)) {
        fprintf(stderr, "bad uncompress\n");
        exit(1);
    } else {
        printf("uncompress(): %s\n", (char *)uncompr);
    }
}




void test_gzio(fname, uncompr, uncomprLen)
    const char *fname;
    Byte *uncompr;
    uLong uncomprLen;
{



    int err;
    int len = (int)strlen(hello)+1;
    gzFile file;
    off_t pos;

    file = gzopen(fname, "wb");
    if (file == ((void *)0)) {
        fprintf(stderr, "gzopen error\n");
        exit(1);
    }
    gzputc(file, 'h');
    if (gzputs(file, "ello") != 4) {
        fprintf(stderr, "gzputs err: %s\n", gzerror(file, &err));
        exit(1);
    }
    if (gzprintf(file, ", %s!", "hello") != 8) {
        fprintf(stderr, "gzprintf err: %s\n", gzerror(file, &err));
        exit(1);
    }
    gzseek(file, 1L, 1);
    gzclose(file);

    file = gzopen(fname, "rb");
    if (file == ((void *)0)) {
        fprintf(stderr, "gzopen error\n");
        exit(1);
    }
    strcpy((char*)uncompr, "garbage");

    if (gzread(file, uncompr, (unsigned)uncomprLen) != len) {
        fprintf(stderr, "gzread err: %s\n", gzerror(file, &err));
        exit(1);
    }
    if (strcmp((char*)uncompr, hello)) {
        fprintf(stderr, "bad gzread: %s\n", (char*)uncompr);
        exit(1);
    } else {
        printf("gzread(): %s\n", (char*)uncompr);
    }

    pos = gzseek(file, -8L, 1);
    if (pos != 6 || gztell(file) != pos) {
        fprintf(stderr, "gzseek error, pos=%ld, gztell=%ld\n",
                (long)pos, (long)gztell(file));
        exit(1);
    }

    if (((file)->have ? ((file)->have--, (file)->pos++, *((file)->next)++) : gzgetc(file)) != ' ') {
        fprintf(stderr, "gzgetc error\n");
        exit(1);
    }

    if (gzungetc(' ', file) != ' ') {
        fprintf(stderr, "gzungetc error\n");
        exit(1);
    }

    gzgets(file, (char*)uncompr, (int)uncomprLen);
    if (strlen((char*)uncompr) != 7) {
        fprintf(stderr, "gzgets err after gzseek: %s\n", gzerror(file, &err));
        exit(1);
    }
    if (strcmp((char*)uncompr, hello + 6)) {
        fprintf(stderr, "bad gzgets after gzseek\n");
        exit(1);
    } else {
        printf("gzgets() after gzseek: %s\n", (char*)uncompr);
    }

    gzclose(file);

}






void test_deflate(compr, comprLen)
    Byte *compr;
    uLong comprLen;
{
    z_stream c_stream;
    int err;
    uLong len = (uLong)strlen(hello)+1;

    c_stream.zalloc = zalloc;
    c_stream.zfree = zfree;
    c_stream.opaque = (voidpf)0;

    err = deflateInit_((&c_stream), ((-1)), "1.2.8", (int)sizeof(z_stream));
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflateInit", err); exit(1); } };

    c_stream.next_in = ( unsigned char *)hello;
    c_stream.next_out = compr;

    while (c_stream.total_in != len && c_stream.total_out < comprLen) {
        c_stream.avail_in = c_stream.avail_out = 1;
        err = deflate(&c_stream, 0);
        { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflate", err); exit(1); } };
    }

    for (;;) {
        c_stream.avail_out = 1;
        err = deflate(&c_stream, 4);
        if (err == 1) break;
        { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflate", err); exit(1); } };
    }

    err = deflateEnd(&c_stream);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflateEnd", err); exit(1); } };
}




void test_inflate(compr, comprLen, uncompr, uncomprLen)
    Byte *compr, *uncompr;
    uLong comprLen, uncomprLen;
{
    int err;
    z_stream d_stream;

    strcpy((char*)uncompr, "garbage");

    d_stream.zalloc = zalloc;
    d_stream.zfree = zfree;
    d_stream.opaque = (voidpf)0;

    d_stream.next_in = compr;
    d_stream.avail_in = 0;
    d_stream.next_out = uncompr;

    err = inflateInit_((&d_stream), "1.2.8", (int)sizeof(z_stream));
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "inflateInit", err); exit(1); } };

    while (d_stream.total_out < uncomprLen && d_stream.total_in < comprLen) {
        d_stream.avail_in = d_stream.avail_out = 1;
        err = inflate(&d_stream, 0);
        if (err == 1) break;
        { if (err != 0) { fprintf(stderr, "%s error: %d\n", "inflate", err); exit(1); } };
    }

    err = inflateEnd(&d_stream);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "inflateEnd", err); exit(1); } };

    if (strcmp((char*)uncompr, hello)) {
        fprintf(stderr, "bad inflate\n");
        exit(1);
    } else {
        printf("inflate(): %s\n", (char *)uncompr);
    }
}




void test_large_deflate(compr, comprLen, uncompr, uncomprLen)
    Byte *compr, *uncompr;
    uLong comprLen, uncomprLen;
{
    z_stream c_stream;
    int err;

    c_stream.zalloc = zalloc;
    c_stream.zfree = zfree;
    c_stream.opaque = (voidpf)0;

    err = deflateInit_((&c_stream), (1), "1.2.8", (int)sizeof(z_stream));
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflateInit", err); exit(1); } };

    c_stream.next_out = compr;
    c_stream.avail_out = (uInt)comprLen;




    c_stream.next_in = uncompr;
    c_stream.avail_in = (uInt)uncomprLen;
    err = deflate(&c_stream, 0);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflate", err); exit(1); } };
    if (c_stream.avail_in != 0) {
        fprintf(stderr, "deflate not greedy\n");
        exit(1);
    }


    deflateParams(&c_stream, 0, 0);
    c_stream.next_in = compr;
    c_stream.avail_in = (uInt)comprLen/2;
    err = deflate(&c_stream, 0);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflate", err); exit(1); } };


    deflateParams(&c_stream, 9, 1);
    c_stream.next_in = uncompr;
    c_stream.avail_in = (uInt)uncomprLen;
    err = deflate(&c_stream, 0);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflate", err); exit(1); } };

    err = deflate(&c_stream, 4);
    if (err != 1) {
        fprintf(stderr, "deflate should report Z_STREAM_END\n");
        exit(1);
    }
    err = deflateEnd(&c_stream);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflateEnd", err); exit(1); } };
}




void test_large_inflate(compr, comprLen, uncompr, uncomprLen)
    Byte *compr, *uncompr;
    uLong comprLen, uncomprLen;
{
    int err;
    z_stream d_stream;

    strcpy((char*)uncompr, "garbage");

    d_stream.zalloc = zalloc;
    d_stream.zfree = zfree;
    d_stream.opaque = (voidpf)0;

    d_stream.next_in = compr;
    d_stream.avail_in = (uInt)comprLen;

    err = inflateInit_((&d_stream), "1.2.8", (int)sizeof(z_stream));
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "inflateInit", err); exit(1); } };

    for (;;) {
        d_stream.next_out = uncompr;
        d_stream.avail_out = (uInt)uncomprLen;
        err = inflate(&d_stream, 0);
        if (err == 1) break;
        { if (err != 0) { fprintf(stderr, "%s error: %d\n", "large inflate", err); exit(1); } };
    }

    err = inflateEnd(&d_stream);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "inflateEnd", err); exit(1); } };

    if (d_stream.total_out != 2*uncomprLen + comprLen/2) {
        fprintf(stderr, "bad large inflate: %ld\n", d_stream.total_out);
        exit(1);
    } else {
        printf("large_inflate(): OK\n");
    }
}




void test_flush(compr, comprLen)
    Byte *compr;
    uLong *comprLen;
{
    z_stream c_stream;
    int err;
    uInt len = (uInt)strlen(hello)+1;

    c_stream.zalloc = zalloc;
    c_stream.zfree = zfree;
    c_stream.opaque = (voidpf)0;

    err = deflateInit_((&c_stream), ((-1)), "1.2.8", (int)sizeof(z_stream));
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflateInit", err); exit(1); } };

    c_stream.next_in = ( unsigned char *)hello;
    c_stream.next_out = compr;
    c_stream.avail_in = 3;
    c_stream.avail_out = (uInt)*comprLen;
    err = deflate(&c_stream, 3);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflate", err); exit(1); } };

    compr[3]++;
    c_stream.avail_in = len - 3;

    err = deflate(&c_stream, 4);
    if (err != 1) {
        { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflate", err); exit(1); } };
    }
    err = deflateEnd(&c_stream);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflateEnd", err); exit(1); } };

    *comprLen = c_stream.total_out;
}




void test_sync(compr, comprLen, uncompr, uncomprLen)
    Byte *compr, *uncompr;
    uLong comprLen, uncomprLen;
{
    int err;
    z_stream d_stream;

    strcpy((char*)uncompr, "garbage");

    d_stream.zalloc = zalloc;
    d_stream.zfree = zfree;
    d_stream.opaque = (voidpf)0;

    d_stream.next_in = compr;
    d_stream.avail_in = 2;

    err = inflateInit_((&d_stream), "1.2.8", (int)sizeof(z_stream));
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "inflateInit", err); exit(1); } };

    d_stream.next_out = uncompr;
    d_stream.avail_out = (uInt)uncomprLen;

    inflate(&d_stream, 0);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "inflate", err); exit(1); } };

    d_stream.avail_in = (uInt)comprLen-2;
    err = inflateSync(&d_stream);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "inflateSync", err); exit(1); } };

    err = inflate(&d_stream, 4);
    if (err != (-3)) {
        fprintf(stderr, "inflate should report DATA_ERROR\n");

        exit(1);
    }
    err = inflateEnd(&d_stream);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "inflateEnd", err); exit(1); } };

    printf("after inflateSync(): hel%s\n", (char *)uncompr);
}




void test_dict_deflate(compr, comprLen)
    Byte *compr;
    uLong comprLen;
{
    z_stream c_stream;
    int err;

    c_stream.zalloc = zalloc;
    c_stream.zfree = zfree;
    c_stream.opaque = (voidpf)0;

    err = deflateInit_((&c_stream), (9), "1.2.8", (int)sizeof(z_stream));
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflateInit", err); exit(1); } };

    err = deflateSetDictionary(&c_stream,
                (const Bytef*)dictionary, (int)sizeof(dictionary));
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflateSetDictionary", err); exit(1); } };

    dictId = c_stream.adler;
    c_stream.next_out = compr;
    c_stream.avail_out = (uInt)comprLen;

    c_stream.next_in = ( unsigned char *)hello;
    c_stream.avail_in = (uInt)strlen(hello)+1;

    err = deflate(&c_stream, 4);
    if (err != 1) {
        fprintf(stderr, "deflate should report Z_STREAM_END\n");
        exit(1);
    }
    err = deflateEnd(&c_stream);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "deflateEnd", err); exit(1); } };
}




void test_dict_inflate(compr, comprLen, uncompr, uncomprLen)
    Byte *compr, *uncompr;
    uLong comprLen, uncomprLen;
{
    int err;
    z_stream d_stream;

    strcpy((char*)uncompr, "garbage");

    d_stream.zalloc = zalloc;
    d_stream.zfree = zfree;
    d_stream.opaque = (voidpf)0;

    d_stream.next_in = compr;
    d_stream.avail_in = (uInt)comprLen;

    err = inflateInit_((&d_stream), "1.2.8", (int)sizeof(z_stream));
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "inflateInit", err); exit(1); } };

    d_stream.next_out = uncompr;
    d_stream.avail_out = (uInt)uncomprLen;

    for (;;) {
        err = inflate(&d_stream, 0);
        if (err == 1) break;
        if (err == 2) {
            if (d_stream.adler != dictId) {
                fprintf(stderr, "unexpected dictionary");
                exit(1);
            }
            err = inflateSetDictionary(&d_stream, (const Bytef*)dictionary,
                                       (int)sizeof(dictionary));
        }
        { if (err != 0) { fprintf(stderr, "%s error: %d\n", "inflate with dict", err); exit(1); } };
    }

    err = inflateEnd(&d_stream);
    { if (err != 0) { fprintf(stderr, "%s error: %d\n", "inflateEnd", err); exit(1); } };

    if (strcmp((char*)uncompr, hello)) {
        fprintf(stderr, "bad inflate with dict\n");
        exit(1);
    } else {
        printf("inflate with dictionary: %s\n", (char *)uncompr);
    }
}





int main_example(argc, argv)
    int argc;
    char *argv[];
{
    Byte *compr, *uncompr;
    uLong comprLen = 10000*sizeof(int);
    uLong uncomprLen = comprLen;
    static const char* myVersion = "1.2.8";

    if (zlibVersion()[0] != myVersion[0]) {
        fprintf(stderr, "incompatible zlib version\n");
        exit(1);

    } else if (strcmp(zlibVersion(), "1.2.8") != 0) {
        fprintf(stderr, "warning: different zlib version\n");
    }

    printf("zlib version %s = 0x%04x, compile flags = 0x%lx\n",
            "1.2.8", 0x1280, zlibCompileFlags());

    compr = (Byte*)calloc((uInt)comprLen, 1);
    uncompr = (Byte*)calloc((uInt)uncomprLen, 1);



    if (compr == 0 || uncompr == 0) {
        printf("out of memory\n");
        exit(1);
    }




    test_compress(compr, comprLen, uncompr, uncomprLen);

    test_gzio((argc > 1 ? argv[1] : "foo.gz"),
              uncompr, uncomprLen);


    test_deflate(compr, comprLen);
    test_inflate(compr, comprLen, uncompr, uncomprLen);

    test_large_deflate(compr, comprLen, uncompr, uncomprLen);
    test_large_inflate(compr, comprLen, uncompr, uncomprLen);

    test_flush(compr, &comprLen);
    test_sync(compr, comprLen, uncompr, uncomprLen);
    comprLen = uncomprLen;

    test_dict_deflate(compr, comprLen);
    test_dict_inflate(compr, comprLen, uncompr, uncomprLen);

    free(compr);
    free(uncompr);

    return 0;
}
