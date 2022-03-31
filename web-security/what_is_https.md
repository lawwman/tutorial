# [Article about what is HTTPS](https://www.cloudflare.com/en-gb/learning/ssl/what-is-https/)
- HTTP sends messages in plain text
- HTTPS sends them in cipher text

HTTPS makes use of TLS protocol to send cipher text or encrypted texts! So...

# What is TLS??
Transport Layer Security (TLS), evolved from Secure Socket Layer (SSL). A security protocol - primarily used to encrypt messages between client and server.

Please read about SSL certs before this.

## Let's learn the handshake! :smirk:
> Note that TLS handshake is done after TCP handshake!
> origin server stores TLS certificate (aka SSL cert)

1. Client pings server with TLS version supported, cipher suites supported and random bytes ("client random")
2. Server response with SSL cert + cert authority, chosen cipher and "server random" (more random bytes).
3. Client verifies SSL cert against cert authority
4. Client sends "premaster" secret (just more random bytes), encrypted with public key found in SSL cert. Can only be decrypted by Server that owns the private key.
5. Server decrypts premaster secret.
6. Both client and server generate session keys (used for symmetric encryption) with the premaster secret. It is deterministic.
7. Client sends a message encrypted by session key.
8. Server replies with its own message encrypted by same key.

Tada! handshake complete.

# SSL Pinning
> Please read about SSL certs before this.

an SSL connection tells the client to make an encrypted connection with any identity matching that host. Pinning tells the client a specific identity they should accept when making a secure connection.

## What is SSL/TLS pinning trying to solve??
Say Client A wants to talk to Server B. How TLS normally works is that there is a certification path and we validate to make sure that the leaf certificate links back to the Root cert. If you are lost, please read more about SSL certs.

How do we know a Root is valid? We don't really... they are self signed. But browsers come shipped with trusted roots.

Here is the problem: An attacker could do a man in the middle attack and serve a fake Server B that looks like it functions exactly the same as Server B. He could also get a legitimate SSL cert. It could come from different CA, with a different root. And you would not know! And how could you know? That SSL cert afterall is legitimate.

Unless of course... your browser remembers what the original Server B's cert looks like? Hehe, yep that is SSL pinning. Just remembering the cert.


## Cons?
Well... SSL pinning essentially means that you hardcode the hash of the cert in your application code. So if your server's SSL cert expires... You have to update both the cert and the application! It is really inconvenient.

## Useful for?
Well say you are a mobile developer. Your mobile app only ever has to communicate with your backend system. Well SSL pinning suddenly makes a lot of sense if you want to be secure. Same goes for game development!

[So-so explanation](https://www.youtube.com/watch?v=3coPpYJgFro)