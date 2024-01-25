//***************************************************************************
//  FUNCIONES DE ITEMS
//***************************************************************************
function cambiar_exp_arma (energia)
begin
    armas_level[armas_select][0] += energia;
    if (energia > 0)
        if (armas_level[armas_select][0] >= armas_level[armas_select][3])
            armas_level[armas_select][0] = armas_level[armas_select][3];
        else
            if (armas_level[armas_select][0] >= (armas_level[armas_select][armas_curr_level + 1]))
                armas_curr_level++;
            end
        end
    end
    if (energia < 0)
        if (armas_level[armas_select][0] < 0)
            armas_level[armas_select][0] = 0;
        else
            if (armas_level[armas_select][0] < (armas_level[armas_select][armas_curr_level]))
                armas_curr_level--;
            end
        end
    end
    refresh_interface_wexp();
end

//***************************************************************************
//  FUNCION PRINCIPAL GENERA ALEATORIO ITEM
//***************************************************************************

function random_item (energia, x2, y2)
private
    int temp_ener;
    int temp_exp;
    int temp;
    int ri_rangos[2];
begin
    if (info_prota.p_energ > 0)
        //calculamos el porcentaje de vida restante
		if (info_prota.p_max_energ != 0)
			temp_ener = (info_prota.p_energ * 100) / info_prota.p_max_energ;
		else
			temp_ener = 100;
		end
		//calculamos el porcentaje de experiencia restante
		if (armas_level[armas_select][3] != 0)
			temp_exp = (armas_level[armas_select][0] * 100) / armas_level[armas_select][3];
		else
			temp_exp = 100;
		end
        //say("% energia: "+itoa(temp_ener));
        //say("% arma: "+itoa(temp_exp));
		
		//Se establecen los rangs para que salga un item u otro
        ri_rangos[0] = 2 * (100 - temp_ener);
        ri_rangos[1] = ri_rangos[0] + 100 - temp_exp;
        //say("rangos: " + itoa(ri_rangos[0]) + "," + itoa(ri_rangos[1]) + "," + itoa(ri_rangos[1] * 1.1) + ";");
		
		//Giramos la ruleta
        temp = rand(0, ri_rangos[1] * 1.1);
        //say("valor aleatorio: " + itoa(temp));
		
        if (temp < ri_rangos[0])
            //generando energía
            ri_rangos[0] = temp_ener;
            if (ri_rangos[0] > 33) ri_rangos[0] = 33; end
            
            if (temp_ener > 33) ri_rangos[1] = temp_ener - 33; else ri_rangos[1] = 0; end
            if (ri_rangos[1] > 33) ri_rangos[1] = 33; end
            ri_rangos[1] = (ri_rangos[1] * 2) + ri_rangos[0];
            
            if (temp_ener > 66) ri_rangos[2] = temp_ener - 66; else ri_rangos[2] = 0; end
            if (ri_rangos[2] > 33) ri_rangos[2] = 33; end
            ri_rangos[2] = (ri_rangos[2] * 3) + ri_rangos[1];
            
            temp_ener = rand(0, ri_rangos[2]);
            temp_exp = 3;
            if ((temp_ener > ri_rangos[0]) && (energia >= 5)) temp_exp = 5; end
            if ((temp_ener > ri_rangos[1]) && (energia >= 15)) temp_exp = 15; end
            item_energy(x2, y2, temp_exp);
        elsif ((temp >= ri_rangos[0]) && (temp < ri_rangos[1]))
            //generando exp arma
            if (rand(0, 100) < 33) energia = energia / 2; end
            while (energia > 0)
                if (energia >= 10)
                    shot_exp(x2, y2, 10, rand(-15, 15));
                    energia -= 10;
                elsif (energia >= 5)
                    shot_exp(x2, y2, 5, rand(-15, 15));
                    energia -= 5;
                else
                    shot_exp(x2, y2, 2, rand(-15, 15));
                    energia -= 2;
                end
            end
        else
            //truño
        end
    end
end