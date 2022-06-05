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
