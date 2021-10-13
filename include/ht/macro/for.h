// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#pragma once  // NOLINT(build/header_guard)

#include "ht/macro/expand.hpp"

/**
 * HT_FOR(count, action, sep, ...)
 *
 * action(1, __VA_ARGS__)
 * sep()
 * action(2, __VA_ARGS__)
 * sep()
 * ...
 */
#define HT_FOR(...) HT_EXPAND(_HT_FOR_I(__VA_ARGS__))

// impl {{{
#define _HT_FOR_I(iters, action, sep, ...) \
  HT_UNDERLIND_CONCAT(_HT_FOR_II, iters)(action, sep, __VA_ARGS__)

#define _HT_FOR_II_0(...)
#define _HT_FOR_II_1(action, sep, ...) action(1, ##__VA_ARGS__)
#define _HT_FOR_II_2(action, sep, ...) \
  _HT_FOR_II_1(action, sep, ##__VA_ARGS__) sep() action(2, ##__VA_ARGS__)
#define _HT_FOR_II_3(action, sep, ...) \
  _HT_FOR_II_2(action, sep, ##__VA_ARGS__) sep() action(3, ##__VA_ARGS__)
#define _HT_FOR_II_4(action, sep, ...) \
  _HT_FOR_II_3(action, sep, ##__VA_ARGS__) sep() action(4, ##__VA_ARGS__)
#define _HT_FOR_II_5(action, sep, ...) \
  _HT_FOR_II_4(action, sep, ##__VA_ARGS__) sep() action(5, ##__VA_ARGS__)
#define _HT_FOR_II_6(action, sep, ...) \
  _HT_FOR_II_5(action, sep, ##__VA_ARGS__) sep() action(6, ##__VA_ARGS__)
#define _HT_FOR_II_7(action, sep, ...) \
  _HT_FOR_II_6(action, sep, ##__VA_ARGS__) sep() action(7, ##__VA_ARGS__)
#define _HT_FOR_II_8(action, sep, ...) \
  _HT_FOR_II_7(action, sep, ##__VA_ARGS__) sep() action(8, ##__VA_ARGS__)
#define _HT_FOR_II_9(action, sep, ...) \
  _HT_FOR_II_8(action, sep, ##__VA_ARGS__) sep() action(9, ##__VA_ARGS__)
#define _HT_FOR_II_10(action, sep, ...) \
  _HT_FOR_II_9(action, sep, ##__VA_ARGS__) sep() action(10, ##__VA_ARGS__)
#define _HT_FOR_II_11(action, sep, ...) \
  _HT_FOR_II_10(action, sep, ##__VA_ARGS__) sep() action(11, ##__VA_ARGS__)
#define _HT_FOR_II_12(action, sep, ...) \
  _HT_FOR_II_11(action, sep, ##__VA_ARGS__) sep() action(12, ##__VA_ARGS__)
#define _HT_FOR_II_13(action, sep, ...) \
  _HT_FOR_II_12(action, sep, ##__VA_ARGS__) sep() action(13, ##__VA_ARGS__)
#define _HT_FOR_II_14(action, sep, ...) \
  _HT_FOR_II_13(action, sep, ##__VA_ARGS__) sep() action(14, ##__VA_ARGS__)
#define _HT_FOR_II_15(action, sep, ...) \
  _HT_FOR_II_14(action, sep, ##__VA_ARGS__) sep() action(15, ##__VA_ARGS__)
#define _HT_FOR_II_16(action, sep, ...) \
  _HT_FOR_II_15(action, sep, ##__VA_ARGS__) sep() action(16, ##__VA_ARGS__)
#define _HT_FOR_II_17(action, sep, ...) \
  _HT_FOR_II_16(action, sep, ##__VA_ARGS__) sep() action(17, ##__VA_ARGS__)
#define _HT_FOR_II_18(action, sep, ...) \
  _HT_FOR_II_17(action, sep, ##__VA_ARGS__) sep() action(18, ##__VA_ARGS__)
#define _HT_FOR_II_19(action, sep, ...) \
  _HT_FOR_II_18(action, sep, ##__VA_ARGS__) sep() action(19, ##__VA_ARGS__)
#define _HT_FOR_II_20(action, sep, ...) \
  _HT_FOR_II_19(action, sep, ##__VA_ARGS__) sep() action(20, ##__VA_ARGS__)
#define _HT_FOR_II_21(action, sep, ...) \
  _HT_FOR_II_20(action, sep, ##__VA_ARGS__) sep() action(21, ##__VA_ARGS__)
#define _HT_FOR_II_22(action, sep, ...) \
  _HT_FOR_II_21(action, sep, ##__VA_ARGS__) sep() action(22, ##__VA_ARGS__)
#define _HT_FOR_II_23(action, sep, ...) \
  _HT_FOR_II_22(action, sep, ##__VA_ARGS__) sep() action(23, ##__VA_ARGS__)
#define _HT_FOR_II_24(action, sep, ...) \
  _HT_FOR_II_23(action, sep, ##__VA_ARGS__) sep() action(24, ##__VA_ARGS__)
#define _HT_FOR_II_25(action, sep, ...) \
  _HT_FOR_II_24(action, sep, ##__VA_ARGS__) sep() action(25, ##__VA_ARGS__)
#define _HT_FOR_II_26(action, sep, ...) \
  _HT_FOR_II_25(action, sep, ##__VA_ARGS__) sep() action(26, ##__VA_ARGS__)
#define _HT_FOR_II_27(action, sep, ...) \
  _HT_FOR_II_26(action, sep, ##__VA_ARGS__) sep() action(27, ##__VA_ARGS__)
#define _HT_FOR_II_28(action, sep, ...) \
  _HT_FOR_II_27(action, sep, ##__VA_ARGS__) sep() action(28, ##__VA_ARGS__)
#define _HT_FOR_II_29(action, sep, ...) \
  _HT_FOR_II_28(action, sep, ##__VA_ARGS__) sep() action(29, ##__VA_ARGS__)
#define _HT_FOR_II_30(action, sep, ...) \
  _HT_FOR_II_29(action, sep, ##__VA_ARGS__) sep() action(30, ##__VA_ARGS__)
#define _HT_FOR_II_31(action, sep, ...) \
  _HT_FOR_II_30(action, sep, ##__VA_ARGS__) sep() action(31, ##__VA_ARGS__)
#define _HT_FOR_II_32(action, sep, ...) \
  _HT_FOR_II_31(action, sep, ##__VA_ARGS__) sep() action(32, ##__VA_ARGS__)
#define _HT_FOR_II_33(action, sep, ...) \
  _HT_FOR_II_32(action, sep, ##__VA_ARGS__) sep() action(33, ##__VA_ARGS__)
#define _HT_FOR_II_34(action, sep, ...) \
  _HT_FOR_II_33(action, sep, ##__VA_ARGS__) sep() action(34, ##__VA_ARGS__)
#define _HT_FOR_II_35(action, sep, ...) \
  _HT_FOR_II_34(action, sep, ##__VA_ARGS__) sep() action(35, ##__VA_ARGS__)
#define _HT_FOR_II_36(action, sep, ...) \
  _HT_FOR_II_35(action, sep, ##__VA_ARGS__) sep() action(36, ##__VA_ARGS__)
#define _HT_FOR_II_37(action, sep, ...) \
  _HT_FOR_II_36(action, sep, ##__VA_ARGS__) sep() action(37, ##__VA_ARGS__)
#define _HT_FOR_II_38(action, sep, ...) \
  _HT_FOR_II_37(action, sep, ##__VA_ARGS__) sep() action(38, ##__VA_ARGS__)
#define _HT_FOR_II_39(action, sep, ...) \
  _HT_FOR_II_38(action, sep, ##__VA_ARGS__) sep() action(39, ##__VA_ARGS__)
#define _HT_FOR_II_40(action, sep, ...) \
  _HT_FOR_II_39(action, sep, ##__VA_ARGS__) sep() action(40, ##__VA_ARGS__)
#define _HT_FOR_II_41(action, sep, ...) \
  _HT_FOR_II_40(action, sep, ##__VA_ARGS__) sep() action(41, ##__VA_ARGS__)
#define _HT_FOR_II_42(action, sep, ...) \
  _HT_FOR_II_41(action, sep, ##__VA_ARGS__) sep() action(42, ##__VA_ARGS__)
#define _HT_FOR_II_43(action, sep, ...) \
  _HT_FOR_II_42(action, sep, ##__VA_ARGS__) sep() action(43, ##__VA_ARGS__)
#define _HT_FOR_II_44(action, sep, ...) \
  _HT_FOR_II_43(action, sep, ##__VA_ARGS__) sep() action(44, ##__VA_ARGS__)
#define _HT_FOR_II_45(action, sep, ...) \
  _HT_FOR_II_44(action, sep, ##__VA_ARGS__) sep() action(45, ##__VA_ARGS__)
#define _HT_FOR_II_46(action, sep, ...) \
  _HT_FOR_II_45(action, sep, ##__VA_ARGS__) sep() action(46, ##__VA_ARGS__)
#define _HT_FOR_II_47(action, sep, ...) \
  _HT_FOR_II_46(action, sep, ##__VA_ARGS__) sep() action(47, ##__VA_ARGS__)
#define _HT_FOR_II_48(action, sep, ...) \
  _HT_FOR_II_47(action, sep, ##__VA_ARGS__) sep() action(48, ##__VA_ARGS__)
#define _HT_FOR_II_49(action, sep, ...) \
  _HT_FOR_II_48(action, sep, ##__VA_ARGS__) sep() action(49, ##__VA_ARGS__)
#define _HT_FOR_II_50(action, sep, ...) \
  _HT_FOR_II_49(action, sep, ##__VA_ARGS__) sep() action(50, ##__VA_ARGS__)
#define _HT_FOR_II_51(action, sep, ...) \
  _HT_FOR_II_50(action, sep, ##__VA_ARGS__) sep() action(51, ##__VA_ARGS__)
#define _HT_FOR_II_52(action, sep, ...) \
  _HT_FOR_II_51(action, sep, ##__VA_ARGS__) sep() action(52, ##__VA_ARGS__)
#define _HT_FOR_II_53(action, sep, ...) \
  _HT_FOR_II_52(action, sep, ##__VA_ARGS__) sep() action(53, ##__VA_ARGS__)
#define _HT_FOR_II_54(action, sep, ...) \
  _HT_FOR_II_53(action, sep, ##__VA_ARGS__) sep() action(54, ##__VA_ARGS__)
#define _HT_FOR_II_55(action, sep, ...) \
  _HT_FOR_II_54(action, sep, ##__VA_ARGS__) sep() action(55, ##__VA_ARGS__)
#define _HT_FOR_II_56(action, sep, ...) \
  _HT_FOR_II_55(action, sep, ##__VA_ARGS__) sep() action(56, ##__VA_ARGS__)
#define _HT_FOR_II_57(action, sep, ...) \
  _HT_FOR_II_56(action, sep, ##__VA_ARGS__) sep() action(57, ##__VA_ARGS__)
#define _HT_FOR_II_58(action, sep, ...) \
  _HT_FOR_II_57(action, sep, ##__VA_ARGS__) sep() action(58, ##__VA_ARGS__)
#define _HT_FOR_II_59(action, sep, ...) \
  _HT_FOR_II_58(action, sep, ##__VA_ARGS__) sep() action(59, ##__VA_ARGS__)
#define _HT_FOR_II_60(action, sep, ...) \
  _HT_FOR_II_59(action, sep, ##__VA_ARGS__) sep() action(60, ##__VA_ARGS__)
#define _HT_FOR_II_61(action, sep, ...) \
  _HT_FOR_II_60(action, sep, ##__VA_ARGS__) sep() action(61, ##__VA_ARGS__)
#define _HT_FOR_II_62(action, sep, ...) \
  _HT_FOR_II_61(action, sep, ##__VA_ARGS__) sep() action(62, ##__VA_ARGS__)
#define _HT_FOR_II_63(action, sep, ...) \
  _HT_FOR_II_62(action, sep, ##__VA_ARGS__) sep() action(63, ##__VA_ARGS__)
#define _HT_FOR_II_64(action, sep, ...) \
  _HT_FOR_II_63(action, sep, ##__VA_ARGS__) sep() action(64, ##__VA_ARGS__)
#define _HT_FOR_II_65(action, sep, ...) \
  _HT_FOR_II_64(action, sep, ##__VA_ARGS__) sep() action(65, ##__VA_ARGS__)
#define _HT_FOR_II_66(action, sep, ...) \
  _HT_FOR_II_65(action, sep, ##__VA_ARGS__) sep() action(66, ##__VA_ARGS__)
#define _HT_FOR_II_67(action, sep, ...) \
  _HT_FOR_II_66(action, sep, ##__VA_ARGS__) sep() action(67, ##__VA_ARGS__)
#define _HT_FOR_II_68(action, sep, ...) \
  _HT_FOR_II_67(action, sep, ##__VA_ARGS__) sep() action(68, ##__VA_ARGS__)
#define _HT_FOR_II_69(action, sep, ...) \
  _HT_FOR_II_68(action, sep, ##__VA_ARGS__) sep() action(69, ##__VA_ARGS__)
#define _HT_FOR_II_70(action, sep, ...) \
  _HT_FOR_II_69(action, sep, ##__VA_ARGS__) sep() action(70, ##__VA_ARGS__)
#define _HT_FOR_II_71(action, sep, ...) \
  _HT_FOR_II_70(action, sep, ##__VA_ARGS__) sep() action(71, ##__VA_ARGS__)
#define _HT_FOR_II_72(action, sep, ...) \
  _HT_FOR_II_71(action, sep, ##__VA_ARGS__) sep() action(72, ##__VA_ARGS__)
#define _HT_FOR_II_73(action, sep, ...) \
  _HT_FOR_II_72(action, sep, ##__VA_ARGS__) sep() action(73, ##__VA_ARGS__)
#define _HT_FOR_II_74(action, sep, ...) \
  _HT_FOR_II_73(action, sep, ##__VA_ARGS__) sep() action(74, ##__VA_ARGS__)
#define _HT_FOR_II_75(action, sep, ...) \
  _HT_FOR_II_74(action, sep, ##__VA_ARGS__) sep() action(75, ##__VA_ARGS__)
#define _HT_FOR_II_76(action, sep, ...) \
  _HT_FOR_II_75(action, sep, ##__VA_ARGS__) sep() action(76, ##__VA_ARGS__)
#define _HT_FOR_II_77(action, sep, ...) \
  _HT_FOR_II_76(action, sep, ##__VA_ARGS__) sep() action(77, ##__VA_ARGS__)
#define _HT_FOR_II_78(action, sep, ...) \
  _HT_FOR_II_77(action, sep, ##__VA_ARGS__) sep() action(78, ##__VA_ARGS__)
#define _HT_FOR_II_79(action, sep, ...) \
  _HT_FOR_II_78(action, sep, ##__VA_ARGS__) sep() action(79, ##__VA_ARGS__)
#define _HT_FOR_II_80(action, sep, ...) \
  _HT_FOR_II_79(action, sep, ##__VA_ARGS__) sep() action(80, ##__VA_ARGS__)
#define _HT_FOR_II_81(action, sep, ...) \
  _HT_FOR_II_80(action, sep, ##__VA_ARGS__) sep() action(81, ##__VA_ARGS__)
#define _HT_FOR_II_82(action, sep, ...) \
  _HT_FOR_II_81(action, sep, ##__VA_ARGS__) sep() action(82, ##__VA_ARGS__)
#define _HT_FOR_II_83(action, sep, ...) \
  _HT_FOR_II_82(action, sep, ##__VA_ARGS__) sep() action(83, ##__VA_ARGS__)
#define _HT_FOR_II_84(action, sep, ...) \
  _HT_FOR_II_83(action, sep, ##__VA_ARGS__) sep() action(84, ##__VA_ARGS__)
#define _HT_FOR_II_85(action, sep, ...) \
  _HT_FOR_II_84(action, sep, ##__VA_ARGS__) sep() action(85, ##__VA_ARGS__)
#define _HT_FOR_II_86(action, sep, ...) \
  _HT_FOR_II_85(action, sep, ##__VA_ARGS__) sep() action(86, ##__VA_ARGS__)
#define _HT_FOR_II_87(action, sep, ...) \
  _HT_FOR_II_86(action, sep, ##__VA_ARGS__) sep() action(87, ##__VA_ARGS__)
#define _HT_FOR_II_88(action, sep, ...) \
  _HT_FOR_II_87(action, sep, ##__VA_ARGS__) sep() action(88, ##__VA_ARGS__)
#define _HT_FOR_II_89(action, sep, ...) \
  _HT_FOR_II_88(action, sep, ##__VA_ARGS__) sep() action(89, ##__VA_ARGS__)
#define _HT_FOR_II_90(action, sep, ...) \
  _HT_FOR_II_89(action, sep, ##__VA_ARGS__) sep() action(90, ##__VA_ARGS__)
#define _HT_FOR_II_91(action, sep, ...) \
  _HT_FOR_II_90(action, sep, ##__VA_ARGS__) sep() action(91, ##__VA_ARGS__)
#define _HT_FOR_II_92(action, sep, ...) \
  _HT_FOR_II_91(action, sep, ##__VA_ARGS__) sep() action(92, ##__VA_ARGS__)
#define _HT_FOR_II_93(action, sep, ...) \
  _HT_FOR_II_92(action, sep, ##__VA_ARGS__) sep() action(93, ##__VA_ARGS__)
#define _HT_FOR_II_94(action, sep, ...) \
  _HT_FOR_II_93(action, sep, ##__VA_ARGS__) sep() action(94, ##__VA_ARGS__)
#define _HT_FOR_II_95(action, sep, ...) \
  _HT_FOR_II_94(action, sep, ##__VA_ARGS__) sep() action(95, ##__VA_ARGS__)
#define _HT_FOR_II_96(action, sep, ...) \
  _HT_FOR_II_95(action, sep, ##__VA_ARGS__) sep() action(96, ##__VA_ARGS__)
#define _HT_FOR_II_97(action, sep, ...) \
  _HT_FOR_II_96(action, sep, ##__VA_ARGS__) sep() action(97, ##__VA_ARGS__)
#define _HT_FOR_II_98(action, sep, ...) \
  _HT_FOR_II_97(action, sep, ##__VA_ARGS__) sep() action(98, ##__VA_ARGS__)
#define _HT_FOR_II_99(action, sep, ...) \
  _HT_FOR_II_98(action, sep, ##__VA_ARGS__) sep() action(99, ##__VA_ARGS__)
#define _HT_FOR_II_100(action, sep, ...) \
  _HT_FOR_II_99(action, sep, ##__VA_ARGS__) sep() action(100, ##__VA_ARGS__)
#define _HT_FOR_II_101(action, sep, ...) \
  _HT_FOR_II_100(action, sep, ##__VA_ARGS__) sep() action(101, ##__VA_ARGS__)
#define _HT_FOR_II_102(action, sep, ...) \
  _HT_FOR_II_101(action, sep, ##__VA_ARGS__) sep() action(102, ##__VA_ARGS__)
#define _HT_FOR_II_103(action, sep, ...) \
  _HT_FOR_II_102(action, sep, ##__VA_ARGS__) sep() action(103, ##__VA_ARGS__)
#define _HT_FOR_II_104(action, sep, ...) \
  _HT_FOR_II_103(action, sep, ##__VA_ARGS__) sep() action(104, ##__VA_ARGS__)
#define _HT_FOR_II_105(action, sep, ...) \
  _HT_FOR_II_104(action, sep, ##__VA_ARGS__) sep() action(105, ##__VA_ARGS__)
#define _HT_FOR_II_106(action, sep, ...) \
  _HT_FOR_II_105(action, sep, ##__VA_ARGS__) sep() action(106, ##__VA_ARGS__)
#define _HT_FOR_II_107(action, sep, ...) \
  _HT_FOR_II_106(action, sep, ##__VA_ARGS__) sep() action(107, ##__VA_ARGS__)
#define _HT_FOR_II_108(action, sep, ...) \
  _HT_FOR_II_107(action, sep, ##__VA_ARGS__) sep() action(108, ##__VA_ARGS__)
#define _HT_FOR_II_109(action, sep, ...) \
  _HT_FOR_II_108(action, sep, ##__VA_ARGS__) sep() action(109, ##__VA_ARGS__)
#define _HT_FOR_II_110(action, sep, ...) \
  _HT_FOR_II_109(action, sep, ##__VA_ARGS__) sep() action(110, ##__VA_ARGS__)
#define _HT_FOR_II_111(action, sep, ...) \
  _HT_FOR_II_110(action, sep, ##__VA_ARGS__) sep() action(111, ##__VA_ARGS__)
#define _HT_FOR_II_112(action, sep, ...) \
  _HT_FOR_II_111(action, sep, ##__VA_ARGS__) sep() action(112, ##__VA_ARGS__)
#define _HT_FOR_II_113(action, sep, ...) \
  _HT_FOR_II_112(action, sep, ##__VA_ARGS__) sep() action(113, ##__VA_ARGS__)
#define _HT_FOR_II_114(action, sep, ...) \
  _HT_FOR_II_113(action, sep, ##__VA_ARGS__) sep() action(114, ##__VA_ARGS__)
#define _HT_FOR_II_115(action, sep, ...) \
  _HT_FOR_II_114(action, sep, ##__VA_ARGS__) sep() action(115, ##__VA_ARGS__)
#define _HT_FOR_II_116(action, sep, ...) \
  _HT_FOR_II_115(action, sep, ##__VA_ARGS__) sep() action(116, ##__VA_ARGS__)
#define _HT_FOR_II_117(action, sep, ...) \
  _HT_FOR_II_116(action, sep, ##__VA_ARGS__) sep() action(117, ##__VA_ARGS__)
#define _HT_FOR_II_118(action, sep, ...) \
  _HT_FOR_II_117(action, sep, ##__VA_ARGS__) sep() action(118, ##__VA_ARGS__)
#define _HT_FOR_II_119(action, sep, ...) \
  _HT_FOR_II_118(action, sep, ##__VA_ARGS__) sep() action(119, ##__VA_ARGS__)
#define _HT_FOR_II_120(action, sep, ...) \
  _HT_FOR_II_119(action, sep, ##__VA_ARGS__) sep() action(120, ##__VA_ARGS__)
// }}}

// vim: fdm=marker
