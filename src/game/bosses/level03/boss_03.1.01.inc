process nave_evento (x2, y2, graph, energia)
private
    int temp;
    int temp_espada;
begin
    file = enem_grafs[0][cte_event];
    loop
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        //impacto con las balas
        /*temp = collision(type normal_shot);
        if (temp != 0)
            energia -= temp.energia;
            //say("enemigo (" + itoa(enem_tx) + "," + itoa(enem_ty) + "): energía: " + itoa(energia));
            //say("el disparo tenía energia: " + itoa(temp.energia));
            temp.energia = 0;
            if ((mi_temblor != 0) && exists(mi_temblor))
                mi_temblor.energia = 3;
            else
                mi_temblor = enem_temblor(id, 3);
            end
        end*/
        temp = get_id(type normal_shot);
        while (temp != 0)
            if (abs(temp.x - x) < 10)
                if (abs(temp.y - y) < 6)
                    energia -= temp.energia;
                    temp.energia = 0;
                    if ((mi_temblor != 0) && exists(mi_temblor))
                        mi_temblor.energia = 3;
                    else
                        mi_temblor = enem_temblor(id, 3);
                    end
                end
            end
            temp = get_id(type normal_shot);
        end
		
        temp = collision(type espadazo);
        if ((temp != 0) && (temp != temp_espada))
            energia -= temp.energia;
            if ((mi_temblor != 0) && exists(mi_temblor))
                mi_temblor.energia = 3;
            else
                mi_temblor = enem_temblor(id, 3);
            end
            temp_espada = temp;
        end
        if (energia <= 0) break; end
        frame;
    end
end


process space_invaders ()
private
	int x3, y3;
    int contx, conty;
	
	int array_naves[9][6];
    int array_grafs[6] = 3,1,2,3,2,1,2;
	
	int vel_horiz;
    int cont_naves;     //cuenta las naves de la ultima fila
    int event_filas;    //indica cual es la última fila de naves vivas
	
	int fin_evento;
	
	int cont_disp, cont_nave_disp;
begin
	//colocacion de las naves
    fin_evento = 0;
    prota_control = 0;
    event_filas = 9;
    x3 = 3708;
    y3 = 48;
    for (conty = 0; conty <= 6; conty++)
        for (contx = 0; contx <= 9; contx++)
            array_naves[contx][conty] = nave_evento(x3 + (contx * 25), y3 + (conty * 16), array_grafs[conty],
													9 - conty);
            //14-(2*conty));
        end
    end
    
    while (get_id(type normal_shot)) frame; end
    
	//say("naves generadas");
    while (x3 != 3422)
        x3 -= 2;
        for (conty = 0; conty <= 6; conty++)
            for (contx = 0; contx <= 9; contx++)
                array_naves[contx][conty].x2 = x3 + (contx * 25);
            end
        end
        frame;
    end
    
    //comienza la juerga
    prota_control = 1;
    vel_horiz = -1;
    while (!fin_evento)
        fin_evento = 1;
        x3 += vel_horiz;
        cont_naves = 0;
        
        //llegados al tope, cambiamos de direccion y bajamos un pixel
        if ((x3 == 3397) || (x3 == 3451))
            vel_horiz = vel_horiz * (-1);
            if (y3 < (98 + (16 * (6 - event_filas))) ) y3++; end
        end
        
        for (conty = 0; conty <= 6; conty++)
            for (contx = 0;contx <= 9; contx++)
                if (exists(array_naves[contx][conty]))
                    fin_evento = 0;
                    array_naves[contx][conty].x2 = x3 + (contx * 25);
                    array_naves[contx][conty].y2 = y3 + (conty * 16);
                    if (conty == event_filas) cont_naves++; end
                end
            end
        end
        
        if (cont_naves == 0) event_filas--; end
        
        if ((cont_disp <= 0) && (!fin_evento))
            //say("entro: cont_disp " + itoa(cont_disp) + " fin evento " + itoa(fin_evento));
            conty = 0;
            cont_nave_disp = rand(0, 53);
            loop
                for (contx = 0; contx <= 9; contx++)
                    if (exists(array_naves[contx][conty]))
                        cont_nave_disp--;
                        if (cont_nave_disp <= 0) break; end
                    end
                end
                if (cont_nave_disp <= 0)
                    break;
                else
                    conty++;
                    if (conty > 6) conty = 0; end
                end
            end
            enem_normal_shot2(enem_grafs[0][cte_event], 10, 10, array_naves[contx][conty].x2,
								array_naves[contx][conty].y2, 0, -90000, 5, 50);
            cont_disp = rand(10, 60);
            //say("salgo");
        else
            cont_disp--;
        end
        
        frame;
    end
    
end