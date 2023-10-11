NAME :=so_long
CC := cc
CFLAGS = -Wall -Wextra -Werror
DEBUG := -g -fsanitize=address
OBJS	= $(SRCS:.c=.o)
INCLUDE := headers

# コンパイル対象ファイル
SRCS = \
so_long.c\
controler.c\
validator.c\
element_count.c\
renderer.c\
util.c\
# debugger.c\



LIB = \
-L./minilibx-linux -lmlx \
-L/usr/X11R6/lib -lX11 -lXext

FW = -framework OpenGL -framework AppKit

$(NAME): $(OBJS)
	$(CC) ${CFLAGS} $(OBJS) $(LIB) $(FW) -o $(NAME) ./libft/libft.a

# $(NAME): $(OBJS)
# 	$(MAKE) -C ./libft
# 	cp libft/libft.a $(NAME)
# 	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) ${CFLAGS} -c $< -o $@
# $(CC)  ${LIB} ${FW} -c $< -o $@

.PHONY: all
all:CFLAGS=-Wall -Wextra -Werror
all:${NAME}

.PHONY: debug
debug:CFLAGS=$(DEBUG)
debug:${NAME}

# 静的解析
.PHONY: analyze
analyze:
	rm -f *.plist
	cc --analyze ${SRCS}

.PHONY: clean
clean: 
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f ${NAME}

.PHONY: re
re: fclean all