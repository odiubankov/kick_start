load(":cc_toolchain_config.bzl", "cc_toolchain_config")

package(default_visibility = ["//visibility:public"])

cc_toolchain_suite(
    name = "clang_suite",
    toolchains = {
        "local": ":local_toolchain",
    },
)

filegroup(name = "empty")

cc_toolchain(
    name = "local_toolchain",
    toolchain_identifier = "local-toolchain",
    toolchain_config = ":local_toolchain_config",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
)

cc_toolchain_config(name = "local_toolchain_config")
