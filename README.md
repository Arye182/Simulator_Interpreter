# Simulator_Interpreter - Mile Stone #1

# Project Name : "THE FLIGHT-PRETER Ver. 1.00"
Choose a self-explaining name for your project.

# Personal Remark  
this is our first milestone project in course 89210 that  
we did as couple and as a team. at first it was very challenging but once  
we understood the dividing work flow it all went much easier.
at first time we actually had to put our trust in each other and rely on the
partner that everything he suppose to supply me is good (like a black box).

# Description  
in this project we actually "take" a plane "Cessna-172-P" and depart it in the well
known Flight-Gear (https://www.flightgear.org/) simulator of flight.
our mission was to fly the plan successfully, but on top of that we actually
support every command that you could possibly want to set in the flight gear
simulator.
in other words, we built an Interpreter programm that take a language of
commands that our instructor wrote, and interpret her first in a lexer and
after analysing the text we parse it in the interpreter in order to execute
every command or instruction.

Programming - Topics we Used:
-----------------------------
* Using Pattern Designs and Architecture
* Communication and Client-Server Architecture
* Using Data Structures and DataBase
* injecting files and data to server and receive as well
* Multythread Programming


The Classes (include 2 interfaces):
-----------------------------------
**Arye's Classes:**   
- main
- RunProgramm
- OpenDataServerCommand
- SleepCommand
- PrintCommand
- Lexer
- Interpreter
- WhileCommand
- IfCommand
- ConditionParserCommand
- <<Command.h>> Interface

**Miri's Classes:**
- Math
- <<Expression.h>> Interface
- Condition
- ConnectCommand
- AssignVarCommand
- DefineVarCommand
- DataBase (singleton)

The Flow of the Programm:
-------------------------
1. dffff
2. ffff
3. ffff
4. fffff
5. fffff
6. ffff
7. fffff
8. fgfffff
9. gfgfgf


# Badges
On some READMEs, you may see small images that convey metadata, such as whether or not all the tests are passing for the project. You can use Shields to add some to your README. Many services also have instructions for adding a badge.

# Visuals  
Depending on what you are making, it can be a good idea to include screenshots or even a video (you'll frequently see GIFs rather than actual videos). Tools like ttygif can help, but check out Asciinema for a more sophisticated method.

# Installation  
1. download the Flight-Gear simulator version 2018 (if you want 2019 you will
 have to update the heading path).
2. save the generic_small.xml  file in data/protocol dir of flight gear.
3. add these 2 lines in te settings:
    ---fffff
    ---ffff
4. open terminal and in the directory of the programm:
5. type: g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
6. run ./a.out fly.txt
7. press Fly!
8. watch the Cesna takes off!

# Support  
arye.amsalem@gmail.com
miriyungreis@gmail.com

# Roadmap  
none.

# Contributing  
none.

# Authors and acknowledgment  
in this opportunity i would like to praise and thank Miri Jungreis - my partner
, that was very strong and dominant in managing the team of this project.

# License  
All rights reserved for Arye & Miri - no open source in this point.

# Project status  
Mile Stone #1 - delivered.


