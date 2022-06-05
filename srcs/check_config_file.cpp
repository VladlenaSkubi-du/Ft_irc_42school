#include "ircserv.hpp"
#include <fstream>
#include <sstream>

int		parse_config_file(std::ifstream& config_file, ConfigValues& config_values) {
	std::string line;
	while (std::getline(config_file, line))
	{
		if (line[0] == '#') {
			continue ;
		}
		std::size_t pos = line.find("=");
		if (pos == std::string::npos) { 
			errors_management(CONFIG_WRONG_FORMAT, line, USAGE_PRINTED);
			exit(1); 
		}
		config_values.save_value_by_key(line.substr(0, pos),
										line.substr(pos + 1, line.size() - pos - 1));
	}
	return (0);
}

int		check_config_file(int argc, char *argv[], ConfigValues& config_values) {
	if (argc < 2) {
		errors_management(CONFIG_NOFILE, "", USAGE_PRINTED);
		exit(1);
	}
	else if (argc != 2) {
		errors_management(CONFIG_DOUPLICATE_FILE, "", USAGE_PRINTED);
		exit(1);
	}
	std::ifstream config_file;
	config_file.open(argv[1], std::ifstream::in);
	if (!config_file) {
		errors_management(CONFIG_CANNOT_OPEN, argv[1], USAGE_NOT_PRINTED);
		exit(1);
	}
	parse_config_file(config_file, config_values);
	config_file.close();
	return (0);
}