//**************************************************************************************************
//  INTERFACES ESPECIALES
//**************************************************************************************************

process enem_ener_interface (eei_enem_id)
private
    int max_energia;
    
    int temp_map;
begin
    //creando cajetin
    graph = map_new(247, 22);
    map_clear(file, graph, rgb(0, 128, 0));
    drawing_map(file, graph);
    drawing_color(0);
    draw_line(0, 0, 0, 1);			//redondeo de esquina
    draw_line(0, 0, 1, 0);
    drawing_color(rgb(0, 212, 0));	//brillo del borde
    draw_line(2, 0, 247, 0);
    draw_line(1, 1, 247, 1);
    draw_line(2, 2, 2, 2);
    draw_line(0, 2, 0, 22);
    draw_line(1, 2, 1, 22);
	
    center_set(file, graph, 0, 0);
    map_put(0, graph, 0, interfaz_grafs[INTERFAZ_ENEM_ENER], 6, 8);	//escribiendo "enemigo"
    //hueco de energias
	drawing_color(rgb(0,0,0));
    draw_rectangle_filled(41, 7, 243-41, 15-7);
    drawing_color(rgb(0, 96, 0));
    draw_line(40, 6, 244, 6);
    draw_line(40, 6, 40, 15);
    drawing_color(rgb(0, 212, 0));
    draw_line(40, 16, 244, 16);
    draw_line(244, 8, 244, 16);
	
    x = 73;
    y = 240;
    z = -6;
    //flags = 4;
    
	if (exists(eei_enem_id))
		energia = eei_enem_id.energia;
	end
    drawing_color(rgb(255, 255, 0));
    draw_rectangle_filled(42, 9, 242-42, 13-9);
    
    while (y > 218)
        y--;
        frame;
    end
    max_energia = energia;
    
    while (exists(info_prota.id_prota) && exists(eei_enem_id))
        if (eei_enem_id.energia != energia)
            if (eei_enem_id.energia > 0)
                energia = (eei_enem_id.energia * 200) / max_energia;
            else
                energia = 1;
            end
            drawing_map(file, graph);
            drawing_color(rgb(255, 255, 0));
            draw_rectangle_filled(42, 9, /*42 +*/ energia, 13-9);
            drawing_color(rgb(0,0,0));
            draw_rectangle_filled(42 + energia + 1, 9, 242-(42 + energia + 1), 13-9);
            energia = eei_enem_id.energia;
        end
		//Transparencia si el prota se esconde detrás
        if ((info_prota.id_prota.x >= x) && (info_prota.id_prota.y >= y))
            flags = 4;
        else
			flags = 0;
		end
        
        frame;
    end
    
    while (y < 240)
        y++;
        frame;
    end
    map_unload(file, graph);
end