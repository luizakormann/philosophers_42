# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/23 22:15:37 by lukorman          #+#    #+#              #
#    Updated: 2025/09/24 22:19:21 by lukorman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               configuration                                  #
# **************************************************************************** #

CC	= cc
CFLAGS	= -Wall -Wextra -Werror -pthread
RM	= rm -rf

# **************************************************************************** #
#                                directories                                   #
# **************************************************************************** #

INC_DIR	= include
SRC_DIR	= src/
OBJ_DIR	= obj/
BIN_DIR	= bin/

# **************************************************************************** #
#                                   files                                      #
# **************************************************************************** #

# executable
NAME	= $(BIN_DIR)philo

# header
HEADERS = $(shell find $(INC_DIR) -name '*.h')

# sources
SRC	= $(shell find $(SRC_DIR) -name '*.c')

# objects
OBJS = $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRC:.c=.o))

# **************************************************************************** #
#                              compile commands                                #
# **************************************************************************** #

COMP_OBJS	= $(CC) $(CFLAGS) -c $< -o $@
COMP	= $(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# **************************************************************************** #
#                                  targets                                     #
# **************************************************************************** #

all: $(NAME)
	@echo "philo compilation completed. run with ./bin/philo"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@echo "compiling  $< -> $@"
	@mkdir -p $(dir $@)
	@$(COMP_OBJS)

$(NAME): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(COMP)

LEAKS	:=	valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --log-file=val-leaks.txt --track-fds=yes

HELGRIND	:=	valgrind --tool=hellgrind \
		--track-origins=yes --log-file=val-helgrind.txt --track-fds=yes

DRD	:=	valgrind --tool=drd \
		--track-origins=yes --log-file=val-drd.txt --track-fds=yes

val_leaks: all
	@echo "running valgrind (leaks). after, find trace at ./val-leaks.txt"
	@$(LEAKS) ./$(NAME)

val_helg: all
	@echo "running valgrind (helgrind). after, find trace at ./val-helgrind.txt"
	@$(HELGRIND) ./$(NAME)

val_drd: all
	@echo "running valgrind (drd). after, find trace at ./val-drd.txt"
	@$(DRD) ./$(NAME)

val_all: val_leaks val_drd val_helg

clean:
	@echo "removing /obj && *.txt files if any"
	@$(RM) $(OBJ_DIR)
	@$(RM) val*.txt

fclean: clean
	@echo "removing /bin"
	@$(RM) $(BIN_DIR)

re: fclean all

.PHONY: all clean fclean re val_leaks val_helg val_drd val_all
