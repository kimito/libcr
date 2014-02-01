TARGET=libcr.so
OBJS=cr.o
CFLAGS=-fPIC

EXAMPLE_TARGET=example
EXAMPLE_OBJS=example.o $(TARGET)

$(TARGET):$(OBJS)
	$(CC) -shared -o $@ $^

$(EXAMPLE_TARGET):$(EXAMPLE_OBJS) 
	$(CC) -L. -lcr -o $@ $<

clean:
	rm -f $(EXAMPLE_TARGET) $(EXAMPLE_OBJS) $(OBJS)
