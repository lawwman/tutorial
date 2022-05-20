- [youtube explanation](https://www.youtube.com/watch?v=ldl0m-5zLz4)

# RDF
Resource Description Framework: Fancy way to say it can describe anything. It is a concept, not a syntax.

3 main things in RDF:
- Subject
- Predicate
- Object

Example: "Dave likes cookies",
- Dave -> subject
- likes -> predicate
- cookies -> object

## CURI
Compact URI. Annoying to always type out long URIs, so we take the long part and compact it to a short word.

Example: `foaf:name`, would expand to `http://xmlns.com/foaf/0.1/name`.

## N3
Syntax for expressing RDF statements.

According to N3 notation, the `<Subject> <Predicate> <Object>` statement is what is known as a `Triple`.

For the statement: "Dave likes cookies", in N3 notation it would look like:
```
@prefix pref: <http://example.org/vocabulary#> .
<#dave> <pref:likes> <#cookies> .
```
## RDFA
N3 is a syntax to describe RDF to humans. RDFA is a syntax to describe RDF to machines.

## Vocabulary
Defines what triples actually mean. example of a popular vocabulary: `foaf`.


# todo
There is a lot more to learn about RDF but I will stop here. no time.