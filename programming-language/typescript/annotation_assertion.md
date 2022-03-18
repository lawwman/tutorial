# Annotation vs Assertion

## [Annotations](https://www.typescriptlang.org/docs/handbook/2/everyday-types.html#type-annotations-on-variables)

Used to add types to your variables. I guess its really helpful in your IDE? Lets you know the shape of the object you are declaring.

```javascript
let myName: string = "Alice";
```

## [Assertions](https://www.typescriptlang.org/docs/handbook/2/everyday-types.html#type-assertions)

We know that the type of an object is of a certain way, but the compiler does not. (i.e. we are parsing a stringified JSON that we already is of a certain type already.)
```javascript
let newObj = JSON.parse(someString) as someType;
```

Basically, "trust me Typescript, I know the type. Let me force it as such".