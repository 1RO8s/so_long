# 実行ファイル名
NAME	= so_long.a


# コンパイル対象ファイル
SRCS = \
ft_printf.c\
ft_puthex.c\
ft_putptr.c\
ft_putuint.c\


# 生成したいオブジェクト
OBJS	= $(SRCS:.c=.o)

# コンパイラの指定
CC		= cc

# コンパイルオプション
CFLAGS	= -Wall -Wextra -Werror

INCLUDE = header

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	# $(CC) $(CFLAGS) -I${INCLUDE} -c $< -o $@

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