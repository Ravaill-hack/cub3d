NAME = cub3d

LIBFT = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

HEADER_DIR = includes
SRCS_DIR = srcs
OBJS_DIR = objs

LIBFT_DIR = ./libft
LIBFT_HEADER_DIR = $(LIBFT_DIR)/includes
LIBFT_SRCS_DIR = ./srcs

INCLUDES = -I$(HEADER_DIR) -I$(LIBFT_HEADER_DIR) 
LIBRARIES = -L$(LIBFT_DIR) -lft

SRCS_FILES = \
	free.c \
	init.c \
	main.c \
	utils.c \

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

all: header $(LIBFT) $(NAME)

header:
	@echo ""
	@echo "\033[38;5;226m                                __====-_  _-====___                                   "
	@echo "\033[38;5;226m                           _--^^^#####//      \\#####^^^--_                               "
	@echo "\033[38;5;220m                        _-^##########// (    ) \\##########^-_                   "
	@echo "\033[38;5;214m                       -############//  |\^^/|  \\############-                   "
	@echo "\033[38;5;208m                     _/############//   (@::@)   \\############\_                   "
	@echo "\033[38;5;202m                    /#############((     \\//     ))#############\                   "
	@echo "\033[38;5;196m                   -###############\\    (oo)    //###############-                   "
	@echo "\033[38;5;196m                  -#################\\  / UUU \  //#################-                   "
	@echo "\033[38;5;196m                 _/|##########/\######(   /   \   )######/\##########|\_                   "
	@echo "\033[38;5;196m                |/ |#/\#/\#/\/  \#/\##\  (     )  /##/\#/  \/\#/\#/\| \                   "
	@echo "\033[38;5;226m                      _                                                             "
	@echo "\033[38;5;226m                     | |                                                                    "
	@echo "\033[38;5;220m                    /   \                                                             "
	@echo "\033[38;5;214m                 |_/     \_|                                                             "
	@echo "\033[38;5;208m                 |/ /\ /\ \|                                                 "
	@echo "\033[38;5;202m                _/  || ||  \_                                           "
	@echo "\033[38;5;196m               |             |                                                     "
	@echo "\033[38;5;196m                ) ^|^|^|^|^ (                                       "
	@echo "\033[38;5;196m                 |         |                                    "
	@echo "\033[38;5;196m                 |         |                                                              "
	@echo ""
	@echo "\033[0m"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBRARIES) -o $(NAME) -lncurses -lreadline

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re header
