# Chapter 1: Modules, Components, Templates and Directives

## [Angular CLI Tool](https://angular.io/cli)
What you will notice is that Angular integrates the `Angular CLI Tool` into the development flow. Creating Angular `components` etc are made easier with CLI. *Personally, not a fan. I'm fine with using Framework specific CLI to build, deploy etc. But even creating files and components are tied into the CLI.*

**Common commands:**
- `npm install -g @angular/cli`
- `ng new angular-tut` (creates new angular project with folder name `angular-tut`)
- `ng serve`
- `ng generate component heroes` (creates new folder containing `.ts`, `.html`, `.css` files required for the `heroes` component)
- `ng generate directive <directive_name>`

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
The `component` class contains whatever variable, methods that you require to give your `component` dynamic behavior. You define your `html` and `css` files as well in the `@Component` decorator. By now you should realise that Angular uses decorators very heavily. *I don't know how to feel about that.*

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

Well that is because Angular uses its own `template` syntax, but borrows the `html` file type. It is very similar but there are slight differences. You can:
- incorporate `if` and `for loop` logic. (Angular uses `*ngIf` and `*ngFor` syntax for that)
- directly bind variable values from `components` into the `template`/`html`! (E.g. "`<p>{{title}}</p>`". In this case, the variable `title` is defined in the `js` file containing the `component` class).
- ... and so much more! (`Pipes`, `Directives` etc)

## Recap on Including `components` into the application!
Alright so lets say we have created a few different components, maybe a header?
```typescript
@Component({
  selector: 'app-header',
  templateUrl: './header.component.html',
  styleUrls: ['./header.component.css']
})
```
or maybe even a footer?
```typescript
@Component({
  selector: 'app-footer',
  templateUrl: './footer.component.html',
  styleUrls: ['./footer.component.css']
})
```
So in the `template`of the main `component` `AppComponent`, we can have something like
```html
<app-header></app-header>
<p>Hello World</p>
<app-footer></app-footer>
```

And that's how we include `components` that we have created! Simple!

## What about child `components`?? How do I pass values from Parent to child `components`?? And Vice-versa??
This [link](https://angular.io/guide/component-interaction) is actually pretty good for that.

---
You are not asking but...
## What the heck are `Directives`??
*Directives are classes that add additional behavior to elements in your Angular applications - Angular*

Well we are already familiar with one type of `Directive`! `Components` are a sub-type of `Directives`! They are defined by a class with a `@Component` decorator. They are `directives` with a `template`!

### Another type of `directives` are [`Attribute directives`](https://angular.io/guide/built-in-directives#built-in-attribute-directives)
Ok. What the heck are those?? Well, I find it best to see examples! We will see some sample code from the 3 most common attribute directives:
- NgClass - adds and removes a set of CSS classes.
- NgStyle - adds and removes a set of HTML styles.
- NgModel - adds two-way data binding to an HTML form element.

Ok lets look at `NgClass`. Say our `component` has a boolean variable `isSpecial`. I want the `template` to have a div with dynamic CSS class. Meaning to say, depending on the value of `isSpecial`, the CSS class will vary!
```html
<div [ngClass]="isSpecial ? 'special' : ''">This div is special</div>
```
This is a neat way to dynamically assign CSS classes with expressions! You can also use [methods](https://angular.io/guide/built-in-directives#using-ngclass-with-a-method)!

Now let's look at `NgStyle`.
```html
<div [ngStyle]="currentStyles">
  This div is italic, normal weight, and extra large (24px).
</div>
```
So where is `CurrentStyles` from? From the `component` itself!
```typescript
setCurrentStyles() { // within the component class!
  // CSS styles: set per current state of component properties
  this.currentStyles = {
    'font-style':  this.canSave      ? 'italic' : 'normal',
    'font-weight': !this.isUnchanged ? 'bold'   : 'normal',
    'font-size':   this.isSpecial    ? '24px'   : '12px'
  };
}
```

Lastly, we have `NgModel`. This is a special one! It requires importing another `NgModule` named `FormsModule`.

`src/app/app.module.ts`
```typescript
import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { FormsModule } from '@angular/forms'; // <- Import Forms Module here!
import { AppComponent } from './app.component';
@NgModule({
  declarations: [AppComponent],
  imports: [
    BrowserModule,
    FormsModule // <--- import into the NgModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
```
Remember that Angular `modules` provide the compilation context! `NgModel` is a directive that is provided by the `FormsModule` module. So please remember to update the current module you are working on to let it know about this import!

Lastly, include `NgModel` into the component's template.
```html
<label for="example-ngModel">[(ngModel)]:</label>
<input [(ngModel)]="currentItem.name" id="example-ngModel">
```
For more info, click [here](https://angular.io/api/forms/NgModel#description)

**Wait a minute**... Those aren't classes!! Did I lie to you?? The above description said that `Directives are classes that add additional behavior...`. What the heck? Well it is because those seen above are **built-in** attribute directives! You do not have to write a class for them. It's available out of the box! Ah yes, if there are built-in directives, there are custom ones too! You can write your own [attribute directives](https://angular.io/guide/attribute-directives) with the use of classes!

### Structural Directives!
For the built-in structural directives, you can use them straight out of the box within the `template` files.

Quick example, `NgIf`. Imagine if you could have an if-block to determine whether to render html elements **within** `.html` file itself. Yea that's what it does.
```html
<app-item-detail *ngIf="isActive" [item]="item"></app-item-detail>
```
And yes, `isActive` is just a variable within the component class in the `.ts` file.

Now, imagine if we could have for-loop logic within `html` itself. Surprise surprise. `NgFor`.

```html
<div *ngFor="let item of items">{{item.name}}</div>
```

Quite self explanatory, for more click [here](https://angular.io/guide/built-in-directives#built-in-structural-directives).

For more info on writing your own custom [structural directives](https://angular.io/guide/structural-directives).