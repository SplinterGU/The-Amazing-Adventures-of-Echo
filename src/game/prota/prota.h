CONST
	//Constantes de estados del prota
	CTE_PROTA_ESTADO_PARADO		= 0;
	CTE_PROTA_ESTADO_ANDANDO	= 1;
	CTE_PROTA_ESTADO_SALTANDO	= 2;
	CTE_PROTA_ESTADO_CAYENDO	= 3;
	//constantes de movimiento del prota
    CTE_PROTA_MAX_VEL		= 20;
    CTE_PROTA_ACELERAC		= 2;
    CTE_PROTA_SALTO			= 30;
    CTE_PROTA_MAX_SALTO		= 10;
    CTE_PROTA_GRAVEDAD		= 2;
    CTE_PROTA_MAX_GRAVEDAD	= 30;
    
    CTE_PROTA_AGUA_MAX_VEL		= 10;
    CTE_PROTA_AGUA_ACELERAC		= 1;
    CTE_PROTA_AGUA_SALTO		= 30;
    CTE_PROTA_AGUA_GRAVEDAD		= 1;
    CTE_PROTA_AGUA_MAX_GRAVEDAD	= 20;
	//constantes de máximo avance del prota dentro de un tile bloqueado
	CTE_PROTA_MAX_AVANZAR_DERECHA   = 11; //16-1-4;
	CTE_PROTA_MAX_AVANZAR_IZQUIERDA = 4; //4
	CTE_PROTA_ALTURA_TECHO = 14; //16-2; //2
	CTE_PROTA_DIFERENCIA_CON_TECHO = 2; //2
END

GLOBAL
	//RECURSOS *************************
	int prota_file;
	
	int prota_control;              //0: no funcionan botones dirección, salto ni disparo
	
	//VARIABLES DE MOVIMIENTO
	//constantes de movimiento
    int var_prota_max_vel;
    int var_prota_acelerac;
    int var_prota_salto;
    int var_prota_gravedad;
    int var_prota_max_gravedad;
    int cont_salto;
	
	//DATOS ****************************
	int p_dur[2][2];    //tiles que rodean al protagonista
	int p_dir;          //indica la dirección hacia la que cambia de tile (cambia según los tiles que rodean al prota)
    int p_dir_ini;      //dirección inicial de cambio de tile
    
	
	struct info_prota
        int id_prota;
        //datos del juego
        int p_energ;       //energía restante del prota
        int p_max_energ;
        int p_invencible;  //indica el tiempo que es invencible (por tocar enemigo o similar)
        //info de posición
        int p_tilex;
        int p_tiley;
        int p_offsx;
        int p_offsy;
        //info de movimiento
        int auto_mov;
        int vel_horiz;
        int vel_vert;
        int p_mover_h;
        int p_mover_v;
        int estado;     // 0: parado
                        // 1: andando
                        // 2: saltando
                        // 3: cayendo
        //int estado_ant;
        int anim;       //como estado, pero referente a la animación que debe hacer (puede tener gráfico distinto
                        //a su estado, por ejemplo, cayendo, pero terminando el salto aun mira arriba)
                        // 0: parado
                        // 1: andando
                        // 2: saltando
                        // 3: cayendo
        int anim_ant;
        //info de daños
        int dano_id;        //proceso que causa daños
        int dano_energia;   //energia que quita el golpe
        int dano_exp;       //exp del arma que quita el golpe
        int dano_vel_horiz; //retroceso del impacto
        int dano_time;      //tiempo que deja de responder por el daño recibido
        int vidas;          //numero de vidas restantes
		
		//info de daño continuo, ocasionado por lava, ácido, gas venenoso, para el que no se puede ser invulnerable
		int dano_cont_id;	//proceso que causa daños
		int dano_cont_ener;	//>0: energía que quita cada frame; <0: (abs) nº frames para quitar una energía
		int dano_cont_time;	//contador que indica cuánto tiempo lleva sufriendo daños de tipo continuo
		
		//info de interacción externa
		int id_plataforma;	//id del proceso plataforma sobre la que está de pie, o -1 si no lo está
		int x2_ant;		//Almacena la posición x2 anterior del prota para elementos interactivos (ver si atraviesa plataf)
		int y2_ant;		//Almacena la posición y2 anterior del prota para elementos interactivos
		int ext_velx;	//Velocidad inducida externamente (resolution = 10)
		int ext_vely;	//Velocidad inducida externamente (resolution = 10)
    end
	
	//ANIMACIONES ********************************************************************************************
    int animation_prota_cont;       //sirve para contar frames antes del próximo cuadro de animación
    int animation_prota_data[2];    //0: inicio animación, 1: final animación, 2: posición actual animación
	
	//el primer valor indica número de imágenes de dicha animación, el resto son graphs
    int animation_prota[]=15,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2, //0:    animación parado
                          4,1,5,1,6,                        //1:    animación andando
                          1,10,                             //2:    animación salto
                          1,11,                             //3:    animación cayendo
                          1,15,                             //4:    animación parado mirando arriba
                          4,15,16,15,17,                    //5:    animación andando mirando arriba
                          1,18;                             //6:    animación salto mirando arriba
    
END