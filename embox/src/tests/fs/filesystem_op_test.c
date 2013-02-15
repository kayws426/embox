/**
 * @file
 * @brief
 *
 * @date 05.07.2012
 * @author Andrey Gazukin
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include <cmd/mkfs.h>
#include <fs/vfs.h>
#include <fs/fs_drv.h>
#include <fs/sys/fsop.h>

#include <drivers/ramdisk.h>
#include <embox/block_dev.h>
#include <embox/test.h>

#include <mem/page.h>

EMBOX_TEST_SUITE("fs/filesystem test");

TEST_SETUP_SUITE(setup_suite);

TEST_TEARDOWN_SUITE(teardown_suite);

#define FS_NAME  "vfat"
#define FS_DEV  "/dev/ramdisk"
#define FS_BLOCKS  124
#define FS_DIR    "/tmp"
#define FS_DIR1   "/tmp/foo"
#define FS_DIR2   "/tmp/foo/bar"
#define FS_FILE1  "/tmp/foo/bar/abc.txt"
#define FS_FILE2  "/tmp/foo/bar/xyz.txt"

TEST_CASE("Create fat filesystem") {
	test_assert_zero(format(FS_DEV, FS_NAME));
}

TEST_CASE("Mount fat filesystem") {
	test_assert_zero(mount(FS_DEV, FS_DIR, FS_NAME));
}

TEST_CASE("Create files and directories") {
	int fd;
	test_assert_zero(mkdir(FS_DIR1, 0777));
	test_assert_zero(mkdir(FS_DIR2, 0777));
	test_assert_not_zero(fd = creat(FS_FILE1, 0));
	test_assert_not_equal(-1, fd);
	close(fd);
	test_assert_not_zero(fd = creat(FS_FILE2, 0));
	test_assert_not_equal(-1, fd);
	close(fd);
}

TEST_CASE("Delete file") {
	test_assert_zero(remove(FS_FILE1));
	test_assert_zero(remove(FS_FILE2));
	test_assert(0 > open(FS_FILE1, O_RDONLY));
	test_assert(0 > open(FS_FILE2, O_RDONLY));
	test_assert_zero(remove(FS_DIR2));
	test_assert_zero(remove(FS_DIR1));
}

static int setup_suite(void) {
	return ramdisk_create(FS_DEV, FS_BLOCKS * PAGE_SIZE());
}

static int teardown_suite(void) {
	return ramdisk_delete(FS_DEV);
}
