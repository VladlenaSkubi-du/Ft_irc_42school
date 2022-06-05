#include "ircserv.hpp"

static 	std::string		error_explaination[ERRORS_NUM] = {
		"no configuration file found",
		"duplication of config file, please define one",
		"can not open configuration file",
		"wrong line formatting in conguration file",
		"no environmental variable found",
		"duplication of environmental variable"
	};

int			irc_usage(void) {
	std::cout << "usage:\n\t./" << PROGRAM_NAME << " config_file\n" <<
		"\tconfig_file should consist of lines with\n" <<
		"\tobligatory:\n" <<
		"\tKEY=VALUE\\n\n" <<
		"\toptional:\n" <<
		"\tKEY=VALUE\\n\n";
	return (0);
}

int					errors_management(error_ircserv ertype, std::string argument, bool usage_needed) {
	std::cerr << PROGRAM_NAME << ": " << error_explaination[static_cast<int>(ertype)];
	if (!argument.empty()) {
		std::cerr << ": " << argument;
	}
	std::cout << "\n";
	if (usage_needed) {
		irc_usage();
	}
	return (1);
}