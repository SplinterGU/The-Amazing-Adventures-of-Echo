//**************************************************************************************************
//**************************************************************************************************
//
//  SALVADO GLOBAL
//
//**************************************************************************************************
//**************************************************************************************************
// Se maneja realizando pequeñas llamadas al fichero de guardado, en lugar de mantener en memoria
// una estructura de datos global todo el rato

function init_global_sav ()
begin
	RUTA_GLOBAL_SAVE_FILE = get_pref_path("bennugd.org", "echo") + "echo.sav";
end

function cargar_global_sav (global_savegame pointer cgs_datos_ptr)
private
    int cgs_fichero_id;
	global_savegame cgs_datos;
	
	int cont;
begin
    if (cgs_datos_ptr != NULL)
        if (fexists(RUTA_GLOBAL_SAVE_FILE))
            cgs_fichero_id = fopen(RUTA_GLOBAL_SAVE_FILE,O_READ);
            fread(cgs_fichero_id, cgs_datos);
            fclose(cgs_fichero_id);
			
			(*cgs_datos_ptr).level_select_desbloqueado = cgs_datos.level_select_desbloqueado;
			(*cgs_datos_ptr).niveles_desbloqueados = cgs_datos.niveles_desbloqueados;
			for (cont = 0; cont < CTE_GS_MAX_NIVELES; cont++)
				(*cgs_datos_ptr).subniveles_desbloqueados[cont] = cgs_datos.subniveles_desbloqueados[cont];
			end
			(*cgs_datos_ptr).armas_desbloqueadas = cgs_datos.armas_desbloqueadas;
			(*cgs_datos_ptr).items_energia = cgs_datos.items_energia;
		
        else
            [cgs_datos_ptr].level_select_desbloqueado = 0;
            [cgs_datos_ptr].niveles_desbloqueados = 0;
			for (cont = 0; cont < CTE_GS_MAX_NIVELES; cont++)
				[cgs_datos_ptr].subniveles_desbloqueados[cont] = 0;
			end
            [cgs_datos_ptr].armas_desbloqueadas = 0;
            [cgs_datos_ptr].items_energia = 0;
        end
    end
end

function salvar_global_sav (global_savegame pointer sgs_datos_ptr)
private
    int sgs_fichero_id;
	global_savegame sgs_datos;
	
	int cont;
begin
    if (sgs_datos_ptr != NULL)
		sgs_datos.level_select_desbloqueado = (*sgs_datos_ptr).level_select_desbloqueado;
		sgs_datos.niveles_desbloqueados = (*sgs_datos_ptr).niveles_desbloqueados;
		for (cont = 0; cont < CTE_GS_MAX_NIVELES; cont++)
			sgs_datos.subniveles_desbloqueados[cont] = (*sgs_datos_ptr).subniveles_desbloqueados[cont];
		end
		sgs_datos.armas_desbloqueadas = (*sgs_datos_ptr).armas_desbloqueadas;
		sgs_datos.items_energia = (*sgs_datos_ptr).items_energia;
		
        sgs_fichero_id = fopen(RUTA_GLOBAL_SAVE_FILE, O_WRITE);
        fwrite(sgs_fichero_id, sgs_datos);
        fclose(sgs_fichero_id);
    end
end

function desbloquear_arma (int da_arma)
private
    global_savegame da_save;
    int da_file_id;
begin
    //Se abre el fichero de salvado (si existe) y se leen los datos
    if (fexists(RUTA_GLOBAL_SAVE_FILE))
        da_file_id = fopen(RUTA_GLOBAL_SAVE_FILE,O_READ);
        fread(da_file_id, da_save);
        fclose(da_file_id);
    else
        da_save.level_select_desbloqueado = 0;
        da_save.armas_desbloqueadas = 0;
        da_save.niveles_desbloqueados = 0;
        da_save.items_energia = 0;
    end
        
    //Se añade el arma
    da_save.armas_desbloqueadas = da_save.armas_desbloqueadas | da_arma;
    //Se guardan de nuevo los datos
    da_file_id = fopen(RUTA_GLOBAL_SAVE_FILE, O_WRITE);
    fwrite(da_file_id, da_save);
    fclose(da_file_id);
end

function desbloquear_nivel (int dn_nivel, int dn_subnivel)
private
    global_savegame dn_save;
    int dn_file_id;
begin
    //Se abre el fichero de salvado (si existe) y se leen los datos
    if (fexists(RUTA_GLOBAL_SAVE_FILE))
        dn_file_id = fopen(RUTA_GLOBAL_SAVE_FILE, O_READ);
        fread(dn_file_id, dn_save);
        fclose(dn_file_id);
    else
        dn_save.level_select_desbloqueado = 0;
        dn_save.armas_desbloqueadas = 0;
        dn_save.niveles_desbloqueados = 0;
        dn_save.items_energia = 0;
    end
        
    //Se añade el nivel
    dn_save.level_select_desbloqueado = 1;
    dn_save.niveles_desbloqueados = dn_save.niveles_desbloqueados | dn_nivel;
    switch (dn_nivel)
    case CTE_GS_DESBLOQUEO_NIVEL_1:
        dn_save.subniveles_desbloqueados[0] = dn_save.subniveles_desbloqueados[0] | dn_subnivel;
    end
    case CTE_GS_DESBLOQUEO_NIVEL_2:
        dn_save.subniveles_desbloqueados[1] = dn_save.subniveles_desbloqueados[1] | dn_subnivel;
    end
    case CTE_GS_DESBLOQUEO_NIVEL_3:
        dn_save.subniveles_desbloqueados[2] = dn_save.subniveles_desbloqueados[2] | dn_subnivel;
    end
    case CTE_GS_DESBLOQUEO_NIVEL_4:
        dn_save.subniveles_desbloqueados[3] = dn_save.subniveles_desbloqueados[3] | dn_subnivel;
    end
    end //switch
    //Se guardan de nuevo los datos
    dn_file_id = fopen(RUTA_GLOBAL_SAVE_FILE, O_WRITE);
    fwrite(dn_file_id, dn_save);
    fclose(dn_file_id);
end

function desbloquear_items_energia (int die_items)
//REVISAR, el metodo no me gusta, no tiene en cuenta si ya se tenia *************************************
private
    global_savegame die_save;
    int die_file_id;
begin
    //Se abre el fichero de salvado (si existe) y se leen los datos
    if (fexists(RUTA_GLOBAL_SAVE_FILE))
        die_file_id = fopen(RUTA_GLOBAL_SAVE_FILE, O_READ);
        fread(die_file_id, die_save);
        fclose(die_file_id);
    else
        die_save.level_select_desbloqueado = 0;
        die_save.armas_desbloqueadas = 0;
        die_save.niveles_desbloqueados = 0;
        die_save.items_energia = 0;
    end
        
    //Se añade los items nuevos de energia
    die_save.items_energia += die_items;
    //Se guardan de nuevo los datos
    die_file_id = fopen(RUTA_GLOBAL_SAVE_FILE, O_WRITE);
    fwrite(die_file_id, die_save);
    fclose(die_file_id);
end
