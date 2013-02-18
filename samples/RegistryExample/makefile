COMPILER_PREFIX=arm-none-linux-gnueabi-

RegistryExample: RegistryExample.o ../../lib/slog.a ../../lib/slog_modtbl.a
	$(COMPILER_PREFIX)gcc -o RegistryExample RegistryExample.o ../../lib/slog.a ../../lib/slog_modtbl.a

RegistryExample.o: RegistryExample.c
	$(COMPILER_PREFIX)gcc -I../../ -c RegistryExample.c

clean:
	rm -f *.o RegistryExample
