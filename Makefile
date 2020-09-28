include makefile.conf

all: $(TARGET)

$(TARGET): $(JHASHTABLE_OBJS)
	$(AR) $@ $^

clean:
	$(RM) $(jHASHTABLE_OBJS)
	$(RM) $(TARGET)

