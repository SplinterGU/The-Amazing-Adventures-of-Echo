process sync_counter ()
begin
    sincronizacion = 0;
    frame;
    loop
        sincronizacion++;
        frame;
    end
end