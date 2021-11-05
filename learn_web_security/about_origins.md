# Browser Enforced Policies


## [Same Origin Policy](https://developer.mozilla.org/en-US/docs/Web/Security/Same-origin_policy)

Origin is `protocol` + `domain` + `port`

Let's say that I’m a browser. I load a website from a URL. Whatever server / origin / source that it comes from, let's call that origin A.

But the website from origin A also needs resources from another server, origin B. 
- How can we trust origin B?
- How can origin B trust origin A?
- What if origin B returns a script that has malicious intent?
- How can origin B protect itself from malicious http requests?
- Should a website loaded from origin A be allowed to make requests to origin B, C, D…?

As the browser, I should enforce that a website loaded from origin A can only call itself. This is the Same Origin Policy.

## What does [Same Origin Policy Control](https://developer.mozilla.org/en-US/docs/Web/Security/Same-origin_policy#cross-origin_network_access)?!

I can load resources (scripts, img, video) from a different origin IF I embed it into
- `<script src="..."></script>`
- `<img>` or `<video>`
- And the list goes on …

It seems the restrictions are more obvious when sending http requests to a different origin (E.g. calling api of different origin).

## Then how to allow access?! [CORS](https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS)!

Let’s say I’m a browser loading a website from origin A. Origin A returns a script that requires me to call external api from origin B, C, D etc.

CORS essentially lets those external origins B, C, D... whitelist other origins. If, say origin B receives a call from origin A, origin B’s response will contain the header Access-Control-Allow-Origin. This header includes a list of whitelisted origins. Origin B will return a response even if the origin calling it is not whitelisted. Why? Origins / Servers do not enforce Same Origin Policy, the browser does!

The browser inspects the response for the header and checks that origin A is included in the header.

# [Content Security Policy](https://developer.mozilla.org/en-US/docs/Web/HTTP/CSP)

Limit the origins we can trust and allow to execute within the context of the website.

Let’s say I’m a browser loading a website from origin A. CSP is not enabled by default. Origin A has to return X-Content-Security-Policy header with a list of trusted origins.

In addition to restricting origins, origin A can specify which protocols are allowed (e.g. only HTTPS).

Useful in preventing Cross Site Scripting attacks (XSS)

https://content-security-policy.com/nonce/
https://www.netsparker.com/blog/web-security/content-security-policy/


## CORS vs Content Security Policy
From the browser pov:
- CORS lets me know if the external origin I’m calling trusts me (whitelists me).
- Content Security Policy lets me know who I can trust.


# XSS

For what it's about: \
- [Not bad explanation by the owasp site](https://owasp.org/www-community/attacks/xss/).
- trying to find a nicer explanation article...

## Stored XSS (aka Persistent)
Malicious script is `stored` in a web app's server. Possible scenario? If the web app stores user input (forum, social media, online shop). Without proper validation, malicious content can get uploaded and persistently stored.

When a victim retrieves the stored data, and the web app does not do any filtering, malicious code can be executed on the victim's browser.

## Reflected XSS (aka Non-Persistent)
Say we have a "trusted" site that has a search function. `https://insecure-website.com/search?term=gift`, and then the site's http response `reflects` that same `gift` in the browser with `<p>You searched for: gift</p>`.

With this, you are now able to `reflect` other types on stuff to be rendered in the browser. `https://insecure-website.com/search?term=<script>/*+Bad+stuff+here...+*/</script>`. \
[Source](https://portswigger.net/web-security/cross-site-scripting/reflected)

## DOM Based

