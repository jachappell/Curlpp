PROG=example2
OBJDIR=.obj
CC=g++

CFLAGS = -Wall --std=c++0x -I.. `pkg-config libcurl --libs`
LDFLAGS = `pkg-config libcurl --libs`

$(shell test -f Fetch.cpp || ln ../Fetch.cpp .)

$(shell mkdir -p $(OBJDIR)) 

OBJS = $(OBJDIR)/example2.o $(OBJDIR)/Fetch.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(PROG)

-include $(OBJS:.o=.d)

$(OBJDIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $*.cpp -o $(OBJDIR)/$*.o
	$(CC) -MM $(CFLAGS) $*.cpp > $(OBJDIR)/$*.d
	@mv -f $(OBJDIR)/$*.d $(OBJDIR)/$*.d.tmp
	@sed -e 's|.*:|$(OBJDIR)/$*.o:|' < $(OBJDIR)/$*.d.tmp > $(OBJDIR)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(OBJDIR)/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $(OBJDIR)/$*.d
	@rm -f $(OBJDIR)/$*.d.tmp

clean:
	rm -rf $(PROG) $(OBJDIR) Fetch.cpp

