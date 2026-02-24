cmake_minimum_required(VERSION 3.31)
project(projekat)

set(CMAKE_CXX_STANDARD 20)

add_executable(projekat main.cpp
        Commands/Command.h
        Commands/Command.cpp
        Reader.h
        Reader.cpp
        Parser.h
        Parser.cpp
        Program.h
        Program.cpp
        Commands/Echo.h
        Commands/Echo.cpp
        Commands/Wc.h
        Commands/Wc.cpp
        Commands/Time.h
        Commands/Time.cpp
        Commands/Date.h
        Commands/Date.cpp
        Commands/Touch.h
        Commands/Touch.cpp
        Commands/Rm.h
        Commands/Truncate.h
        Commands/Rm.cpp
        Commands/Truncate.cpp
        Commands/Prompt.h
        Commands/Prompt.cpp
        Commands/Head.h
        Commands/Head.cpp
        Commands/Tr.h
        Commands/Tr.cpp
        Commands/streamInterfaces.h)
