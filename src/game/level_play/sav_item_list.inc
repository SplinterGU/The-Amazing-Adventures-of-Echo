function int savegame_item_got_list_len ()
private
    savegame_item_got pointer aux_ptr;
    int cont;
begin
    aux_ptr = savegame_item_got_list;
    cont = 0;
    while (aux_ptr != null)
        cont++;
        aux_ptr = aux_ptr.sig;
    end
    
    return (cont);
end

function savegame_item_got_list_add (savegame_item_got sigla_new)
private
    savegame_item_got pointer aux_ptr;
begin
    if (savegame_item_got_list == null)
        //init list
        savegame_item_got_list = alloc(sizeof(savegame_item_got));
        //go to new node
        aux_ptr = savegame_item_got_list;
    else
        //go to end of list
        aux_ptr = savegame_item_got_list;
        while (aux_ptr.sig != null)
            aux_ptr = aux_ptr.sig;
        end
        //add new node
        aux_ptr.sig = alloc(sizeof(savegame_item_got));
        //go to new node
        aux_ptr = aux_ptr.sig;
    end
    
    //at this point, aux_ptr points to last node, who is empty
    aux_ptr.level = sigla_new.level;
    aux_ptr.sublevel = sigla_new.sublevel;
    aux_ptr.pos_x = sigla_new.pos_x;
    aux_ptr.pos_y = sigla_new.pos_y;
    aux_ptr.item = sigla_new.item;
    aux_ptr.sig = NULL;
    //say("added item "+sigla_new.item);
end

//**************************************************************************************************
//  DELETE FUNCTIONS
//**************************************************************************************************
function savegame_item_got_list_delete_all ()
private
    savegame_item_got pointer aux_ptr;
begin
    while (savegame_item_got_list != null)
        aux_ptr = savegame_item_got_list;
        savegame_item_got_list = savegame_item_got_list.sig;
        free(aux_ptr);
    end
    //say("list cleared");
end

function int savegame_item_got_list_delete (int n)
//First node to delete is 1
private
    savegame_item_got pointer ant_ptr;
    savegame_item_got pointer sig_ptr;
    int dato_a_devolver;    // 0 = correcto
                            //-1 = fuera de rango
                            //-2 = lista vacía
    int cont;
begin
    dato_a_devolver = 0;
    if (savegame_item_got_list == null)
        dato_a_devolver = -2;
    else
        //checking range
        if ( (n > 0) && (n <= savegame_item_got_list_len()) )
            if (n == 1)
                //deleting first node
                sig_ptr = savegame_item_got_list.sig;
                free(savegame_item_got_list);
                savegame_item_got_list = sig_ptr;
            else
                ant_ptr = savegame_item_got_list;
                for (cont = 1; cont < n-1; cont++)
                    ant_ptr = ant_ptr.sig;
                end
                //there is always a sig_ptr node
                sig_ptr = ant_ptr.sig;
                ant_ptr.sig = sig_ptr.sig;
                free(sig_ptr);
            end
        else
            dato_a_devolver = -1;
			//say("Fuera de rango: " + n + "/" + itoa(savegame_item_got_list_len()));
        end
    end
    
    return (dato_a_devolver);
end

//**************************************************************************************************
//  SAVE FILES CHECK
//**************************************************************************************************

function int savefile_check ()      //not finished*****************************
//The savefile must be loaded previously
private
    int sc_correct;
    savegame_item_got pointer aux_ptr;
    int cont;
begin
    sc_correct = 1;
    
    //check number of energy items get
    cont = 0;
    aux_ptr = savegame_item_got_list;
    while (aux_ptr != null)
        if (aux_ptr.item = 225) cont++; end
        aux_ptr = aux_ptr.sig;
    end
    
    if (game_global_sav.max_energ != 10 + (cont * 2))
        sc_correct = 0;
    end
    
    
    
    
    return (sc_correct);
end


function savegame_item_got_list_say ()
private
	savegame_item_got pointer aux_ptr;
	int cont;
begin
	say("Leyendo");
	aux_ptr = savegame_item_got_list;
	cont = 1;
	while (aux_ptr != NULL)
		say("Nodo " + cont + ": nivel " + aux_ptr.level + "-" + aux_ptr.sublevel + "  (" +
			aux_ptr.pos_x + "," + aux_ptr.pos_y + ") = " + aux_ptr.item + ".");
		cont++;
		aux_ptr = aux_ptr.sig;
	end
end