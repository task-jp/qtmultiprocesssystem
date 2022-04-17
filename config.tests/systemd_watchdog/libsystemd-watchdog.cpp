#include <systemd/sd-daemon.h>

int main(int argc,char **argv)
{
    return sd_notify(0, "WATCHDOG＝1");
}
