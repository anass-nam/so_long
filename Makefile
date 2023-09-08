# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anammal <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/11 02:45:24 by anammal           #+#    #+#              #
#    Updated: 2023/06/11 02:45:28 by anammal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME=so_long
HEADER=src/$(NAME:=.h)
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
CC=cc
CFLAGS= -g # -Werror -Wall -Wextra
LFTDIR=libft
LIBFT=$(LFTDIR:=.a)
LFT= -I$(LFTDIR) -L$(LFTDIR) -lft
LMATH= -lm

R=\033[1;31m
G=\033[1;32m
Y=\033[1;33m
NC=\033[1;0m
CLR=\033[2J\033[u

all: $(NAME)
	
$(NAME): $(LIBFT) $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJ) $(LFT) $(LMATH) -o $@
	@echo "$(CLR)$(G)The compilation of $@ was successful.$(NC)"

$(LIBFT):
	@make -C $(LFTDIR)
	@make bonus -C $(LFTDIR)
	@make gnl -C $(LFTDIR)

%.o: %.c
	@echo "$(CLR)$(Y) Compiling: $< ... Done$(NC)!"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LFTDIR)
	@echo "$(CLR)$(R)The object file has been cleaned.$(NC)"
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LFTDIR)
	@echo "$(CLR)$(R)$(NAME) has been completely cleaned.$(NC)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
