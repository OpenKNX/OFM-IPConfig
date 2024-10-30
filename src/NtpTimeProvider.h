#pragma once
#include "OpenKNX.h"
#ifdef NET_USE_NTP
class NtpTimeProvider : public OpenKNX::Time::TimeProvider
{
        static NtpTimeProvider* currentInstance;
    protected:
        const std::string logPrefix() override;
        void setup() override;
        void logInformation() override;
        ~NtpTimeProvider() override;
};
#endif