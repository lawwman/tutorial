# what is this for?
the `go` language itself is fairly straight forward for developers. but the code organisation and how packages are managed might be a bit confusing. hence im writing this for myself to rmb.

# terminologies
- `package` is a collection of `.go` files in the same dir that are `compiled tgt`
- `module` is a collection of related Go packages that are `released tgt`

# working with packages
When you build reusable pieces of code, you will develop a package as a shared library. But when you develop executable programs, you will use the package “main” for making the package as an executable program.

## `main`
The package “main” tells the Go compiler that the package should compile as an executable program instead of a shared library. The main function in the package “main” will be the entry point of our executable program. When you build shared libraries, you will not have any main package and main function in the package.
```
package main

import "fmt"

func main() {
  fmt.Println("Hello, world.")
}
```
When you import packages (like `import "fmt"`), the Go compiler will look on the locations specified by the environment variable GOROOT and GOPATH. Packages from the standard library are available in the GOROOT location. The packages that are created by yourself, and third-party packages which you have imported, are available in the GOPATH location.

sources:
- https://thenewstack.io/understanding-golang-packages/ (quite a good read)

# working with modules
a module typically contains a `go.mod` file. `go.mod` is a file that acts like a `requirements.txt` (if you have python background). It helps to track what other modules/dependencies your module requires. just like your typical `requirements.txt` or `package.json`, it should be version controlled in your repo as well.

this can be created with `go mod init <module path>`. more on [what to name the module](https://go.dev/doc/modules/managing-dependencies#naming_module).

`<module path>` is used to prefix for all packages within the module. e.g: module C has a `module path` called "example/moduleC". to refer to a package A in module C, i might write something like "example/moduleC/packageA". (`<module path>/<package path within module>`)

the `module path` of a module also indicates a location for `go` to figure out where to download said module. often the `module path` is also the url to the git repo.

example `go.mod`:
```
module github.com/grafana/phlare

go 1.18

require (
	github.com/bufbuild/connect-go v1.0.0
	github.com/bufbuild/connect-grpchealth-go v0.1.0
)
```
something useful with this is `go mod tidy`. it ensures that the go.mod file matches the source code in the module. It adds any missing module requirements necessary to build the current module’s packages and dependencies, and it removes requirements on modules that don’t provide any relevant packages. It also adds any missing entries to `go.sum` and removes unnecessary entries.

what is `go.sum`? the `go.mod` file is enough for a successful build. They why go.sum file is needed?. The checksum present in `go.sum` file is used to validate the checksum of each of direct and indirect dependency to confirm that none of them has been modified.

example `go.sum`:
```
github.com/google/uuid v1.0.0 h1:b4Gk+7WdP/d3HZH8EJsZpvV7EtDOgaZLtnaNGIu1adA=
github.com/google/uuid v1.0.0/go.mod h1:TIyPZe4MgqvfeYDBFedMoGGpEw/LqOeaOT+nhxU+yHo=
github.com/pborman/uuid v1.2.1 h1:+ZZIw58t/ozdjRaXh/3awHfmWRbzYxJoAdNJxe/3pvw=
github.com/pborman/uuid v1.2.1/go.mod h1:X/NO0urCmaxf9VXbdlT7C2Yzkj2IKimNn4k+gtPdI/k=
```

# go build, install, get

[build vs install](https://stackoverflow.com/questions/30612611/what-does-go-build-build-go-build-vs-go-install)

`go get` fetches the src code (e.g. from github) into `GOPATH/pkg`.