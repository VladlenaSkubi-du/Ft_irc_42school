#include "ircserv.hpp"
#include <fstream>
#include <sstream>

int		parse_config_file(std::ifstream& config_file) {
	std::string line;
	while (std::getline(config_file, line))
	{
		if (line[0] == '#') {
			continue ;
		}
		if (line.find("=") == std::string::npos) { 
			errors_management(CONFIG_WRONG_FORMAT, line, 1);
			exit(1); 
		}
	}
	return (0);
}

int		check_config_file(int argc, char *argv[]) {
	if (argc < 2) {
		errors_management(CONFIG_NOFILE, "", 1);
		exit(1);
	}
	else if (argc != 2) {
		errors_management(CONFIG_DOUPLICATE_FILE, "", 1);
		exit(1);
	}
	std::ifstream config_file;
	config_file.open(argv[1], std::ifstream::in);
	if (!config_file) {
		errors_management(CONFIG_CANNOT_OPEN, argv[1], 0);
		exit(1);
	}
	parse_config_file(config_file);
	config_file.close();
	return (0);
}