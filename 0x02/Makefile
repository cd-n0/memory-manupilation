CC = gcc
CFLAGS = -std=c89 -Wall -Wextra -ggdb -D_DEFAULT_SOURCE -DDEBUG_PRINT=1 -fsanitize=address

SRCDIR = src
INCDIR = inc

SRCS = $(wildcard $(SRCDIR)/*.c)
INCS = $(wildcard $(INCDIR)/*.h)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

OBJDIR = obj
BINDIR = bin
TARGET = $(BINDIR)/ac_trainer

all: build

build: $(TARGET)
	@echo "Build complete."

$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS) | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
