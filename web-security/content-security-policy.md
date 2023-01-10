good reads:
- https://developer.mozilla.org/en-US/docs/Web/HTTP/CSP
- https://www.invicti.com/blog/web-security/content-security-policy/

# overview
it is a browser-enforced policy that works by specifying the domains that the browser should consider to be valid sources.

The modern web requires sites to include lots of assets from external sources, such as scripts and other resources from content delivery networks (CDNs), Google Analytics scripts, fonts, styles, comment modules, social media buttons etc.

Malicious hackers use cross-site scripting (XSS) attacks to trick websites trusted by the user into delivering malicious code. Without additional safety measures, the browser executes all code from a trusted origin and can’t tell which code is legitimate, so any injected malicious code is executed as well.

# enabling
configure web server to return `content-security-policy` http header or simply add the following to the html you are returning:
```
<meta
  http-equiv="Content-Security-Policy"
  content="default-src 'self'; img-src https://*; child-src 'none';" />
```
# examples of policies
```
# all content has to come from site's own origin (this excludes subdomains.)
Content-Security-Policy: default-src 'self'

# allow content from a trusted domain and all its subdomains (it doesn't have to be the same domain that the CSP is set on.)
Content-Security-Policy: default-src 'self' example.com *.example.com

# can include images from any origin, but restrict audio or video media to trusted providers, and all scripts only to come from userscripts.example.com
Content-Security-Policy: default-src 'self'; img-src *; media-src example.org example.net; script-src userscripts.example.com

# all its content is loaded using TLS, in order to prevent attackers from eavesdropping on requests.
Content-Security-Policy: default-src https://onlinebanking.example.com
```

# TLDR
when user is on our website, we can delegate to browser what sources to trust (via the http header `content-security-policy`). the types of sources can range from:
- script-src
- style-src
- connect-src
- object-src
- img-src
- font-src
- media-src

etc...