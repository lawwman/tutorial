Referring to `tsconfig.ts`:
```javascript
{
  ...
  "module": "commonjs",
  "moduleResolution": "node",
  "target": "es2020"
  ...
}
```

# what the hell is a `module`?
`module` describes the `import` and `export` of the **compiled** js code.  It can accept values of `commonjs`, `es2020`, `umd` and so on.

**It affects what your compiled js code looks like.**

```javascript
// Typescript code
import { valueOfPi } from "./constants";
export const twoPi = valueOfPi * 2;

// the compiled javascript code when built with module: CommonJS
"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.twoPi = void 0;
const constants_1 = require("./constants");
exports.twoPi = constants_1.valueOfPi * 2;

// the compiled javascript code when built with module: ES2020
import { valueOfPi } from "./constants";
export const twoPi = valueOfPi * 2;

// ... and the list goes on
```

# what about `moduleResolution`?
`moduleResolution` describes how the compiler finds modules **based on your import statements.**
- default value of `moduleResolution` is affected by `module`

**It does not affects what your compiled js code looks like.**


# simi is `target`?
`target` signifies which target of JavaScript should be emitted from the given TypeScript. Hence it affects which JS features are downleveled and which are left intact. 

**It affects what your compiled js code looks like.**

For example, an arrow function () => this will be turned into an equivalent function expression if target is ES5 or lower.

# huh, `lib`?
`lib` specifies a list of built-in API declaration groups to include in the project.
- default value of `lib` is affected by `target`

**It does not affects what your compiled js code looks like.**

For instance, if you expect your runtime to have support for Map, Set and Promise (e.g. most evergreen browsers today), just include --lib es2015.collection,es2015.promise. Similarly you can exclude declarations you do not want to include in your project, e.g. DOM if you are working on a node project using --lib es5,es6.


# Reads
- https://stackoverflow.com/questions/72597681/trying-to-understand-how-module-moduleresolution-differ
- https://stackoverflow.com/questions/42415942/what-is-target-in-tsconfig-json-for
- https://stackoverflow.com/questions/39303385/what-does-the-tsconfig-option-lib-do