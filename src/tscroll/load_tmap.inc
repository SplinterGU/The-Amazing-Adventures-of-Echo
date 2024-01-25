function identifica_mapa (string im_dir_mapa)
private
    string im_extension;
    int im_file;
    byte im_datob;

    int cont;
    int dato_a_devolver;
begin
    im_extension = substr(im_dir_mapa, -4, -1);
    im_extension = ucase(im_extension);
    //say(im_extension);
    if (im_extension == ".TMF") dato_a_devolver = 1; end
    if ((dato_a_devolver == 0) && (im_extension == ".TPR")) dato_a_devolver = 2; end

    if (dato_a_devolver == 0)
        if (fexists(im_dir_mapa))
            im_extension = "";
            im_file = fopen(im_dir_mapa,o_read);
            for (cont = 0; cont < 16; cont++)
                fread(im_file, im_datob);
                im_extension = im_extension + chr(im_datob);
            end
            if (im_extension == "TileMapFile " + chr(26) + chr(13) + "\\n") dato_a_devolver = 1; end
            if (im_extension == "TilemapPRoy " + chr(26) + chr(13) + "\\n") dato_a_devolver = 2; end
            if (substr(im_extension, 0, 6) == "fpg" + chr(26) + chr(13) + chr(10) + chr(0)) dato_a_devolver = 3; end
            if (substr(im_extension, 0, 6) == "f16" + chr(26) + chr(13) + chr(10) + chr(0)) dato_a_devolver = 3; end
            fclose(im_file);
        end
    end
    //say (im_extension + "   "+dato_a_devolver);
    return (dato_a_devolver);
end


process load_tmf (string tmf_carga, t_mapa pointer tmf_mapa)
private
    int id_tmf;
    
    int cont;
    int cont2;
    byte dato;
    int16 dato2;
    int32 dato3;
    char magic[15];
    
    int filas;
    int columnas;
    int capas;
    int tam_dato;
    int guardado_correcto;

    //byte pointer lb_mapa;
    //int16 pointer lw_mapa;
    //int pointer li_mapa;
begin
    [tmf_mapa].tipo_mapa = 1;
    guardado_correcto = 0;
    if (fexists(tmf_carga))
        id_tmf = fopen(tmf_carga, o_read);
        //LECTURA CAMPO MAGIC
        fread(id_tmf, magic);
        //say("Magic leido ");
        if (magic == "TileMapFile " + chr(26) + chr(13) + "\\n")
            //LECTURA DE LA VERSION
            fread(id_tmf, dato3);
            [tmf_mapa].version = dato3;

            //LECTURA DE FILAS, COLUMNAS Y CAPAS
            fread(id_tmf, dato3);
            columnas = dato3;
            [tmf_mapa].columnas = dato3;

            fread(id_tmf, dato3);
            filas = dato3;
            [tmf_mapa].filas = dato3;

            fread(id_tmf, dato3);
            capas = dato3;
            [tmf_mapa].capas = dato3;

            cont2 = columnas * filas * capas;

            //LECTURA DE TIPO DE DATO
            fread(id_tmf, dato3);
            tam_dato = dato3;
            [tmf_mapa].tipo_dato = dato3;

            if ( tam_dato == 3 )
                say("tam dato error!!!!!!");
                exit(1);
            end

            //LECTURA DE ANIMACIONES (temporalmente disabled)
            fread(id_tmf, dato3);
            //say("Datos de TMF leidos "+tam_dato);

            //ZONA DE DATOS
            //say(cont2 * sizeof(int));

            [tmf_mapa].b_mapa = alloc(cont2 * sizeof(int));

            //say("Tipo de datos leido: " + tam_dato);

            //write(0, 400, 100, 0, tam_dato);
            cont = 1;
            for (cont = 1; cont <= cont2; cont++)
                switch (tam_dato)
                    case 0:
                        fread(id_tmf, dato);
                        [tmf_mapa].b_mapa[cont - 1] = dato;
                    end
                    case 1:
                        fread(id_tmf, dato2);
                        [tmf_mapa].b_mapa[cont - 1] = dato2;
                    end
                    case 2:
                        fread(id_tmf, dato3);
                        [tmf_mapa].b_mapa[cont - 1] = dato3;
                    end
                end
            end

            guardado_correcto = 1;
        end
        //say("Mapa leido ");
        fclose(id_tmf);
    end
    return (guardado_correcto);
end


process load_tpr (string tpr_carga, t_mapa pointer tpr_mapa)
private
    int id_tpr;

    int cont;
    int cont2;
    byte dato;
    int16 dato2;
    int32 dato3;
    char magic[15];

    int filas;
    int columnas;
    int capas;
    int tam_dato;

    int guardado_correcto;
begin
    [tpr_mapa].tipo_mapa = 2;
    guardado_correcto = 0;
    if (fexists(tpr_carga))
        id_tpr = fopen(tpr_carga, o_read);
        //LECTURA CAMPO MAGIC
        fread(id_tpr, magic);
        if (magic == "TilemapPRoy " + chr(26) + chr(13) + "\\n")
            //LECTURA DE LA VERSION
            fread(id_tpr, dato3);
            [tpr_mapa].version = dato3;

            //LECTURA DE FILAS, COLUMNAS Y CAPAS
            fread(id_tpr, dato3);
            columnas = dato3;
            [tpr_mapa].columnas = dato3;

            fread(id_tpr, dato3);
            filas = dato3;
            [tpr_mapa].filas = dato3;

            fread(id_tpr, dato3);
            capas = dato3;
            [tpr_mapa].capas = dato3;

            cont2 = columnas * filas * capas;

            //LECTURA DE TIPO DE DATO
            fread(id_tpr, dato3);
            tam_dato = dato3;
            [tpr_mapa].tipo_dato = dato3;

            //TAMAÑO DEL TILE EN PIXELS
            fread(id_tpr, dato3);
            [tpr_mapa].ancho_tile = dato3;

            fread(id_tpr, dato3);
            [tpr_mapa].alto_tile = dato3;

            //DIR DEL FPG
            [tpr_mapa].fpg = fgets(id_tpr);

            //LECTURA DE ANIMACIONES (temporalmente disabled)
            fread(id_tpr, dato3);

            //ZONA DE DATOS

            [tpr_mapa].b_mapa = alloc(cont2 * sizeof(int));
            //write(0, 400, 100, 0, tam_dato);
            cont = 1;
            for (cont = 1; cont <= cont2; cont++)
                switch (tam_dato)
                    case 0:
                    fread(id_tpr, dato);
                        [tpr_mapa].b_mapa[cont - 1] = dato;
                    end
                    case 1:
                        fread(id_tpr, dato2);
                        [tpr_mapa].b_mapa[cont - 1] = dato2;
                    end
                    case 2:
                        fread(id_tpr, dato3);
                        [tpr_mapa].b_mapa[cont - 1] = dato3;
                    end
                end
            end
            guardado_correcto = 1;
        end
        fclose(id_tpr);
    end
    return (guardado_correcto);
end


process load_tmg (string tmg_carga, t_mapa pointer tmg_mapa)
private
    int cont1;
    int guardado_correcto;
begin
    //cargamos el fpg que sirve de mapa
    [tmg_mapa].fpg_mapa = fpg_load(tmg_carga);
    //comprobamos que al menos hay un mapa
    guardado_correcto = 0;
    for (cont1 = 1; cont1 < 1000; cont1++)
        if (map_exists([tmg_mapa].fpg_mapa, cont1) != 0)
            guardado_correcto = 1;
            break;
        end
    end

    //si hay un mapa, empezamos la carga de datos
    if (guardado_correcto)
        [tmg_mapa].tipo_mapa = 3;
        //LECTURA DE LA VERSION
        [tmg_mapa].version = 1;
        //LECTURA DE FILAS, COLUMNAS
        [tmg_mapa].columnas = graphic_info([tmg_mapa].fpg_mapa, cont1, G_WIDE);
        [tmg_mapa].filas = graphic_info([tmg_mapa].fpg_mapa, cont1, G_HEIGHT);

        //LECTURA DE TIPO DE DATO
        /*switch (graphic_info([tmg_mapa].fpg_mapa, cont1, g_depth))
        case 8:
        [tmg_mapa].tipo_dato = 0;
        end
        case 16:
        [tmg_mapa].tipo_dato = 1;
        end
        default: guardado_correcto = 0; end
        end //switch*/
        [tmg_mapa].tipo_dato = 3;

        //LECTURA DE CAPAS
        //para ver el número de capas buscamos el último gráfico válido
        cont1 = 999;
        while (map_exists([tmg_mapa].fpg_mapa, cont1) == 0)
            cont1--;
        end
        [tmg_mapa].capas = cont1;
    end
    return guardado_correcto;
end


//*******************************************************************************
//  PROCESOS DE DESCARGA
//*******************************************************************************

process unload_tmf (t_mapa pointer tmf_mapa)
begin
    [tmf_mapa].version = 0;
    [tmf_mapa].filas = 0;
    [tmf_mapa].columnas = 0;
    [tmf_mapa].capas = 0;
    [tmf_mapa].ancho_tile = 0;
    [tmf_mapa].alto_tile = 0;
    [tmf_mapa].fpg = "";
    free([tmf_mapa].b_mapa);
    [tmf_mapa].tipo_dato = 0;
end

process unload_tpr (t_mapa pointer tpr_mapa)
begin
    [tpr_mapa].version = 0;
    [tpr_mapa].filas = 0;
    [tpr_mapa].columnas = 0;
    [tpr_mapa].capas = 0;
    [tpr_mapa].ancho_tile = 0;
    [tpr_mapa].alto_tile = 0;
    [tpr_mapa].fpg = "";
    free([tpr_mapa].b_mapa);
    [tpr_mapa].tipo_dato = 0;
end

process unload_tmg (t_mapa pointer tmg_mapa)
begin
    [tmg_mapa].version = 0;
    [tmg_mapa].filas = 0;
    [tmg_mapa].columnas = 0;
    [tmg_mapa].capas = 0;
    [tmg_mapa].ancho_tile = 0;
    [tmg_mapa].alto_tile = 0;
    [tmg_mapa].fpg = "";
    fpg_unload([tmg_mapa].fpg_mapa);
    [tmg_mapa].tipo_dato = 0;
end

//*******************************************************************************
//  PROCESOS DE DEBUG
//*******************************************************************************
process escribir_datos (t_mapa pointer dat_mapa)
private
    int cont;
    t_mapa pointer ptr;
begin
    //cont = 1;
    ptr = [dat_mapa];
    write(0, 10, 10, 0, "VERSIÓN: " + [ptr].version);
    write(0, 10, 30, 0, "FILAS: " + [ptr].filas);
    write(0, 10, 40, 0, "COLUMNAS: " + [ptr].columnas);
    write(0, 10, 50, 0, "CAPAS: " + [ptr].capas);
    cont++;
    while ([ptr].null2 == 1)
        ptr = [ptr].sig;
        write(0, 10, 10 + (60 * cont), 0, "VERSIÓN: " + [ptr].version);
        write(0, 10, 30 + (60 * cont), 0, "FILAS: " + [ptr].filas);
        write(0, 10, 40 + (60 * cont), 0, "COLUMNAS: " + [ptr].columnas);
        write(0, 10, 50 + (60 * cont), 0, "CAPAS: " + [ptr].capas);
        cont++;
    end
end

/*BEGIN
set_fps(0,0);
lista_mapas=alloc(1*sizeof(t_mapa));
lista_mapas_vacia=0;
load_tmf("CSal3.tmf",&lista_mapas);
[lista_mapas].sig=alloc(1*sizeof(t_mapa));
[lista_mapas].null2=1;
load_tmf("IFenix2.tmf",&[lista_mapas].sig);
[[lista_mapas].sig].sig=alloc(1*sizeof(t_mapa));
[[lista_mapas].sig].null2=1;
load_tpr("nivel02.tpr",&[[lista_mapas].sig].sig);
loop
if (key(_c)) break; end
frame;
end
escribir_datos(&lista_mapas);
loop
if (key(_esc)) break; end
frame;
end
END*/
