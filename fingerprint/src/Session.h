#pragma once
#include <aidl/android/hardware/biometrics/fingerprint/BnSession.h>
#include <vendor/mediatek/hardware/biometrics/fingerprint/2.1/ITranBiometricsFingerprint.h>
#include <android/hidl/base/1.0/IBase.h>

namespace aidl::android::hardware::biometrics::fingerprint {
class Session : public BnSession {
public:
    Session(int32_t sensorId, int32_t userId, const std::shared_ptr<ISessionCallback>& callback);
    ~Session();
    ndk::ScopedAStatus generateChallenge() override;
    ndk::ScopedAStatus revokeChallenge(int64_t challenge) override;
    ndk::ScopedAStatus enroll(const keymaster::HardwareAuthToken& hat) override;
    ndk::ScopedAStatus authenticate(int64_t operationId) override;
    ndk::ScopedAStatus detectInteraction() override;
    ndk::ScopedAStatus enumerateEnrollments() override;
    ndk::ScopedAStatus removeEnrollments(const std::vector<int32_t>& enrollmentIds) override;
    ndk::ScopedAStatus getAuthenticatorId() override;
    ndk::ScopedAStatus invalidateAuthenticatorId() override;
    ndk::ScopedAStatus resetLockout(const keymaster::HardwareAuthToken& hat) override;
    ndk::ScopedAStatus close() override;
    ndk::ScopedAStatus onPointerDown(int32_t pointerId, int32_t x, int32_t y, float minor, float major) override;
    ndk::ScopedAStatus onPointerUp(int32_t pointerId) override;
    ndk::ScopedAStatus onUiReady() override;
    ndk::ScopedAStatus cancel() override;

private:
    int32_t mSensorId;
    int32_t mUserId;
    std::shared_ptr<ISessionCallback> mCallback;
    android::sp<vendor::mediatek::hardware::biometrics::fingerprint::V2_1::ITranBiometricsFingerprint> mVendorHal;
};
}  // namespace aidl::android::hardware::biometrics::fingerprint
