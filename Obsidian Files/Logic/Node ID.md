#logic
Each node function in a different way. This is defined by the combination of header and id.

The header is represented by the first 2 most representative bits. The id are the latter 6. 

The 3 node families are thus divided this way. A fourth family is available and currently not used.

***00** Input nodes
	values from 0 to 63

***01*** Neuron nodes
	values from 64 to 127

***10*** Action nodes
	values from 128 to 191

***11*** Free category
	values from 192 to 255

Every node is represented whole by his relative [[Node Genome]]