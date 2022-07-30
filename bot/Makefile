# Basic info

CC=clang++
RM=/bin/rm -rf
PRINTF=printf
MKDIR=mkdir -p

NAME :=	ircbot

FLAGS := -Wall -Wextra -Werror
FLAGS += -std=c++98

SOURCES := main.cpp \
		   IRCBot.cpp


DIR_O := objs
DIR_S := source
INCLUDE_DIR = include

INCLUDES := \
			-I $(INCLUDE_DIR)

SRCS := $(addprefix $(DIR_S)/,$(SOURCES))
OBJS := $(addprefix $(DIR_O)/,$(SOURCES:.cpp=.o))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(PRINTF) "\r\033[32;1mCompiling ircserv...\033[0m                                     \n"
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@$(PRINTF) "\r\033[32;1mircserv is ready\033[0m                                     \n"
	@$(PRINTF) "\033[?25h"

$(OBJS): $(DIR_O)/%.o: $(DIR_S)/%.cpp $(wildcard $(INCLUDE_DIR)/*.h) | $(DIR_O)
	@$(PRINTF) "\033[?25l"
	@$(PRINTF) "\r\033[34;1mNow compiling $@!                                    		\033[0m"
	@$(CC) $(FLAGS) -c $(INCLUDES) -o $@ $<

$(DIR_O):
	@$(MKDIR) $(DIR_O)

clean:
	@$(PRINTF) "\r\033[34mDeleting ircserv o-files\033[0m                                     \n"
	@$(RM) $(DIR_O)

fclean: clean
	@$(PRINTF) "\r\033[34mDeleting ircserv binary\033[0m                                     \n"
	@$(RM) $(NAME)

re: fclean all
