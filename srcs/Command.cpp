# include "Server.hpp"

void	Server::execute(User &user, Message message)
{
	std::string					prefix = message.prefix();
	std::string					command = message.command();
	std::vector<std::string>	params = message.params();

	try
	{
		if (command == "QUIT")
			quit(user);
		else if (command == "PING")
			cmd_ping(user, user.message());
		else if (command == "PONG")
			cmd_pong(user, user.message());
		else if (command == "PASS")
			cmd_pass(user, params);
		else if (command == "NICK")
			cmd_nick(user, params);
		else if (command == "USER")
			cmd_user(user, params);
		else if (!user.is_registered() && command != "NICK" && command != "USER")
			user.send_err(ERR_NOTREGISTERED);
		else if (command == "OPER")
			cmd_oper(user, params);
		else if (command == "MODE")
			cmd_mode(user, params);
		else if (is_flooding(user))
			return ;
		else if (command == "JOIN")
			cmd_join(user, params);
		else if (command == "KICK")
			cmd_kick(user, params);
		else if (command == "PART")
			cmd_part(user, params);
		else if (command == "PRIVMSG")
			cmd_privmsg(user, params);
		else if (command == "NOTICE")
			cmd_notice(user, params);
		else if (command == "NAMES")
			cmd_names(user, params);
		else if (command == "LIST")
			cmd_list(user, params);
		else if (command == "TOPIC")
			cmd_topic(user, params);
		else
			user.send_err(ERR_UNKNOWNCOMMAND);
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what();
	}
}

void	Server::cmd_pass(User &user, std::vector<std::string> &params)
{
	if (params.size() != 1)
		user.send_err(ERR_NEEDMOREPARAMS(user.nickname(), "pass"));
	if (user.is_authenticated())
		user.send_err(ERR_ALREADYREGISTRED(user.nickname()));
	if (params.size() == 1)
	{
		if (params[0] == _password)
		{
			user.set_authenticated(true);
			user.send_msg(RPL_NONE((std::string)"Authenticated..."));
		}
		else
			user.send_err(ERR_PASSWDMISMATCH(user.nickname()));
	}
}

bool check_nick(std::string const &str) {
	return (str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") ==
		std::string::npos) && (str.size() > 0 && str.size() < 9);
}

void	Server::cmd_nick(User &user, std::vector<std::string> &params)
{
	if (params.size() < 1)
		user.send_err(ERR_NONICKNAMEGIVEN);
	if (!check_nick(params[0]))
		user.send_err(ERR_ERRONEUSNICKNAME(params[0]));
	else if (is_user(params[0]))
		user.send_err(ERR_NICKNAMEINUSE(params[0]));
	else if (user.is_registered())
		user.send_err(ERR_ALREADYREGISTRED(user.nickname()));
	else
	{
		_users[params[0]] = user;
		_users[params[0]].set_nickname(params[0]);
		_users.erase(user.nickname());
		_nicks[_users[params[0]].fd()] = params[0];
		if (_users[params[0]].nickname().size() > 0 && _users[params[0]].username().size() > 0)
		{
			_users[params[0]].set_registered(true);
			send_motd(_users[params[0]]);
		}
	}
}

void	Server::cmd_user(User &user, std::vector<std::string> &params)
{
	if (params.size() != 4)
		user.send_err(ERR_NEEDMOREPARAMS(user.nickname(), "USER"));
	if (user.is_registered())
		user.send_err(ERR_ALREADYREGISTRED(user.nickname()));
	else
	{
		if (user.username().empty())
		{
			user.set_username(params[0]);
			user.set_realname(params[3]);
		}
		else
		{
			user.send_err(ERR_ALREADYREGISTRED(user.nickname()));
		}
		if (user.nickname().size() > 0 && user.username().size() > 0)
		{
			user.set_registered(true);
			send_motd(user);
		}
	}
}

void	Server::cmd_oper(User &user, std::vector<std::string> &params)
{
	if (params.size() != 2)
		user.send_err(ERR_NEEDMOREPARAMS(user.nickname(), "OPER"));
	if (params[0] != SUPER_NICK)
		user.send_err(ERR_ERRONEUSNICKNAME(user.nickname()));
	if (params[1] != SUPER_PASS)
		user.send_err(ERR_PASSWDMISMATCH(user.nickname()));
	user.set_admin(true);
	user.send_msg(RPL_YOUREOPER(user.nickname()));
}
void	Server::cmd_mode(User &user, std::vector<std::string> &params)
{
	if (params.size() >= 1 && params[0][0] == '#')
		return ;
	if (params.size() >= 2 && (params[0].empty() || params[1].empty()))
		user.send_err(ERR_NEEDMOREPARAMS(user.nickname(), "MODE"));
	if ((params[0][0] == '+' || params[0][0] == '-' ) && params[0][1] == 'o' && params[0].size() == 2)
	{
		if (!is_user(params[1]))
			user.send_err(ERR_NOSUCHNICK(user.nickname()));
		if (!user.is_admin())
			user.send_err(ERR_NOPRIVILEGES(user.nickname()));
		if (params[0][0] == '+')
			_users[params[1]].set_admin(true);
		else
			_users[params[1]].set_admin(false);
	}
}

void	Server::cmd_join(User &user, std::vector<std::string> &params)
{
	if (params.size() < 1)
		user.send_err(ERR_NEEDMOREPARAMS(user.nickname(), "JOIN"));
	if (is_valid_room_name(params[0]) == false)
		user.send_err(ERR_NOSUCHCHANNEL(user.nickname(), params[0]));
	if (!is_room(params[0]))
	{
		_channels[params[0]] = Room(params[0]);
		_channels[params[0]].set_operator(user.nickname());
		_channels[params[0]].join(user);
		user.send_msg(user.fullname() + " JOIN " + params[0] + "\n");
		user.send_msg(RPL_NOTOPIC(user.nickname(), _channels[params[0]].name()));
		user.send_msg(RPL_NAMREPLY(user.nickname(), _channels[params[0]].name(), _channels[params[0]].user_list()));
		user.send_msg(RPL_ENDOFNAMES(user.nickname(), _channels[params[0]].name()));
	}
	else
	{
		if (_channels[params[0]].users().size() > 10)
			user.send_err(ERR_CHANNELISFULL(user.nickname(), _channels[params[0]].name()));
		_channels[params[0]].join(user);
		_channels[params[0]].send_msg(_users, user.fullname() + " JOIN " + params[0] + "\n");
		if (_channels[params[0]].topic() == "")
			user.send_msg(RPL_NOTOPIC(user.nickname(), _channels[params[0]].name()));
		else
			user.send_msg(RPL_TOPIC(user.nickname(), _channels[params[0]].name(), _channels[params[0]].topic()));
		user.send_msg(RPL_NAMREPLY(user.nickname(), _channels[params[0]].name(), _channels[params[0]].user_list()));
		user.send_msg(RPL_ENDOFNAMES(user.nickname(), _channels[params[0]].name()));
	}
}

void	Server::cmd_list(User &user, std::vector<std::string> &params)
{
	user.send_msg(RPL_LISTSTART(user.nickname()));
	if (params.size() == 0)
	{
		for (std::map<std::string, Room>::iterator it = _channels.begin(); it != _channels.end(); it++)
		{
			std::stringstream	tmp;
			tmp.str("");
			tmp << it->second.users().size();
			user.send_msg(RPL_LIST(user.nickname(), it->second.name(), tmp.str(), it->second.topic()));
		}
	}
	else if (params.size() == 1)
	{
		std::vector<std::string>	channels = split(params[0], ',');
		for(unsigned int i = 0; i < channels.size(); i++)
		{
			if (!is_room(params[0]))
				user.send_err(ERR_NOSUCHCHANNEL(user.nickname(), channels[i]));
			else
			{
				std::stringstream	tmp;
				tmp.str("");
				tmp << _channels[params[0]].users().size();
				user.send_msg(RPL_LIST(user.nickname(), _channels[params[0]].name(), tmp.str(), _channels[params[0]].topic()));
			}
		}
	}
	user.send_msg(RPL_LISTEND(user.nickname()));
}

void	Server::cmd_kick(User &user, std::vector<std::string> &params)
{
	if (params.size() < 2)
		user.send_err(ERR_NEEDMOREPARAMS(user.nickname(), "KICK"));

	if (!is_room(params[0]))
		user.send_err(ERR_NOSUCHCHANNEL(user.nickname(), params[0]));
	if (!_channels[params[0]].is_operator(user.nickname()))
		user.send_err(ERR_NOPRIVILEGES(user.nickname()));
	if (!_channels[params[0]].isin(user.nickname()))
		user.send_err(ERR_NOTONCHANNEL(user.nickname(), _channels[params[0]].name()));
	if (_channels[params[0]].isin(params[1]) == false)
		user.send_err(ERR_NOSUCHNICK(user.nickname()));

	_channels[params[0]].send_msg(_users, user.fullname() + " KICK " + params[0] + " " + params[1] + "\n");
	_channels[params[0]].part(_users[params[1]]);
	if (_channels[params[0]].users().size() == 0)
		_channels.erase(params[0]);
	else
		_channels[params[0]].set_operator(*(_channels[params[0]].users().begin()));
}

void	Server::cmd_part(User &user, std::vector<std::string> &params)
{
	if (params.size() < 1)
		user.send_err(ERR_NEEDMOREPARAMS(user.nickname(), "PART"));
	if(!is_room(params[0]))
		user.send_err(ERR_NOSUCHCHANNEL(user.nickname(), params[0]));
	if(!_channels[params[0]].isin(user.nickname()))
		user.send_err(ERR_NOTONCHANNEL(user.nickname(), params[0]));

	_channels[params[0]].send_msg(_users, user.fullname() + " PART " + _channels[params[0]].name() + "\n");
	_channels[params[0]].part(user);
	if (_channels[params[0]].users().size() == 0)
		_channels.erase(params[0]);
	else
		_channels[params[0]].set_operator(*(_channels[params[0]].users().begin()));
}

void	Server::cmd_privmsg(User &user, std::vector<std::string> &params)
{
	if (!params.size() || params[0][0] == ':')
		user.send_err(ERR_NORECIPIENT(user.nickname(), params[0]));
	if (params.size() < 2)
		user.send_err(ERR_NOTEXTTOSEND(user.nickname()));

	if (params[0][0] == '#')
	{
		if (!is_room(params[0]))
			user.send_err(ERR_NOTONCHANNEL(user.nickname(), params[0]));
		_channels[params[0]].send_msg(_users, user.nickname(), user.fullname() + " PRIVMSG " + params[0] + " :" + params[1] + "\n");

	}
	else
	{
		if (!is_user(params[0]))
			user.send_err(ERR_NOSUCHNICK(user.nickname()));
		_users[params[0]].send_msg(user.fullname() + " PRIVMSG " + params[0] + " :" + params[1] + "\n");
	}
}

void	Server::cmd_notice(User &user, std::vector<std::string> &params)
{
	if (!params.size() || params[0][0] == ':')
		return ;
	if (params.size() < 2)
		return ;

	if (params[0][0] == '#')
	{
		if (!is_room(params[0]))
			return ;
		_channels[params[0]].send_msg(_users, user.fullname() + user.nickname() + " NOTICE " + params[0] + " :" + params[1] + "\n");

	}
	else
	{
		if (!is_user(params[0]))
			return ;
		_users[params[0]].send_msg(user.fullname() + " NOTICE " + params[0] + " :" + params[1] + "\n");
	}
}

void	Server::cmd_names(User &user, std::vector<std::string> &params)
{
	std::string msg = " :";

	if (params.size() > 1)
		user.send_err(ERR_NEEDMOREPARAMS(user.nickname(), "NAMES"));
	else if (params.size() == 0)
	{
		for (std::map<std::string, Room>::iterator it = _channels.begin(); it != _channels.end(); it++)
		{
			user.send_msg(RPL_NAMREPLY(user.nickname(), it->second.name(), it->second.user_list()));
			user.send_msg(RPL_ENDOFNAMES(user.nickname(), it->second.name()));
		}
		user.send_msg(RPL_NAMREPLY(user.nickname(), "*", wait_list()));
		user.send_msg(RPL_ENDOFNAMES(user.nickname(), "*"));
	}
	else if (params.size() == 1)
	{
		if (!is_room(params[0]))
			user.send_err(ERR_NOSUCHCHANNEL(user.nickname(), params[0]));
		else
		{
			user.send_msg(RPL_NAMREPLY(user.nickname(), _channels[params[0]].name(), _channels[params[0]].user_list()));
			user.send_msg(RPL_ENDOFNAMES(user.nickname(), _channels[params[0]].name()));
		}
	}
}

void	Server::cmd_topic(User &user, std::vector<std::string> &params)
{
	if  (params.empty() || (params.size() != 1 && params.size() != 2))
		user.send_err(ERR_NEEDMOREPARAMS(user.nickname(), "TOPIC"));
	if (!is_room(params[0]))
		user.send_err(ERR_NOSUCHCHANNEL(user.nickname(), params[0]));
	if (params.size() == 1)
	{
		if (_channels[params[0]].topic().empty())
			user.send_msg(RPL_NOTOPIC(user.nickname(), params[0]));
		else
			user.send_msg(RPL_TOPIC(user.nickname(), params[0], _channels[params[0]].topic()));
	}
	else
	{
		if (!_channels[params[0]].isin(user.nickname()))
			user.send_err(ERR_NOTONCHANNEL(user.nickname(), params[0]));
		if (!_channels[params[0]].is_operator(user.nickname()))
			user.send_err(ERR_CHANOPRIVSNEEDED(user.nickname(), params[0]));
		_channels[params[0]].set_topic(params[1]);
		_channels[params[0]].send_msg(_users, RPL_SETTOPIC(params[0], params[1]));
		_channels[params[0]].send_msg(_users, RPL_TOPIC(user.nickname(), params[0], _channels[params[0]].topic()));
	}
}

void	Server::quit(User &user)
{
	while (!user.channels().empty())
	{
		std::string name = *user.channels().begin();
		_channels[name].part(user);
		if (_channels[name].users().size() == 0)
			_channels.erase(name);
		else
			_channels[name].set_operator(*(_channels[name].users().begin()));
	}


	user.send_msg(RPL_NONE((std::string)"Goodbye!"));
	close(user.fd());
	std::cout << "User " << user.fd() << " disconnected." << std::endl;

	for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); it++)
		if (it->fd == user.fd())
		{
			_fds.erase(it);
			break ;
		}
	_nicks.erase(user.fd());
	_users.erase(user.nickname());
}

bool	Server::is_flooding(User &user)
{
	time_t t = time(0);

	if (t - user.last_message_time() > user.message_timeout())
	{
		user.set_last_message_time(t);
		user.set_message_timeout(1);
		return false;
	}
	user.set_last_message_time(t);
	if (user.message_timeout() < (2 << 6))
		user.set_message_timeout(user.message_timeout() * 2);
	std::stringstream ss;
	ss << user.message_timeout();
	user.send_err(ERR_FLOOD(ss.str()));
	return true;
}

void	Server::cmd_ping(User &user, const Message &msg)
{
	std::string name = SERV;
	if (msg.params().size() == 0)
		user.send_err(ERR_NOORIGIN);
	else
		send_pong(user, msg.params()[0]);
}

void	Server::cmd_pong(User &user, const Message &msg)
{
	if (msg.params().size() <= 0 || msg.params()[0] != SERV)
	{
		if (msg.params().size() > 0)
			user.send_err(ERR_NOSUCHSERVER(msg.params()[0]));
		else
			user.send_err(ERR_NOSUCHSERVER((std::string)""));
	}
}

bool	Server::is_valid_room_name(const std::string &name)
{
	if (name.length() < 2 || name.length() > 50 || name.find_first_of("&@#+!") != 0)
		return false;
	for (unsigned int i = 0; i < name.length(); i++) {
		if (isspace(name[i]) || iscntrl(name[i]) || name[i] == ',')
			return false;
	}
	return true;
}
