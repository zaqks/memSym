<img src="https://github.com/zaqks/memSym/blob/main/docs/Screenshot%20from%202024-01-12%2000-18-03.png"></img>

# what is this

memSym stands for "memory simulator"
it is a process memory allocation simulation software built in C
which allows you to visualize in realtime mainly through the UI
how a virtual processor manages a hsi central memory for
processes execution after being loaded to the RAM without dismissing
the fact that each operation is followed by a particular sound to
provide a maximum user experience and understanding of each system state

# how to run it

there are 3 ways to run the program it depends on your operating system

it is recommanded to be on a Linux OS as it provides the best developer
experience ever and a full control over your system, and most importantly
the software was built and tested on a custom Linux Kernel
(Linux Arch with xfce/Gnome display server, x11 windowing system
coupled with an i5-6300U CPU @ 2.40GHz quad core)
so it's garenteed that it will be compatible with the system's drivers as long as
you are using any Linux Distro

on windows there is a small probability of facing some compatibility
issues which will be discussed later renforced by the fact it wasnt
tested on any windows version

- Linux
  the easy and direct way to run memSym is to directly use the main binary
  since it is the compilation result of our source files
  so you don't need to worry about having a c compiler
  just go to the build folder and run the main binay by double clicking it
  or by using your terminal(recommanded since there is a functionality of
  display some data on it)

another way is to recompile the codebase which is useless if you don't want
to change something in the code
to do so, you need first to have the gcc compiler installed in your system
which is availble by default in some linux distros such Ubuntu
(you can use any compiler you want but gcc is adviced as it was used in this project)
now if you have a basic knowledge about compilers you could easily compile everything
by including the required header files that would be mentioned later then you run the binary

else a python script was written to do the compilation process for you using gcc and running
the project just to avoid typing the long commands and including the header files
so you just need to rebuild the project by running the run.py file after installing the python
interpreter in your system of course then run it using build/main as previously described or it
would be ran automatically after the compilation process if you're choosen

- Windows
  for windows there are no compiled executable files to directly run the program
  so you need to compile everything using a c compiler for windows such mingw
  depending on you system architecture in a Windows or Linux OS with the installed
  headers, then you copy the executable file to the build folder and run it from there
  and here you go

# how to use it

after running the program you can see an User Interface that contains
3 sections in a row

by looking at the third section at the righ you can see to other sections
display in a column
the first on at the top is the vitual processor status
the second one at the bottom contains the control keys to interact with the
program
they were made to be easily memorized on a QWERTY keyboard but can be used on other
keyboards alsoyou will

in the middle you can see an representation of the RAM in the form of empty partitions
obviously since the virtual processor hasnt ran yet

lastly, the one at the left which is the first one represents the iStack aka instruction stack
that contains iQueues aka instruction queues (called also ready queues)
basically the iQueues contains pending processes that will be loaded to the RAM for their execution
the iStack contains the iQueues. the reason of the iStack existance is to implent what is called an execution
priority; when enabled, forces the higher priority processes to be loaded first until the last one from
the most left non empty iQueue then the lower ones to be loaded after

seeing a realtime visualization is better than reading a description so you are invited to run the program
or at least link what you are reading with the screenshots

so enough explanations, let's start testing it out
by looking at the controls section you can see the following:

<q> toggle processor
<w> toggle queue
<e> first fit
<r> best fit
<t> worst fit
<y> toggle priority
<u> toggle print mode
<i> toggle sound

<Esc> exit

each key of the above ones triggers a particular action
now each action's status (if it is enabled or not) can be
observed in the status section as the following:

<off> processor
<off> queue
<on> first fit
<off> best fit
<off> worst fit
<off> priority
<off> print iStack
<on> sound

to start the execution you need to fill the iQueues else nothing will be
executed
there are 2 ways to fill it

the first one is from a file located in build/data/userdata
which contains a parts when the iStack is defined
and it will be discussed later as it is written in a custom scripting language
so the user can define how the iStack looks when staring the program by writing
his own state
if the file contains an error or doesn't even exist then the program will randomly
create an iQueue following certain rules. in this case we are talking about the second
method to fill the iQueues
so the second way consists of letting the the program fill it by him self
to do so, all you need is to toggle it by press the <w> and you will see the queues
being filled with process progressivly according to the virtual processing clock
and you can stop it by pressing the same key again as it is a toggle key

now we need to start the execution we need to load the processes in the RAM
which will immediatly execute them
so we just press the <q> key to toggle the execution process
as you can see the processes are loaded one by one according to the selected
allocation stategy that will be explained later and the priority status which
was simply explained before.
the allocation statergy can be selected using the keys: <e>, <r>, <t>
while the toggle key of the priority is <y>

the process is loaded into a convinient partiton and as it only occupies a certain space
that's why the remaining space is converted into a new partiton
so you've guessed it, a partiton is just a RAM division that allows the execution of multiple
processes at the same time instead of one and this is called multi-threading

you can that after each pressed key the status section is being update in order to
let the user have a complet understaing of what is going on

you can also hear sounds while processing occurs and if you are not a big fan of it you can just
disable it by pressing the <i> key
and as mentioned waay before, this is for a better interaction an to give a life to the program
and a kind of enjoyement and fun to the user

each sound represents on of the following actions:
clock tick, process execution started, process excution terminated, partition merged

now you are wondering what is a clock tick; basically the processor operates with a certain speed
which is called clock speed represented in GHz
so to be clear if the clock speed is equal to 1Hz then you will have 1 operation per second
the operation is called a cycle
if you have a speed of 1GHz this means you have 1 billion clock cycles per second

in our program we have defined some specs that are like the identity of a mini computer
or a virtual machine
those specs are:

*a clock speed of 4Hz (1 clock tick each 250ms)
*a 3 levels iStack (3 levels of priority)
*3 iQueues of 10 processes slots each
*30 pending processes slots according to the iStack
and iQueues specs
\*a 1024Bytes RAM (1KB) which is the total size of
our RAM partitions

by default our virtual processor clock is tunned to 4Hz which meaning 4 cycles/s
in other words you hear a tick each 250ms
the reason it was set to a low value it to allow the user the see what is actually happening
else it can be set to the physical processor speed which is 2.4GHz (over clocking)
and we will see soon how to do it

a process is a sequence of instructions that requires a certain number of clock cycles
in order for it to be terminated
from here we can estimate the lifespan of a process using the following formula:
lifeSpan(in seconds) = processCycles/processorClock

if the neccecary processing cycles value is less than 0, it means that the lifespan of this process is
unlimited meaning it will run as long as the computer is running, this case applies mainly for system processes
that are important such file indexing, drivers, the shell it self, or any process linked to a program are long as
the program is responding
a negative value can only be retrived from the defined user iQueue and can't be set automatically
this

now according to that for each processor being executed, you can see its remaining clock cycles
are being decreased and updated

once a process is terminated, it is deleted from its current partiton. that means the partiton in question in no
longer occupied resulting in being free
so what if we have multiple small free partitions that are not sufficient to hold new incomming proccesses?
no worries, the program automatically merges the free partitions after each termination so that you can have
new bigger partitions and this is the definition of partition merging introduced above

if you want more details about what is going on
we got you
if you run the program from a terminal you will be
able to see 3 new types of information
infos about the userdata,
if it was loaded, corrupted
this is shown at the begining of the program,
iStack info
shows the current iQueues and their content,
ramStatus
shows the ram status, including the partitions
and their content

we can toggle between showing iStack or ram informations or nothing
we using the <u> key

and basically that's how you can easily interact with
the memSym software

# how it works

now after giving a basic overview about the software
and how to use it, let's dive a little deep into the
concepts used to make all the magic happen before seeing
the actual code that runs under that hood

let's start about the core of our program, the mainloop

in orders to explain this concept we need to travel from
the world of software developement and engineering to
one of its famous branches which is game developement
by understanding some of it's main concepts, we can easily
understand how memSym works since it was made using a custom
game engine

-what is a game engine
a game engine is a set of tools and settings that forms a self-sufficiant
framework allowing us to create a game development environment and build on top
of it using a dedicated programming language for a better perfomance or any set
UI tools. with a game engine you can easily handle the display of pixels,2D/3D transfomations,
user input, and sounds etc..

there are many prime game engines examples such Unity & Unreal which could be used by anyone
but have some limitions escpecially when it comes to licencing,
or any open-source one such godot, pygame etc..
with enough knowledge, they could be transformed into beasts by doing extrem memory management
and some compilation tricks and of course applying some math while rendering to limit the
ressources requirement, it could even lead to an era when GPUs are useless since everything could
be achieved using software rendering; all this to come to the fact that with enough work
a custom game engine could demolish the famous and bigger ones and more interstingly
more user friendly for it's creator since he's its creator.
this is a reason why big companies holding the game industry such Rockstar are using their private
game engines

to recap everything, a game engine could be considered as a library that could be adapted to the
developer needs and built on top of any existing library especially the ones that handles the display

now the way a game engine works varies between one to another but we will give a general concept
on each game/most of software/mobile apps we have a loop called the mainloop or gameloop for games-dev
this loop will do all the treatements in the program, the only tasks that could be excluded from it are the
initialization functions generally required to run only one time at the begining.
for the included treatements we have the window refreshing, ui updating, events capture, and user defined
functions.
a fact about the gameloop is that it doesn't constantly run overloading the cpu as it is delayed by a certain
amount of time after each itteration just to let the user see the new composed frame.
the less the it is the better the framerate
for a delay of 33ms you have a frame rate of 33fps(frame per second) which is good for an average game
another fun fact about the human eye is that is can only percieve a framerate located between 30 to 70 fps
so no need to use a refresh rate above those.
refreshing the display is not the only operation done in a gameloop,
it also checks for user events such mouse events(clicks, tracking the cursor position), keyboard events(such
keypresses aka keydown, keyrelease aka keyup), gamepads events ...
it also checks if a window is moved, resized, closed

in general everything happens inside the mainloop as everything need to be updated according to the refresh
rate

after giving a short overview about what a gameengine could be, we have all the required terminology to start introducing
our software architecture

as perviously mentioned, memSym was built on top of a custom game engine
this game engine follows exactly the principles introduced above, a mainloop that contains everything and updates everything
according to the default defined refresh rate of 33 fps
if you were attentive when you ran the software previously, there is a possiblity now of you assuming that the refresh rate
was 4fps because if you remember, when there is a change in a screen you head a tick sound which occurs each 250ms;
well the 2 values are completly unrelated
let's suppose a c function as the following:

void wait(const int time); // in ms

it's name shows it, it its a function which blocks the execution of a program for a certain duration in other words, waits for
the passed duration
and let's consider the following instructions:

#defile REFRSHRATE 33
#define CLK 250 //divide 1000 by CLK to have the value in Hz

int counter = CLK / REFRESHRATE;

while(1){
if(counter>=CLK / REFRESHRATE){
  counter = 0;
}
counter ++;

wait(REFRESHRATE);
}

as you can see this is an exacts replica of our mainloop interpretation
you have the loop running according to the frame rate
a counter was associated the it inorder to count if the CLK time has passed
in another point of view, the loop need to run n time in order to do a virtual clock 
cycle where n=CLK/REFRESHRATE (don't forget that the 2 values are in ms so the result would be dimensionless value)

that way we could easily run the same program at basically 2 different clock speeds even thought they are not related
the same concept could be used to run more than 1 clock according to the refresh rate
even the section responsible about the refreshing could be nested in a lower delay loop in certain cases
this principle is called timing 

so our game engine is equipped with a timer where all the functions responsible of updating the virtual memory state are called

now let's focus about our engines architecture

-custom game engine
-what is sdl
-widget
-sound support

# how was it made (a dive into the code)

- project directory structure
- used tools & requirements

- sdl
  -widgets(draw update ...)
  -gameloop
  -mainloop
  -eventloop

- sound system

- userData concept + custom scripting langage

- funcs
  -dataStructs

- compilation

- merging

-git+Github

# what to add

animations
hex support