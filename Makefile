NAME = pipex

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

LIBFT = ./Libft/libft.a

SRCS = ./src/pipex.c\
		./src/utils.c

SRCS_BONUS = ./src_bonus/pipex_bonus.c
$(NAME) :
	make re -C ./Libft
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

all : $(NAME)

re :	fclean all

fclean : clean
		$(RM) $(NAME)

clean :
		$(RM) $(NAME)

bonus : clean
	make re -C ./Libft
	$(CC)  $(SRCS_BONUS) $(LIBFT) -o $(NAME)

