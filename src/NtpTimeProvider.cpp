#include "NtpTimeProvider.h"
#ifdef ParamNET_NTP
    #include "lwip/apps/sntp.h"
    #include <esp_sntp.h>

NtpTimeProvider* NtpTimeProvider::currentInstance = nullptr;

void NtpTimeProvider::logInformation()
{
    logInfoP("Time Provider NTP");
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
    for (size_t i = 0; const char* serverName = sntp_getservername(i); i++)
    {
        serverFound = true;
        logInfoP("NTP Server %s: %d %s", serverName, (int)sntp_getreachability(i), sntp_getreachability(i) == 0 ? "not reachable or not used" : "reachable");
    }
    if (!serverFound)
        logErrorP("No NTP server configured");
}

const std::string NtpTimeProvider::logPrefix()
{
    return "NTP";
}

void NtpTimeProvider::setup()
{
    sntp_stop();
    u8_t index = 0;
    if (strlen((const char*)ParamNET_NTPServer1) > 0)
        sntp_setservername(index++, (const char*)ParamNET_NTPServer1);
    if (strlen((const char*)ParamNET_NTPServer2) > 0)
        sntp_setservername(index++, (const char*)ParamNET_NTPServer2);
    if (strlen((const char*)ParamNET_NTPServer3) > 0)
        sntp_setservername(index++, (const char*)ParamNET_NTPServer3);
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