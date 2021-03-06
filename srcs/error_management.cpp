#include "debug.hpp"

static const std::string		error_explaination[] = {
		"no configuration file found",
		"duplication of config file, please define one",
		"can not open configuration file",
		"wrong line formatting in conguration file",
		"environmental variable not found",
		"value should not contain the following",
		"key is empty, please, comment with # or define",
		"value for key is empty, please, comment with # or define",
		"host IP stated is unavailable",
		"can not create socket for server",
		"can not create new channel",
		"can not create new user"
	};

void		usage(void) {
	std::cout << "usage:\n\t./" << PROGRAM_NAME << " config_file\n" <<
		"\tconfig_file should consist of lines with\n" <<
		"\tKEY=VALUE\\n\n" <<
		"\tobligatory: PASSWORD, PORT" <<
		"\toptional: HOSTNAME\n";
}

int					errors_management(ErrorType ertype, const std::string &argument, bool usage_needed) {
	std::cerr << PROGRAM_NAME << ": " << error_explaination[static_cast<int>(ertype)];
	if (!argument.empty()) {
		std::cerr << ": " << argument;
	}
	std::cout << std::endl;
	if (usage_needed) {
		usage();
	}
	return (static_cast<int>(ertype));
}