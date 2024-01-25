process intro_boss_03_02 ()
private
	int temp_posx;
	int cont;
begin
	x = 160;
	y = 300;
	z = -10;
	file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/blom_intro.fpg");
	graph = 1;
	
	for (y = 300; y > 120; y -= 2)
		frame;
	end
	
	for (cont = 0; cont < 150; cont++)
		frame;
	end
	
	for (y = 120; y > 27; y--)
		//size = ((y - 77) * 100) / 43;
		size = ((y - 27) * 100) / 93;
		frame;
	end
	
onexit
	fpg_unload(file);
end
