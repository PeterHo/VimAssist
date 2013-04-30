CROSS=arm-linux-

^PROJECTNAME^.bin: ^PROJECTNAME^.c
	${CROSS}gcc ^PROJECTNAME^.c -c -o ^PROJECTNAME^.o
	${CROSS}ld -Ttext=0x50200000 ^PROJECTNAME^.o -o ^PROJECTNAME^.elf
	${CROSS}objcopy -O binary ^PROJECTNAME^.elf ^PROJECTNAME^.bin
	rm -f *.elf *.o
clean:
	rm -f *.elf *.o
	rm -f ^PROJECTNAME^.bin
