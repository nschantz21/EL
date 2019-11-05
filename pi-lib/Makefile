
# This makefile is intended for use with a Yocto project SDK where the various
# tools such as CC, LD, etc, have been defined as environment variables.

# Uncomment the following line to orient the display as portrait. The default
# is landscape.
#PORTRAIT = y

CFLAGS	+= -Wall -g -Og -fPIC
LIB	= libmchw.so
SLIB	= libmchw.a

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
	$(CC) $(CFLAGS) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $< -I ../includes
	@mv $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
	
-include $(DEPS)
$(LIB): $(LIBOBJ)
	$(CC) $(LDFLAGS) -shared -o $@ $^
$(SLIB): $(LIBOBJ)
	$(AR) rc $@ $^
	$(RANLIB) $@
	
install: $(LIB)
	install ../includes/libfahw*.h /usr/local/include
	install --mode=644 libfahw.so /usr/local/lib
	install --mode=644 libfahw.a /usr/local/lib
	ldconfig
clean:
	rm -rf $(LIB) $(LIBOBJ) $(SLIB) $(DEPS) $(OBJDIR) $(DEPDIR)
