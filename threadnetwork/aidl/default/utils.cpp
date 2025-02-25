
/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <openthread/instance.h>
#include <openthread/logging.h>
#include <openthread/platform/alarm-milli.h>
#include <utils/Log.h>

void otLogPlatArgs(otLogLevel aLogLevel, const char* aPlatModuleName, const char* aFormat,
                   va_list aArgs) {
    OT_UNUSED_VARIABLE(aPlatModuleName);
    static const android_LogPriority kLogPriorities[] = {ANDROID_LOG_SILENT, ANDROID_LOG_FATAL,
                                                         ANDROID_LOG_WARN,   ANDROID_LOG_INFO,
                                                         ANDROID_LOG_INFO,   ANDROID_LOG_DEBUG};

    if (aLogLevel >= sizeof(kLogPriorities) / sizeof(android_LogPriority)) {
        return;
    }

    __android_log_vprint(kLogPriorities[aLogLevel], LOG_TAG, aFormat, aArgs);
}

void otLogCritPlat(const char* format, ...) {
    va_list args;

    va_start(args, format);
    __android_log_vprint(ANDROID_LOG_FATAL, LOG_TAG, format, args);
    va_end(args);
}

void otDumpDebgPlat(const char* aText, const void* aData, uint16_t aDataLength) {
#ifdef DEV_BUILD
    constexpr uint16_t kBufSize = 512;
    char buf[kBufSize];

    if ((aText != nullptr) && (aData != nullptr)) {
        const uint8_t* data = reinterpret_cast<const uint8_t*>(aData);

        for (uint16_t i = 0; (i < aDataLength) && (i < (kBufSize - 1) / 3); i++) {
            snprintf(buf + (i * 3), (kBufSize - 1) - (i * 3), "%02x ", data[i]);
        }

        __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "%s: %s", aText, buf);
    }
#else
    OT_UNUSED_VARIABLE(aText);
    OT_UNUSED_VARIABLE(aData);
    OT_UNUSED_VARIABLE(aDataLength);
#endif
}

OT_TOOL_WEAK void otPlatAlarmMilliFired(otInstance* aInstance) {
    OT_UNUSED_VARIABLE(aInstance);
}
