# Linked data:
- [youtube explanation: linked data](https://www.youtube.com/watch?v=4x_xzT5eF5Q)
- [TED talk by the man himself, Tim Berners-Lee](https://www.youtube.com/watch?v=OM6XIICm_qo)

web pages are linked to other web pages. Easy for **humans** to use and discover other sites. Not so much for **computers**. Code only knows that there is a link present in a html document. It does not understand the context / significance of it.

What we want to create is a huge graph of interconnected nodes(reprensenting data).

3 rules to linked data:
- All conceptual things should have a name starting with HTTP.
- Looking up an HTTP name should return useful data about the thing in question in a standard format.
- Anything else that that same thing has a relationship with through its data should also be given a name beginning with HTTP.

Perhaps a node can refer to a person named Bob. He would be identified with a URL. Say he knows a person named Sally, who is also represented by her own node. Then both those nodes (pieces of data) can be linked together.

Cool examples:
- Google Knowledge Graph
- Facebook Open Graph Protocol

# json-ld: extension to json.
- [youtube explanation](https://www.youtube.com/watch?v=vioCbTo3C-4)
- [main site](https://json-ld.org/)

**json is:**
- key value pair
- easily readable by machines
- easily readable by humans
- **not standardised. 2 systems might have different meaning to the same key. If system A has a json with `name` property, system B might use `name` differently**

idea of json-ld: standardise json accross different systems. If every system use json the same way, integration and understanding of data becomes much simpler.

## How to achieve this?

an easy solution is that we can just be very specific.
```json
{
  "http://example.com/name": "bob",
  "http://example2.com/age": "22"
}
```
using urls as keys, we can be sure if another system use the same keys, we are talking about the same thing.

But this is not an ideal solution, as a developer, I don't want to deal with ugly jsons. I want to use simple terms. So how we achieve this is with `@context`.

```json
{
  "@context": "http://example.com/human.jsonld",
  "name": "bob",
  "age": "22"
}
```
`@context` will provide the... context. That way if I see a json object with the same `@context`, I know that my system can handle it.

json-ld also uses `@id` to identify documents with URLs!

```json
{
  "@context": "http://example.com/human.jsonld",
  "@id": "http://lamehuman.com/bob",
  "name": "bob",
  "age": "22"
}
```

hence json-ld:
- provides very specific context on what a json document is about (`@context`)
- provides very specific ways to refer to other documents (`@id`)

There are many more types like:
- `@type`
- `@language`
- `@value` etc...