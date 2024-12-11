# What is this project?

This is a simulation on how cells interact and evolve in a virtual environment. Each cell has an unique genome, and this genome composes what it's essentially the cell brain.

Each cell will independently take actions based on what their little brain will tell them to do, no input from the user is done. 
Also, food is required by the cells to live, so eating is essential for survival.

After a set amount of time, all cells still alive begin a new generation, while those who failed will stop there. 
During the generation, cells can create child between them and creating new cells with mixed genome from their parent.

The result is (hopefully) after many generation, a set of cells capable of feeding themselves and survive autonomously.

# Why?
After watching a video about simple creatures evolving in a virtual simulation, I wanted to try and implement it on my own (credits at the end). 

This project merges machine learning with genetics, and it's fascinating how closely related these two worlds are.

# What to expect?
You can easily clone the repository and see how those simulations works for yourself. 

Code wise, i did it all by myself. Here you will hardly find some neat c++ code as this is my first "big" thing in this language.

That said, if someone find it useful or has some suggestions, let me know!

# Can I edit / copy / contribute / etc...?
Sure you can, just put me in the credits if you use it. 

For contributors, I'd like to keep it as is.

# Launch and build the project in Fedora Linux
1) Using Visual Studio code, install c++ extensions and cmake tools
2) Pull repository
3) Check if gcc is installed with ```gcc -v```
4) Install cmake with ```sudo dnf install cmake``` 
5) Install g++ with ```sudo dnf install g++``` 
6) Install SDL2 with ```sudo yum install SDL2-devel```
7) Configure the cmake file with ___Ctrl Shift P___ and ```Cmake: Configure```

Ready to be launched!

## Credits

Video inspiration, some stuff implemented is loosely inspired by it: https://www.youtube.com/watch?v=N3tRFayqVtk

And his relative repository: https://github.com/davidrmiller/biosim4

