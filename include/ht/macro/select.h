// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include "ht/macro/expand.hpp"

// select an argument, index is 1-based
#define HT_SELECT(i, ...) HT_EXPAND(HT_SELECT_I(i, __VA_ARGS__))

#define HT_SELECT_I(i, ...) \
  HT_EXPAND(HT_UNDERLIND_CONCAT(HT_SELECT_II, i)(__VA_ARGS__))

// impl {{{
#define HT_SELECT_II_0(...)
#define HT_SELECT_II_1(a0, ...) a0
#define HT_SELECT_II_2(a0, a1, ...) a1
#define HT_SELECT_II_3(a0, a1, a2, ...) a2
#define HT_SELECT_II_4(a0, a1, a2, a3, ...) a3
#define HT_SELECT_II_5(a0, a1, a2, a3, a4, ...) a4
#define HT_SELECT_II_6(a0, a1, a2, a3, a4, a5, ...) a5
#define HT_SELECT_II_7(a0, a1, a2, a3, a4, a5, a6, ...) a6
#define HT_SELECT_II_8(a0, a1, a2, a3, a4, a5, a6, a7, ...) a7
#define HT_SELECT_II_9(a0, a1, a2, a3, a4, a5, a6, a7, a8, ...) a8
#define HT_SELECT_II_10(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) a9
#define HT_SELECT_II_11(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a10
#define HT_SELECT_II_12(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) \
  a11
#define HT_SELECT_II_13(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       ...)                                                   \
  a12
#define HT_SELECT_II_14(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, ...)                                              \
  a13
#define HT_SELECT_II_15(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, ...)                                         \
  a14
#define HT_SELECT_II_16(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, ...)                                    \
  a15
#define HT_SELECT_II_17(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, ...)                               \
  a16
#define HT_SELECT_II_18(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, ...)                          \
  a17
#define HT_SELECT_II_19(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, ...)                     \
  a18
#define HT_SELECT_II_20(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, ...)                \
  a19
#define HT_SELECT_II_21(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, ...)           \
  a20
#define HT_SELECT_II_22(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, ...)      \
  a21
#define HT_SELECT_II_23(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, ...) \
  a22
#define HT_SELECT_II_24(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       ...)                                                   \
  a23
#define HT_SELECT_II_25(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, ...)                                              \
  a24
#define HT_SELECT_II_26(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, ...)                                         \
  a25
#define HT_SELECT_II_27(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, ...)                                    \
  a26
#define HT_SELECT_II_28(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, ...)                               \
  a27
#define HT_SELECT_II_29(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, ...)                          \
  a28
#define HT_SELECT_II_30(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, ...)                     \
  a29
#define HT_SELECT_II_31(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, ...)                \
  a30
#define HT_SELECT_II_32(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, ...)           \
  a31
#define HT_SELECT_II_33(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, ...)      \
  a32
#define HT_SELECT_II_34(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, ...) \
  a33
#define HT_SELECT_II_35(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       ...)                                                   \
  a34
#define HT_SELECT_II_36(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, ...)                                              \
  a35
#define HT_SELECT_II_37(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, ...)                                         \
  a36
#define HT_SELECT_II_38(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, ...)                                    \
  a37
#define HT_SELECT_II_39(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, ...)                               \
  a38
#define HT_SELECT_II_40(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, ...)                          \
  a39
#define HT_SELECT_II_41(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, ...)                     \
  a40
#define HT_SELECT_II_42(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, ...)                \
  a41
#define HT_SELECT_II_43(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, ...)           \
  a42
#define HT_SELECT_II_44(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, ...)      \
  a43
#define HT_SELECT_II_45(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, ...) \
  a44
#define HT_SELECT_II_46(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, ...) \
  a45
#define HT_SELECT_II_47(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, ...)                                              \
  a46
#define HT_SELECT_II_48(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, ...)                                         \
  a47
#define HT_SELECT_II_49(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, ...)                                    \
  a48
#define HT_SELECT_II_50(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, a49, ...)                               \
  a49
#define HT_SELECT_II_51(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, a49, a50, ...)                          \
  a50
#define HT_SELECT_II_52(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, a49, a50, a51, ...)                     \
  a51
#define HT_SELECT_II_53(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, a49, a50, a51, a52, ...)                \
  a52
#define HT_SELECT_II_54(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, a49, a50, a51, a52, a53, ...)           \
  a53
#define HT_SELECT_II_55(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, a49, a50, a51, a52, a53, a54, ...)      \
  a54
#define HT_SELECT_II_56(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, a49, a50, a51, a52, a53, a54, a55, ...) \
  a55
#define HT_SELECT_II_57(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, ...)                     \
  a56
#define HT_SELECT_II_58(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, ...)                \
  a57
#define HT_SELECT_II_59(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, ...)           \
  a58
#define HT_SELECT_II_60(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, ...)      \
  a59
#define HT_SELECT_II_61(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, ...) \
  a60
#define HT_SELECT_II_62(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, \
                       a57, a58, a59, a60, a61, ...)                          \
  a61
#define HT_SELECT_II_63(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, \
                       a57, a58, a59, a60, a61, a62, ...)                     \
  a62
#define HT_SELECT_II_64(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, \
                       a57, a58, a59, a60, a61, a62, a63, ...)                \
  a63
#define HT_SELECT_II_65(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, \
                       a57, a58, a59, a60, a61, a62, a63, a64, ...)           \
  a64
#define HT_SELECT_II_66(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, \
                       a57, a58, a59, a60, a61, a62, a63, a64, a65, ...)      \
  a65
#define HT_SELECT_II_67(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, \
                       a57, a58, a59, a60, a61, a62, a63, a64, a65, a66, ...) \
  a66
#define HT_SELECT_II_68(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, ...)                                         \
  a67
#define HT_SELECT_II_69(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, ...)                                    \
  a68
#define HT_SELECT_II_70(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, ...)                               \
  a69
#define HT_SELECT_II_71(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, ...)                          \
  a70
#define HT_SELECT_II_72(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, ...)                     \
  a71
#define HT_SELECT_II_73(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, ...)                \
  a72
#define HT_SELECT_II_74(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, ...)           \
  a73
#define HT_SELECT_II_75(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, ...)      \
  a74
#define HT_SELECT_II_76(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, ...) \
  a75
#define HT_SELECT_II_77(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, \
                       a57, a58, a59, a60, a61, a62, a63, a64, a65, a66, a67, \
                       a68, a69, a70, a71, a72, a73, a74, a75, a76, ...)      \
  a76
#define HT_SELECT_II_78(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
                       a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, \
                       a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, \
                       a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, \
                       a46, a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, \
                       a57, a58, a59, a60, a61, a62, a63, a64, a65, a66, a67, \
                       a68, a69, a70, a71, a72, a73, a74, a75, a76, a77, ...) \
  a77
#define HT_SELECT_II_79(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, ...)                                                             \
  a78
#define HT_SELECT_II_80(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, ...)                                                        \
  a79
#define HT_SELECT_II_81(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, ...)                                                   \
  a80
#define HT_SELECT_II_82(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, ...)                                              \
  a81
#define HT_SELECT_II_83(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, ...)                                         \
  a82
#define HT_SELECT_II_84(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, ...)                                    \
  a83
#define HT_SELECT_II_85(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, ...)                               \
  a84
#define HT_SELECT_II_86(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, ...)                          \
  a85
#define HT_SELECT_II_87(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, ...)                     \
  a86
#define HT_SELECT_II_88(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, ...)                \
  a87
#define HT_SELECT_II_89(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, ...)           \
  a88
#define HT_SELECT_II_90(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, ...)      \
  a89
#define HT_SELECT_II_91(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, ...) \
  a90
#define HT_SELECT_II_92(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    ...)                                                                       \
  a91
#define HT_SELECT_II_93(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, ...)                                                                  \
  a92
#define HT_SELECT_II_94(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, ...)                                                             \
  a93
#define HT_SELECT_II_95(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, ...)                                                        \
  a94
#define HT_SELECT_II_96(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, ...)                                                   \
  a95
#define HT_SELECT_II_97(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, ...)                                              \
  a96
#define HT_SELECT_II_98(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, ...)                                         \
  a97
#define HT_SELECT_II_99(                                                        \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, ...)                                    \
  a98
#define HT_SELECT_II_100(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, ...)                               \
  a99
#define HT_SELECT_II_101(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, ...)                         \
  a100
#define HT_SELECT_II_102(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, ...)                   \
  a101
#define HT_SELECT_II_103(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, ...)             \
  a102
#define HT_SELECT_II_104(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, ...)       \
  a103
#define HT_SELECT_II_105(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104, ...) \
  a104
#define HT_SELECT_II_106(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, ...)                                                                 \
  a105
#define HT_SELECT_II_107(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, ...)                                                           \
  a106
#define HT_SELECT_II_108(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, ...)                                                     \
  a107
#define HT_SELECT_II_109(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, ...)                                               \
  a108
#define HT_SELECT_II_110(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, ...)                                         \
  a109
#define HT_SELECT_II_111(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, ...)                                   \
  a110
#define HT_SELECT_II_112(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, ...)                             \
  a111
#define HT_SELECT_II_113(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, ...)                       \
  a112
#define HT_SELECT_II_114(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, ...)                 \
  a113
#define HT_SELECT_II_115(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, ...)           \
  a114
#define HT_SELECT_II_116(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, ...)     \
  a115
#define HT_SELECT_II_117(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116,    \
    ...)                                                                       \
  a116
#define HT_SELECT_II_118(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116,    \
    a117, ...)                                                                 \
  a117
#define HT_SELECT_II_119(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116,    \
    a117, a118, ...)                                                           \
  a118
#define HT_SELECT_II_120(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116,    \
    a117, a118, a119, ...)                                                     \
  a119
#define HT_SELECT_II_121(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116,    \
    a117, a118, a119, a120, ...)                                               \
  a120
#define HT_SELECT_II_122(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116,    \
    a117, a118, a119, a120, a121, ...)                                         \
  a121
#define HT_SELECT_II_123(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116,    \
    a117, a118, a119, a120, a121, a122, ...)                                   \
  a122
#define HT_SELECT_II_124(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116,    \
    a117, a118, a119, a120, a121, a122, a123, ...)                             \
  a123
#define HT_SELECT_II_125(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116,    \
    a117, a118, a119, a120, a121, a122, a123, a124, ...)                       \
  a124
#define HT_SELECT_II_126(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116,    \
    a117, a118, a119, a120, a121, a122, a123, a124, a125, ...)                 \
  a125
#define HT_SELECT_II_127(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116,    \
    a117, a118, a119, a120, a121, a122, a123, a124, a125, a126, ...)           \
  a126
#define HT_SELECT_II_128(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116,    \
    a117, a118, a119, a120, a121, a122, a123, a124, a125, a126, a127, ...)     \
  a127
#define HT_SELECT_II_129(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116,    \
    a117, a118, a119, a120, a121, a122, a123, a124, a125, a126, a127, a128,    \
    ...)                                                                       \
  a128
#define HT_SELECT_II_130(                                                       \
    a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116,    \
    a117, a118, a119, a120, a121, a122, a123, a124, a125, a126, a127, a128,    \
    a129, ...)                                                                 \
  a129
// }}}

// vim: fdm=marker

