CONST
    CTE_GS_DESBLOQUEO_BLUE_STAR		= 1;
    CTE_GS_DESBLOQUEO_LEAF_BLADE	= 2;
    CTE_GS_DESBLOQUEO_GREEN_CAT		= 4;
    //CTE_GS_DESBLOQUEO_SUN_BLASTER		= 8;
    //CTE_GS_DESBLOQUEO_BLUE_STAR	=16;
    CTE_GS_DESBLOQUEO_NIVEL_1	= 1;
    CTE_GS_DESBLOQUEO_NIVEL_2	= 2;
    CTE_GS_DESBLOQUEO_NIVEL_3	= 4;
    CTE_GS_DESBLOQUEO_NIVEL_4	= 8;
    CTE_GS_DESBLOQUEO_SUBNIVEL_1	= 1;
    CTE_GS_DESBLOQUEO_SUBNIVEL_2	= 2;
    CTE_GS_DESBLOQUEO_SUBNIVEL_3	= 4;
    CTE_GS_DESBLOQUEO_SUBNIVEL_4	= 8;
    CTE_GS_DESBLOQUEO_SUBNIVEL_5	=16;
    CTE_GS_DESBLOQUEO_SUBNIVEL_6	=32;
	
	CTE_GS_MAX_NIVELES	= 4;
END
    

type global_savegame
    byte level_select_desbloqueado;
    byte niveles_desbloqueados;
    byte subniveles_desbloqueados[CTE_GS_MAX_NIVELES - 1];
    byte armas_desbloqueadas;
    byte items_energia;
end

GLOBAL
    string RUTA_GLOBAL_SAVE_FILE; //= "save/echo.sav";
END
