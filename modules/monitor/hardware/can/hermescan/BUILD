load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "hermescan_checker_lib",
    srcs = [
        "hermescan_checker.cc",
        "hermescan_test.cc",
    ],
    hdrs = [
	"hermescan_checker.h",
	"hermescan_test.h",
    ],
    deps = [
        "//modules/common:log",
        "//modules/common:macro",
        "//modules/common/util:string_util",
        "//modules/monitor/hardware:hardware_checker",
        "@adv_plat//:adv_plat",
    ],
)

cpplint()
