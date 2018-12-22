cmake_minimum_required(VERSION 3.12)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project1 main.cpp BinaryExpression.h Command.h
        Div.h Expression.h Minus.h Mul.h Num.h Plus.h SleepCommand.h SYalgorithm.cpp SYalgorithm.h PrintCommand.h ControlParser.cpp ControlParser.h DefineVarCommand.cpp DefineVarCommand.h SymbolTable.cpp SymbolTable.h IfCommand.cpp IfCommand.h WhileCommand.cpp WhileCommand.h AssignCommand.h ClassMain.cpp ClassMain.h)