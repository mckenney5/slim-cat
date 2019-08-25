cat.out: src/cat.c
	$(CC) -Wall -Ofast -o cat.out src/cat.c

cat.1.gz: cat.1
	gzip -k cat.1

debug: src/cat.c
	$(CC) -Wall -O0 -g -o cat.debug.out src/cat.c

clean:
	rm cat.*out
	rm cat.1.gz

install: cat.out cat.1.gz
	sudo cp /usr/bin/cat /usr/bin/cat.bak
	sudo cp cat.out /usr/bin/cat
	sudo cp /usr/share/man/man1/cat.1.gz /usr/share/man/man1/cat.1.gz.bak
	sudo cp cat.1.gz /usr/share/man/man1/

uninstall: /usr/bin/cat.bak /usr/share/man/man1/cat.1.gz.bak
	sudo mv /usr/bin/cat.bak /usr/bin/cat
	sudo mv /usr/share/man/man1/cat.1.gz.bak /usr/share/man/man1/cat.1.gz

unsafe-install: cat.out cat.1.gz
	overwrites cat in /usr/bin
	sudo cp cat.out /usr/bin/cat
	sudo cp cat.1.gz /usr/share/man/man1/

unsafe-uninstall:
	sudo rm /usr/bin/cat
	sudo rm /usr/share/man/man1/cat.1.gz

