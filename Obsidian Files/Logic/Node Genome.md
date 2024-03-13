#logic
A node genome represents one or more Hexadecimal values that links the current node with his child/children nodes. 

**It numerically represents all the linked child nodes the current node will write his output to.**

A single genome is composed of 24 bits (6 hexadecimal values).

The genome is subdivided in a way to represent the following informations:

Hexadecimal values
First            Second       Third            Fourth           Fifth              Sixth
| 1  2  3  4  |  5  6  7  8  |  9 10 11 12 | 13 14 15 16 | 17 18 19 20 | 21 22 23 24 |

- 1
	If connection logic is negated (output inverted values)

- 2 to 4
	Link weight (output multiplier)

- 5 to 8
	Genome weight domination (considered while mixing genomes)

- 9 to 16
	Current [[Node ID]] 

- 17 to 24
	Linked [[Node ID]] where this node will write his output value.