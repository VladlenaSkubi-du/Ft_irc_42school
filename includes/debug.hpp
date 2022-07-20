#pragma once

#include <iostream>

#define PROGRAM_NAME "ircserv"
#define USAGE_NOT_PRINTED false
#define USAGE_PRINTED true

enum ErrorType {
	CONFIG_NOFILE = 0,
	CONFIG_DOUPLICATE_FILE,
	CONFIG_CANT_OPEN,
	CONFIG_WRONG_FORMAT,
	CONFIG_NOKEY,
	CONFIG_VALUE_INVALID,
	CONFIG_KEY_EMPTY,
	CONFIG_VALUE_EMPTY,
	SERVER_NO_HOSTIP,
	SERVER_CANT_SOCKET,
	SERVER_CANT_CREATE_CHANNEL,
	SERVER_CANT_CREATE_USER
};

int			errors_management(ErrorType ertype, std::string argument, bool usage_needed);
void		usage(void);