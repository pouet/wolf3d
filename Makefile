# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/01 10:58:46 by nchrupal          #+#    #+#              #
#    Updated: 2016/04/26 14:41:53 by nchrupal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = $(sort main.c errors.c load.c events.c texture_lock.c anim.c \
		   texture.c init_quit.c xmalloc.c     keys.c image.c)
SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIBFT_PATH = ./libft/
SDL_PATH = ./SDL2.framework/Versions/Current
INC_PATH = ./includes/ $(LIBFT_PATH)includes/ $(MLX_PATH) SDL2.framework/Headers
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = $(addprefix -L,$(LIBFT_PATH) $(MLX_PATH) $(SDL_PATH))
LDLIBS = -lft -lm -F . -framework SDL2 -framework Cocoa
NAME = wolf3d

.PHONY: all clean fclean re libft

all: libft $(NAME)

libft:
	@printf "/--------------- creating library \e[1;36m$@\e[0m... ----------/\n"
	@make -C $(LIBFT_PATH)
	@printf "/---------------- library $@ created... ----------/\n"

$(NAME): $(OBJ)
	@printf "%-50s" "create executable "$(notdir $@)...
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJ) -o $(NAME)
#-g3 -gdwarf-2 -O0 -fsanitize=address
	@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2\
		@executable_path/SDL2.framework/SDL2 $(NAME)
	@printf "\e[1;32m[OK]\e[0m\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@printf "%-50s" "compiling "$(notdir $<)...
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@printf "\e[1;32m[OK]\e[0m\n"

clean:
	@printf "%-50s" "deleting objects..." 
	@$(RM) $(OBJ)
	@$(RM) -r $(OBJ_PATH)
	@printf "\e[1;32m[OK]\e[0m\n"

fclean: clean
	@printf "%-50s" "deleting executable..." 
	@$(RM) $(NAME)
	@printf "\e[1;32m[OK]\e[0m\n"

re: fclean all
