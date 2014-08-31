# TP0 - Sistema de recomendações
# Victor Pires Diniz
# victorpiresdiniz@dcc.ufmg.br

TARGET = TP0.exe

CC = gcc
CFLAGS = -g -pg -Wall -O2 -std=c99

LINKER = gcc
LDFLAGS = -Wall -pg

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(LINKER) -o $@ $^ $(LDFLAGS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJECTS)
