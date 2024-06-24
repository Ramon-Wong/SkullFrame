CC				= gcc
compile 		= -Wall -c
build			= -Wall -o

src_dir			= src
obj_dir			= build
web_dir			= web
inc_dir			= include

ALL_SOURCE		= $(wildcard $(src_dir)/*.c)
SOURCE			= $(filter-out $(src_dir)/webkit.c, $(wildcard $(src_dir)/*.c))
ALL_OBJECTS		= $(patsubst $(src_dir)/%.c, $(obj_dir)/%.o, $(ALL_SOURCE))

WEBKIT_SRC		= $(src_dir)/webkit.c
WEBKIT_OBJ		= $(obj_dir)/webkit.o

TARGET 			= $(obj_dir)/bin/.main
PKG_LIBS		= `pkg-config --libs gtk+-3.0 webkit2gtk-4.0` -lpthread
PKG_FLAGS		= `pkg-config --cflags gtk+-3.0 webkit2gtk-4.0`

all:
	@echo cooking stuff
	$(CC) $(PKG_FLAGS) $(compile) $(WEBKIT_SRC) $(PKG_LIBS) -I$(inc_dir) -o $(WEBKIT_OBJ)
	@for i in $(SOURCE); do \
		obj=`echo $$i | sed 's|$(src_dir)|$(obj_dir)|' | sed 's|.c|.o|'`; \
		$(CC) $(PKG_FLAGS) $(compile) $$i $(PKG_LIBS) -I$(inc_dir) -o $$obj ; \
	done	
	@echo baking the pizza....
	$(CC) $(build) $(TARGET) $(ALL_OBJECTS) $(PKG_LIBS)

run:
	@echo Running...
	$(TARGET)

source:
	@for file in $(ALL_SOURCE); do \
		echo Filename: $$file; \
	done

object:
	@echo $(OBJECTS)
	@echo $(OBJECTS)

clean:
	rm -f $(ALL_OBJECTS)
	rm -f $(TARGET)

