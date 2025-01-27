/*
* Copyright (C) 2015 MediaTek Inc.
* Modification based on code covered by the mentioned copyright
* and/or permission notice(s).
*/
/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <errno.h>
#include <sys/mman.h>
#include <unistd.h>

#include "private/ErrnoRestorer.h"

extern "C" void* _mmap_arm64_internal(void*, size_t, int, int, int, off64_t);

static bool kernel_has_MADV_MERGEABLE = true;

void* mmap64(void* addr, size_t size, int prot, int flags, int fd, off64_t offset) {
  if (offset < 0) {
    errno = EINVAL;
    return MAP_FAILED;
  }

  bool is_private_anonymous = (flags & (MAP_PRIVATE | MAP_ANONYMOUS)) != 0;
  void* result = _mmap_arm64_internal(addr, size, prot, flags, fd, offset);

  if (result != MAP_FAILED && kernel_has_MADV_MERGEABLE && is_private_anonymous) {
    ErrnoRestorer errno_restorer;
    int rc = madvise(result, size, MADV_MERGEABLE);
    if (rc == -1 && errno == EINVAL) {
      kernel_has_MADV_MERGEABLE = false;
    }
  }

  return result;
}

void* mmap(void* addr, size_t size, int prot, int flags, int fd, off_t offset) {
  return mmap64(addr, size, prot, flags, fd, static_cast<off64_t>(offset));
}
