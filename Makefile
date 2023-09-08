# 実行ファイル名
NAME	= so_long

# コンパイル対象ファイル
SRCS = \
so_long.c\
controler.c\
debugger.c\

# 生成したいオブジェクト
OBJS	= $(SRCS:.c=.o)

# コンパイラの指定
CC		= cc

# コンパイルオプション
CFLAGS	= -Wall -Wextra -Werror

LIB = \
-L./minilibx-linux -lmlx \
-L/usr/X11R6/lib -lX11 -lXext

FW = -framework OpenGL -framework AppKit

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIB) $(FW) -o $(NAME)

%.o: %.c
	$(CC)  ${LIB} ${FW} -c $< -o $@

.PHONY: all
all: ${NAME}


.PHONY: clean
clean: 
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f ${NAME}

.PHONY: re
re: fclean all