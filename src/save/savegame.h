CONST
    max_savefiles=6;
END

type savegame_item_got
    int level;
    int sublevel;
    int pos_x;
    int pos_y;
    int item;
// jjp      savegame_item_got pointer sig;
    int pointer sig;
end

type savegame
    //datos visibles en el select file
    byte level;
    byte sublevel;
	byte init_level;
    byte difficulty;
    byte lives;
    byte armas;
    
    //otros datos no visibles en select file
    int32 max_energ;
    int32 energ;
    int32 armas_level[cte_last_weapon][3];
end

GLOBAL
    savegame game_global_sav;
    savegame_item_got pointer savegame_item_got_list;
    int savegame_pos;
    byte savegame_exists_file[max_savefiles-1];
END
