NAME = philo

CC = cc -pthread -g
CFLAGS = -Wall -Wextra -Werror

SRC = main.c utils.c

SRCDIR = sources
OBJDIR = obj

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(NAME)
	@echo "\033[32mCompilation successful !\033[0m"

$(NAME): $(OBJ)
	@$(CC) ${CFLAGS} ${OBJ} -o ${NAME}

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compilating $@"
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@echo "\033[32mClean ok\033[0m"

fclean: clean
	@rm -f $(NAME)

re: fclean all
