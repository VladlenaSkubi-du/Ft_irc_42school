#include "IrcServer.hpp"
#include "debug.hpp"

std::size_t		IrcServer::getAvailableUserId(void){
	if (availableUserId_ + 1 > 0)
		return ++availableUserId_;
	else {
		errors_management(SERVER_CANT_CREATE_USER, "", USAGE_NOT_PRINTED);
		return 0;
	}
}

std::size_t		IrcServer::getAvailableChannelId(void){
	if (availableChannelId_ + 1 > 0)
		return ++availableChannelId_;
	else {
		errors_management(SERVER_CANT_CREATE_CHANNEL, "", USAGE_NOT_PRINTED);
		return 0;
	}
}
