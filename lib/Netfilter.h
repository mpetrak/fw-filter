
#ifndef NETFILTER_H
#define	NETFILTER_H

#define EB_OUTUP_FILE "data/ebfile"
#define EB_CHAIN "FORWARD"

#define EB_COMMAND "ebtables-restore < %1"
#define EB_COMMAND_APPEND "-A"
#define EB_COMMAND_CHAIN ""
#define EB_COMMAND_INPUT_IFACE "-i"
#define EB_COMMAND_OUTPUT_IFACE "-o"
#define EB_COMMAND_SOURCE_ADDR "-s"
#define EB_COMMAND_DEST_ADDR "-d"
#define EB_COMMAND_ACTION "-j"

#endif	/* NETFILTER_H */

