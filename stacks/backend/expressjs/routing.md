# Deeper look into Express routing

*Routing refers to how an application’s endpoints (URIs) respond to client requests.*

We are already familiar with `app.get`, `app.post` etc...

## [app.all(path, callback [, callback...])](https://expressjs.com/en/4x/api.html#app.all)

Matches all http verbs.
```javascript
app.all('/example', function (req, res, next) { // works for /example GET, POST, DELETE...
  console.log('Accessing the example section ...')
  next() // pass control to the next handler
})
```
or we could also have:
```javascript
app.all('*', requireAuthentication)
app.all('*', loadUser)
```

## [app.use([path], callback [, callback...])](https://expressjs.com/en/4x/api.html#app.use)

Matches every request. [.all vs .use](https://bambielli.com/til/2016-12-27-app-use-app-all/)


## app.route()
```javascript
app.route('/book')
  .get(function (req, res) {
    res.send('Get a random book')
  })
  .post(function (req, res) {
    res.send('Add a book')
  })
  .put(function (req, res) {
    res.send('Update the book')
  })
```

## Router
```javascript
/* bird.js */
var express = require('express')
var router = express.Router()

// middleware that is specific to this router
router.use(function timeLog (req, res, next) {
  console.log('Time: ', Date.now())
  next()
})
// define the home page route
router.get('/', function (req, res) { /* matches path: "/birds" */
  res.send('Birds home page')
})
// define the about route
router.get('/about', function (req, res) {  /* matches path: "/birds/about" */
  res.send('About birds')
})

module.exports = router

/* app.js */
var birds = require('./birds')

// ...

app.use('/birds', birds)
```
A router object is an isolated instance of middleware and routes. You can think of it as a “mini-application,” capable only of performing middleware and routing functions. Every Express application has a built-in app router.

A router behaves like middleware itself, so you can use it as an argument to app.use() or as the argument to another router’s use() method.