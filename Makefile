# Project name
EXEC=compilo

# Compiler
IDIR=src
IDIRFLAG=$(foreach idir, $(IDIR), -I$(idir))
CXXFLAGS=$(IDIRFLAG)

# Linker
LFLAGS=$(IDIRFLAG)

# Directories
SRCDIR=src
OBJDIR=obj
BINDIR=.

# Files
SOURCES=$(foreach sdir, $(SRCDIR), $(wildcard $(sdir)/*.c))
OBJECTS=$(patsubst %.c, $(OBJDIR)/%.o, $(notdir $(SOURCES)))


vpath %.c $(SRCDIR)

# Reminder, 'cause it is easy to forget makefile's fucked-up syntax...
# $@ is what triggered the rule, ie the target before :
# $^ is the whole dependencies list, ie everything after :
# $< is the first item in the dependencies list

# Rules
#gcc: clean
gcc: CXX=gcc
gcc: LINKER=gcc -o
gcc: $(BINDIR)/$(EXEC)

#gcc-debug: clean
gcc-debug: CXX=gcc
gcc-debug: LINKER=gcc -o
gcc-debug: CXXFLAGS += -ggdb
gcc-debug: $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC): $(OBJECTS)
	$(LINKER) $@ $^ $(LFLAGS)

$(OBJDIR)/%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: gcc gcc-debug clang clang-debug clean

clean:
	rm -fr $(OBJECTS) $(BINDIR)/$(EXEC)
