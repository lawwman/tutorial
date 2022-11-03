# What is an SSL Certificate
Secure Socket Layer (SSL) Certificate. Typically contains:
- domain name that the cert is issued for (and Associated subdomains)
- individual/organisation/device it was issued to
- Issuer and Issuer's signature (aka Certificate Authority (CA))
- Issue and expiry date of certificate
- public key

# What is it used for?
- The certificate proves an origin server owns that public key (and of course, it should own the private key!)
- enables an encrypted connection!

# How are certs created??
- https://www.ssl.com/article/browsers-and-certificate-validation/

Firstly, CAs themselves have a self-issued cert that contains a public key. That self-issued cert is signed with the CA's own private key. Hence the Issuer's signature on the cert can be verified by the public key that is also in the cert. Tada! self-signed.

This is known as a "Root" cert. To minimize exposure, the Root cert then uses its private key to sign another "intermediate" cert. Now this Intermediate cert's CA signature can be verified by the Root cert. And of course, the Intermediate cert has its own private and public key pair to be used to sign even more certs! A fucking certification path!

# How do browsers verify certs?
Browsers are shipped with a built-in list of trusted roots.

To verify a certificate, a browser will obtain a sequence of certificates, each one having signed the next certificate in the sequence, connecting the signing CA’s root to the server’s certificate. This sequence of certificates is called a certification path. The path’s root is called a trust anchor and the server’s certificate is called the leaf or end entity certificate.

After a candidate certification path is constructed, browsers validate it using information contained in the certificates. A path is valid if browsers can cryptographically prove that, starting from a certificate directly signed by a trust anchor, each certificate’s corresponding private key was used to issue the next one in the path, all the way down to the leaf certificate.

# How is it used??
By itself, it is just a certificate. We need to look into TLS handshaking to understand the protocol/steps for using an SSL certificate.
