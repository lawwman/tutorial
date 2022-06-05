- [RDF Primer](https://www.w3.org/TR/rdf11-primer/) // i have not read this yet
- [RDF concepts](https://www.w3.org/TR/rdf11-concepts/)

# Resource Description Framework (RDF)
It is a framework for representing information in the Web. The core structure is a `triple` consisting of `<subject> <predicate> <object>`. Example: "Dave likes cookies".

The `subject` and `object` are both nodes in the RDF. There can be 3 types of nodes:
- Internationalized Resource Identifier (`IRI`)
  - `URI` is limited to ASCII set. `IRI` builds on top of `URI`, but it can contain characters from UNICode (including chinese, japanese, korean etc)
  - `IRIs` are globally unique identifiers
- `literals`
  - used for strings, numbers and dates.
  - `subject` cannot be a literal
  - consists of a `string`, `IRI` linking to the datatype, `language tag` if the `IRI` datatype is `http://www.w3.org/1999/02/22-rdf-syntax-ns#langString`.
- `blank nodes`
  - honestly im not sure
  - not part of the RDF abstract syntax, but are entirely dependent on the concrete syntax or implementation

The predicate itself is an `IRI` too.

## How RDF is organised
- A set of `triples` is called an RDF graph.
- An RDF dataset is a collection of RDF graphs.


## RDF Vocabulary
An RDF vocabulary is a collection of `IRIs` intended for use in RDF graphs.

`IRIs` in RDF vocabulary often begin with `namespace IRI`. Some `namespace IRIs` are associated with a short name known as `namespace prefix`. For example: the `namespace IRI` http://www.w3.org/1999/02/22-rdf-syntax-ns#	 has a `namespace prefix` of `rdf`.

Sometimes for readability, the `IRI` http://www.w3.org/1999/02/22-rdf-syntax-ns#XMLLiteral can be abbreviated to `rdf:XMLLiteral`. However, note that these are not valid `IRIs`.


## RDF syntax
An `RDF document` is a document that encodes an RDF graph or RDF dataset in a concrete RDF syntax, such as:
- Turtle
- RDFA
- JSON-LD
- TRIG
`RDF documents` enable the exchange of RDF graphs and RDF datasets between systems.
