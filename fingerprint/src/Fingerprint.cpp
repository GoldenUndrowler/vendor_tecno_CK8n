#include "Fingerprint.h"
#include "Session.h"
#include <android-base/logging.h>

namespace aidl::android::hardware::biometrics::fingerprint {
ndk::ScopedAStatus Fingerprint::getSensorProperties(SensorProperties* _return) {
    LOG(INFO) << "Getting sensor properties";
    _return->sensorId = 0;
    _return->sensorStrength = common::SensorStrength::STRONG;
    _return->maxEnrollmentsPerUser = 5;
    _return->sensorType = SensorType::UDFPS_OPTICAL;
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Fingerprint::createSession(int32_t sensorId, int32_t userId,
                                             const std::shared_ptr<ISessionCallback>& cb,
                                             std::shared_ptr<ISession>* _return) {
    LOG(INFO) << "Creating new session for sensorId: " << sensorId << " userId: " << userId;
    auto session = ndk::SharedRefBase::make<Session>(sensorId, userId, cb);
    *_return = session;
    return ndk::ScopedAStatus::ok();
}
}  // namespace aidl::android::hardware::biometrics::fingerprint
