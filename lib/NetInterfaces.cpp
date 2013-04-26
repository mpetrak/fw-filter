
#include "NetInterfaces.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ifaddrs.h>

NetInterfaces::NetInterfaces() {
    this->ifList = new QStringList();
    /* load initial informations */
    this->reloadInterfaces();
}

NetInterfaces::~NetInterfaces() {
    free(this->ifList);
}

bool NetInterfaces::reloadInterfaces() {

    struct ifaddrs *ifaddr, *ifa;

    /* On load error exit */
    if (getifaddrs(&ifaddr) == -1) {
        return false;

    } else {

        /* iterate each interface */
        for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {

            int family = ifa->ifa_addr->sa_family;

            /* add to interface list every of AF_PACKET family */
            if (family == AF_PACKET) {
                this->ifList->append(QString(ifa->ifa_name));
            }

            /* print interface */
            //            printf("%s - family: %d(%s)\n",
            //                    ifa->ifa_name,
            //                    family,
            //                    (family == AF_PACKET) ? " (PACKET)" :
            //                    (family == AF_INET) ? " (INET)" :
            //                    (family == AF_INET6) ? "(INET6)" : "");      
        }

        freeifaddrs(ifaddr);
        return true;
    }
}

QStringList NetInterfaces::getIfList() const {
    return *this->ifList;
}

