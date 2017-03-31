# Project name
EXEC=compilo
TEST_EXEC=testo

CXX=gcc
LINKER=gcc -o

# Compiler
IDIR=src
IDIRFLAG=$(foreach idir, $(IDIR), -I$(idir))
CXXFLAGS=-Wall $(IDIRFLAG)

# Linker
LFLAGS=$(IDIRFLAG)

# Directories
SRCDIR=src
OBJDIR=obj
BINDIR=.

# Files
SOURCES=$(foreach sdir, $(SRCDIR), $(wildcard $(sdir)/*.c))
OBJECTS=$(patsubst %.c, $(OBJDIR)/%.o, $(notdir $(SOURCES)))

# Can have only one main function per executable
EXEC_OBJECTS=$(filter-out $(OBJDIR)/test.o, $(OBJECTS))
TEST_OBJECTS=$(filter-out $(OBJDIR)/main.o, $(OBJECTS))

vpath %.c $(SRCDIR)

# Reminder, 'cause it is easy to forget makefile's fucked-up syntax...
# $@ is what triggered the rule, ie the target before :
# $^ is the whole dependencies list, ie everything after :
# $< is the first item in the dependencies list

# Rules
all: main test

main: $(BINDIR)/$(EXEC)
test: $(BINDIR)/$(TEST_EXEC)

debug: CXXFLAGS += -ggdb
debug: clean all

$(BINDIR)/$(EXEC): $(EXEC_OBJECTS)
	$(LINKER) $@ $^ $(LFLAGS)

$(BINDIR)/$(TEST_EXEC): $(TEST_OBJECTS)
	$(LINKER) $@ $^ $(LFLAGS)

$(OBJDIR)/%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean all main test debug

clean:
	rm -fr $(OBJECTS) $(BINDIR)/$(EXEC)
