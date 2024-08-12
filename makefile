CC				= gcc
compile 		= -Wall -c 
build			= -Wall -o

src_dir			= src
obj_dir			= build
web_dir			= web
inc_dir			= include

RESOURCES_XML	= resources.xml
RESOURCES_C		= $(src_dir)/resources.c
RESOURCES_H		= $(inc_dir)/resources.h

ALL_SOURCE		= $(wildcard $(src_dir)/*.c)
ALL_OBJECTS		= $(patsubst $(src_dir)/%.c, $(obj_dir)/%.o, $(ALL_SOURCE))

TARGET 			= $(obj_dir)/bin/main
TARGET_SIZE	    = $(shell stat -c%s $(TARGET))
PKG_FLAGS		= `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0 libxml-2.0 glib-2.0`

CONFIG_XML		= config.xml

JQUERY_URL		= https://unpkg.com/jquery@3.6.0/dist/jquery.min.js
REACT_URL		= https://unpkg.com/react@16.14.0/umd/react.production.min.js
REACT_DOM_URL	= https://unpkg.com/react-dom@16.14.0/umd/react-dom.production.min.js

# Get the target project folder from the command line
TARGET_DIR		= $(filter-out $@,$(MAKECMDGOALS))

FILE_C_EXISTS	= $(shell test -f $(RESOURCES_C) && echo yes || echo no)
VALGRIND_PARAM  = --tool=memcheck --leak-check=full --leak-resolution=high --track-origins=yes --num-callers=20 --log-file=vgdump --smc-check=all --trace-children=yes

help:
	@echo "help on how to use\n" \
	"make clean			>> delete the compiled resources (html/javascript/css)\n" \
	"make all			>> compile/build all the C sources\n" \
	"make run			>> run the build with the config.xml file\n" \
	"make valgrind			>> run the application with valgrind for memory leaks\n" \

all:
	@if [ -f $(RESOURCES_C) ] && [ -f $(RESOURCES_H) ]; then \
		echo "compiling and building your shit"; \
		echo "list of sources: $(ALL_SOURCE)"; \
		$(CC) $(build) $(TARGET) $(ALL_SOURCE) -I include $(PKG_FLAGS); \
		echo "..Done!!, run 'make run' to test\n"; \
	else \
		echo "One or both of the resources.xml files does not exist."; \
		echo "please check the resources.xml and build these with"; \
		echo "make resources"; \
	fi; \

run:
	@echo Running...
	$(TARGET) $(CONFIG_XML)

resources:
	@if [ -f $(RESOURCES_C) ] && [ -f $(RESOURCES_H) ]; then \
		echo "Both files exist (resources.c/resources.h)"; \
	else \
		echo "One or both files do not exist. but don't worry, I'll create these ASAP"; \
		glib-compile-resources --generate-source $(RESOURCES_XML) --target=$(RESOURCES_C); \
		glib-compile-resources --generate-header $(RESOURCES_XML) --target=$(RESOURCES_H); \
		echo "..Done!!"; \
	fi; \

source:
	@for file in $(ALL_SOURCE); do \
		echo Filename: $$file; \
	done

valgrind:
	@echo "agruments: $(arg1)"
    ifeq ($(arg1), deep)
	@echo "Starting valgrind, deep check"
	valgrind $(VALGRIND_PARAM) $(TARGET) $(CONFIG_XML)
    else	
	@echo "Starting valgrind, regular quick check"
	valgrind $(TARGET) $(CONFIG_XML)
    endif 

object:
	@echo $(OBJECTS)
	@echo $(OBJECTS)

prepare:
	mkdir -p $(obj_dir)
	mkdir -p $(obj_dir)/bin

clean:
	rm -f $(RESOURCES_C) $(RESOURCES_H)
	rm -f $(TARGET)

example1:
	@echo "why me? $(arg1)"
    ifeq ($(arg1), jquery)
		@echo "Downloading ⏳ jQuery..."
		# curl -o ./web/script/jquery/jquery.js $(JQUERY_URL)
    else ifeq ($(arg1), react)
		@echo "Downloading ⏳ REACT..."
		# curl -o ./web/script/react.production.min.js $(REACT_URL)
		# curl -o ./web/script/react-dom.production.min.js $(REACT_DOM_URL)
    else ifeq ($(arg1), exist)
		@echo "detecting ⏳ file..."
        ifeq ($(FILE_C_EXISTS), yes)
		@echo "using FILE_C_EXISTS but positive..."
        else
		@echo "using FILE_C_EXISTS but negative..."
        endif
    else
		@echo "No valid argument provided. No download."
    endif
	@echo "Check on download file"


example2:
	@echo "why me again? $(arg1)"
	@if [ $(arg1) = "bacon" ]; then \
		echo "You and I are friends!!"; \
	elif [ "$(arg1)" = "burger" ]; then \
		echo "Maybe"; \
	else \
		echo "We are not brothers"; \
	fi; \
