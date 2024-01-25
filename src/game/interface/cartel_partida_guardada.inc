process game_saved_graph ()
private
    int cont;
    int cont_anim;
begin
    file = 0;
    graph = interfaz_grafs[INTERFAZ_SALVADO1];
    x = 401;
    y = 228;
    z = -11;
    while (x > 319)
        x -= 2;
        cont_anim++;
        switch (cont_anim)
        case 20: graph = interfaz_grafs[INTERFAZ_SALVADO2]; end
        case 40: graph = interfaz_grafs[INTERFAZ_SALVADO1]; cont_anim = 0; end
        end //switch
        frame;
    end
    
    for (cont = 0; cont < 150; cont++)
        cont_anim++;
        switch (cont_anim)
        case 20: graph = interfaz_grafs[INTERFAZ_SALVADO2]; end
        case 40: graph = interfaz_grafs[INTERFAZ_SALVADO1]; cont_anim = 0; end
        end //switch
        frame;
    end
    
    while (x < 400)
        x += 2;
        cont_anim++;
        switch (cont_anim)
        case 20: graph = interfaz_grafs[INTERFAZ_SALVADO2]; end
        case 40: graph = interfaz_grafs[INTERFAZ_SALVADO1]; cont_anim = 0; end
        end //switch
        frame;
    end
end
