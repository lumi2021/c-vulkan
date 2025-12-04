CC = gcc

CFLAGS := \
	-O2 -g -m64 -Ideps/include -Ilib \
	$(shell pkg-config --cflags sdl3) \
	$(shell pkg-config --cflags vulkan)

LIBS := \
	$(shell pkg-config --libs sdl3) \
	$(shell pkg-config --libs vulkan) \
	-ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

OUTPUTFILENAMEOPT := -o 
BUILDDIR := bin

define c2o
$(patsubst %.c,$(BUILDDIR)/%.o,$(notdir $(1)))
endef

ifeq ($(OS),Windows_NT)
	DLLENDING := .dll
	DLLFLAGS  := -Wl,--subsystem,windows
	EXEENDING := .exe
	PDBCLEAN := del *.pdb
	CLEAN := rmdir /s /q
else
	DLLENDING := .a
	DLLFLAGS  := 
	EXEENDING :=
	PDBCLEAN := 
	CLEAN := rm -rf
endif

define c2dll
$(patsubst %.c,%$(DLLENDING),$(notdir $(1)))
endef

SRCS := $(wildcard src/*.c src/**/*.c deps/*.c lib/*.c)
OBJS := $(patsubst %.c,$(BUILDDIR)/%.o,$(SRCS))

all: $(BUILDDIR) | main$(EXEENDING)
	@$(BUILDDIR)/main$(EXEENDING)

main$(EXEENDING): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $^ $(OUTPUTFILENAMEOPT) $(BUILDDIR)/$@ $(LINKFLAGS)

# Create build dir
$(BUILDDIR):
	mkdir $@

$(BUILDDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(CLEAN) $(BUILDDIR)
	del main$(EXEENDING)
	$(PDBCLEAN)
	$(MAKE) -C tests clean
	del *.dll

.PHONY: all clean