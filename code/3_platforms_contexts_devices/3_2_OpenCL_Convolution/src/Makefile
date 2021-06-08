PROJECT_NAME = 3_2_OpenCL_Convolution
.SILENT: all project

all: 
	cd ../build; \
	make
	@echo -e "\033[92m ------------- Compilation Successful ------------------- \033[0m"
project:
	if [ ! -d "../build" ]; then mkdir ../build; fi
	if [ ! -d "../bin" ]; then mkdir ../bin; fi
	cd ../build; \
	cmake ..; \
	make
run:
	../bin/$(PROJECT_NAME)
	@echo -e "\033[92m ------------- Execution Successful ------------------- \033[0m"
debug:
	cd ../build && \
	cmake -G "CodeLite - Unix Makefiles" .. && \
	codelite ${PROJECT_NAME}.workspace &! > /dev/null
clean:
	rm -rf ../build/*
	rm ../bin/*
