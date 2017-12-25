### Washup

Some of the things I learned. Some wins. Some areas I was able to improve. And notes on my solutions.

The most important thing is to say THANK-YOU to topaz2078 daggerdragon and Aneurysm9.

__Puzzles__
1. Warm-up puzzle, and getting us warmed up for the various hilarious scenarios through the coming puzzles. **[[Day 1: Inverse Captcha](http://adventofcode.com/2017/day/1)] [[code](/day_01.1.cpp)] [[code](/day_01.2.cpp)]**

2. Ok, but need to apply some proper idiom and forward iterators on the input. **[[--- Day 2: Corruption Checksum ---](http://adventofcode.com/2017/day/2)] [[code](/day_02.1.cpp)] [[code](/day_02.2.cpp)]**

3. This puzzle bit me pretty hard, though I did it the 'hard' way initially using math. Then I had to take the simple approach to get Part 2. I rewrote this one, and that code could use some improvement also. **[[--- Day 1: Spiral Memory ---](http://adventofcode.com/2017/day/3)] [[code](/day_03.cpp)]**

4. List processing puzzle. I should have spotted I could have used a `std::set<>` and saved myself some typing. **[[--- Day 4: High-Entropy Passphrases ---](http://adventofcode.com/2017/day/4)] [[code](/day_04.cpp)]**

5. Really-fun self-modifying code. One of my better solutions. [[Day 5: A Maze of Twisty Trampolines, All Alike](http://adventofcode.com/2017/day/5)] [[code](/day_05.cpp)]

6. Memory reallocation on a circular buffer. I kind of like this solution, though it's a bit tricky to read. ([Day 6: Memory Reallocation](http://adventofcode.com/2017/day/6))

7. Topological sorting and balancing. This puzzle took us a step up in difficulty, and it will be worth studyinh others' solutions. My code works but nothing to be proud of. ([Day 7: Recursive Circus](http://adventofcode.com/2017/day/7))

8. Simulate a CPU. Fun puzzle and a nice solution. I especially enjoyed tweaking this one to run lambdas out of a `std::map<>`. ([Day 8: I Heard You Like Registers](http://adventofcode.com/2017/day/8))

9. I did a C-style parser for this one, as I typically would when say parsing the kind of data I am often tasked with munging during my day job. Lexing is probably one of my favorite things and my code for this is probably the most me. I still have my [Cole & Morrison: An Introduction to Programming with S-Algol](https://www.amazon.com/dp/0521250013) hardcover where I picked this up. ([Day 9: Stream Processing](http://adventofcode.com/2017/day/9))
10. Implementing a hashing function including a salt and various cryptoblocks and generation of a final hash value. My code for this works but is not great. Generally I've been quite strong on writing bug-free code, aside from the odd typo, but I could really use some time with the latest C++ manual. ([Day 10: Knot Hash](http://adventofcode.com/2017/day/10))
11. Reduction of a sequence of moves across a grid of hexagons to a running maximum and a final distance. I found this quite tricky initially, but I was able to identify appropriate reduction rules and apply these in constant time, without needing to track anything except the total count of each of the possible 6 moves from one hexagon to another. ([Day 11: Hex Ed](http://adventofcode.com/2017/day/11))
12. A graph puzzle, and not my strongest area. I am planning on taking the puzzles I had the hardest time with, and solving them in a variety of languages. ([Day 12: Digital Plumber](http://adventofcode.com/2017/day/12))
13. A modulus puzzle. Wasn't sure if this was supposed to be brute-forced, but if so, C++ is a great tool. ([Day 13: Packet Scanners](http://adventofcode.com/2017/day/13))
14. A fun puzzle utilizing Day 10 Knot Hash to generate a grid of bits. The challenge is to generate the grid given a seed, and count the bits, and to count the contiguous 4-connected regions. ([Day 14: Disk Defragmentation](http://adventofcode.com/2017/day/14))
15. A pair of pseudo-random number generators are implemented, with the task being to count collisions. ([Day 15: Dueling Generators](http://adventofcode.com/2017/day/15))
16. Part 1 implements a permutation routine, and Part 2 asks you to run through an infeasibly large number of permutations. Of course, a cycle can be found, and in my case, only 40 iterations needed to be run to get the correct answer. ([Day 16: Permutation Promenade](http://adventofcode.com/2017/day/16))
17. A circular buffer and modulus puzzle that required some lateral thinking. ([Day 17: Spinlock](http://adventofcode.com/2017/day/17))
18. Entirely possible that this CPU simulation Duet was my favorite puzzle. Simulate a simple CPU, tracking register values, then gasp in Part 2, as the tables are turned, and you have to simulate two CPUs and the communications FIFOs between them. ([Day 18: Duet](http://adventofcode.com/2017/day/18))
19. A simple path-following puzzle. Even so I still had an off-by-1 error, as did many others. I think my code for this is ok, but could stand to be tightened up a tad. ([Day 19: A Series of Tubes](http://adventofcode.com/2017/day/19))
20. In this puzzle, a bunch of particles are simulated. I misread the instructions and got stuck for a while trying to find my error of applying velocity to the position, before applying acceleration. Oops. I did try and write this in F#, but ended up bashing out a C++ solution for testing that worked. ([Day 20: Particle Swarm](http://adventofcode.com/2017/day/20))
21. A grid reduction / fractal generation puzzle. I found this one a bit tough as there was a lot of effort required throughout to ensure that the grids of matchers and generators (terminology?) were composed and decomposed correctly. At 159 lines of code, this was one of my longest solutions. ([Day 21: Fractal Art](http://adventofcode.com/2017/day/21))
22. A grid puzzle utilizing Langton's Ant. ([Day 22: Sporifica Virus](http://adventofcode.com/2017/day/22))
23. For the second time, a previous puzzle is utilized, this time Duet from Day 18. However, different code is being run. Part 1 is simple, but Part 2 requires us to understand and optimize the assembly language prgram provided. ([Day 23: Coprocessor Conflagration](http://adventofcode.com/2017/day/23))
24. Part 1 of Day 24 - Electromagnetic Moat tasks us with searching a set of components that behave like dominoes to build the strongest possible bridge. Part 2 also asks for the longest bridge, with the strongest being returned if more than one bridge is possible of the same length. Despite having actively prepared for a A*/BFS/DFS problem, I got a bit bogged-down initially and came back to this one later in the day after a good think. ([Day 24: Electromagnetic Moat](http://adventofcode.com/2017/day/24))
25. The last puzzle crossed implementing a Turing Machine off my programming bucket list. Sadly a botched copy/paste and a buried typo put paid to a sniff of a lower leaderboard position. ([Day 25: The Halting Problem](http://adventofcode.com/2017/day/25))

__Fixes and Enhancements__
1. Apply modern C++ idiom throughout,
2. Clean up some poor data structures,
3. Clean up some poor code structuring,
4. 

__Extra Credit__
1. Generate some graphics output in puzzles that are graphically oriented,
2. Put together a debugger, decompiler, console, native code compiler for Duet,
3. 

__Further Reading__
1. 
