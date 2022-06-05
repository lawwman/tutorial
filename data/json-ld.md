# json-ld: extension to json.
- [w3c document](https://www.w3.org/TR/json-ld11/#the-context)

Json-ld is a concrete RDF syntax.

## Intro
json is **not standardised.** 2 systems might have different meaning to the same key. If system A has a json with `name` property, system B might use `name` differently.
```json
{
  "name": "Manu Sporny",
  "homepage": "http://manu.sporny.org/",
  "image": "http://manu.sporny.org/images/manu.png"
}
```

Linked Data, and the Web in general, uses `IRIs` (as described in `./rdf.md`) for unambiguous identification. The idea is to use `IRIs` to assign unambiguous identifiers to data that may be of use to other developers.

Leveraging the popular schema.org vocabulary, the example above could be unambiguously expressed as follows:
```json
{
  "http://schema.org/name": "Manu Sporny",
  "http://schema.org/url": {
    "@id": "http://manu.sporny.org/"
  },
  "http://schema.org/image": {
    "@id": "http://manu.sporny.org/images/manu.png"
  }
}
// The '@id' keyword means 'This value is an identifier that is an IRI'
```
While this is a valid JSON-LD document that is very specific about its data, the document is also overly verbose and difficult to work with for human developers.
To address this issue, JSON-LD introduces the notion of a context as described in the next section.

Simple example:
```json
{
  "@context": "https://json-ld.org/contexts/person.jsonld",
  "@id": "http://dbpedia.org/resource/John_Lennon",
  "name": "John Lennon",
  "born": "1940-10-09",
  "spouse": "http://dbpedia.org/resource/Cynthia_Lennon"
}
```
json-ld:
- provides very specific context on what a json document is about (`@context`)
- provides very specific ways to refer to other documents (`@id`)

## keyword aliasing
```json
{
  "@context": {
    "id": "@id",
    "type": "@type",
    ...
  }
}
```
the above means: "id" and "@id" will be the same. This makes it easier for us to access the property in code. Easier to type `obj.type` rather than `obj["@type"]`.