NAME = webserv
CC = c++
CFLAGS = -g -Wall -Wextra -Werror -std=c++98
SRC = \
	main.cpp \
	domain/Root.cpp \
	domain/Location.cpp \
	domain/Server.cpp \
	fixtures/provider.cpp \
	cycle/loop.cpp \
	cycle/socket_manager.cpp \
	cycle/request_manager.cpp \
	parser/parser.cpp


OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))
OBJ_DIR = ./objs

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/domain
	mkdir -p $(OBJ_DIR)/fixtures
	mkdir -p $(OBJ_DIR)/cycle
	mkdir -p $(OBJ_DIR)/parser

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): format $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

format:
	find -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format --style=Google -i

test: 
	./$(NAME) example.conf

run: re test

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re test run format
