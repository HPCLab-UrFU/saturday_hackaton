CC = icc
BINDIR := bin
OBJDIR := obj
SDIR := .#Same directory. There should be no space at line end
LIBS = -lm
INCLUDES = /opt/intel/mkl/include.
LIBRARIES = /opt/intel/mkl/lib/intel64
CFLAGS= -std=c99 -O3 -mkl=parallel -fopenmp -L$(LIBRARIES) -I$(INCLUDES)

program_NAME := mkl_test
program_C_SRCS := $(wildcard $(SDIR)/*.c)

#For the first time let us compile the library iniparser by such way
iniparserlib_SDIR := third_party/iniparser
iniparserlib_INCLUDES := third_party/iniparser
iniparserlib_SRCS := $(wildcard $(iniparserlib_SDIR)/*.c)
iniparserlib_OBJS := $(notdir ${iniparserlib_SRCS:.c=.o})

_OBJS = ${program_C_SRCS:.c=.o}
_OBJS += $(iniparserlib_OBJS)
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

.PHONY: all clean

all: $(program_NAME)


$(program_NAME): $(OBJS)
	$(CC) -o $(BINDIR)/$(program_NAME) $(OBJS)  $(CFLAGS) $(LIBS)

$(OBJDIR)/%.o: $(SDIR)/%.c $(wildcard $(INCLUDES)/*.h)
	    $(CC) -c -o $@ $< $(CFLAGS) 

