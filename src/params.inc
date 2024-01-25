function leer_parametros ()
private
	string s_argumento;
	int n_argumentos;
	int cont;
	string temp_string;
begin
	//say("ARGUMENTOS");
	n_argumentos = argc;
	for (cont = 0; cont < n_argumentos; cont++)
		//say("Argumento: " + argv[cont]);
		//say("Primer caracter: " + argv[cont][0]);
		if (argv[cont][0] == '-')
			s_argumento = substr(argv[cont], 1);
			s_argumento = ucase(s_argumento);
			//say("Argumento sin valores: " + s_argumento);
			switch (1)
			case find(s_argumento, "OS_ID") > -1:
				temp_string = substr(s_argumento, 6);
				//say("Valor del argumento: " + temp_string);
				OS_ID = atoi(temp_string);
			end
			default:
				say("Argumento sin valores: " + s_argumento);
			end
			end //switch
		end
	end
end