//**************************************************************************************************
//  CONTROL DEL FICHERO DE CONFIGURACIÓN
//**************************************************************************************************

function create_default_config (cdc_os)
begin
#if 0
    switch (cdc_os)
    case 0:     //normal
#endif
        config_data.teclas[k_up][0]			= _up;
        config_data.teclas[k_down][0]		= _down;
        config_data.teclas[k_left][0]		= _left;
        config_data.teclas[k_right][0]		= _right;
        config_data.teclas[k_jump][0]		= _z;		//salto
        config_data.teclas[k_fire][0]		= _x;		//disparo
        config_data.teclas[k_previous][0]	= _a;		//arma anterior
        config_data.teclas[k_next][0]		= _s;		//arma_siguiente
        config_data.teclas[k_enter][0]		= _enter;	//pausa
        config_data.teclas[k_esc][0]		= _esc;		//salir
        config_data.teclas[k_vol_up][0]		= _c_plus;	//subir volumen
        config_data.teclas[k_vol_down][0]	= _c_minus;	//bajar volumen
#if 0        
        config_data.teclas[k_up][1]			= JOY_HAT_UP;
        config_data.teclas[k_down][1]		= JOY_HAT_DOWN;
        config_data.teclas[k_left][1]		= JOY_HAT_LEFT;
        config_data.teclas[k_right][1]		= JOY_HAT_RIGHT;
        config_data.teclas[k_jump][1]		= _jkey_x;			//salto
        config_data.teclas[k_fire][1]		= _jkey_a;			//disparo
        config_data.teclas[k_previous][1]	= _jkey_l;			//arma anterior
        config_data.teclas[k_next][1]		= _jkey_r;			//arma siguiente
        config_data.teclas[k_enter][1]		= _jkey_start;		//pausa
        config_data.teclas[k_esc][1]		= _jkey_select;		//salir
        config_data.teclas[k_vol_up][1]		= _jkey_volup;		//subir volumen
        config_data.teclas[k_vol_down][1]	= _jkey_voldown;	//bajar volumen
#endif
        config_data.usar_joy_hat = 1;
#if 0
    end
    case 1:     //GP2X
        config_data.teclas[k_up][0]			= _up;
        config_data.teclas[k_down][0]		= _down;
        config_data.teclas[k_left][0]		= _left;
        config_data.teclas[k_right][0]		= _right;
        config_data.teclas[k_jump][0]		= _z;		//salto
        config_data.teclas[k_fire][0]		= _x;		//disparo
        config_data.teclas[k_previous][0]	= _a;		//arma anterior
        config_data.teclas[k_next][0]		= _s;		//arma_siguiente
        config_data.teclas[k_enter][0]		= _enter;	//pausa
        config_data.teclas[k_esc][0]		= _esc;		//salir
        config_data.teclas[k_vol_up][0]		= _c_plus;	//subir volumen
        config_data.teclas[k_vol_down][0]	= _c_minus;	//bajar volumen
        
        config_data.teclas[k_up][1]			= _gp2x_jkey_up;
        config_data.teclas[k_down][1]		= _gp2x_jkey_down;
        config_data.teclas[k_left][1]		= _gp2x_jkey_left;
        config_data.teclas[k_right][1]		= _gp2x_jkey_right;
        config_data.teclas[k_jump][1]		= _gp2x_jkey_x;			//salto
        config_data.teclas[k_fire][1]		= _gp2x_jkey_a;			//disparo
        config_data.teclas[k_previous][1]	= _gp2x_jkey_l;			//arma anterior
        config_data.teclas[k_next][1]		= _gp2x_jkey_r;			//arma siguiente
        config_data.teclas[k_enter][1]		= _gp2x_jkey_start;		//pausa
        config_data.teclas[k_esc][1]		= _gp2x_jkey_select;	//salir
        config_data.teclas[k_vol_up][1]		= _gp2x_jkey_volup;		//subir volumen
        config_data.teclas[k_vol_down][1]	= _gp2x_jkey_voldown;	//bajar volumen
    end
	case 2:		//Dremcast
		config_data.teclas[k_up][0]			= _up;
        config_data.teclas[k_down][0]		= _down;
        config_data.teclas[k_left][0]		= _left;
        config_data.teclas[k_right][0]		= _right;
        config_data.teclas[k_jump][0]		= _s;		//salto
        config_data.teclas[k_fire][0]		= _a;		//disparo
        config_data.teclas[k_previous][0]	= _w;		//arma anterior
        config_data.teclas[k_next][0]		= _d;		//arma_siguiente
        config_data.teclas[k_enter][0]		= _enter;	//pausa
        config_data.teclas[k_esc][0]		= _esc;		//salir
        config_data.teclas[k_vol_up][0]		= _c_plus;	//subir volumen
        config_data.teclas[k_vol_down][0]	= _c_minus;	//bajar volumen
        
        config_data.teclas[k_up][1]			= JOY_HAT_UP;
        config_data.teclas[k_down][1]		= JOY_HAT_DOWN;
        config_data.teclas[k_left][1]		= JOY_HAT_LEFT;
        config_data.teclas[k_right][1]		= JOY_HAT_RIGHT;
        config_data.teclas[k_jump][1]		= _jkey_x;			//salto
        config_data.teclas[k_fire][1]		= _jkey_a;			//disparo
        config_data.teclas[k_previous][1]	= _jkey_l;			//arma anterior
        config_data.teclas[k_next][1]		= _jkey_r;			//arma siguiente
        config_data.teclas[k_enter][1]		= _jkey_start;		//pausa
        config_data.teclas[k_esc][1]		= _jkey_select;		//salir
        config_data.teclas[k_vol_up][1]		= _jkey_volup;		//subir volumen
        config_data.teclas[k_vol_down][1]	= _jkey_voldown;	//bajar volumen
        
        config_data.usar_joy_hat = 1;
	end
	case 3:     //OPEN_DINGUX
        config_data.teclas[k_up][0]			= _up;
        config_data.teclas[k_down][0]		= _down;
        config_data.teclas[k_left][0]		= _left;
        config_data.teclas[k_right][0]		= _right;
        config_data.teclas[k_jump][0]		= _control;	//salto
        config_data.teclas[k_fire][0]		= _alt;		//disparo
        config_data.teclas[k_previous][0]	= _tab;		//arma anterior
        config_data.teclas[k_next][0]		= _q;		//arma_siguiente
        config_data.teclas[k_enter][0]		= _enter;	//pausa
        config_data.teclas[k_esc][0]		= _esc;		//salir
        config_data.teclas[k_vol_up][0]		= _c_plus;	//subir volumen
        config_data.teclas[k_vol_down][0]	= _c_minus;	//bajar volumen
        
        config_data.teclas[k_up][1]			= JOY_HAT_UP;
        config_data.teclas[k_down][1]		= JOY_HAT_DOWN;
        config_data.teclas[k_left][1]		= JOY_HAT_LEFT;
        config_data.teclas[k_right][1]		= JOY_HAT_RIGHT;
        config_data.teclas[k_jump][1]		= _jkey_x;			//salto
        config_data.teclas[k_fire][1]		= _jkey_a;			//disparo
        config_data.teclas[k_previous][1]	= _jkey_l;			//arma anterior
        config_data.teclas[k_next][1]		= _jkey_r;			//arma siguiente
        config_data.teclas[k_enter][1]		= _jkey_start;		//pausa
        config_data.teclas[k_esc][1]		= _jkey_select;		//salir
        config_data.teclas[k_vol_up][1]		= _jkey_volup;		//subir volumen
        config_data.teclas[k_vol_down][1]	= _jkey_voldown;	//bajar volumen
        
        config_data.usar_joy_hat = 0;
    end
    end //switch
#endif
end

function save_config ()
begin
    save(get_pref_path("bennugd.org", "echo") + "echo.cfg", config_data);
end

function load_config ()
begin
    load(get_pref_path("bennugd.org", "echo") + "echo.cfg", config_data);
end
