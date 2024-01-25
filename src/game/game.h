CONST
	CTE_GAME_MAX_VIDAS	= 5;
	
    //DEFINICIÓN DE LAS REGIONES
    CTE_REGION_VOLUMEN		= 1;
    CTE_REGION_GET_WEAPON	= 2;
    CTE_REGION_TITULO_NIVEL = 2;
    CTE_REGION_MENU_PORTADA = 2;
    CTE_REGION_INTERFAZ_ARMAS = 3;
	CTE_REGION_FONDOS		= 9;
	CTE_REGION_BOSS_INTRO	= 2;
	
	//DEFINICIÓN DE LOS SCROLLS
	CTE_FIRST_BACKGROUND_SCROLL = 1;
	CTE_FIRST_FOREGROUND_SCROLL = 6;
    
    //constantes de lo que se activa con los interruptores
    CTE_INTERRUPTORES=15;
    CTE_DOOR=0;
    CTE_BRIDGE=1;
END

GLOBAL
    //variables del scroll del mapa
    t_mapa durezas;
    t_mapa nivel;
    tscroll id_tscroll;
    
    
    //variables del prota
	
    //****************************************
    //ARMAS
    
    
               
    //*****************************************
    //JUEGO
    int dificultad;
    int next_level;         //indica un cambio de nivel de juego
    int next_sublevel;      //indica cambio a otra pantalla del mismo nivel (exteriores a castillo)
    int init_level;         //indica en qué comienzo del (sub)nivel debemos empezar
    int end_level;          //avisa de que se ha terminado el nivel (incluye muerte)
    int sincronizacion;     //contador que sirve para sincronizar elementos del nivel
    
    int enem_grafs[1][cte_enem_last];
    int item_grafs;
	int checkpoint_grafs;
    int explosion_grafs;
    
    int interruptores[cte_interruptores];   //guardan el estado de cada botón/interruptor activable del nivel
    int obj_interruptor[1];                 //indican el gráfico de cada cosa que es activada por un boton
                                            //0: puerta
                                            //1: puente
    
    int pausa_estado;
    
    //*******************************************
    //SONIDO
    int sfx_id[1][CTE_SFX_LAST];
END

//**************************************************
//   USO DE REGIONES
//   0: NORMAL
//   1: VOLUMEN
//   2: GET WEAPON, TITULO NIVEL, MENU PORTADA
//   3: ICONOS ARMAS DE INTERFAZ
//**************************************************
