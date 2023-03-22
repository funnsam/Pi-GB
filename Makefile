build:
	# png2asset tiles.png -spr8x8 -tiles_only -pack_mode 1bpp
	# mv tiles.c src/ && mv tiles.h src/
	lcc -Wa-l -Wl-m -Wl-j -Wl-yp0x143=0x80 -o main.gbc src/main.c
	bgb64 main.gbc