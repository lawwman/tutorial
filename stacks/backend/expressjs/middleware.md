# Useful Middlewares to know!

## Built-in middlewares

- `express.static(root, [options])`. Click [here](https://expressjs.com/en/4x/api.html#express.static) to find out more.
- `express.json([options])`. Click [here](https://expressjs.com/en/4x/api.html#express.json) to find out more.
- `express.urlencoded([options])`. Click [here](https://expressjs.com/en/4x/api.html#express.urlencoded) to find out more.

```javascript
import express = require('express');
const app = express();

app.use(express.static('./public')); // Serve static files from /public folder
app.use(express.json()); // inbuilt middleware in express to recognize the incoming Request Object as a JSON Object.
app.use(express.urlencoded()); // inbuilt middleware in express to recognize the incoming Request Object as strings or arrays.
```
> Note to self, should update more specifically the difference btween .json and .urlencoded. As far as I can tell, something to do with HTML submit forms.

---

## 3rd Party middlewares

