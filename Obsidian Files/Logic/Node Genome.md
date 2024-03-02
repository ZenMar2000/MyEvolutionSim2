#logic
A single genome is composed of 24 bits (6 hexadecimal values).

The genome is subdivided in a way to represent the following informations:

Hexadecimal values
First            Second       Third            Fourth           Fifth              Sixth
| 1  2  3  4  |  5  6  7  8  |  9 10 11 12 | 13 14 15 16 | 17 18 19 20 | 21 22 23 24 |

- 1
	If connection logic is negated (output inverted values)

- 2 to 4
	Link weight (output multiplier)

- 5 to 12
	This unique [[Node ID]] function

- 13 to 20
	Unique linked [[Node ID]] where this node will write his output value

- 21 to 24
	 Genome weight domination (considered while mixing genomes)