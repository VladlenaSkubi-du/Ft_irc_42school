#pragma once

#include <iostream>

#define PROGRAM_NAME "ircserv"
#define USAGE_NOT_PRINTED 0
#define USAGE_PRINTED 1
#define ERRORS_NUM 10

enum  error_ircserv {
	CONFIG_NOFILE = 0,
	CONFIG_DOUPLICATE_FILE,
	CONFIG_CANNOT_OPEN,
	CONFIG_WRONG_FORMAT,
	CONFIG_NOKEY,
	CONFIG_VALUE_INVALID,
	CONFIG_KEY_EMPTY,
	CONFIG_VALUE_EMPTY,
	SERVER_NO_HOSTIP,
	SERVER_CANNOT_SOCKET,
};

int			errors_management(error_ircserv ertype, std::string argument, bool usage_needed);
void		irc_usage(void);