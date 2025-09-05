#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include "Fingerprint.h"

using aidl::android::hardware::biometrics::fingerprint::Fingerprint;

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(1);
    auto hal = ndk::SharedRefBase::make<Fingerprint>();
    const std::string name = std::string() + Fingerprint::descriptor + "/default";

    if (AServiceManager_addService(hal->asBinder().get(), name.c_str()) != STATUS_OK) {
        LOG(ERROR) << "Could not register service: " << name;
        return 1;
    }
    LOG(INFO) << "Fingerprint HAL service running.";
    ABinderProcess_joinThreadPool();
    return 1; // Should not reach
}
