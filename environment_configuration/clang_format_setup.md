# How to setup clang-format in project and integrate it in vscode

Install clang-format

```
sudo apt install clang-format
```

Create a configuration file and put it to your project root directory. Some pre-defined configurations are available e.g. google, chromium, llvm, etc.

```
clang-format -style=google -dump-config > ./.clang-format
```

Setup integration in vscode. Launch VS Code Quick Open (Ctrl+P) and enter
```
ext install xaver.clang-format
```

Update settings to run formatting on save and use clang-format as default formatter

```
// ~/.config/Code/User/settings.json
{
    "editor.formatOnSave": true,
    "clang-format.executable": "/usr/bin/clang-format",
    "[cpp]": {
        "editor.defaultFormatter": "xaver.clang-format"
    }
}
```