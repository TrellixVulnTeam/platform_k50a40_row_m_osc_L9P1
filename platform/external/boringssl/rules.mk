# Copyright (C) 2015 The Android Open Source Project.
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
# SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
# OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
# CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

# This file is not used in the Android build process! It's used only by Trusty.


LOCAL_DIR := $(GET_LOCAL_DIR)
LOCAL_PATH := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

TARGET_ARCH := $(ARCH)
TARGET_2ND_ARCH := $(ARCH)

# Reset local variables
LOCAL_CFLAGS :=
LOCAL_C_INCLUDES :=
LOCAL_SRC_FILES_$(TARGET_ARCH) :=
LOCAL_SRC_FILES_$(TARGET_2ND_ARCH) :=
LOCAL_CFLAGS_$(TARGET_ARCH) :=
LOCAL_CFLAGS_$(TARGET_2ND_ARCH) :=
LOCAL_ADDITIONAL_DEPENDENCIES :=

# get target_c_flags, target_c_includes, target_src_files
MODULE_SRCDEPS += $(LOCAL_DIR)/crypto-sources.mk
include $(LOCAL_DIR)/crypto-sources.mk

LOCAL_SRC_FILES += $(crypto_sources)

# Some files in BoringSSL use OS functions that aren't supported by Trusty. The
# easiest way to deal with them is not to include them. As long as no path to
# the functions defined in these files exists, the linker will be happy. If
# such a path is created, it'll be a link-time error and something more complex
# may need to be considered.
LOCAL_SRC_FILES := $(filter-out android_compat_hacks.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out src/crypto/bio/connect.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out src/crypto/bio/fd.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out src/crypto/bio/file.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out src/crypto/bio/socket.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out src/crypto/bio/socket_helper.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out src/crypto/directory_posix.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out src/crypto/rand/urandom.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out src/crypto/time_support.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out src/crypto/x509/by_dir.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out src/crypto/x509v3/v3_utl.c,$(LOCAL_SRC_FILES))

# BoringSSL detects Trusty based on this define and does things like switch to
# no-op threading functions.
MODULE_CFLAGS += -DTRUSTY

MODULE_SRCS += $(addprefix $(LOCAL_DIR)/,$(LOCAL_SRC_FILES))
ifeq (arm, $(ARCH))
MODULE_SRCS += $(addprefix $(LOCAL_DIR)/,$(linux_arm_sources))
else
ifeq (arm64, $(ARCH))
MODULE_SRCS += $(addprefix $(LOCAL_DIR)/,$(linux_arm64_sources))
else
MODULE_SRCS += $(addprefix $(LOCAL_DIR)/,$(LOCAL_SRC_FILES_$(ARCH)))
endif
endif
LOCAL_C_INCLUDES := src/crypto src/include

GLOBAL_INCLUDES += $(addprefix $(LOCAL_DIR)/,$(LOCAL_C_INCLUDES))

MODULE_DEPS := \
	lib/openssl-stubs \
	lib/libc-trusty

include make/module.mk
