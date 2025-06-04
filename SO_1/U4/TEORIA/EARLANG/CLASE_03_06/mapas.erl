
%Estructura dinamica persistente -- Like diccionario. Cada vez q lo modificamos, se crea otro nuevo.  

maps:new()->Mapa %mapa empty
mapsfrom_list(Lista) %de lista[clave,valor] a mapa.

maps:put(Clave,Valor,Mapa1)>Mapa2 
maps:find(Clave,Mapa) -> {ok,Valor} | error  %atomo
maps:get(Clave,Mapa) -> Valor %error ejec
maps:find(Clave,Mapa,Def) %si no esta, return value x default

maps:update(Clave,Valor,Mapa) -> Mapa2
maps:update_with(Clave,Valor,Fun,Mapa) -> Mapa2
maps:update_with(Clave,Valor,Fun,Mapa,Def) -> Mapa2 %si no E, la crea y hace fun sobre default

maps:remove(Clave,Mapa)
