process intro_boss_01_image (file, graph, x, y, z)
begin
	signal(id, s_freeze);
	frame;
end

//******************************************************************************************

process intro_boss_01_3_01 ()
private
	int temp_angle1, temp_angle2;
	int cont;
begin
	x = 160;
	y = 120;
	z = -10;
	alpha = 0;
	file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/ghyppo_intro.fpg");
	graph = 1;
	
	for (alpha = 0; alpha < 255; alpha++)
		temp_angle1 += 3500;
		if (temp_angle1 > 360000) temp_angle1 -= 360000; end
		temp_angle2 += 1500;
		if (temp_angle2 > 360000) temp_angle2 -= 360000; end
		x = 160 + (3 * sin(temp_angle1));
		y = 120 + (5 * sin(temp_angle2));
		frame;
	end
	alpha = 255;
	
	for (cont = 0; cont < 70; cont++)
		temp_angle1 += 3500;
		if (temp_angle1 > 360000) temp_angle1 -= 360000; end
		temp_angle2 += 1500;
		if (temp_angle2 > 360000) temp_angle2 -= 360000; end
		x = 160 + (3 * sin(temp_angle1));
		y = 120 + (5 * sin(temp_angle2));
		frame;
	end
	
	for (alpha = 255; alpha > 0; alpha--)
		temp_angle1 += 3500;
		if (temp_angle1 > 360000) temp_angle1 -= 360000; end
		temp_angle2 += 1500;
		if (temp_angle2 > 360000) temp_angle2 -= 360000; end
		x = 160 + (3 * sin(temp_angle1));
		y = 120 + (5 * sin(temp_angle2));
		frame;
	end
	alpha = 0;

onexit
	fpg_unload(file);
end


process intro_boss_01_3_02 ()
private
	int temp_posx;
	int cont;
begin
	x = 160;
	y = 120;
	z = -10;
	region = CTE_REGION_BOSS_INTRO;
	file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/gravor_intro.fpg");
	graph = 1;
	
	temp_posx = 1;
	region_define(CTE_REGION_BOSS_INTRO, 45, 80, temp_posx, 160);
	
	for (temp_posx = 1; temp_posx <= 230; temp_posx += 2)
		region_define(CTE_REGION_BOSS_INTRO, 45, 80, temp_posx, 160);
		frame;
	end
	region_define(CTE_REGION_BOSS_INTRO, 45, 80, 230, 160);
	
	for (cont = 0; cont < 200; cont++)
		frame;
	end
	
	for (temp_posx = 230; temp_posx > 0; temp_posx -= 2)
		region_define(CTE_REGION_BOSS_INTRO, 45 + (230 - temp_posx), 80, temp_posx, 160);
		frame;
	end
	
onexit
	fpg_unload(file);
end



process intro_boss_01_4 ()
private
	int temp_posx;
	int ib_hijo;
	
	int cont;
begin
	temp_posx = -150;
	x = 0 + temp_posx;
	y = 115;
	z = -11;
	file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/satavamp_intro.fpg");
	graph = 1;
	ib_hijo = intro_boss_01_image(file, 2, 320 - temp_posx, 120, z + 1);
	
	for (cont = 0; cont < 100; cont++) frame; end
	
	for (temp_posx = -150; temp_posx < 110; temp_posx += 7)
		x = temp_posx;
		ib_hijo.x = 320 - temp_posx;
		frame;
	end
	
	for (temp_posx = 110; temp_posx < 210; temp_posx++)
		x = temp_posx;
		ib_hijo.x = 320 - temp_posx;
		frame(200);
	end
	
	for (temp_posx = 210; temp_posx < 470; temp_posx += 7)
		x = temp_posx;
		ib_hijo.x = 320 - temp_posx;
		frame;
	end
	
onexit
	if ((ib_hijo != 0) && exists(ib_hijo))
		signal(ib_hijo, s_kill);
	end
	fpg_unload(file);
end