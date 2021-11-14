# Functions

## [get()](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Functions/get) and [set()](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Functions/set)

### get()
```
const obj = {
  something: 'something',
  get getSomething() {
    return this.something;
  }
}
```
Attaching a `property` to an object. Not a function... a `property`. Why do I emphasize property? You call it with `obj.getSomething`, not `obj.getSomething()`.

*Definition: The get syntax binds an object property to a function that will be called when that property is looked up.*

So its like a property that kind of behaves like a function?

```
const expr = 'foo';
const obj = {
  get [expr]() { return 'bar'; }
};
console.log(obj.foo); // "bar"
```
Example of using a computed property name. Pretty cool!

### set()
```
const language = {
  set current(name) {
    this.log.push(name);
  },
  log: []
};

language.current = 'EN';
language.current = 'FA';

console.log(language.log);
```