# BIN binary 
#OBJ object 
#SRC source

BIN:= Hello
BINDIR:= bin

SRCDIR:= src
INCDIR:= include
OBJDIR:= obj
cc:= gcc
RM:= rm -f
RMDIR:= rm -rf
MKDIR:= mkdir

SRC:= $(wildcard $(SRCDIR)/*.c)
OBJ:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
CLIBS:= -I$(INCDIR)

# linkage gcc pt_BR.o es.o en.o selector.o Hello.o -o Hello
$(BINDIR)/$(BIN): $(OBJ) | $(BINDIR)
	@$(cc) $^ -o $@
	@echo "Generating C binary\033[1;32m" $@

$(OBJ): | $(OBJDIR)

# compilation
.PHONY: all
all: $(BINDIR)/$(BIN)

# auto variables $< and %@
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(cc) $(CLIBS) -c $< -o $@

$(OBJDIR) $(BINDIR):
	$(MKDIR) $@

.PHONY: clean
clean:
	$(RMDIR) $(OBJDIR)
# *.o *~

distclean: clean
	$(RMDIR) $(BINDIR)

# task verification
.PHONY: dump
dump:
	@echo "src:" $(SRC)
	@echo "obj:" $(OBJ)
