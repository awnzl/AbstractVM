NAME	= avm

CC		= clang++
FLG		= #-Wall -Werror -Wextra

SRCDIR	= ./src
INCDIR	= ./inc
OBJDIR	= ./obj

SRC		= main.cpp AbstractVM.class.cpp Int8.class.cpp #Int8.class.cpp Int16.class.cpp \
			Int32.class.cpp Float.class.cpp Double.class.cpp

#ATTR	= 

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.cpp=.o))

$(NAME) : $(OBJ)
	$(CC) $(FLG) $(OBJ) -o $(NAME)

all		: obj $(NAME)

obj		:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.cpp
	$(CC) $(FLG) -I $(INCDIR) -o $@ -c $<

clean	:
	rm -f $(OBJ)

fclean	: clean
	rm -f $(NAME)

re		: fclean all