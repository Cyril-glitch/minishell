NAME = lib/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC =  src/ft_atoi.c \
       src/ft_atol.c \
       src/ft_isalnum.c \
       src/ft_islower.c \
       src/ft_itoa.c \
       src/ft_memccpy.c \
       src/ft_mempcpy.c \
       src/ft_putnbr.c \
       src/ft_strcat.c \
       src/ft_striteri.c \
       src/ft_strmapi.c \
       src/ft_strrchr.c \
       src/ft_toupper.c \
       src/ft_bzero.c \
       src/ft_isalpha.c \
       src/ft_isprint.c \
       src/ft_memchr.c \
       src/ft_memrchr.c \
       src/ft_putnbr_fd.c \
       src/ft_strchr.c \
       src/ft_strjoin.c \
       src/ft_strncat.c \
       src/ft_strstr.c \
       src/ft_calloc.c \
       src/ft_isascii.c \
       src/ft_isset.c \
       src/ft_memcmp.c \
       src/ft_memset.c \
       src/ft_putstr.c \
       src/ft_strcmp.c \
       src/ft_strlcat.c \
       src/ft_strncmp.c \
       src/ft_strtrim.c \
       src/ft_countword.c \
       src/ft_ischarset.c \
       src/ft_isspace.c \
       src/ft_memcpy.c \
       src/ft_putchar_fd.c \
       src/ft_putstr_fd.c \
       src/ft_strcpy.c \
       src/ft_strlcpy.c \
       src/ft_strncpy.c \
       src/ft_substr.c \
       src/ft_freeiter.c \
       src/ft_isdigit.c \
       src/ft_isupper.c \
       src/ft_memmove.c \
       src/ft_putendl_fd.c \
       src/ft_split.c \
       src/ft_strdup.c \
       src/ft_strlen.c \
       src/ft_strnstr.c \
       src/ft_tolower.c \
       src/ft_dtablen.c \
       src/ft_freedtab.c \
	   src/ft_flags.utils.c \
       src/ft_freeall.c \
       src/ft_printf.c \
       src/ft_printptr_hex.c \
       src/ft_printupper_hex.c \
       src/ft_fmtinit.c \
       src/ft_padandprint.c \
       src/ft_printlower_hex.c \
       src/ft_printstr.c \
       src/ft_utoabase.c \
       src/ft_format.utils.c \
       src/ft_printchar.c \
       src/ft_printnbr.c \
       src/ft_zero.c \
       src/ft_printunsigned.c \
	   src/ft_putdouble.c \
	   src/ft_dtoa.c \
           src/ft_tablen.c \
           src/ft_atoll.c \
           src/ft_sort_dtab.c

OBJ = $(SRC:.c=.o)

SRCBO = src/ft_lstadd_back.c \
        src/ft_lstadd_front.c \
        src/ft_lstclear.c \
        src/ft_lstdelone.c \
        src/ft_lstiter.c \
        src/ft_lstlast.c \
        src/ft_lstmap.c \
        src/ft_lstnew.c \
        src/ft_lstsize.c

OBJBO = $(SRCBO:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

bonus: $(OBJ) $(OBJBO)
	ar -rcs $(NAME) $(OBJ) $(OBJBO)

.PHONY: all clean fclean re

clean:
	rm -f $(OBJBO) $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
