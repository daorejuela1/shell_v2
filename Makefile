# -*- MakeFile -*-

NAME = hsh
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic

SRCDIR = src
OBJDIR = obj

INC_DIR = SRCDIR

BUILTINDIR = builtins
FILESDIR = files
GETLINEDIR = getline
MESSAGESDIR = messages
OPERATORSDIR = operators
PARSESDIR = parsers
PROCESSESDIR = processes
UTILSDIR = utils

OBJ = $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/*.c))
OBJ += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(BUILTINDIR)/*.c))
OBJ += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(FILESDIR)/*.c))
OBJ += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(GETLINEDIR)/*.c))
OBJ += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(MESSAGESDIR)/*.c))
OBJ += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(OPERATORSDIR)/*.c))
OBJ += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(PARSESDIR)/*.c))
OBJ += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(PROCESSESDIR)/*.c))
OBJ += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(UTILSDIR)/*.c))

.PHONY : all clean oclean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) *~ $(NAME)

oclean:
	$(RM) $(OBJ)

fclean: clean oclean

re: oclean $(NAME)

print-%:
	@echo '$*=$($*)'
