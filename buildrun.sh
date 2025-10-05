if [ ! -d "bin" ]; then
    mkdir bin
else
	rm bin/*
fi
g++ -g -O0 -I . -o bin/interrupts interrupts.cpp
./bin/interrupts ./input_files/trace_overlap.txt vector_table.txt device_table.txt