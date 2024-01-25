process lsm_chapter_label (file, graph, int pointer lsm_activar)
private
	int cont;
begin
	x = -180;
	y = 106;
	z = -4;
	loop
		if (*lsm_activar && (cont < 20))
			cont++;
		end
		if (!(*lsm_activar) && (cont > 0))
			cont--;
		end
		x = -190 + (cont * 10);
		frame;
	end
end

process lsm_episode_name (file, graph, int pointer lsm_seleccionado, int n)
begin
	x = 160;
	y = 147;
	z = -5;
	size_y = 0;
	loop
		if (*lsm_seleccionado == n)
			if (size_y < 100)
				size_y += 6;
				if (size_y > 100) size_y = 100; end
			end
			if (y < 132) y++; end
			if (y > 132) y--; end
		elsif (*lsm_seleccionado < n)
			if (size_y > 0)
				size_y -= 6;
				if (size_y < 0) size_y = 0; end
			end
			if (y < 147) y++; end
		elsif (*lsm_seleccionado > n)
			if (size_y > 0)
				size_y -= 6;
				if (size_y < 0) size_y = 0; end
			end
			if (y > 117) y--; end
		end
		frame;
	end
end

process lsm_chapter_screenshot (file, graph, int pointer lsm_seleccionado, int n)
//Screenshots de 100x75 (espacio disponible 120x78)
begin
	x = 60;
	y = 319;
	//z = -5;
	loop
		if (*lsm_seleccionado == n)
			if (size < 100)
				size ++;
				//if (size_y > 100) size_y = 100; end
			end
			/*if (y < 189)
				y += 13;
				if (y > 189) y = 189; end
			end*/
			if (y > 189)
				y -= 13;
				if (y < 189) y = 189; end
			end
			if (x < 60)
				x += 13;
				if (x > 60) x = 60; end
			end
			/*if (x > 60)
				x -= 13;
				if (x < 60) x = 60; end
			end*/
		elsif (*lsm_seleccionado < n)
			if (size > 80)
				size -= 2;
				if (size < 80) size = 80; end
			end
			if (x < 60)
				x += 13;
				if (x > 60) x = 60; end
			end
			if (y < 319)
				y += 13;
				if (y > 319) y = 319; end
			end
		elsif (*lsm_seleccionado > n)
			if (size > 80)
				size -= 2;
				if (size < 80) size = 80; end
			end
			if (x > -100)
				x -= 20;
				if (x < -100) x = -100; end
			end
			if (y > 189)
				y -= 13;
				if (y < 189) y = 189; end
			end
		end
		frame;
	end
end