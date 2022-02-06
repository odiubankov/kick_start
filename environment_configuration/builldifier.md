# How to setup bazel buildifier

Install go
```
sudo snap install go --classic
```

Check the go installation path
```
go env GOPATH
```

Add go bin to the PATH in .bashrc
```
PATH=$PATH:~/go/bin
```

Install buildifier
```
go install github.com/bazelbuild/buildtools/buildifier@latest
```

Use buildifier
```
buildifier /path/to/BUILD
```
