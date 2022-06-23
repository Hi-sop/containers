CC= c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 

SRC_DIR = ./src/
INC_DIR = ./includes/

SRCS= $(addprefix $(SRC_DIR), \
	  main.cpp \
	  tree.cpp)

OBJS= $(SRCS:.cpp=.o)

NAME= container

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INC_DIR) -o $(NAME)

.cpp.o:
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $(<:.cpp=.o)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:fclean all
