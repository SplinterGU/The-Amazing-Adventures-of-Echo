CONST
#if 0
    _GP2X_JKEY_UP        =  0 ;
    _GP2X_JKEY_UPLEFT    =  1 ;
    _GP2X_JKEY_LEFT      =  2 ;
    _GP2X_JKEY_DOWNLEFT  =  3 ;
    _GP2X_JKEY_DOWN      =  4 ;
    _GP2X_JKEY_DOWNRIGHT =  5 ;
    _GP2X_JKEY_RIGHT     =  6 ;
    _GP2X_JKEY_UPRIGHT   =  7 ;
    _GP2X_JKEY_START     =  8 ;
    _GP2X_JKEY_SELECT    =  9 ;
    _GP2X_JKEY_L         = 10 ;
    _GP2X_JKEY_R         = 11 ;
    _GP2X_JKEY_A         = 12 ;
    _GP2X_JKEY_B         = 13 ;
    _GP2X_JKEY_X         = 14 ;
    _GP2X_JKEY_Y         = 15 ;
    _GP2X_JKEY_VOLUP     = 16 ;
    _GP2X_JKEY_VOLDOWN   = 17 ;
    _GP2X_JKEY_CLICK     = 18 ;

    _GP2X_JKEY_LAST      = 19 ;
    
    _JKEY_UP        =  0 ;
    _JKEY_LEFT      =  1 ;
    _JKEY_DOWN      =  2 ;
    _JKEY_RIGHT     =  3 ;
    _JKEY_START     =  4 ;
    _JKEY_SELECT    =  5 ;
    _JKEY_A         =  6 ;
    _JKEY_B         =  7 ;
    _JKEY_X         =  8 ;
    _JKEY_Y         =  9 ;
    _JKEY_L         = 10 ;
    _JKEY_R         = 11 ;
    _JKEY_VOLUP     = 12 ;
    _JKEY_VOLDOWN   = 13 ;
    _JKEY_CLICK     = 14 ;

    _JKEY_LAST      = 15 ;
#endif

    K_UP		= 0;
    K_DOWN		= 1;
    K_LEFT		= 2;
    K_RIGHT		= 3;
    K_JUMP		= 4;
    K_FIRE		= 5;
    K_NEXT		= 6;
    K_PREVIOUS	= 7;
    K_ENTER		= 8;
    K_ESC		= 9;
    K_VOL_UP	= 10;
    K_VOL_DOWN	= 11;
    K_LAST		= 12;
END

GLOBAL
	//variables de control del personaje
    string nombre_tecla;    //guarda el nombre de una tecla al pulsarla en la config
    int teclas[K_LAST-1][2];    //almacena el codigo de la tecla asignada y cuanto lleva pulsada
	int teclas_hat_seleccionado;
END