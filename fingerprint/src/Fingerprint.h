#pragma once
#include <aidl/android/hardware/biometrics/fingerprint/BnFingerprint.h>

namespace aidl::android::hardware::biometrics::fingerprint {
class Fingerprint : public BnFingerprint {
    ndk::ScopedAStatus getSensorProperties(SensorProperties* _return) override;
    ndk::ScopedAStatus createSession(int32_t sensorId, int32_t userId,
                                     const std::shared_ptr<ISessionCallback>& callback,
                                     std::shared_ptr<ISession>* _return) override;
};
}  // namespace aidl::android::hardware::biometrics::fingerprint
