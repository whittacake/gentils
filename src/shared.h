/*
 * Functions and types prefixed with g_
 * to make a common POSIX-like interface 
 * between GNU/Linux and Windows
 */
#ifndef GENTILS_SHARED_H
#define GENTILS_SHARED_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#ifndef _WIN32
#include <features.h>
#endif

#if defined(_POSIX_SOURCE)

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

enum { G_O_BINARY = 0 };

#define g_open(P, F, M)		open(P, F, M)
#define g_read(F, B, N)		read(F, B, N)
#define g_write(F, B, N)	write(F, B, N)
#define g_lseek(F, O, W)	lseek(F, O, W)
#define g_close(F)		close(F)
#define g_mkdir(P, M)		mkdir(P, M)
#define g_rmdir(P)		rmdir(P)
#define g_unlink(P)		unlink(P)

#elif defined(_WIN32)

#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>

enum { G_O_BINARY = O_BINARY };

#define g_open(P, F, M)		_open(P, F, M)
#define g_read(F, B, N)		_read(F, B, N)
#define g_write(F, B, N)	_write(F, B, N)
#define g_lseek(F, O, W)	_lseek(F, O, W)
#define g_close(F)		_close(F)
#define g_mkdir(P, M)		_mkdir(P)
#define g_rmdir(P)		_rmdir(P)
#define g_unlink(P)		_unlink(P)

#else
#error Fuck off macfag.
#endif

enum {
	G_O_APPEND = O_APPEND,
	G_O_CREAT = O_CREAT,
	G_O_EXCL = O_EXCL,
	G_O_RDONLY = O_RDONLY,
	G_O_RDWR = O_RDWR,
	G_O_TRUNC = O_TRUNC,
	G_O_WRONLY = O_WRONLY
};

#ifdef __cplusplus
}
#endif

#endif
