# How DNS works
- https://www.cloudflare.com/en-gb/learning/dns/what-is-dns/
- https://www.cloudflare.com/en-gb/learning/dns/dns-server-types/

map domain name to IP address.

# what happens when browser makes a DNS query?

## **step 1: query goes to `DNS recursor `(a.k.a DNS Recursive resolver)**

`DNS recursor` is just a middleman between browser and `name servers `(fancy name for servers that work within DNS system). DNS recursor will go back and forth with different name servers to eventually get you the IP address.

## **step 2: DNS recursor talks to `Root nameserver`**

[`Root nameserver`](https://www.cloudflare.com/en-gb/learning/dns/glossary/dns-root-server/) will respond to the `DNS recursor` on which server to contact next. If the domain name ends with `.com` or `.org` etc, the `root server` will direct the `recursor` to the correct `top level domain server`.

## **step 3: DNS recursor talks to `TLD server`**
`top level domain server`(TLD) will have information on where the domain records are held. The records are stored within an `authoritative nameserver`. TLD server will respond to the `recursor` to the correct `authoritative nameserver`.

## **step 4: DNS recursor talks to `authoritative nameserver`**
Put simply, an `authoritative DNS server` is a server that actually holds, and is responsible for, `DNS resource records`. This is the server at the bottom of the DNS lookup chain that will respond with the queried resource record, ultimately allowing the web browser making the request to reach the IP address needed to access a website or other web resources.

finally, the `recursor` will return the IP address to the browser.

# security
DNS uses UDP. No connections, stateless.

Problem: with UDP, the `recursor` does not know which udp message belongs to which query.

Solution: we tag each UDP with a query id.

## DNS Poisoning
attacker can just spam `recursor` with udp packets with random query id, ip address and port.

the ip address could be malicious. oh no.

## DNSSEC
As DNS was originally designed, a resolver cannot easily detect a forged response to one of its queries. An attacker can easily masquerade as the authoritative server that a resolver originally queried by spoofing a response that appears to come from that authoritative server. In other words an attacker can redirect a user to a potentially malicious site without the user realizing it.

Hence, `DNS Security Extensions `(DNSSEC).

`DNSSEC` strengthens authentication in `DNS` using digital signatures based on public key cryptography. With `DNSSEC`, it's not `DNS` queries and responses themselves that are cryptographically signed, but rather DNS data itself is signed by the owner of the data.

Each DNS zone (server) has a public/private key pair.

- the zone's private key is used to sign incoming DNS data and generate digital signatures over that data.
- The zone's public key is published in the zone itself for anyone to retrieve. Any recursive resolver that looks up data in the zone also retrieves the zone's public key, which it uses to validate the authenticity of the DNS data.

DNSSEC adds two important features to the DNS protocol:
- Data origin authentication allows a resolver to cryptographically verify that the data it received actually came from the zone where it believes the data originated.
- Data integrity protection allows the resolver to know that the data hasn't been modified in transit since it was originally signed by the zone owner with the zone's private key.

can read up more at https://www.icann.org/resources/pages/dnssec-what-is-it-why-important-2019-03-05-en). Good article.