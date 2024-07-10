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
PKG_FLAGS		= `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0 libxml-2.0`

CONFIG_XML		= config.xml

all:
	@if [ -f $(RESOURCES_C) ] && [ -f $(RESOURCES_H) ]; then \
		echo "compiling and building your shit"; \
		echo "list of sources: $(ALL_SOURCE)"; \
		$(CC) $(build) $(TARGET) $(ALL_SOURCE) -I include $(PKG_FLAGS); \
		echo "..Size of $(TARGET) is $$(($(TARGET_SIZE) / 1024)) KB"; \
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
	valgrind $(TARGET) $(CONFIG_XML)

object:
	@echo $(OBJECTS)
	@echo $(OBJECTS)

prepare:
	mkdir -p $(obj_dir)
	mkdir -p $(obj_dir)/bin

clean:
	rm -f $(RESOURCES_C) $(RESOURCES_H)
	rm -f $(TARGET)

