cmake_minimum_required(VERSION 3.12)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project1 main.cpp BinaryExpression.h Command.h oldDefineVarCommand.cpp
         Div.h Expression.h MainClass.h MainClass.cpp Minus.h Mul.h Num.h Plus.h SleepCommand.h SYalgorithm.cpp SYalgorithm.h PrintCommand.h ControlParser.cpp ControlParser.h DefineVarCommand.cpp DefineVarCommand.h)