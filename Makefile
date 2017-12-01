NAME	= avm

CC		= clang++
FLG		= #-Wall -Werror -Wextra

SRCDIR	= ./src
INCDIR	= ./inc
OBJDIR	= ./obj

SRC		= main.cpp AbstractVM.class.cpp OperandsFactory.class.cpp AVMLexer.class.cpp \
		  AVMException.class.cpp

ATTR	= -std=c++11 #-g

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.cpp=.o))

$(NAME) : $(OBJ)
	$(CC) $(FLG) $(OBJ) $(ATTR) -o $(NAME)

all		: obj $(NAME)

obj		:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.cpp
	$(CC) $(FLG) $(ATTR) -I $(INCDIR) -o $@ -c $<

clean	:
	rm -f $(OBJ)

fclean	: clean
	rm -f $(NAME)

re		: fclean all