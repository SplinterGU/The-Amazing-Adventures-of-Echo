CONST
	CTE_GLOBAL_MODE_PORTADA 		= 0;
	CTE_GLOBAL_MODE_LEVELSELECT		= 2;
	CTE_GLOBAL_MODE_JUEGO			= 3;
	CTE_GLOBAL_MODE_CREDITOS		= 4;
	CTE_GLOBAL_MODE_PLAYLEVELSELECT	= 5;
	CTE_GLOBAL_MODE_SALIR			= 100;
	CTE_GLOBAL_MODE_DEBUG			= 101;
END

LOCAL
    int energia;
END
    
GLOBAL
    //Variables para ports
	string dreamcast_ruta;
	
    //variables globales del programa
    int global_mode;
    int global_opt;
END