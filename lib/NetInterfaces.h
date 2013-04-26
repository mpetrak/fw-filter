
#ifndef NETINTERFACES_H
#define	NETINTERFACES_H

#include <stdlib.h>
#include <stdio.h>
#include <QStringList>
#include <QString>

class NetInterfaces {
public:
    NetInterfaces();
    virtual ~NetInterfaces();

    /**
     * Reload information about network interfaces from
     * system.
     * @return true - success / false - fault 
     */
    bool reloadInterfaces();

    /**
     * Get list of system network interfaces.
     * @return list of interfaces names
     */
    QStringList getIfList() const;
private:
    /** List of interfaces names */
    QStringList *ifList;

};

#endif	/* NETINTERFACES_H */

