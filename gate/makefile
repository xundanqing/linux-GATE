#通用makefile
#文件目录
DEBUG_DIR=./debug
SRC_DIR=./source
INC_DIR=./include ./libbase

SRC=$(wildcard $(SRC_DIR)/*.cc )  #源文件
OBJS=$(patsubst $(SRC_DIR)/%.cc,$(DEBUG_DIR)/%.o,$(SRC))

#目标文件名
TARGET=gate
INSTALL_PATH ?= .

#修改编译器
ARCH ?= arm-hismall-linux-
CC=$(ARCH)gcc
CPP=$(ARCH)g++
AR=$(ARCH)ar
STRIP=$(ARCH)strip


CFLAGS += -Wall 
LDFLAGS += -lpthread

#加载库文件
ifeq ($(ARCH), arm-hismall-linux-)
LDFLAGS += ./lib/hi351x/libbase.a
LDFLAGS += ./lib/hi351x/libzlog.a
else
ifeq ($(ARCH), arm-hisiv100nptl-linux-)
LDFLAGS += ./lib/hi3531/libbase.a
LDFLAGS += ./lib/hi3531/libzlog.a
else
ifeq ($(ARCH), arm-hisiv300-linux-)
LDFLAGS += ./lib/hi3521/libbase.a
#LDFLAGS += ./lib/hi3521/libzlog.a
else
LDFLAGS += ./lib/x86/libbase.a
LDFLAGS += ./lib/x86/libzlog.a
endif
endif
endif

CFLAGS  += $(foreach dir,$(INC_DIR),-I$(dir))

all:$(TARGET)
$(TARGET): $(OBJS)
	$(CPP) $(OBJS) -o $@ $(CFLAGS) $(LDFLAGS)
	$(STRIP) $(TARGET)
#cp $(TARGET) $(INSTALL_PATH)


$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CPP) $(CFLAGS) -c $< -o $@ 

print:
	@echo $(SRC)
	@echo $(OBJS)

	
clean:
	-rm $(OBJS) $(LIB_TARGET)

