GLOBAL
    struct config_data
        int32 teclas[k_last-1][1];
        byte usar_joy_hat;
        byte tipo_graficos = 1;
        byte usar_scroll_fondo = 1;
        byte usar_scroll_frontal = 1;
        int32 cte_frameskip;
    end
    
    string graph_dir = "stylish";
    int cte_frameskip = 0;
	int GP2X_mode;
    int game_background_scroll = 1;
    int game_foreground_scroll = 1;
END
