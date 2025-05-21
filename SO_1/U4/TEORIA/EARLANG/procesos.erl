-module(procesos).  
-export ([pong/0,ping/0,play/0]).

pong() -> 
    receive
        {0, PidPing} -> 
            io:fwrite("END pong ~n") ,
            PidPing! { fin, self()},
            pongok;
        {N, PidPing} -> 
            io:fwrite("Pong! recv: ~p ~n", [N]),
            PidPing ! {(N-1),self()},
            pong()
    end.

ping() -> 
    receive
        {fin, _} ->
            io:fwrite("END ping ~n") ,
            pingok;
        {N,PidPong} -> 
            io:fwrite("Ping!"),
            PidPong ! {N,self()},
            ping()
    end.

play()->
    PidPong = spawn(procesos,pong,[]),
    PidPing= spawn(procesos,ping,[]),
    PidPong ! {10,PidPing},
    playok.



