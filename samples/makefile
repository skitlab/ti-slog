SLOG_ROOT_DIR = ./
COMPILER_PREFIX = arm-none-linux-gnueabi-

all: HelloWorld_ RegistryExample_

HelloWorld_:
	echo make -C ./HelloWorld COMPILER_PREFIX=$(COMPILER_PREFIX)
	make -C ./HelloWorld COMPILER_PREFIX=$(COMPILER_PREFIX)

RegistryExample_:
	echo make -C ./RegistryExample COMPILER_PREFIX=$(COMPILER_PREFIX)
	make -C ./RegistryExample COMPILER_PREFIX=$(COMPILER_PREFIX)

clean: HelloWorld_clean RegistryExample_clean
	
HelloWorld_clean:
	make -C ./HelloWorld clean

RegistryExample_clean:
	make -C ./RegistryExample clean
