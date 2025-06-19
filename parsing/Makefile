NAME = minishel
CC = cc
FLAGS = -Wall -Wextra -Werror
SRC = main.c utils.c tokenzation.c syntax_errors.c expand.c join_tokens.c tokens_type.c print.c add_spaces_symbols.c is_quoted.c get_command_args.c
OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@ -lreadline

%.o:%.c main.h
	$(CC) $(FLAGS) -c $< -o $@

fclean:
	rm -rf *.o
	rm -rf $(NAME)

clean:
	rm -rf *.o

re: fclean all

me: fclean all 
	./minishel