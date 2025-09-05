#include "Session.h"
#include <android-base/file.h>
#include <android-base/logging.h>

namespace aidl::android::hardware::biometrics::fingerprint {

using ::android::sp;
using ::vendor::mediatek::hardware::biometrics::fingerprint::V2_1::ITranBiometricsFingerprint;

// Helper to write to the proc file, preserving the original HAL's quirk.
static void notifyDriverState(const std::string& payload) {
    if (!::android::base::WriteStringToFile(payload, "/proc/fingerprint_status")) {
        LOG(ERROR) << "Failed to write to /proc/fingerprint_status";
    }
}

Session::Session(int32_t sId, int32_t uId, const std::shared_ptr<ISessionCallback>& cb)
    : mSensorId(sId), mUserId(uId), mCallback(cb) {
    LOG(INFO) << "Session created";
    mVendorHal = ITranBiometricsFingerprint::getService("default", false);
    if (mVendorHal == nullptr) {
        LOG(ERROR) << "Could not connect to Mediatek Fingerprint HAL";
    }
}
Session::~Session() {
    close();
}
ndk::ScopedAStatus Session::enroll(const keymaster::HardwareAuthToken& hat) {
    LOG(INFO) << "Session::enroll";
    notifyDriverState("\x21\x18");
    if (mVendorHal != nullptr) {
        // TODO: Adapt the callback and parameters as needed.
        // mVendorHal->preEnroll();
        // mVendorHal->enroll(...);
    }
    return ndk::ScopedAStatus::ok();
}
ndk::ScopedAStatus Session::authenticate(int64_t operationId) {
    LOG(INFO) << "Session::authenticate";
    notifyDriverState("\x21\x18");
    if (mVendorHal != nullptr) {
        // mVendorHal->authenticate(operationId, mUserId);
    }
    return ndk::ScopedAStatus::ok();
}
ndk::ScopedAStatus Session::cancel() {
    LOG(INFO) << "Session::cancel";
    if (mVendorHal != nullptr) {
        mVendorHal->cancel();
    }
    return ndk::ScopedAStatus::ok();
}
ndk::ScopedAStatus Session::close() {
    LOG(INFO) << "Session::close";
    notifyDriverState("\x21\x18"); // Mimics cancel behavior from original file
    cancel();
    mCallback->onSessionClosed();
    return ndk::ScopedAStatus::ok();
}

// --- Empty implementations for the rest of the interface ---
ndk::ScopedAStatus Session::generateChallenge() { return ndk::ScopedAStatus::ok(); }
ndk::ScopedAStatus Session::revokeChallenge(int64_t) { return ndk::ScopedAStatus::ok(); }
ndk::ScopedAStatus Session::detectInteraction() { return ndk::ScopedAStatus::ok(); }
ndk::ScopedAStatus Session::enumerateEnrollments() { return ndk::ScopedAStatus::ok(); }
ndk::ScopedAStatus Session::removeEnrollments(const std::vector<int32_t>&) { return ndk::ScopedAStatus::ok(); }
ndk::ScopedAStatus Session::getAuthenticatorId() { return ndk::ScopedAStatus::ok(); }
ndk::ScopedAStatus Session::invalidateAuthenticatorId() { return ndk::ScopedAStatus::ok(); }
ndk::ScopedAStatus Session::resetLockout(const keymaster::HardwareAuthToken&) { return ndk::ScopedAStatus::ok(); }
ndk::ScopedAStatus Session::onPointerDown(int32_t, int32_t, int32_t, float, float) { return ndk::ScopedAStatus::ok(); }
ndk::ScopedAStatus Session::onPointerUp(int32_t) { return ndk::ScopedAStatus::ok(); }
ndk::ScopedAStatus Session::onUiReady() { return ndk::ScopedAStatus::ok(); }
}
