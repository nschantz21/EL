
# This makefile builds libsim to run in an x86 environment.

CFLAGS	+= -Wall -g -Og -fPIC
LIB		= libsim.so
SLIB	= libsim.a

OBJDIR	= obj
DEPDIR	= deps
LIBSRC	= $(wildcard *.c)
LIBOBJ	= $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(LIBSRC))))
DEPS	= $(patsubst %.c,$(DEPDIR)/%.Po,$(LIBSRC))

all: $(LIB) $(SLIB)
lib: $(LIB)
slib: $(SLIB)
$(OBJDIR)/%.o: %.c
	@test -d $(DEPDIR) || mkdir -p $(DEPDIR)
	@test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	gcc $(CFLAGS) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $< -I ../includes
	@mv $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
	
-include $(DEPS)
$(LIB): $(LIBOBJ)
	gcc $(LDFLAGS) -shared -o $@ $^
$(SLIB): $(LIBOBJ)
	ar rc $@ $^
	ranlib $@
	
clean:
	rm -rf $(LIB) $(LIBOBJ) $(SLIB) $(DEPS) $(OBJDIR) $(DEPDIR)
