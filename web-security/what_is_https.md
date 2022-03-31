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

