// SPDX-License-Identifier: GPL-2.0
/*
 * C++ stream style string formatter and printer used in KUnit for outputting
 * KUnit messages.
 *
 * Copyright (C) 2019, Google LLC.
 * Author: Mike Krinkin <krinkin@google.com>
 */
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/stddef.h>
#include <linux/string.h>
#include <test/strerror.h>


#define SUCCESS	0
#define MAKE_ERROR(errno)	[errno] = #errno

static const char * const errmap[] = {
	MAKE_ERROR(SUCCESS),
	MAKE_ERROR(EPERM),
	MAKE_ERROR(ENOENT),
	MAKE_ERROR(ESRCH),
	MAKE_ERROR(EINTR),
	MAKE_ERROR(EIO),
	MAKE_ERROR(ENXIO),
	MAKE_ERROR(E2BIG),
	MAKE_ERROR(ENOEXEC),
	MAKE_ERROR(EBADF),
	MAKE_ERROR(ECHILD),
	MAKE_ERROR(EAGAIN),
	MAKE_ERROR(ENOMEM),
	MAKE_ERROR(EACCES),
	MAKE_ERROR(EFAULT),
	MAKE_ERROR(ENOTBLK),
	MAKE_ERROR(EBUSY),
	MAKE_ERROR(EEXIST),
	MAKE_ERROR(EXDEV),
	MAKE_ERROR(ENODEV),
	MAKE_ERROR(ENOTDIR),
	MAKE_ERROR(EISDIR),
	MAKE_ERROR(EINVAL),
	MAKE_ERROR(ENFILE),
	MAKE_ERROR(EMFILE),
	MAKE_ERROR(ENOTTY),
	MAKE_ERROR(ETXTBSY),
	MAKE_ERROR(EFBIG),
	MAKE_ERROR(ENOSPC),
	MAKE_ERROR(ESPIPE),
	MAKE_ERROR(EROFS),
	MAKE_ERROR(EMLINK),
	MAKE_ERROR(EPIPE),
	MAKE_ERROR(EDOM),
	MAKE_ERROR(ERANGE),
	MAKE_ERROR(EDEADLK),
	MAKE_ERROR(ENAMETOOLONG),
	MAKE_ERROR(ENOLCK),
	MAKE_ERROR(ENOSYS),
	MAKE_ERROR(ENOTEMPTY),
	MAKE_ERROR(ELOOP),
	MAKE_ERROR(ENOMSG),
	MAKE_ERROR(EIDRM),
	MAKE_ERROR(ECHRNG),
	MAKE_ERROR(EL2NSYNC),
	MAKE_ERROR(EL3HLT),
	MAKE_ERROR(EL3RST),
	MAKE_ERROR(ELNRNG),
	MAKE_ERROR(EUNATCH),
	MAKE_ERROR(ENOCSI),
	MAKE_ERROR(EL2HLT),
	MAKE_ERROR(EBADE),
	MAKE_ERROR(EBADR),
	MAKE_ERROR(EXFULL),
	MAKE_ERROR(ENOANO),
	MAKE_ERROR(EBADRQC),
	MAKE_ERROR(EBADSLT),
	MAKE_ERROR(EBFONT),
	MAKE_ERROR(ENOSTR),
	MAKE_ERROR(ENODATA),
	MAKE_ERROR(ETIME),
	MAKE_ERROR(ENOSR),
	MAKE_ERROR(ENONET),
	MAKE_ERROR(ENOPKG),
	MAKE_ERROR(EREMOTE),
	MAKE_ERROR(ENOLINK),
	MAKE_ERROR(EADV),
	MAKE_ERROR(ESRMNT),
	MAKE_ERROR(ECOMM),
	MAKE_ERROR(EPROTO),
	MAKE_ERROR(EMULTIHOP),
	MAKE_ERROR(EDOTDOT),
	MAKE_ERROR(EBADMSG),
	MAKE_ERROR(EOVERFLOW),
	MAKE_ERROR(ENOTUNIQ),
	MAKE_ERROR(EBADFD),
	MAKE_ERROR(EREMCHG),
	MAKE_ERROR(ELIBACC),
	MAKE_ERROR(ELIBBAD),
	MAKE_ERROR(ELIBSCN),
	MAKE_ERROR(ELIBMAX),
	MAKE_ERROR(ELIBEXEC),
	MAKE_ERROR(EILSEQ),
	MAKE_ERROR(ERESTART),
	MAKE_ERROR(ESTRPIPE),
	MAKE_ERROR(EUSERS),
	MAKE_ERROR(ENOTSOCK),
	MAKE_ERROR(EDESTADDRREQ),
	MAKE_ERROR(EMSGSIZE),
	MAKE_ERROR(EPROTOTYPE),
	MAKE_ERROR(ENOPROTOOPT),
	MAKE_ERROR(EPROTONOSUPPORT),
	MAKE_ERROR(ESOCKTNOSUPPORT),
	MAKE_ERROR(EOPNOTSUPP),
	MAKE_ERROR(EPFNOSUPPORT),
	MAKE_ERROR(EAFNOSUPPORT),
	MAKE_ERROR(EADDRINUSE),
	MAKE_ERROR(EADDRNOTAVAIL),
	MAKE_ERROR(ENETDOWN),
	MAKE_ERROR(ENETUNREACH),
	MAKE_ERROR(ENETRESET),
	MAKE_ERROR(ECONNABORTED),
	MAKE_ERROR(ECONNRESET),
	MAKE_ERROR(ENOBUFS),
	MAKE_ERROR(EISCONN),
	MAKE_ERROR(ENOTCONN),
	MAKE_ERROR(ESHUTDOWN),
	MAKE_ERROR(ETOOMANYREFS),
	MAKE_ERROR(ETIMEDOUT),
	MAKE_ERROR(ECONNREFUSED),
	MAKE_ERROR(EHOSTDOWN),
	MAKE_ERROR(EHOSTUNREACH),
	MAKE_ERROR(EALREADY),
	MAKE_ERROR(EINPROGRESS),
	MAKE_ERROR(ESTALE),
	MAKE_ERROR(EUCLEAN),
	MAKE_ERROR(ENOTNAM),
	MAKE_ERROR(ENAVAIL),
	MAKE_ERROR(EISNAM),
	MAKE_ERROR(EREMOTEIO),
	MAKE_ERROR(EDQUOT),
	MAKE_ERROR(ENOMEDIUM),
	MAKE_ERROR(EMEDIUMTYPE),
	MAKE_ERROR(ECANCELED),
	MAKE_ERROR(ENOKEY),
	MAKE_ERROR(EKEYEXPIRED),
	MAKE_ERROR(EKEYREVOKED),
	MAKE_ERROR(EKEYREJECTED),
	MAKE_ERROR(EOWNERDEAD),
	MAKE_ERROR(ENOTRECOVERABLE),
	MAKE_ERROR(ERFKILL),
	MAKE_ERROR(EHWPOISON)
};

const char *strerror_str(int errno)
{
	if (errno < 0 || errno >= ARRAY_SIZE(errmap))
		return NULL;
	return errmap[errno];
}

const char *strerror_r(int errno, char *buf, size_t buflen)
{
	const char *err = strerror_str(errno);

	if (!buflen)
		return NULL;

	// GNU version of strerror_r() may sometimes return a pointer to a
	// static string, this implementation doesn't do it mostly to keep
	// the behavior consistent and predicatble.
	buf[buflen - 1] = '\0';
	if (err)
		return strncpy(buf, err, buflen - 1);
	snprintf(buf, buflen - 1, "%d (unknown error)", errno);
	return buf;
}
EXPORT_SYMBOL_GPL(strerror_r);