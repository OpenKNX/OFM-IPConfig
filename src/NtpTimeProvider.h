#ifdef ParamNET_NTP
    #ifdef ARDUINO_ARCH_ESP32
        #pragma once
        #include "OpenKNX.h"
        #include "knxprod.h"

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
#endif