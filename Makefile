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
	@echo "\033[38;5;226m            _|_                             _____________________                             _|_         "
	@echo "\033[38;5;226m           (   )                      _____/      #########      \_____                      (   )        "
	@echo "\033[38;5;226m           /---\                  ___/      #**#      #     #          \___                  /---\        "
	@echo "\033[38;5;226m          /     \              __/   #     #          #     #       ####   \__              /     \       "
	@echo "\033[38;5;226m         /       \          __/     # #     *###      #     #       #     __  \__          /       \      "
	@echo "\033[38;5;226m      __/_________\__     _/       #   #        #     #     #       #**      \   \_     __/_________\__   "
	@echo "\033[38;5;226m     |_______________|   |  ###   #######  #    #     #     ##      #     __ /  _  |   |_______________|  "
	@echo "\033[38;5;226m       |___________|    /  #     #       #  ####  __________  ####  ####     \ |  \ \    |___________|    "
	@echo "\033[38;5;226m        |_________|    |   #           __________/          \__________   __ / |   | |    |_________|     "
	@echo "\033[38;5;226m       |___________|  /     ### _____/                                 \_____  |_ /   \  |___________|    "
	@echo "\033[38;5;226m        | _______ |__/       __/                                             \__       \__| _______ |     "
	@echo "\033[38;5;226m        ||   _   ||         /    o                                         o    \         ||   _   ||     "
	@echo "\033[38;5;226m        ||  (_)  ||       _|     |                   o o                   |     |_       ||  (_)  ||     "    
	@echo "\033[38;5;226m        ||_______||_____--       |                   |_|                   |       --_____||_______||     "     
	@echo "\033[38;5;226m        |_________|          o  /_\  o               | |               o  /_\  o          |_________|     "   
	@echo "\033[38;5;220m       |___________|         |_/   \_|           *  /   \  *           |_/   \_|         |___________|    "     
	@echo "\033[38;5;214m        |_________|          |/  o  \|           |_/     \_|           |/  o  \|          |_________|     "     
	@echo "\033[38;5;208m       |___________|         /   |_x_x_x_x_x_x_x_|/ /\ /\ \|_x_x_x_x_x_x_x_|   \         |___________|    "     
	@echo "\033[38;5;202m        |   |_|   |      *  /   /              |_/  || ||  \_|              \   \  *      |   |_|   |     "      
	@echo "\033[38;5;196m        |         |      |_/   /  |         |  |             |  |         |  \   \_|      |         |     "      
	@echo "\033[38;5;196m        |         |      | ===/  / \       / \  ) ^|^|^|^|^ (  / \       / \  \=== |      |         |     "
	@echo "\033[38;5;196m        |         |       )|_/   | |       | |   |         |   | |       | |   \_|(       |         |     "     
	@echo "\033[38;5;196m        |         |        | ====================|  |_|_|  |==================== |        |         |     "      
	@echo "\033[38;5;196m        |         |         ) ^|^|^|^|^|^|^|^|^|^|         |^|^|^|^|^|^|^|^|^|^ (         |         |     "      
	@echo "\033[38;5;196m        |         |          |    _         |    | o  |  o |    |         _    |          |         |     "      
	@echo "\033[38;5;196m        |         |          |   / \       /*\   |   /*\   |   /*\       / \   |          |         |     "      
	@echo "\033[38;5;196m        |         |          |   | |      |   |  |  |   |  |  |   |      | |   |          |         |     "      
	@echo "\033[38;5;196m        |         |          |   |_| *    |   |  |  |   |  |  |   |    * |_|   |          |         |     "      
	@echo "\033[38;5;196m        |         |          |       |_x_x_x_x_x_|_x_x_x_x_|_x_x_x_x_x_|       |          |         |     "      
	@echo "\033[38;5;196m        |         |          |        \|^|^|^|^|\|^|^|^|^|^|/|^|^|^|^|/        |          |         |     "     
	@echo "\033[38;5;196m        |         |          |    _    |    _    |  _/o\_  |    _    |    _    |          |         |     "      
	@echo "\033[38;5;196m        |         |          |   | |   |   | |   | /_o o_\ |   | |   |   | |   |          |         |     "      
	@echo "\033[38;5;196m   ____ |         | _________|   |_|   |   |_|   | ||   || |   |_|   |   |_|   |_________ |         | ____"     
	@echo "\033[38;5;196m        |         |          |_________|_________|_||___||_|_________|_________|          |         |     "      
	@echo "\033[38;5;196m        |         |         /=========/=========/===|===|===\=========\=========\         |         |     "      
	@echo "\033[38;5;196m        |         |         |______( *    )_____|___|===|___|_____( *    )______|         |         |     "     
	@echo "\033[38;5;196m        |         |              ( *   *    )       /   \       ( *   *    )              |         |     "      
	@echo "\033[38;5;196m        |         |              ()*  * *   )      /     \      ()*  * *   )              |         |     "     
	@echo "\033[38;5;196m        |         |               ((*)     )      /       \      ((*)     )               |         |     "      
	@echo "\033[38;5;196m        |         |                 ((___)       /         \       ((___)                 |         |     "      
	@echo "\033[38;5;196m        |         |                   ||        /           \        ||                   |         |     "      
	@echo "\033[38;5;196m        |         |                 __||__     /             \     __||__                 |         |     "      
	@echo "\033[38;5;196m        |         |                /_____/|   /               \   |\_____\                |         |     "      
	@echo "\033[38;5;196m       _|_________|_               |     ||  /                 \  ||     |               _|_________|_    "      
	@echo "\033[38;5;196m      |_____________|              |     |  /                   \  |     |              |_____________|   "      
	@echo "\033[38;5;196m       |  _______  |               |_____| /                     \ |_____|               |  _______  |    "      
	@echo "\033[38;5;196m       | |       | |                      /                       \                      | |       | |    "
	@echo "\033[38;5;196m       | |       | |                     /                         \                     | |       | |    "
	@echo "\033[38;5;196m       | |_______| |                    /                           \                    | |_______| |    "
	@echo "\033[38;5;196m       |___________|                   /                             \                   |___________|    "
	@echo "\033[38;5;196m      |             |                 /                               \                 |             |   "
	@echo "\033[38;5;196m      |             |                /                                 \                |             |   "
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
