function int veo_prota (x, y, int veo_dir, int veo_distx, int veo_disty)
//Comprueba si el enemigo ve al prota en alguno de los dos lados
private
    int temp;
    int dato_a_devolver;
begin
    dato_a_devolver = 0;
    if (exists(info_prota.id_prota))
        if (abs(info_prota.id_prota.y2 - y) < veo_disty)
            temp = info_prota.id_prota.x2 - x;
			//Mirando hacia la derecha
            if ((veo_dir == 1) && (temp > 0) && (temp < veo_distx))
                dato_a_devolver = 1;
            end
			//Mirando a la izquierda
            if ((veo_dir == 0) && (temp < 0) && (abs(temp) < veo_distx))
                dato_a_devolver = 1;
            end
			//Mirando en ambas direcciones
            if ((veo_dir == 2) && (abs(temp) < veo_distx))
                dato_a_devolver = 1;
            end
        end
    end
    
    return (dato_a_devolver);
end

function int veo_prota2 (x, y, int veo_distx1, int veo_disty1, int veo_distx2, int veo_disty2)
//Comprueba si el enemigo ve al prota a unas determinadas distancias horizontal o verticalmente
private
    int temp;
    int dato_a_devolver;
begin
    dato_a_devolver = 0;
    //reordenamos las distancias, para hacerlo todo más homogeneo
    if (veo_disty2 < veo_disty1)
        temp = veo_disty1;
        veo_disty1 = veo_disty2;
        veo_disty2 = temp;
    end
    if (veo_distx2 < veo_distx1)
        temp = veo_distx1;
        veo_distx1 = veo_distx2;
        veo_distx2 = temp;
    end
    
    //say("límites x: " + itoa(veo_distx1) + " " + itoa(veo_distx2));
    //say("límites y: " + itoa(veo_disty1) + " " + itoa(veo_disty2));
    //say(itoa(info_prota.id_prota.x2) + " " + itoa(x));
    //say(itoa(info_prota.id_prota.y2) + " " + itoa(y));
    if (exists(info_prota.id_prota))
        temp = info_prota.id_prota.y2 - y;
        if ((temp > veo_disty1) && (temp < veo_disty2))
            temp = info_prota.id_prota.x2 - x;
            if ((temp > veo_distx1) && (temp < veo_distx2))
                dato_a_devolver = 1;
            end
        end
    end
    
    return (dato_a_devolver);
end