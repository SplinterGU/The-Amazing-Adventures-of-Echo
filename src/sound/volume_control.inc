process volume_control ()
begin
    global_vol = _CTE_MAX_VOLUME/2;
    channel_set_volume(-1, global_vol);
    music_set_volume(global_vol);
	
    loop
        if (teclas[k_vol_up][2] > 0)
            global_vol++;
            if (global_vol > _CTE_MAX_VOLUME) global_vol = _CTE_MAX_VOLUME; end
            channel_set_volume(-1, global_vol);
            music_set_volume(global_vol);
        end
        if (teclas[k_vol_down][2]>0)
            global_vol--;
            if (global_vol < _CTE_MIN_VOLUME) global_vol = _CTE_MIN_VOLUME; end
            channel_set_volume(-1, global_vol);
            music_set_volume(global_vol);
        end
        frame;
    end
end