# This

reads:
- [developer mozilla](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/this)

value of `this` depends on execution context.
- Global? (outside of any function)
- Function? (inside a function)


## `this` refers to Global object in Global and Function Context
`this` would refer to the global object.
```
function f1() {
  return this;
}

this === window   // true. In web browsers, the window object is the global object.
a = 37;           // this.a == window.a == 37
this.b = "MDN";   // window.b === b === "MDN"
f1() === window;  // true
```
*In function calls like f(), the `this` value was the global object. In strict mode, it is now undefined.*
```
function f2() {
  'use strict'; // see strict mode
  return this;
}
f2() === undefined; // true
```

## Class Context
