COMPILER_PREFIX=arm-none-linux-gnueabi-

HelloWorld: HelloWorld_static.o ../../lib/slog.a ../../lib/slog_modtbl.a
	$(COMPILER_PREFIX)gcc -o HelloWorld HelloWorld_static.o ../../lib/slog.a ../../lib/slog_modtbl.a

HelloWorld_static.o: HelloWorld_static.c
	$(COMPILER_PREFIX)gcc -I../../ -c HelloWorld_static.c

clean:
	rm -f *.o HelloWorld
