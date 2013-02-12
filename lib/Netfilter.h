
#ifndef NETFILTER_H
#define	NETFILTER_H

#define EB_OUTUP_FILE "data/ebfile"
#define EB_CHAIN "FILTER"

#define EB_COMMAND "ebtables-restore < %1"
#define EB_COMMAND_APPEND "-A"
#define EB_COMMAND_CHAIN ""
#define EB_COMMAND_INPUT_IFACE "-i"
#define EB_COMMAND_OUTPUT_IFACE "-o"
#define EB_COMMAND_SOURCE_ADDR "-s"
#define EB_COMMAND_DEST_ADDR "-d"
#define EB_COMMAND_PROTOCOL "-p"
#define EB_COMMAND_ACTION "-j"

#define IP_OUTUP_FILE "data/ipfile"
#define IP_CHAIN "FILTER"

#define IP_COMMAND "iptables-restore < %1"
#define IP_COMMAND_APPEND "-A"
#define IP_COMMAND_CHAIN ""
#define IP_COMMAND_INPUT_IFACE "-i"
#define IP_COMMAND_OUTPUT_IFACE "-o"
#define IP_COMMAND_SOURCE_ADDR "-s"
#define IP_COMMAND_DEST_ADDR "-d"
#define IP_COMMAND_PROTOCOL "-p"
#define IP_COMMAND_ACTION "-j"

#endif	/* NETFILTER_H */

