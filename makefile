COMPILER_PREFIX = arm-none-linux-gnueabi-
SLOG_ROOT_DIR = ./
SLOG_SRC_DIR = $(SLOG_ROOT_DIR)/src

all: slog.a slog_modtbl.a

slog.a: LoggerSys.o Log.o System.o Registry.o Text.o TimestampNull.o TimestampStd.o Diags.o LoggerBuf.o Config.o
	$(COMPILER_PREFIX)ar cr $(SLOG_ROOT_DIR)/lib/slog.a LoggerSys.o Log.o System.o Registry.o Text.o TimestampNull.o TimestampStd.o Diags.o LoggerBuf.o Config.o

slog_modtbl.a: slog_modtbl.o
	$(COMPILER_PREFIX)ar cr $(SLOG_ROOT_DIR)/lib/slog_modtbl.a slog_modtbl.o

LoggerSys.o: $(SLOG_SRC_DIR)/LoggerSys.c
	$(COMPILER_PREFIX)gcc -I$(SLOG_ROOT_DIR) -c $(SLOG_SRC_DIR)/LoggerSys.c

LoggerBuf.o: $(SLOG_SRC_DIR)/LoggerBuf.c
	$(COMPILER_PREFIX)gcc -I$(SLOG_ROOT_DIR) -c $(SLOG_SRC_DIR)/LoggerBuf.c
	
Log.o: $(SLOG_SRC_DIR)/Log.c
	$(COMPILER_PREFIX)gcc -I$(SLOG_ROOT_DIR) -c $(SLOG_SRC_DIR)/Log.c

System.o: $(SLOG_SRC_DIR)/System.c
	$(COMPILER_PREFIX)gcc -I$(SLOG_ROOT_DIR) -c $(SLOG_SRC_DIR)/System.c

Registry.o: $(SLOG_SRC_DIR)/Registry.c
	$(COMPILER_PREFIX)gcc -I$(SLOG_ROOT_DIR) -c $(SLOG_SRC_DIR)/Registry.c

Text.o: $(SLOG_SRC_DIR)/Text.c
	$(COMPILER_PREFIX)gcc -I$(SLOG_ROOT_DIR) -c $(SLOG_SRC_DIR)/Text.c

TimestampNull.o: $(SLOG_SRC_DIR)/TimestampNull.c
	$(COMPILER_PREFIX)gcc -I$(SLOG_ROOT_DIR) -c $(SLOG_SRC_DIR)/TimestampNull.c

TimestampStd.o: $(SLOG_SRC_DIR)/TimestampStd.c
	$(COMPILER_PREFIX)gcc -I$(SLOG_ROOT_DIR) -c $(SLOG_SRC_DIR)/TimestampStd.c

Diags.o: $(SLOG_SRC_DIR)/Diags.c
	$(COMPILER_PREFIX)gcc -I$(SLOG_ROOT_DIR) -c $(SLOG_SRC_DIR)/Diags.c

Config.o: $(SLOG_SRC_DIR)/Config.c
	$(COMPILER_PREFIX)gcc -I$(SLOG_ROOT_DIR) -c $(SLOG_SRC_DIR)/Config.c

slog_modtbl.o: $(SLOG_SRC_DIR)/slog_modtbl.c
	$(COMPILER_PREFIX)gcc -I$(SLOG_ROOT_DIR) -c $(SLOG_SRC_DIR)/slog_modtbl.c

clean:
	rm  -f *.o ./lib/*.a
