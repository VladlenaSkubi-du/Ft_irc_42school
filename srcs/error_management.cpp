#include "ircserv.hpp"

int			irc_usage(void) {
	std::cout << "usage:\n\t./" << PROGRAM_NAME << " config_file\n";
	return (0);
}

static std::string	irc_errors_explanation(int sequence_num) {
	std::string		seq_action[ERRORS_NUM] = {
		"no configuration file found",
		"dublication of environmental variable",
		"no environmental variable found"
	};
	return (seq_action[sequence_num]);
}

int					errors_management(error_ircserv ertype, std::string argument, bool usage_needed) {
	std::cerr << PROGRAM_NAME << ": " << irc_errors_explanation(static_cast<int>(ertype));
	if (!argument.empty()) {
		std::cerr << ": " << argument;
	}
	std::cout << "\n";
	if (usage_needed) {
		irc_usage();
	}
	return (1);
}