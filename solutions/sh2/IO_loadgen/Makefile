TARGET=my_loadgen
OUTPUT=output.txt

all: $(TARGET)

$(TARGET): $(TARGET).c
	gcc -Wall -Wextra -std=c11 $(TARGET).c -o $(TARGET)

clean:
	rm -f $(TARGET) *.o $(OUTPUT_FILE)