process item_press_down (x2, y2)
private
	int graph1, graph2;
	int cont;
begin
	file = item_grafs;
	graph1 = 71;
	graph2 = 72;
	graph = graph1;
	z = -1;
	if (exists(info_prota.id_prota))
		priority = info_prota.id_prota.priority + 1;
	end
	
	loop
		if (exists(info_prota.id_prota))
			x2 = info_prota.id_prota.x2;
			y2 = info_prota.id_prota.y2 - 24;
		end
		tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
		if (cont < 7)
			cont++;
		else
			cont = 0;
			if (graph == graph1)
				graph = graph2;
			else
				graph = graph1;
			end
		end
		frame;
	end
end