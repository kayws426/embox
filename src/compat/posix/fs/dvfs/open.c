/**
 * @file
 * @brief
 *
 * @author  Denis Deryugin
 * @date    29 Mar 2015
 */

#include <fs/dvfs.h>
#include <kernel/task.h>
#include <kernel/task/resource/file_table.h>

int open(const char *path, int __oflag, ...) {
	struct file *file;
	struct file_table *ft;
	int res;

	file = dvfs_alloc_file();
	res = dvfs_open(path, file, __oflag);

	ft = task_resource_file_table(task_self());
	for (res = 0; res < FILE_TABLE_SZ; res++)
		if (ft->file[res] == NULL) {
			ft->file[res] = file;
			break;
		}

	if (res == FILE_TABLE_SZ)
		res = -1;

	return res;
}

