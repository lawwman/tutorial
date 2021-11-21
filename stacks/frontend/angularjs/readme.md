# Learning Angular

## Purpose of this markdown
I'm sure I will forget how to use Angular after a short while. If I need to learn this again, I don't want to have to endure hours of Youtube videos, or deciphering the poorly written documentation.

## Quick Links
- [Local setup](https://angular.io/guide/setup-local)
- [Tutorial](https://angular.io/tutorial). Can slowly read and read up the concepts used. I think its not bad if you already have a vague idea of how it works.
- [Good youtube tutorial to follow along with](https://www.youtube.com/watch?v=3dHNOWTI7H8).
- [Glossary of Angular terms. Not bad for a reference.](https://angular.io/guide/glossary)


## [Angular CLI Tool](https://angular.io/cli)
What you will notice is that Angular integrates the `Angular CLI Tool` into the development flow. Creating Angular `components` etc are made easier with CLI. *Personally, not a fan. I'm fine with using Framework specific CLI to build, deploy etc. But even creating files and components are tied into the CLI.*

**Common commands:**
- `npm install -g @angular/cli`
- `ng new angular-tut` (creates new angular project with folder name `angular-tut`)
- `ng serve`
- `ng generate component heroes` (creates new folder containing `.ts`, `.html`, `.css` files required for the `heroes` component)

## What you get running `ng new <project_name>` (The Angular CLI command you use when starting new project)
```
<project_name>/
|-- src/
    |-- app/
        |-- app.component.css
        |-- app.component.html
        |-- app.component.spec.ts
        |-- app.component.ts
        |-- app.module.ts
    |-- assets/
        |-- .gitkeep
    |-- environments/
        |-- environment.prod.ts
        |-- environment.ts
    |-- favicon.ico
    |-- index.html
    |-- main.ts
    |-- polyfills.ts
    |-- style.css
    |-- test.ts
|-- browserslistrc
|-- .editorconfig
|-- .gitignore
|-- angular.json
|-- karma.conf.js
|-- package-lock.json
|-- package.json
|-- README.md
|-- tsconfig.app.json
|-- tsconfig.json
|-- tsconfig.spec.json
```

You can consider `src/index.html` and `src/main.ts` the "starting" or "entry" into your application. You can start tracing the code from these 2 files.

`src/index.html`:
```html
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>AngularTut</title>
  <base href="/">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" type="image/x-icon" href="favicon.ico">
</head>
<body>
  <app-root></app-root>
</body>
</html>
```
While tracing the code, you will find that it only contains `app-root`. Much like `ReactJS`, you will be using Javascript / Typescript to define what exactly is `app-root`.

Initial questions:
- How does Angular know what to do when it sees `app-root`? (Has to do with `components`... explained later. What you need to know for now is that `app-root` is a `component` we define. Even the name `app-root` can be varied)
- Where is this `app-root` definition? In `src/app/`!

---
`src/main.ts`
```typescript
import { enableProdMode } from '@angular/core';
import { platformBrowserDynamic } from '@angular/platform-browser-dynamic';
import { AppModule } from './app/app.module';
import { environment } from './environments/environment';
if (environment.production) enableProdMode();
platformBrowserDynamic().bootstrapModule(AppModule).catch(err => console.error(err));
```
As you can tell, we are bootstrapping from the `AppModule` module, which uses the `NgModule` decorator.

---
`src/app/app.module.ts`
```typescript
import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { AppComponent } from './app.component';
@NgModule({
  declarations: [AppComponent],
  imports: [BrowserModule],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
```
We are bootstrapping from this `AppModule` class. So this brings us to our first question...

## What the heck is a [`NgModule`](https://angular.io/guide/ngmodules)??
They are "containers" for `components`, `service providers` etc. Yes yes, we also don't know what `components` and `service providers` are yet. We will get to those soon.
- Angular projects require at least 1 root module, conventionally named `AppModule`.
- The application is bootstrapped/launched from this root module.

You will notice in the above `src/app/app.module.ts` snippet, `NgModule`s use the `@NgModule` decorator. Such readable code. Wow.

Right. So `NgModules` are "containers" for `components`. As of now, you can think of `components` as just pieces of your web application. It could refer to your header, footer, list of stuff, whatever. Your whole application could be built on 1 `component`. It could be built on 100. It's really up to you.

`NgModules` are also "compilation contexts" for Angular. It lets angular know
- what other `NgModules` you need to `import`? What are you exporting from this module?
- What `components` does this `NgModule` have?
- What `providers` does this `NgModule` have? (yes, we still don't know wtf are `providers`)
- and other stuff...

Maybe a good TLDR is that `NgModules` group and organise Angular thingies together and helps Angular know how to compile whatever you made?

---
Ok so now we roughly know what are `NgModules`. We also know that it only contains one `component`, `AppComponent`. Next question...

## What the heck is a [Component](https://angular.io/guide/architecture-components)??
Think of it as a piece of your web application. Typically, a web application requires `.js`, `.css` and `.html`. If you were to "break" your application up into many different pieces, each with their own set of `.js`, `.css` and `.html`, that's basically an Angular `component`.

```typescript
import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'angular-tut';
}
```
The dynamic behavior that Javascript provides is within the `component` class. You define your `html` and `css` files as well in the `@Component` decorator. By now you should realise that Angular uses decorators very heavily. *I don't know how to feel about that.*

> Remember, what makes it a component, is the `@Component` decorator!

Quick clarifications:
- What is the `selector` metadata in `@Component`? It lets Angular know what html to render. Following the above example, with `app-root` selector, if Angular sees `<app-root></app-root>` tag in html, it will render whatever is in the `templateUrl` with the appropriate styles.
- Pretty common sense, `templateUrl` and `styleUrls` are the links to the html and css files of the `component`.

We can define our templates and css directly in the `@Component` metadata.
```typescript
@Component({
  selector: 'app-component-overview',
  template: '<h1>Hello World!</h1>',
  styles: ['h1 { font-weight: normal; }']
})
```

Now you might be wondering, why is it called `template`?? Isn't it just `html`?