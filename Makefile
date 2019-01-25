# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/07 09:28:26 by aroi              #+#    #+#              #
#    Updated: 2019/01/25 18:32:14 by aroi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_ls
CC		=	gcc
FLAGS	=	-Wall -Werror -Wextra

FILES	=	main \
			open_dir \
			out_file \
			out_long \
			info_long \
			out_columns \
			t_file_func \
			quicksort \
			quicksort_2 \
			error


LIBFT	=	libft
SRC 	=	$(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ 	=	$(addprefix obj/, $(addsuffix .o, $(FILES)))
HEADERS	=	-I ./libft/includes -I ./includes

obj/%.o: src/%.c
	@$(CC) -O3 -o $@ -c $^ $(HEADERS)
	@echo "\033[32m...Making some magic...\033[0m"

all: $(NAME)

$(NAME): libft/libft.a $(OBJ) 
	@$(CC) $(OBJ) -O3 $(FLAGS) $(HEADERS) -L $(LIBFT) -lft -o $(NAME)
	@echo "\033[1;32m$(NAME)\033[0m\033[32m is ready to use!\033[0m"

libft/libft.a:
	@echo "\033[32mCrafting \033[1mlibft.a\033[0m\033[32m...\033[0m"
	@make -C libft

clean:
	@make -C libft clean
	@rm -rf $(OBJ)
	@echo "\033[31mRemoving object files...\033[0m"

fclean:
	@make -C libft fclean
	@rm -rf $(OBJ)
	@rm -rf $(NAME)
	@echo "\033[31mRemoving object files...\033[0m"
	@echo "\033[31mRemoved \033[1m$(NAME)\033[0m\033[31m file.\033[0m"

re: fclean all

.PHONY: all clean
.NOTPARALLEL: all $(NAME) libft/libft.a clean fclean re
