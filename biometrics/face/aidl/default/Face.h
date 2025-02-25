/*
 * Copyright (C) 2020 The Android Open Source Project
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

#pragma once

#include <aidl/android/hardware/biometrics/face/BnFace.h>
#include "FaceConfig.h"
#include "Session.h"

namespace aidl::android::hardware::biometrics::face {

class Face : public BnFace {
  public:
    Face() : mSession(nullptr) {}
    ndk::ScopedAStatus getSensorProps(std::vector<SensorProps>* _aidl_return) override;

    ndk::ScopedAStatus createSession(int32_t sensorId, int32_t userId,
                                     const std::shared_ptr<ISessionCallback>& cb,
                                     std::shared_ptr<ISession>* _aidl_return) override;

    binder_status_t dump(int fd, const char** args, uint32_t numArgs);
    binder_status_t handleShellCommand(int in, int out, int err, const char** argv, uint32_t argc);

    static FaceConfig& cfg() {
        static FaceConfig* cfg = nullptr;
        if (cfg == nullptr) {
            cfg = new FaceConfig();
            cfg->init();
        }
        return *cfg;
    }
    void resetConfigToDefault();
    static const char* type2String(FaceSensorType type);
    static const char* strength2String(common::SensorStrength strength);

  private:
    std::shared_ptr<Session> mSession;
    void onHelp(int);
};

}  // namespace aidl::android::hardware::biometrics::face
