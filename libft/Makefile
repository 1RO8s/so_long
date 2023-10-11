NAME	= libft.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
OBJS	= $(SRCS:.c=.o)
INCLUDE = headers

SRCS =  \
$(LIBFT)\
$(PRINTF)\
$(GNL)

LIBFT := $(wildcard ./libc/*.c)
PRINTF = $(wildcard ./printf/*.c)
GNL = $(wildcard ./get_next_line/*.c)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I${INCLUDE} -c $< -o $@

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