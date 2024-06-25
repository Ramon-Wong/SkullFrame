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
SOURCE			= $(filter-out $(src_dir)/webkit.c, $(wildcard $(src_dir)/*.c))
ALL_OBJECTS		= $(patsubst $(src_dir)/%.c, $(obj_dir)/%.o, $(ALL_SOURCE))

TARGET 			= $(obj_dir)/bin/.main
PKG_LIBS		= `pkg-config --libs gtk+-3.0 webkit2gtk-4.0` -lpthread
PKG_FLAGS		= `pkg-config --cflags gtk+-3.0 webkit2gtk-4.0`

all: prepare
	@echo cooking the stuff
	@for i in $(SOURCE); do \
		obj=`echo $$i | sed 's|$(src_dir)|$(obj_dir)|' | sed 's|.c|.o|'`; \
		$(CC) $(PKG_FLAGS) $(compile) $$i $(PKG_LIBS) -I$(inc_dir) -o $$obj ; \
	done	
	@echo baking the pizza....
	$(CC) $(build) $(TARGET) $(ALL_OBJECTS) $(PKG_LIBS)

run:
	@echo Running...
	$(TARGET)

resources:
	@if [ -f $(RESOURCES_C) ] && [ -f $(RESOURCES_H) ]; then \
		echo "Both files exist (resources.c/resources.h)"; \
	else \
		echo "One or both files do not exist. but don't worry, I'll create these ASAP"; \
		glib-compile-resources --generate-source $(RESOURCES_XML) --target=$(RESOURCES_C); \
		glib-compile-resources --generate-header $(RESOURCES_XML) --target=$(RESOURCES_H); \
		echo "..done"; \
	fi; \

source:
	@for file in $(ALL_SOURCE); do \
		echo Filename: $$file; \
	done

object:
	@echo $(OBJECTS)
	@echo $(OBJECTS)

prepare:
	mkdir -p $(obj_dir)
	mkdir -p $(obj_dir)/bin

clean:
	rm -f $(RESOURCES_C) $(RESOURCES_H)
	rm -f $(ALL_OBJECTS)
	rm -f $(TARGET)

