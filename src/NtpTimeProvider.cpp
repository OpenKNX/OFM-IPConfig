#ifdef NET_USE_NTP
#include "NtpTimeProvider.h"
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
    for (size_t i = 0; const char* serverName = sntp_getservername(i); i++)
    { 
        logInfoP("NTP Server %s: %d %s", serverName, (int) sntp_getreachability(i), sntp_getreachability(i) == 0 ? "not reachable or not used" : "reachable");
    }
}

const std::string NtpTimeProvider::logPrefix()
{
    return "NTP";
}


void NtpTimeProvider::setup()
{
    sntp_stop();
    currentInstance = this;
    sntp_set_time_sync_notification_cb([](struct timeval *tv) {
        currentInstance->timeSet();
    });
    sntp_set_sync_mode(SNTP_SYNC_MODE_SMOOTH);
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "0.at.pool.ntp.org");
    sntp_setservername(1, "1.at.pool.ntp.org");
    sntp_setservername(2, "2.at.pool.ntp.org");
    sntp_init();
 
}

NtpTimeProvider::~NtpTimeProvider()
{
    sntp_stop();
    currentInstance = nullptr;
}

#endif