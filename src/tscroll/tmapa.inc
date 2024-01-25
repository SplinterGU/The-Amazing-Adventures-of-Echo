function obtener_tile (t_mapa pointer ot_struct, int at_posx, int at_posy, int at_posz)
private
    int dato_a_devolver;
    int at_pos;
begin
    if ( (at_posx >= 0) && (at_posx < [ot_struct].columnas) &&
         (at_posy >= 0) && (at_posy < [ot_struct].filas) &&
         (at_posz >= 0) && (at_posz < [ot_struct].capas) )
        at_pos = (at_posz * [ot_struct].columnas * [ot_struct].filas) +
                 (at_posy * [ot_struct].columnas) +
                  at_posx;
        dato_a_devolver = [ot_struct].b_mapa[at_pos];
    else
        dato_a_devolver = 0;
    end
    return (dato_a_devolver);
end

function modificar_tile (t_mapa pointer ot_struct, int at_posx, int at_posy, int at_posz, int at_valor)
private
    int dato_a_devolver;
    int at_pos;
begin
    if ( (at_posx >= 0) && (at_posx < [ot_struct].columnas) &&
         (at_posy >= 0) && (at_posy < [ot_struct].filas) &&
         (at_posz >= 0) && (at_posz < [ot_struct].capas) )
        at_pos = (at_posz * [ot_struct].columnas * [ot_struct].filas) +
                 (at_posy * [ot_struct].columnas) +
                  at_posx;
        [ot_struct].b_mapa[at_pos] = at_valor;
        dato_a_devolver = 1;
    else
        dato_a_devolver = 0;
    end
    return (dato_a_devolver);
end
