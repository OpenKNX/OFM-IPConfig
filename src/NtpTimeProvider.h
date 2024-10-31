#pragma once
#include "OpenKNX.h"
#include "knxprod.h"

#ifdef ParamNET_NTP
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