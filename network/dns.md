# How Domain Name System (DNS) works
- https://www.cloudflare.com/en-gb/learning/dns/what-is-dns/
- https://www.cloudflare.com/en-gb/learning/dns/dns-server-types/

# what happens when browser makes a DNS query?

1. query goes to `DNS resolver`
    - `DNS resolver` is just a middleman between browser and `name servers`(fancy name for servers that work within DNS system). DNS resolver will go back and forth with different name servers to eventually get you the IP address.

2. DNS resolver talks to `Root nameserver`

    - [`Root nameserver`](https://www.cloudflare.com/en-gb/learning/dns/glossary/dns-root-server/) will respond to the `DNS resolver` on which server to contact next. If the domain name ends with `.com` or `.org` etc, the `root server` will direct the `resolver` to the correct `top level domain server`.

3. DNS resolver talks to `top level domain server` (TLD)
    - TLD will have information on where the domain records are held. The records are stored within an `authoritative nameserver`. TLD server will respond to the `resolver` to the correct `authoritative nameserver`.

4. DNS resolver talks to `authoritative nameserver`
    - Put simply, an `authoritative DNS server` is a server that actually holds, and is responsible for, `DNS resource records`. This is the server at the bottom of the DNS lookup chain that will respond with the queried resource record, ultimately allowing the web browser making the request to reach the IP address needed to access a website or other web resources.

finally, the `resolver` will return the IP address to the browser.

# DNS Records

## DNS A record
https://www.cloudflare.com/en-gb/learning/dns/dns-records/dns-a-record/
- "A" stands for "Address"
- Indicates the IP address of a given domain
- e.g: if you pull the DNS records of cloudflare.com, the A record currently returns an IP address of: 104.17.210.9.
- A records hold IPV4 only. AAAA records hold IPV6.

The most common usage of A records is IP address lookups by a `DNS resolver`.

## DNS CNAME record
https://www.cloudflare.com/en-gb/learning/dns/dns-records/dns-cname-record/
- "CNAME" stands for "Canonical name"
- "A" records point to an IP. CNAME records point to another domain
- e.g: `blog.example.com` has a CNAME record with value of `example.com`. When a DNS server hits the DNS records for `blog.example.com`, it triggers a DNS lookup to `example.com`, returning `example.com`’s IP address via its "A" record. `blog.example.com.`'s true/canonical name is `example.com`.
- often, sites have subdomains like `blog.example.com` or `shop.example.com` and those subdomains will have CNAME records that point to a root domain (`example.com`). If the IP address of the host changes, only the DNS A record for the root domain needs to be updated and all the CNAME records will follow along with whatever changes are made to the root.
- A CNAME record does not always resolve to the same website as the domain it points to. It only points the client to the root domain's IP. Once the client hits that IP address, the web server will still handle the URL accordingly. e.g: `blog.example.com` might have a CNAME that points to `example.com`, directing the client to `example.com`’s IP address. But when the client actually connects to that IP address, the web server will look at the URL, see that it is `blog.example.com`, and deliver the blog page rather than the home page.

# Security Concerns
DNS uses UDP. No connections, stateless.
## Problem
- with UDP, the `resolver` does not know which udp message belongs to which query.
  - 1 solution is that we can tag each UDP with a query id. But this is not good enough.
- attacker can just spam `resolver` with udp packets with random query id, ip address and port. the ip address could be malicious.

This is called `DNS Poisoning`.

## Solution: `DNS Security Extensions` (DNSSEC)

`DNSSEC` strengthens authentication in `DNS` using digital signatures based on public key cryptography. With `DNSSEC`, it's not `DNS` queries and responses themselves that are cryptographically signed, but rather DNS data itself is signed by the owner of the data.

Each DNS server/zone has a public/private key pair.

- the zone's private key is used to sign incoming DNS data and generate digital signatures over that data.
- The zone's public key is published in the zone itself for anyone to retrieve. Any recursive resolver that looks up data in the zone also retrieves the zone's public key, which it uses to validate the authenticity of the DNS data.

DNSSEC adds two important features to the DNS protocol:
- Data origin authentication allows a resolver to cryptographically verify that the data it received actually came from the zone where it believes the data originated.
- Data integrity protection allows the resolver to know that the data hasn't been modified in transit since it was originally signed by the zone owner with the zone's private key.

can read up more at https://www.icann.org/resources/pages/dnssec-what-is-it-why-important-2019-03-05-en). Good article.