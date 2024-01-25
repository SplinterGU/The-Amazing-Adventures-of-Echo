			switch (enem_p_dir)
				case 1: p_libre = enem_dur[0][2]; end
				case 2: p_libre = enem_dur[1][2]; end
				case 3: p_libre = enem_dur[2][2]; end
				case 4: p_libre = enem_dur[0][1]; end
				case 5: p_libre = 0; end
				case 6: p_libre = enem_dur[2][1]; end
				case 7: p_libre = enem_dur[0][0]; end
				case 8: p_libre = enem_dur[1][0]; end
				case 9: p_libre = enem_dur[2][0]; end
			end //Switch
			
			if (p_libre > 0 && p_libre < 150)
				enem_mover_h = 0;
				vel_horiz = 0;
				vel_vert = 0;
			end
			
			x3 += vel_horiz;   //actualizamos posición
			y3 += vel_vert;
			
			enem_offsx = (x3 / resolution3) % id_tscroll.tmapa[0].ancho_tile;
			enem_offsy = (y3 / resolution3) % id_tscroll.tmapa[0].alto_tile;
			