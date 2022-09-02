# Browser Enforced Policies

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
