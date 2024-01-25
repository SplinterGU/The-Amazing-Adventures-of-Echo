//**************************************************************************************************
//  PROCESOS ADICIONALES A LOS NIVELES (decorados)
//**************************************************************************************************

function game_draw_background (int n)
begin
    switch (n)
    case 1:     //fondo de estrellas para nivel 1-1 y 1-3
        map_clear(background.file, background.graph, rgb(0, 0, 64));
        drawing_map(0, 0);
        drawing_color(rgb(255, 255, 212));
        draw_circle_filled(250, 40, 28);
        put(enem_grafs[0][cte_level], 1, 17, 70);
        put(enem_grafs[0][cte_level], 1, 75, 45);
        put(enem_grafs[0][cte_level], 2, 30, 135);
        put(enem_grafs[0][cte_level], 1, 82, 120);
        //put(enem_grafs[0][cte_level], 2, 24, 204);
        //put(enem_grafs[0][cte_level], 1, 109, 175);
        put(enem_grafs[0][cte_level], 2, 121, 78);
        put(enem_grafs[0][cte_level], 2, 181, 48);
        put(enem_grafs[0][cte_level], 1, 178, 141);
        put(enem_grafs[0][cte_level], 1, 209, 91);
        put(enem_grafs[0][cte_level], 2, 275, 116);
        //put(enem_grafs[0][cte_level], 1, 230, 189);
    end
    end //switch
end