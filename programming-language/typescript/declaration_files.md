# Learning about declaring stuff

## `Declare` keyword

Within TS handbook, there is no information on how this magic keyword works...

I found a clue [here](https://www.typescriptlang.org/docs/handbook/namespaces.html#working-with-other-javascript-libraries): *"To describe the shape of libraries not written in TypeScript, we need to declare the API that the library exposes."*

## About `namespaces`
`Namespaces` are just a way to organise code.

```javascript
namespace SomeNamespace {
    export interface SomeType {
        someName: string;
    }
}
const object: SomeNamespace.SomeType = { someName: 'lawrence' };
```
With the `SomeNamespace` namespace, I can just refer to the `SomeType` interface with `'.'`.

## Small usecase on `declare` with `namespaces`
Now, if we have a Javascript library that we are using in a Typescript code base, we can't use it typed because it isn't implemented with Typescript code. What if I want to add a namespace to that Javascript library??

Well, we can attach a `.d.ts` file to it. And we also have to use the mysterious `declare` keyword. I intepret the `declare` keyword as:

*"Well there is this module that is already implemented. I want to 'declare' that it has certain types and you will just have to trust me. The module was not created with the types I'm declaring, it does not have the same `interface` or `types` in its implementation. I'm just declaring that it does so we can use it as if it is implemented in TS."*

We call these Namespaces, Ambient Namespaces. **Highly recommend future me that has forgetten how all this works to read [this](https://stackoverflow.com/questions/43335962/purpose-of-declare-keyword-in-typescript/54913954#54913954).**


## Links:
- [Some examples of: code snippets and their corresponding declarations](https://www.typescriptlang.org/docs/handbook/declaration-files/by-example.html)



## todo...
- read this https://www.typescriptlang.org/docs/handbook/declaration-files/library-structures.html. But first, I need to readup more on modules... ughhhh
- https://github.com/DefinitelyTyped/DefinitelyTyped