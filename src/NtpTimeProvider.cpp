#include "NtpTimeProvider.h"
#ifdef ARDUINO_ARCH_ESP32
#ifdef ParamNET_NTPServer
    #include "lwip/apps/sntp.h"
    #include <esp_sntp.h>

NtpTimeProvider* NtpTimeProvider::currentInstance = nullptr;

void NtpTimeProvider::logInformation()
{
    logInfoP("Timeprovider: NTP");
    switch (sntp_get_sync_status())
    {
        case sntp_sync_status_t::SNTP_SYNC_STATUS_COMPLETED:
            logInfoP("Time synchronized");
            break;
        case sntp_sync_status_t::SNTP_SYNC_STATUS_IN_PROGRESS:
            logInfoP("Time synchronization in progress");
            break;
        case sntp_sync_status_t::SNTP_SYNC_STATUS_RESET:
            logInfoP("Time synchronization reset");
            break;
    }
    bool serverFound = false;
    bool reachable = false;
    for (size_t i = 0; sntp_getservername(i); i++)
    {
        if ((int)sntp_getreachability(i))
            reachable = true;
        serverFound = true;
    }
    if (serverFound)
        logInfoP("NTP Server %s: %s", ParamNET_NTPServer, reachable ? "reachable" : "not reachable or not used");
    else
        logErrorP("No NTP server configured");
}

const std::string NtpTimeProvider::logPrefix()
{
    return "Time<NTP>";
}

void NtpTimeProvider::setup()
{
    sntp_stop();
    u8_t index = 0;
    if (strlen((const char*)ParamNET_NTPServer) > 0)
    {
        // Configure the NTP server 3 times because the DNS should be queried multible times to return differnt IP addresses
        sntp_setservername(index++, (const char*)ParamNET_NTPServer);
        sntp_setservername(index++, (const char*)ParamNET_NTPServer);
        sntp_setservername(index++, (const char*)ParamNET_NTPServer);
    }
    if (index > 0)
    {
        currentInstance = this;
        sntp_set_time_sync_notification_cb([](struct timeval* tv) {
            currentInstance->timeSet();
        });
        sntp_set_sync_mode(SNTP_SYNC_MODE_SMOOTH);
        sntp_setoperatingmode(SNTP_OPMODE_POLL);
        sntp_init();
    }
    else
    {
        logErrorP("No NTP server configured");
    }
}

NtpTimeProvider::~NtpTimeProvider()
{
    sntp_stop();
    currentInstance = nullptr;
}

#endif
#endif