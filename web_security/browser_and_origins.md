# Browser Enforced Policies

## [Same Origin Policy](https://developer.mozilla.org/en-US/docs/Web/Security/Same-origin_policy)

Origin = `protocol` + `domain` + `port`.

Let's say that I’m a browser. I load a website from a URL. Whatever server / origin / source that it comes from, let's call that `origin A`.

The website from `origin A` also needs resources from another server, `origin B`.
- How can `origin B` trust `origin A`? And vice versa.
- What if `origin B` returns a script that has malicious intent?
- Should an untrusted `origin A` be allowed to call `origin B` (which the user is signed into)?

As the browser, I should enforce that scripts loaded from an origin can only make requests to the same origin.

## What restrictions does [Same Origin Policy](https://developer.mozilla.org/en-US/docs/Web/Security/Same-origin_policy#cross-origin_network_access) have?!

I can still load resources (scripts, img, video) from a different origin IF I embed it into
- `<script src="..."></script>`
- `<img>` or `<video>`
- And the list goes on …

I can even send http requests to other origins... What? Same Origin Policy not working??

Seems like I can still do a lot. What can't I do? Well, its the responses from other origins that are blocked! Let me be specific...
- I can still send http requests to another origin, HUH... Same Origin Policy allows it!
- Other origins can receive and return a response! HUH...
- But browser detects that the response is from different origin. HERE IS THE BLOCK!

## Then how to allow access?! [CORS](https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS)!

Let’s say I’m a browser loading a website from `origin A`. `Origin A` returns a script that requires me to call external api from `origin B, C, D` etc.

It is up to the other `origins B, C, D`... to whitelist other origins!

If, say `origin B` receives a call from `origin A`, `origin B`’s response will contain the header Access-Control-Allow-Origin. This header includes a list of whitelisted origins. `Origin B` will return a response even if the origin calling it is not whitelisted. Why? Origins / Servers do not enforce Same Origin Policy, the browser does!

The browser inspects the response for the header and checks that `origin A` is included in the header. THEN the response is permitted by the browser.

# [Content Security Policy](https://developer.mozilla.org/en-US/docs/Web/HTTP/CSP)

Limit the origins we can trust and allow to execute within the context of the website.

Let’s say I’m a browser loading a website from `origin A`. CSP is not enabled by default. `Origin A` has to return X-Content-Security-Policy header with a list of trusted origins.

In addition to restricting origins, `origin A` can specify which protocols are allowed (e.g. only HTTPS).

## Other Applications of CSP
- https://content-security-policy.com/nonce/
- https://www.netsparker.com/blog/web-security/content-security-policy/


## SOP vs CSP in a nutshell...
From the browser pov:
- SOP: Who trusts me? (Which origin will let me call them)
- CSP: Who do I trust? (Which origin am I allowed to call)


# XSS

## For what it's about:
- [Not bad explanation by the owasp site](https://owasp.org/www-community/attacks/xss/).
- [Slightly better explanation on portswigger](https://portswigger.net/web-security/cross-site-scripting)

## Stored XSS (aka Persistent)
Malicious script is `stored` in a web app's server. Possible scenario? If the web app stores user input (forum, social media, online shop). Without proper validation, malicious content can get uploaded and persistently stored.

When a victim retrieves the stored data, and the web app does not do any filtering, malicious code can be executed on the victim's browser.

## Reflected XSS (aka Non-Persistent)
Say we have a "trusted" site that has a search function. `https://insecure-website.com/search?term=gift`, and then the site's http response `reflects` that same `gift` in the browser with `<p>You searched for: gift</p>`.

With this, you are now able to `reflect` other types on stuff to be rendered in the browser. `https://insecure-website.com/search?term=<script>/*+Bad+stuff+here...+*/</script>`. \
[Source](https://portswigger.net/web-security/cross-site-scripting/reflected)

## DOM Based
[Good read](https://portswigger.net/web-security/cross-site-scripting/dom-based)

Honestly, lots of overlaps with Stored and Reflected. Occurs when an attacker-controllable `source` finds its way into a `sink`.

An example of a `source` is `location.search`, which is the URL. If the victim's browser's javascript grabs data from `location.search` and that data finds its way into a `sink` (e.g. `.innerHTML`), whatever malicious content within the URL would have made its way into the DOM. So its DOM based.


### My guesses on the differences... Not 100% on this
I would say the slight differences between `Stored / Reflective` vs `DOM` is that `Stored / Reflective` XSS does not have to have the malicious script enter the `DOM`? It could just be executed?

Another difference I feel is that a purely DOM based XSS does not involve a HTTP request? It should be purely client side. Whereas, for a reflective XSS, the attack comes from the vulnerable site's http response that `reflects` the attack from the malicious URL link. What does it mean to `reflect`? The malicious request has to hit the server and be bounced or reflected back to the client.
