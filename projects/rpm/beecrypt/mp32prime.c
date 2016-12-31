/** \ingroup MP_m
 * \file mp32prime.c
 *
 * Multi-precision primes, code.
 */

/*
 * Copyright (c) 2000, 2001 Virtual Unlimited B.V.
 *
 * Author: Bob Deblier <bob@virtualunlimited.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#define BEECRYPT_DLL_EXPORT

#include "mp32prime.h"
#include "mp32.h"
#include "mp32barrett.h"

#if HAVE_STDLIB_H
# include <stdlib.h>
#endif
#if HAVE_MALLOC_H
# include <malloc.h>
#endif

#include <stdio.h>

/**
 * A word of explanation here on what these tables accomplish:
 *
 * For fast checking whether a candidate prime can be divided by small primes, we use this table,
 * which contains the products of all small primes starting at 3, up to a word size equal to the size
 * of the candidate tested.
 *
 * Instead of trying each small prime in successive divisions, we compute one gcd with a product of small
 * primes from this table.
 * If the gcd result is not 1, the candidate is divisable by at least one of the small primes(*). If the gcd
 * result is 1, then we can subject the candidate to a probabilistic test.
 *
 * (*) Note: the candidate prime could also be one of the small primes, in which is it IS prime,
 * but too small to be of cryptographic interest. Hence, use only for candidate primes that are large enough.
 */

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_01[] =	/* primes 3 to 29 */
{ 0xc0cfd797 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_02[] =	/* primes 3 to 53 */
{ 0xe221f97c, 0x30e94e1d };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_03[] =	/* primes 3 to 73 */
{ 0x41cd66ac, 0xc237b226, 0x81a18067 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_04[] =	/* primes 3 to 101 */
{ 0x5797d47c, 0x51681549, 0xd734e4fc, 0x4c3eaf7f };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_05[] =	/* primes 3 to 113 */
{ 0x02c4b8d0, 0xd2e0d937, 0x3935200f, 0xb49be231,
  0x5ce1a307 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_06[] =	/* primes 3 to 149 */
{ 0x1e6d8e2a, 0x0ffceafb, 0xbcbfc14a, 0x4c3bc1e1,
  0x009c6a22, 0xa0a7adf5 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_07[] =	/* primes 3 to 167 */
{ 0x049265d3, 0x574cefd0, 0x4229bfd6, 0x62a4a46f,
  0x8611ed02, 0x26c655f0, 0x76ebade3 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_08[] =	/* primes 3 to 193 */
{ 0xdbf05b6f, 0x5654b3c0, 0xf5243551, 0x43958688,
  0x9f155887, 0x819aed2a, 0xc05b9335, 0x2be98677 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_09[] =	/* primes 3 to 223 */
{ 0x5e75cec8, 0xb5de5ea1, 0x5da8302a, 0x2f28b4ad,
  0x2735bdc3, 0x9344c52e, 0x67570925, 0x6feb71ef,
  0x6811d741 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_10[] =	/* primes 3 to 239 */
{ 0x3faa5dad, 0xb695ce58, 0x4a579328, 0xeab20f1f,
  0xef00fe27, 0xffc36456, 0x0a65723e, 0x27d8884a,
  0xd59da0a9, 0x92f77529 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_11[] =	/* primes 3 to 263 */
{ 0x3c9b6e49, 0xb7cf685b, 0xe7f3a239, 0xfb4084cb,
  0x166885e3, 0x9d4f65b4, 0x0bb0e51c, 0x0a5d36fe,
  0x98c32069, 0xfd5c441c, 0x6d82f115 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_12[] =	/* primes 3 to 281 */
{ 0x501201cc, 0x51a492a5, 0x44d3900a, 0xd4f8b32a,
  0x203c8584, 0x06a4457c, 0xab0b4f80, 0x5ab18ac6,
  0xeb9572ac, 0x6e9394fa, 0x522bffb6, 0xf44af2f3 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_13[] =	/* primes 3 to 311 */
{ 0x9397b5b4, 0x414dc331, 0x04561364, 0x79958cc8,
  0xfd5ea01f, 0x5d5e9f61, 0xbd0f1cb6, 0x24af7e6a,
  0x3284dbb2, 0x9857622b, 0x8be980a6, 0x5456a5c1,
  0xed928009 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_14[] =	/* primes 3 to 331 */
{ 0x0120eb4d, 0x70279230, 0x9ed122fc, 0xe0488be4,
  0x1d0c99f5, 0xd8c039ad, 0x058c90b4, 0x780500fe,
  0xf39c05cc, 0x09817a27, 0xc3e1776a, 0x246b6af2,
  0x946a10d6, 0x6eafaedf };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_15[] =	/* primes 3 to 353 */
{ 0x03c91dd1, 0x2e893191, 0x94095649, 0x874b41d6,
  0x05810c06, 0x195d70eb, 0xbd54a862, 0x50c52733,
  0x06dc6648, 0x1c251ca4, 0xa02c9a04, 0x78c96f0d,
  0x02f0db0b, 0x39d624ca, 0x0b0441c1 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_16[] =	/* primes 3 to 379 */
{ 0x106aa9fb, 0x7646fa6e, 0xb0813c28, 0xc5d5f09f,
  0x077ec3ba, 0x238bfb99, 0xc1b631a2, 0x03e81187,
  0x233db117, 0xcbc38405, 0x6ef04659, 0xa4a11de4,
  0x9f7ecb29, 0xbada8f98, 0x0decece9, 0x2e30c48f };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_17[] =	/* primes 3 to 401 */
{ 0x5aa88d8c, 0x594bb372, 0xc4bc813f, 0x4a87a266,
  0x1f984840, 0xdab15692, 0x2c2a177d, 0x95843665,
  0x6f36d41a, 0x11c35ccc, 0x2904b7e9, 0xc424eb61,
  0x3b3536a4, 0x0b2745bd, 0xadf1a6c9, 0x7b23e85a,
  0xdc6695c1 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_18[] =	/* primes 3 to 421 */
{ 0x0185dbeb, 0x2b8b11d3, 0x7633e9dc, 0x1eec5415,
  0x65c6ce84, 0x31d227ee, 0x28f0328a, 0x60c90118,
  0xae031cc5, 0xa781c824, 0xd1f16d25, 0xf4f0cccf,
  0xf35e9745, 0x79072ec8, 0xcaf1ac8e, 0xefd5566f,
  0xa15fb94f, 0xe34f5d37 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_19[] =	/* primes 3 to 443 */
{ 0x0cde6fd1, 0xcf108066, 0xcc548df9, 0x070e102c,
  0x2c651b88, 0x5f24f503, 0xaaffe276, 0xfeb57311,
  0x0c1e4592, 0xa35890d7, 0x678aaeee, 0x9f44800f,
  0xc43f999d, 0x5d06b89f, 0xcb22e533, 0x5a9287bc,
  0x6d75a3e9, 0x1e53906d, 0x413163d5 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_20[] =	/* primes 3 to 463 */
{ 0x833a505c, 0xf9922bee, 0xc80265a6, 0xd50e1cce,
  0xa22f6fec, 0x2eb84450, 0xcec64a3c, 0x0e10d472,
  0xdd653b9b, 0x51d81d0e, 0x3a3142ea, 0x49b91e3a,
  0x5e210232, 0x67bda426, 0x738730cf, 0xb8e6e2ae,
  0xc08c9d4b, 0xd2420066, 0xdccf95ef, 0x49a560b7 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_21[] =	/* primes 3 to 487 */
{ 0x035417f1, 0xe321c06c, 0xbe32ffce, 0xae752cc9,
  0xa9fe11a6, 0x3d94c946, 0x456edd7d, 0x5a060de1,
  0x84a826a6, 0xf0740c13, 0x48fa1038, 0x911d771d,
  0xb3773e87, 0x52300c29, 0xc82c3012, 0x131673bb,
  0x491cbd61, 0x55e565af, 0x4a9f4331, 0x0adbb0d7,
  0x06e86f6d };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_22[] =	/* primes 3 to 509 */
{ 0x309d024b, 0xd5380319, 0x2ca33469, 0x0bafb43a,
  0x0abd5840, 0xfbeb24d1, 0xf49b6330, 0x47902bae,
  0x581ca4cb, 0xa778fdb1, 0x6dc0a6af, 0xef960687,
  0x16855d95, 0x93746604, 0x201f1919, 0xb725fcb7,
  0x8ffd0db8, 0xe8fa61a1, 0x6e1c0970, 0xbeb81adc,
  0xf49c82df, 0xf960d36f };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_23[] =	/* primes 3 to 541 */
{ 0x01ab244a, 0x33bc047e, 0x804590b4, 0xc3207237,
  0xea503fa0, 0x7541b251, 0x57cfd03f, 0xf602c9d0,
  0x3dcd12ba, 0xa4947ae6, 0xc6ee61be, 0xedf6c716,
  0xfa45377d, 0x5b3c84fa, 0x5fb78b41, 0x395251eb,
  0xb6a5129c, 0x7699fb5c, 0xccec6d45, 0x56c9b8ea,
  0xfa05897c, 0xb8c5cf72, 0xb77603d9 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_24[] =	/* primes 3 to 569 */
{ 0x25eac89f, 0x8d4da338, 0x337b4985, 0x0d2d1489,
  0x2663177b, 0x4010af3d, 0xd23eeb0b, 0x228f3832,
  0xffcee2e5, 0xcbd1acc9, 0x8f47f251, 0x873380ae,
  0x10f0ffdd, 0x8e602ffa, 0x210f41f6, 0x69a1570a,
  0x93c158c1, 0xa9a8227f, 0xf81a90c5, 0x630e9c44,
  0x845c755c, 0x7df35a7d, 0x430c679a, 0x11575655 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_25[] =	/* primes 3 to 587 */
{ 0x01b515a8, 0xdca3d6e4, 0x69090373, 0x84febfe8,
  0xf32e06cf, 0x9bde8c89, 0x6b3f992f, 0x2ff23508,
  0xe1c01024, 0x3b8ad0c4, 0xac54e7c7, 0x3f4081d8,
  0xe495d54d, 0x74ed01e8, 0x9dfcbdde, 0x1fe7e61a,
  0x839bd902, 0xf43bf273, 0x2441f0ae, 0xb4211c70,
  0x6b3faafc, 0x0f200b35, 0x7485ce4a, 0x2f08f148,
  0xcce6887d };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_26[] =	/* primes 3 to 607 */
{ 0x3383219d, 0x26454f06, 0xe2789b7f, 0x9c3b940e,
  0x03be2105, 0x798e3ff7, 0x945bd325, 0x997bc262,
  0x025598f8, 0x8577748e, 0xc7155ff8, 0x8a1ff4c9,
  0x2ce95bd8, 0xb015101f, 0x19b73b14, 0x81627f9a,
  0x6f83da3a, 0x03259fbd, 0x41f92a6e, 0x85ac6efa,
  0xde195be8, 0x6e66ba89, 0xb0ab042d, 0x3276976c,
  0x3dbeb3d7, 0x413ea96d };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_27[] =	/* primes 3 to 619 */
{ 0x02ced4b7, 0xf15179e8, 0x7fcba6da, 0x7b07a6f3,
  0xf9311218, 0xa7b88985, 0xac74b503, 0xbf745330,
  0x6d0a23f5, 0x27a1fa9a, 0xc2b85f1a, 0x26152470,
  0x6ac242f3, 0x518cc497, 0x09a23d74, 0xff28da52,
  0xe7bbf7f7, 0xa63c1c88, 0x6f684195, 0x65e472ce,
  0x80751585, 0xc70e20c2, 0x2d15d3fe, 0xc1b40c7f,
  0x8e25dd07, 0xdb09dd86, 0x791aa9e3 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_28[] =	/* primes 3 to 647 */
{ 0x6e026454, 0x60adbd18, 0xcd52ce1a, 0x1beab1c0,
  0x36e468e9, 0xf350d69b, 0x1d357d08, 0x3a59f778,
  0xc2cc262b, 0x4a29ce52, 0x509bcf97, 0x349ba2bf,
  0x22402d71, 0x6b32517e, 0x1941e18a, 0xce76cbd8,
  0x5809701e, 0x70eaef96, 0x9aac365c, 0x8a9fea5e,
  0xc74d951d, 0xb361f061, 0xc4d14f00, 0x0d806db4,
  0xcd939110, 0xc7cab492, 0x2f3ea4c4, 0x852ca469 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_29[] =	/* primes 3 to 661 */
{ 0x074921f7, 0x6a76cec3, 0xaeb05f74, 0x60b21f16,
  0x49dece2f, 0x21bb3ed9, 0xe4cb4ebc, 0x05d6f408,
  0xed3d408a, 0xdee16505, 0xdc657c6d, 0x93877982,
  0xf2d11ce6, 0xcb5b0bb0, 0x579b3189, 0xb339c2cc,
  0xcf81d846, 0xa9fbde0c, 0x723afbc7, 0x36655d41,
  0x0018d768, 0x21779cf3, 0x52642f1b, 0x2d17165d,
  0xc7001c45, 0x4a84a45d, 0x66007591, 0x27e85693,
  0x2288d0fb };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_30[] =	/* primes 3 to 683 */
{ 0x00872313, 0x1f66758a, 0x414bbebb, 0x2f8670bf,
  0x01dc959d, 0x74468901, 0x57c57f40, 0xe210c9c2,
  0x74f54469, 0x7c71cc1d, 0xe2be67a2, 0x03d8d56f,
  0x6c363fca, 0x0a78676a, 0x2b977789, 0x6ea2db50,
  0xdb31b737, 0x51992f73, 0x0def293e, 0xbc028877,
  0xdf95ac1b, 0x4d0c0128, 0x9a0b05e0, 0x0e6c0bc8,
  0xe61b766e, 0xc0943254, 0x1cd70f0f, 0xd5a0ce6b,
  0x8ab998fb, 0x8ab36e0d };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_31[] =	/* primes 3 to 719 */
{ 0x1e595df4, 0x3064a8c9, 0xd61ae17b, 0xde1938f0,
  0x22ee6357, 0x35f4cadd, 0x3d39f473, 0xafed7df5,
  0x92ae0fd3, 0xfe910508, 0x9ad9e939, 0x988b0227,
  0x60dec749, 0xae7ee54f, 0xeb0572ac, 0x0aed266d,
  0x92daafd8, 0x6135f7a3, 0xe4e8bf05, 0x0124c928,
  0xb0d719d5, 0x2181aec8, 0x0f79820f, 0xcb158642,
  0x20969ec0, 0x1a480d31, 0x331b3252, 0x01b36fab,
  0x3d5b415b, 0x1a4567e7, 0x3baf6389 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_32[] =	/* primes 3 to 739 */
{ 0x02c85ff8, 0x70f24be8, 0x0f62b1ba, 0x6c20bd72,
  0xb837efdf, 0x121206d8, 0x7db56b7d, 0x69fa4c02,
  0x1c107c3c, 0xa206fe8f, 0xa7080ef5, 0x76effc82,
  0xf9b10f57, 0x50656b77, 0x94b16afd, 0x70996e91,
  0xaef6e0ad, 0x15e91b07, 0x1ac9b24d, 0x98b233ad,
  0x86ee0555, 0x18e58e56, 0x638ef18b, 0xac5c74cb,
  0x35bbb6e5, 0xdae2783d, 0xd1c0ce7d, 0xec4fc70e,
  0x5186d411, 0xdf36368f, 0x061aa360, 0x11f30179 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_33[] =	/* primes 3 to 761 */
{ 0xd0440ea6, 0x8b382bcb, 0x75b4df8b, 0x6f8aa6cd,
  0x494daee4, 0x38b1922e, 0x46cef6ca, 0xdc74a93e,
  0xdf45643d, 0x05cc1aa5, 0x556f9c72, 0x0682676d,
  0x6668f9c1, 0x89284c78, 0xa770e3a8, 0x423b3833,
  0x96c4b063, 0xdb37bced, 0xd891a10f, 0x99328d8a,
  0x7c863078, 0xbd323cbc, 0x5ccea379, 0x252d31d3,
  0x39d2a084, 0x1717596a, 0x005fbd71, 0xa171925c,
  0x902bfb88, 0x6d99e44c, 0xb3a33020, 0xf05cadbe,
  0x4a8014ad };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_34[] =	/* primes 3 to 787 */
{ 0x16af5c18, 0xa2bef8ef, 0xf2278332, 0x182d0fbf,
  0x0038cc20, 0x5148b83d, 0x06e3d7d9, 0x32828b18,
  0xe11e0940, 0x28c7eaed, 0xa3395017, 0xe07d8ae9,
  0xb5940604, 0x51d05f93, 0x084cb481, 0x663c94c6,
  0xff980dde, 0xccdb42ad, 0x37097f41, 0xa7837fc9,
  0x5afe3f18, 0xad76f234, 0x83ae942e, 0x0f0c0bc6,
  0xe4001612, 0x3189872b, 0xe58f6dfc, 0x239ca28f,
  0xb0cfbf96, 0x4c8f27ce, 0x05d6c77a, 0x01f9d332,
  0x36c9d442, 0xad69ed33 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_35[] =	/* primes 3 to 811 */
{ 0x02c30b50, 0xedc2e94a, 0x3940a943, 0x968984e8,
  0x5a132fca, 0x78aedf5b, 0x4e307eec, 0xec19323e,
  0x71957e6e, 0xc70aab41, 0x43eb94a6, 0x20e9ca78,
  0x25d112d2, 0x055a3562, 0x1629b4b7, 0xb9208518,
  0x395b967a, 0xa4b564f8, 0x307459f7, 0x851d00e0,
  0x89d845dc, 0xa8e9423d, 0x2f0293bf, 0xdf0a3123,
  0xa1719e4c, 0xe4c577b3, 0x485ede33, 0xdd79a1ad,
  0xb6f9d10c, 0x8707cd1c, 0x2006396a, 0x192645b9,
  0x105ad4a4, 0xbd28a578, 0x5394c375 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_36[] =	/* primes 3 to 827 */
{ 0x005bfd25, 0x83ab7a44, 0x13d4df0f, 0x537c686c,
  0xa8e6b583, 0xe491130e, 0x96dfcc1c, 0x05ba298f,
  0x8701314b, 0x45bf6ff4, 0xecf372ff, 0xe78bccdf,
  0xfc18365a, 0x6ae5ca41, 0x2794281f, 0xbcc762f1,
  0x8ca1eb11, 0xfc8efe0b, 0x6bb5a7a0, 0x9954e758,
  0x074256ad, 0x443a8e4b, 0xaa267515, 0x4c43d626,
  0x46411944, 0x6e683d08, 0xd4683db5, 0x757d1199,
  0x9513a9cb, 0xe3e67e3a, 0xe501c1c5, 0x22aa8ba9,
  0xf9557895, 0x89161feb, 0xc69941a1, 0x47aa9685 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_37[] =	/* primes 3 to 857 */
{ 0x2a89d844, 0x7bf83428, 0x8464b909, 0x31ce3aaa,
  0xed0c2683, 0xb26f15e4, 0x32e95677, 0x65036627,
  0x80802634, 0x4328b107, 0x89fb23c6, 0x11b484ca,
  0xcd937f07, 0x65e0f5df, 0xc8f9a3a2, 0xc7aac35f,
  0x3e8a8a35, 0x26515cc0, 0x38c822e0, 0x7a1bd893,
  0x852c7ec0, 0xc01d7303, 0x90f69c22, 0xf56ba6cc,
  0xd90063cf, 0x72d6ad3d, 0x7a0a7455, 0xef28f5c6,
  0x1af3825a, 0x536b8464, 0xe90b2d32, 0x9e831029,
  0x638a6241, 0x8946766c, 0x6392ec57, 0x9bd0c31a,
  0xb4ce65ab };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_38[] =	/* primes 3 to 877 */
{ 0x06706918, 0xe8355b7f, 0xfd3f024d, 0xa6b012e2,
  0xbb7338f3, 0x0d51a968, 0x0f3d9120, 0x35ed70e0,
  0x2d38d422, 0xe41812d4, 0xe29d637b, 0x318ce6f4,
  0xea117321, 0xce8b712d, 0xcca9345f, 0xd03ccaf5,
  0x2e75dafc, 0xda909cd4, 0xb41a9f87, 0x53c8df3d,
  0x284198bc, 0xb759d059, 0x94136057, 0x2b7ab25f,
  0x396b9fa3, 0x7ae0a200, 0xd998ea09, 0x167edc30,
  0xf9d2c45c, 0x7e487029, 0x92750098, 0x3f7fb4e8,
  0xe85d8e94, 0x34a37006, 0x8cebc960, 0x60ab2f87,
  0x81efeb18, 0x2d0e724b };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_39[] =	/* primes 3 to 887 */
{ 0x0108d441, 0xce330894, 0xff143672, 0x5fee20c5,
  0x9b8fb49f, 0xbb29ad13, 0x5f0888b0, 0x59181b63,
  0x54380731, 0x8906204b, 0x7e16cc5e, 0x2d8c613b,
  0x4414b03a, 0x30587c32, 0xa08bbc57, 0x95f63e1e,
  0x6f237e7c, 0xdfc70204, 0xdd20d5d2, 0xd93a0fcb,
  0xd54d4e92, 0xd750c3c8, 0x4b276eca, 0x9081b543,
  0xa8979c2b, 0xb14e3fa1, 0x7c87d031, 0x300588b2,
  0x6b1aa738, 0xbe02e7b4, 0x57a9ed5f, 0x341b72e6,
  0x19296afb, 0x2ae2f6b0, 0xf6f00832, 0x9e0d7b8f,
  0x61a10c17, 0xa07a962e, 0x5bc81157 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_40[] =	/* primes 3 to 929 */
{ 0xa9e9591f, 0x7815617e, 0xcabe352f, 0xa13445c4,
  0xf8e319ba, 0x63042e1c, 0xb0a017d0, 0xe729a699,
  0x5480da4e, 0x5091cab4, 0x12910cf4, 0x7bb0f24e,
  0x5e1db412, 0x64b9f96a, 0x2b327e90, 0x1d9d0a39,
  0x12659a52, 0xd3792d52, 0x991bfa96, 0x4fe7d212,
  0x60374c24, 0xa04de69d, 0xf5d4e46b, 0x249cafc7,
  0x347c6181, 0xbd6dc6b8, 0x13a29dc6, 0xd4f785ac,
  0x78066355, 0x13530cd5, 0xdb94de48, 0x58c157f0,
  0x30b96bfb, 0x6475393b, 0x5f43a549, 0xd95c5619,
  0x7e274850, 0xad1a6d18, 0xb5eaa41d, 0xd42fda55 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_41[] =	/* primes 3 to 947 */
{ 0x2108556d, 0x64bbc9f2, 0xa87149a3, 0x26013838,
  0x4d8e761d, 0xab793496, 0x415dad5b, 0xa6682448,
  0xe3c8495c, 0xd3f2e881, 0xf3546b54, 0xb8b14068,
  0x97668326, 0xe4aa5c56, 0xe8b03fe7, 0x32b53f8b,
  0xe55d11c4, 0xfce09e57, 0xee4d8232, 0x1447c16b,
  0xe0e1a32d, 0x54972732, 0x5b58b113, 0x136127eb,
  0xf48c987d, 0x6532476f, 0x8800deab, 0x4b93a717,
  0x6a7cdc07, 0xf51ff3ef, 0x8fdc7d30, 0x289949c2,
  0xad7f1d56, 0xe40ca555, 0xa3a33043, 0x74bc64b1,
  0x546974cb, 0x927a6b4e, 0x85bf34af, 0x54cd54d6,
  0xbbec2afb };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_42[] =	/* primes 3 to 971 */
{ 0x06e1d136, 0xcb78cac5, 0x4da4bfcb, 0x6f2c4a24,
  0xfcf3796b, 0x77719c31, 0xd2791586, 0x0001f03e,
  0x4347621b, 0xf62577e0, 0x280ebfdb, 0x77b4f1e9,
  0x0f954eca, 0xfd198609, 0x68629be9, 0x1424c37a,
  0x8f320a34, 0x444953d5, 0x2c278d64, 0x85238798,
  0x709d0063, 0xe3fa8623, 0xea24bf2a, 0x2c5278e7,
  0x4460d05a, 0x0a708bd9, 0xc019d632, 0xe39e7300,
  0x22b9dbb9, 0x13df73cf, 0xb959dffe, 0x348f9623,
  0xf697a822, 0xf4a11320, 0xbd044ecc, 0x74878f53,
  0x0d57d0f0, 0x76647b0a, 0xb191f543, 0xdc08c392,
  0x3167e5ee, 0x56c66847 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_43[] =	/* primes 3 to 991 */
{ 0x0186695f, 0xa95755fc, 0xe74a9a4e, 0x8fbc30df,
  0x119e4901, 0x7edb320f, 0xe8114129, 0xb3bddd0d,
  0x2b0cf0f7, 0x2306fb1d, 0x6a5cae26, 0xe4a286ce,
  0xe1acd2fb, 0x5e6770b2, 0xc58355ca, 0x1c782114,
  0xb05f881d, 0x090a7fcb, 0xe043ebaa, 0x592672ae,
  0x9e0335e3, 0xc77acab9, 0xc4aeb4cb, 0xdc1f1341,
  0x20257620, 0x7c2ecd85, 0x130f3c11, 0xcad1192b,
  0xb43daff3, 0xfd555877, 0xce47d74b, 0x1e878cfd,
  0xd7b779a5, 0xca965949, 0xb03075a8, 0x25f009ab,
  0x509f0ff9, 0x5202ec37, 0xe9a0f3f4, 0xdc2d184d,
  0x10575170, 0xe3e7d4d0, 0xaf86a76f };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_44[] =	/* primes 3 to 1013 */
{ 0x005ca1a9, 0x2edd0e81, 0x9619289e, 0x1ecfe2d7,
  0xf3949eaf, 0x363a5fe8, 0xf6fee01c, 0xcd480490,
  0x30a1346a, 0xb83c4967, 0x8c7d5882, 0x6caf81ca,
  0x1d02473b, 0xea8ad400, 0xd1ce270a, 0x5743c3cd,
  0x892c3bd9, 0x3b84525d, 0x8a42071a, 0x508fdb8f,
  0x32952aaa, 0x2384cf5d, 0xf23ed81d, 0x10ac0031,
  0xd85d0e95, 0xe3c5bb51, 0x71a0e3f1, 0x2b671f8f,
  0xb07965cc, 0x353a784b, 0x78f71968, 0x1326c790,
  0x6e2b7f7b, 0x0782848e, 0xeb1aea5b, 0xab10b80e,
  0x5b7138fc, 0x36f7989c, 0xe85b07c2, 0xd4d59d42,
  0x1541c765, 0xf6c2111d, 0xb82eca06, 0xb437f757 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_45[] =	/* primes 3 to 1033 */
{ 0x5d59c98b, 0x452d0c02, 0x1291e1ef, 0x6ab50494,
  0xce984e89, 0xdc563773, 0x96b510a6, 0xeef593cb,
  0x73e4eb74, 0x6a1c83ef, 0x9a7bff75, 0x7ee6e25a,
  0xe12d86af, 0x743e83ad, 0x0f28e9c6, 0x0aee1694,
  0xf5bd9a93, 0xd9e9dc26, 0xd1ed4b29, 0xff2f3094,
  0xd431b844, 0xe0cea92f, 0x639ebb6f, 0x7107f740,
  0x7c23abc1, 0xcc3789e9, 0x4ddb2532, 0x32ecc6c5,
  0x0ecbe5e5, 0x32fd5097, 0x49cc5252, 0x2730c08e,
  0x1f7117c2, 0x71c83657, 0x087f4608, 0xe003e4f6,
  0x7cb9e029, 0xd33f00ae, 0xd3dad2a0, 0x76735950,
  0x7da17074, 0xb23e9701, 0x7e0e9f7e, 0x2ed03221,
  0x76712827 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_46[] =	/* primes 3 to 1051 */
{ 0x18e5b310, 0x229f618d, 0xe0f54782, 0xf57fff33,
  0x10546ba8, 0xefc0a69c, 0xac4b573b, 0x749cc43d,
  0xd3ba4df6, 0x1fe2800d, 0x733f4eb7, 0x19a6ea7f,
  0xa88aebf2, 0xd35b26c8, 0x6e89fe0b, 0x27e198de,
  0xe12a14da, 0x03cef215, 0xe6651c60, 0xbe9cf337,
  0x3620f4ab, 0xa453eeb9, 0xeb439ba0, 0x79201376,
  0x0e3cc7f8, 0x722f09a4, 0x685a5556, 0xb4efd158,
  0xb27a6b79, 0xb15f161f, 0xecf3fd80, 0x2767da7a,
  0x37ceb764, 0xbebfcc2b, 0x2d833be0, 0x0b21bb68,
  0xeab326b9, 0xebb20cc2, 0xd76273ed, 0xefa152ad,
  0x531bccbf, 0x17e3c78d, 0x5c43d8f6, 0x866ad640,
  0xfdbbba0f, 0xe997b27b };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_47[] =	/* primes 3 to 1069 */
{ 0x06fd3257, 0x047a7639, 0xcb2cfcfb, 0x193180fe,
  0x1f21979a, 0x2376042b, 0x6b2809ba, 0x216e6d5b,
  0x57fec6ff, 0x96b878bb, 0xe1d4371b, 0x2f53c7e0,
  0x036c8309, 0x2f6b0512, 0x7416844f, 0xbdc36a56,
  0xa1d7ae59, 0x332552e8, 0xe32f4324, 0xdc90f2d8,
  0x546904d8, 0x3b8f0e24, 0x8df97f60, 0x7af99875,
  0xae419d8e, 0x2954463b, 0x1f4aef0c, 0x52a102b4,
  0xccca2b78, 0x9d2b46c2, 0x0fb3c949, 0x49cbafc5,
  0x5ec2b085, 0x03b5beb4, 0x6b6eb1d1, 0xed78e5f2,
  0x398baf6c, 0x33ae0815, 0xf0bd3d5b, 0xe1ebbadc,
  0x5aa7a694, 0x352122fc, 0xd4c1c770, 0x016d76cb,
  0xc050191f, 0x6ce5ab73, 0x6d43113d };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_48[] =	/* primes 3 to 1093 */
{ 0x021bf949, 0x7091b8c3, 0x68cc7c8e, 0x00c1990c,
  0x6027481b, 0x79215ac8, 0xa7517749, 0xa2151377,
  0x9a993d29, 0x58fcb49a, 0x73680292, 0x68527994,
  0xc6cc1928, 0xadd41295, 0x96765f4c, 0xc3141a04,
  0x4eb1d615, 0x78881667, 0x57d86187, 0x81813062,
  0x03226798, 0x7df0d471, 0x9cd38f1b, 0x7085fca5,
  0x334be3a6, 0x003a3ce7, 0xe19aba55, 0x3e80cc5a,
  0xe4060eff, 0x6e180666, 0x1da5eeb7, 0xd142d3b2,
  0xe40739f1, 0x443dee3a, 0x198637f0, 0x3c062845,
  0xeaff3ff2, 0x7ea38d93, 0x44d8a902, 0x22472df0,
  0x7dfb5c9c, 0x8ada77cd, 0x0d5b94ef, 0xf021e02e,
  0x307d0801, 0x0312d57c, 0xb5d97576, 0x4697842d };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_49[] =	/* primes 3 to 1109 */
{ 0x00a8b455, 0xb6b4a84f, 0x6834364b, 0x936a996f,
  0xbceb3f49, 0x88ee2732, 0x24b48131, 0x2357ae12,
  0x4d520af5, 0xc87eb399, 0x90944c44, 0xc3a75724,
  0x1e3caf22, 0x26585d51, 0x6875521d, 0xb3f466ec,
  0xe4117740, 0x5c808598, 0xeded00eb, 0x951faff9,
  0xf8d8beee, 0x127c796c, 0x2a358484, 0x8df645d1,
  0x31b11876, 0xb04f57d2, 0x4e0c0751, 0x4448e66a,
  0x4bd5c496, 0x435274ce, 0x9a059e30, 0xb39a47d0,
  0x0c6cbf84, 0x8a46fc8c, 0x4bb19382, 0xe2799723,
  0x5fb598f1, 0xdfb21e4a, 0x05b2eeb2, 0xfa25db86,
  0x5183ce51, 0xcf330c32, 0xe2749deb, 0x4b7d3fd7,
  0x9781307a, 0xc1aee399, 0x0451d911, 0xc9204d5e,
  0x80edaf17 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_50[] =	/* primes 3 to 1151 */
{ 0xfa1bd62b, 0xaae1e767, 0x47535af3, 0x830fc07d,
  0xebcf3ef7, 0xe5a8e46b, 0x8937c4af, 0xe02aef0a,
  0xce420c7b, 0x2c3f2fac, 0xb9dc94e5, 0x100a7191,
  0xb47cf523, 0x520f613b, 0xee8e095a, 0x7b06d781,
  0xb6204bde, 0x1648e17f, 0x0f1bd4ab, 0xa00f7e90,
  0xd8fc2a05, 0xf5f1e832, 0x6e88a4a6, 0x7e73cae1,
  0xc4a93d89, 0xad6b301b, 0x1f185b13, 0x0246ab44,
  0x5cadc384, 0x931189b5, 0x566b3ed9, 0xdafba4e6,
  0x59f5446e, 0x5a70c8d1, 0x4626b66d, 0x0f1ccfbf,
  0xd4238b68, 0x84af7dd3, 0xa91d2063, 0xceb2c2f7,
  0xf273b1da, 0x4cb542ea, 0x62c624cf, 0x4fcb0486,
  0x138b42a3, 0xc1d9593c, 0xe1254fb3, 0x214d2b08,
  0x52532bc5, 0x28bc6467 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_51[] =	/* primes 3 to 1171 */
{ 0x5b7091ea, 0xdbc63f00, 0x64dd01de, 0x204ee72f,
  0xc4644db7, 0x573e04ee, 0x706df728, 0x7a49af78,
  0xc5b99680, 0x528566bc, 0x17d57a00, 0x16a5b12e,
  0xf30fa9e3, 0xa1d437c8, 0xbf8e3283, 0x3eeb4036,
  0xaf3dfa3d, 0xd69f4d6a, 0xae6b7947, 0x18e2e8fa,
  0xafccb2a5, 0xf3b3ed57, 0xaac15fb8, 0xd04f7035,
  0x0f9edc0e, 0xd868ec8d, 0x430f42ab, 0xad8cf315,
  0xee97237c, 0x6df5577e, 0x5a2857d5, 0xc6e41cfc,
  0x1557e427, 0xafc62698, 0x9703722f, 0x50f10c60,
  0x78579c80, 0x32f8bec2, 0x5bbce21a, 0xa20c3cdb,
  0xdbb80d64, 0x31c06f68, 0xa743d08d, 0x220c0f0a,
  0x1fbb5766, 0xb6977732, 0x3f869dd0, 0xe286a091,
  0x7e3f520e, 0xc3203bce, 0x170ef097 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_52[] =	/* primes 3 to 1193 */
{ 0x239afcd4, 0x38799705, 0xab8a0cda, 0x4802bc8f,
  0xb0e87f44, 0xa568f618, 0x7c604708, 0xdfb79072,
  0xe24b49cb, 0x8b2ac531, 0x005cf298, 0x2437b16e,
  0x027fa014, 0x14e3dbf5, 0xbf766811, 0x66e276ff,
  0xcf676855, 0x0bc1cd9a, 0x1b387eba, 0xaa8550ae,
  0xfc10c69c, 0x372a0254, 0xb84666ff, 0x35044b9a,
  0xa34fcf7c, 0x817b33f3, 0x7088a289, 0xa17891a7,
  0xe66f88e8, 0xec2ba784, 0xb2a09a91, 0x02609726,
  0x17a3dbea, 0x8463439d, 0x47972d09, 0xb0e63752,
  0xbac58d33, 0x9b402dc1, 0xa0991554, 0x3360cd68,
  0x4df24e43, 0x7487571d, 0xfaf68f4f, 0xe0a93546,
  0x66aa84bf, 0x84d4448d, 0x21190291, 0x66db27bd,
  0x515599cd, 0xcd147810, 0x3acf73e7, 0xfe62aed9 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_53[] =	/* primes 3 to 1217 */
{ 0x0eb29f45, 0x5fc46bf0, 0xd4857e41, 0xa0059da0,
  0xda0b3770, 0xf445bac2, 0x37decad9, 0x954f2a17,
  0x849520eb, 0x001349bf, 0xf0264427, 0xb01519ec,
  0xf6fdb496, 0x80797a72, 0x17df3f5e, 0x95dea2d3,
  0xfded40a1, 0x3bcd8ac6, 0x0af97a12, 0x43383501,
  0x915ba38c, 0x90ec4f69, 0x2f931a60, 0x56bf7e42,
  0xd2969fab, 0xd442987c, 0x62e0fe9e, 0xaa412cba,
  0x8335fe9d, 0x33343d9f, 0x760e9e43, 0xf2b0f8dc,
  0xbe1e28ac, 0xa0ce2864, 0x5db05820, 0x71a88a56,
  0x4013a0f7, 0xc3d72268, 0x6e2fb29a, 0xc2d23e4e,
  0x6ad5ff62, 0x99a85da1, 0x535ff17b, 0x0e26402a,
  0xf5669a3d, 0x513660ce, 0x800afdf9, 0xe6ef66e1,
  0x9a202974, 0xa1069be2, 0xd54ceff7, 0x8e333c48,
  0x4ebbe265 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_54[] =	/* primes 3 to 1231 */
{ 0x0654f0d4, 0xcdacb307, 0x5419612f, 0xae3cf746,
  0xfbab751f, 0xd0887955, 0x28adc68d, 0x26f32877,
  0xeb1b772d, 0xb48e49f6, 0xcb445987, 0xc4966560,
  0xdff84737, 0x02bb0fd4, 0xf8b68b5c, 0xe2d496a6,
  0x0dc7d7e4, 0x3c3cb0bf, 0x72665c6e, 0x4c86a7ce,
  0xb78c9da4, 0x0f4d90a8, 0xf5dfe2a4, 0xdc559b8a,
  0xba10a63a, 0x0ca25d3a, 0xdec2c419, 0x8b688d80,
  0x71c05d3b, 0x694f19de, 0xda32955f, 0x77fbb577,
  0x27eb6521, 0x40495e56, 0x2f4a13e8, 0xb648daf2,
  0x13d1da75, 0xe3f04bb0, 0x43fedcd2, 0xb2a0cd30,
  0xa4339e3a, 0x03b7f3a0, 0xe02a31c2, 0x8394368c,
  0x7f73bbf3, 0x2712e69e, 0x7ac58373, 0xe5f7c7e7,
  0x55e0d645, 0x628c5475, 0x6217c0bd, 0xf119900b,
  0x05ea71dd, 0x714fd2c9 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_55[] =	/* primes 3 to 1259 */
{ 0x02de1de4, 0xcbca29fc, 0x94a50bb7, 0xae89c417,
  0xb8063484, 0x5c71a8c6, 0xa641d997, 0x65355b7e,
  0xed63ea84, 0xeaeead3c, 0x2a49b4d2, 0xefdd333e,
  0xbc90594b, 0x30eab1fb, 0x519151b2, 0x536ef5a7,
  0x40b8e2d9, 0x2c02ffd5, 0x149dc0db, 0xcb0416cf,
  0xf8b08c27, 0xcc47095e, 0xbbe5263c, 0x327da58a,
  0xcd5825d9, 0x3a0ac60e, 0x7a667d47, 0x084d08aa,
  0x5c2449e0, 0x65b7f051, 0xc34d6fb8, 0xac5a5d99,
  0xd082950c, 0x11650560, 0x4f2fa1de, 0xf26e51ea,
  0xa4ea5ac2, 0x87e2f953, 0xcdfc4d30, 0xf05d6553,
  0xa2a28858, 0xea28dc4d, 0x24ae0063, 0xa49c8d44,
  0xeedc858f, 0x55e16f54, 0xf9c3f019, 0x6a9c92c9,
  0x7b685023, 0x3f0d9c13, 0x7f7c114d, 0xbe550751,
  0xbc8560cb, 0x746a4b6c, 0x373cde1f };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_56[] =	/* primes 3 to 1283 */
{ 0x01662c66, 0xdab7a4fa, 0xdba4265a, 0xc2075912,
  0x59e9c885, 0xe1330cb6, 0xc91bee92, 0xf1b334ff,
  0x384f827c, 0xc8057aa7, 0xc3b65fc6, 0xde53dcac,
  0x2db6d790, 0x3febbe07, 0xcc401232, 0x6b128eb7,
  0x1afd3136, 0xa9e7f786, 0x14648da1, 0x7b4f50c7,
  0xbd4129ca, 0x746dab21, 0x09583797, 0xfc1c2ecd,
  0x4c0768a8, 0x1892bd16, 0xdfea8227, 0xbcb2b8bf,
  0x168a1452, 0x370b0863, 0xb299d088, 0x8434c213,
  0x2383a6c7, 0xb6b4bf20, 0x5addc8da, 0x76d2b172,
  0xb416f5b0, 0xb9a38d87, 0x738c1cca, 0x3fe33dd2,
  0xf9b7570e, 0x3f663f8b, 0x34169076, 0x51b1dd42,
  0x2192331d, 0x9436304a, 0x0303422f, 0x4d420389,
  0x4548a055, 0x62ed1c09, 0x1a63309b, 0xf1a9df8b,
  0xf0c59af9, 0x12a62c22, 0xe1e1f49b, 0xb0115c17 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_57[] =	/* primes 3 to 1297 */
{ 0x00b3fde4, 0xe9dbc2a2, 0x1c8f4d4b, 0x53b0ff59,
  0x643cf537, 0x88f9d4ba, 0x69472171, 0x6a2f33d5,
  0xa93b03b2, 0x59142a0e, 0x117006bc, 0x8b4e1475,
  0x1adf80d1, 0x96c20ffd, 0xfa1775f1, 0x83b2df43,
  0x1c766011, 0xdefc6c34, 0xc6bfafcd, 0xd51ef8ef,
  0x253052b2, 0xc818df16, 0x37372435, 0xe9e55783,
  0x6c7d476d, 0x966ec455, 0x1ef8d32f, 0x7d687828,
  0xc978db5a, 0xabf1cc69, 0x74e86c65, 0x260bec72,
  0x1a609875, 0x6d5942ef, 0x4d4d8b42, 0x6a9cd4fb,
  0xe0030023, 0xd9bf209b, 0x4a93c089, 0xc4f634b1,
  0xd5463616, 0x33307dbf, 0x127489d6, 0xaa674108,
  0xe2c74fd3, 0x63aba6a2, 0x9f2f887d, 0xfc8b13a6,
  0xbb230a35, 0x390669ff, 0x22f8243b, 0xbc59cf3d,
  0x58bafd1a, 0xc6f2f456, 0xe938c1f8, 0x4051aadc,
  0x54d4a035 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_58[] =	/* primes 3 to 1307 */
{ 0x005cda0c, 0x54b07f4f, 0xff0caca0, 0x7cc89b95,
  0x1c021191, 0x164be693, 0x6665357e, 0xbb2f689c,
  0x7157ea4f, 0x98037ce1, 0x5aca14ca, 0x3cf1a386,
  0xb03e831e, 0xe09a8d5c, 0x48d51f5e, 0x6646ed8a,
  0x7ec2b955, 0x216587f0, 0x7f3c42ee, 0x06ae3844,
  0x4c776b8c, 0x3ef32747, 0x97cd2ac1, 0xc7cce7ec,
  0xe75bb029, 0x0f5b5a0e, 0x2c96c460, 0x0c678a21,
  0x0d992d36, 0xd441b1fd, 0x682adf0e, 0xf289947e,
  0x6d3de1a2, 0xaf0ca945, 0x859aa1f2, 0xb2bb793d,
  0x351dbebf, 0xe05144ee, 0xfe9c752d, 0x75ec602c,
  0x0e0344dd, 0xcfcb642b, 0x6cfc8722, 0x19d69873,
  0xb8c4ace3, 0xffd460e9, 0x43d903b4, 0x5de9d402,
  0x958a41fb, 0x5e008a94, 0xc9361081, 0x4e5e2811,
  0xd052c10a, 0xbfc67bf6, 0x915d4435, 0x2688091b,
  0x1eb1c711, 0x7c91eae5 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_59[] =	/* primes 3 to 1327 */
{ 0x0031fc6d, 0x6918c954, 0x9fe61e37, 0xe79cea8a,
  0xe12d234b, 0x7642915b, 0x85e4b88b, 0x83eeba5f,
  0x429d8086, 0x9a31c342, 0x0020beb9, 0xbc48ece8,
  0xcb7bb572, 0xad3a8e34, 0x085a4765, 0x6ba28651,
  0xad8a45d5, 0x26ea9c98, 0x90740760, 0xca7bf7e9,
  0x9acf6665, 0xc6a9232a, 0x720b8d78, 0x1f51a8b2,
  0xdfcbe4ee, 0xa4a48126, 0xad4a6fd8, 0xb5a0c187,
  0x12021d6c, 0x3ca2c624, 0xd477495f, 0x11752cc7,
  0x77c2b465, 0x8b3cfc3f, 0x2cb0ab3c, 0xc70277e3,
  0xd1d97a12, 0xebc6b0db, 0xfe7ad411, 0xdede9e15,
  0x905166d9, 0x403ae854, 0x9432b6a4, 0xf45d1540,
  0xca51bffd, 0xf107b16c, 0x08deae8e, 0x49bc15e8,
  0xd1d3ac9c, 0x2a76465a, 0xe778cc84, 0x810878db,
  0xfad8b7e5, 0xd5151c83, 0x9045920b, 0xfa0cecd0,
  0x43e94546, 0xee4f4361, 0x84901bb5 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_60[] =	/* primes 3 to 1381 */
{ 0xa0604bc5, 0x4c251ade, 0xcf22bf07, 0x5a150bb1,
  0x2a67d65a, 0x5045c183, 0x17246627, 0x0d72a8c6,
  0x3e2dd1c4, 0x6694a251, 0xf55bca5e, 0x7d834c87,
  0x2a8d10e5, 0xea91ba4d, 0xcce166f1, 0x6b1be0ef,
  0xba025bf3, 0x62f29284, 0xa36db516, 0x75c7d25e,
  0xac751992, 0x5560c7a1, 0xc7047093, 0x8bdf2818,
  0xed42d042, 0x53130bef, 0x0d92e596, 0x844e073b,
  0xdd40bd15, 0x6f433f09, 0xbdfd3e38, 0x769a485c,
  0xf29380b7, 0x9c18989c, 0xed0e6ec4, 0x3bcc7b73,
  0x087e1fb9, 0x4e8cf2d3, 0x475c7760, 0x5c707f6b,
  0x31f7217c, 0x4c628da2, 0xe3263e30, 0xa83c1066,
  0x1378f415, 0x33ca7d71, 0x5d4e2b87, 0xc0e142ba,
  0x462e6ffb, 0x506e09f9, 0x7850c73e, 0x4b3f7a24,
  0xca98bda0, 0x5c0c6ac6, 0x666daad0, 0x14d2ff3f,
  0x7138fa68, 0xddd5e9f0, 0xe92edcaa, 0x62b56483 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_61[] =	/* primes 3 to 1423 */
{ 0x68bd8015, 0x91071573, 0x8a205b51, 0xe1be9357,
  0xdab961de, 0x59c9e43c, 0xb9becf7a, 0x8adba9a9,
  0x926a87bb, 0x7f574190, 0x3ee07b97, 0x83b5ed87,
  0x503ee854, 0xbfc61ca4, 0x9531565e, 0x4e8136f5,
  0xdb315f85, 0x3ae9f609, 0x2deebbac, 0x45e36b1b,
  0x1f3a6d76, 0xe4e758c0, 0x2477bd33, 0x40b9cf8e,
  0xe1815167, 0x132e13ab, 0x82cf7f08, 0x51b86b6f,
  0xfd7cfaea, 0x9b7b7dcc, 0xcd7c9d57, 0x9ccb5269,
  0xa01e7ef9, 0x52ec1995, 0xbc6df02c, 0x649435e7,
  0x3e12d47d, 0xc484c579, 0xda72631f, 0x976b8eda,
  0x270cc80b, 0x56141511, 0xf857bc1c, 0x898e8aeb,
  0xb836ca21, 0x2ed0d5cb, 0xcd16c412, 0x81a67e69,
  0xbbb68933, 0x5ead39cf, 0xdefe9acb, 0x9721e75c,
  0xd59b372e, 0xc91ec67d, 0x0df39398, 0x106914b7,
  0xba405fde, 0xe85bb37c, 0xdae528dd, 0xe98d3250,
  0xbec22e6b };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_62[] =	/* primes 3 to 1433 */
{ 0x4742fdaf, 0xf7e8231a, 0xded68277, 0x58493423,
  0x12b13d2f, 0x5925c539, 0x82d876ef, 0x7ff69e7f,
  0x5b4ff04e, 0x8454faea, 0x620dc960, 0x0c65fd57,
  0x2aecce4c, 0x9656588f, 0x79dfb5df, 0xd7f99148,
  0x196c24df, 0x6d8c704b, 0xd6ffb8d9, 0xcedb8ee8,
  0x448d4352, 0xd834cef7, 0xfce9b929, 0x07eeca6a,
  0xcc107008, 0xfa118ff7, 0xedcc0b84, 0x207c3eef,
  0xdb5ea3ef, 0x89c684d8, 0x89c4187a, 0x10775358,
  0xc429d4d2, 0xa76bb2c3, 0x9f406fdc, 0x49dcf4b6,
  0xed773586, 0x770e4651, 0xcb63c783, 0x54d2a578,
  0x5f52816b, 0x14d29d62, 0x06d952ca, 0x4428030e,
  0x2e793590, 0xf75f1d07, 0x79363fa6, 0x047f0c64,
  0xf3ed6a91, 0x2dbc4437, 0x673d4184, 0x00d005ca,
  0x9ca42ff6, 0x841c84dd, 0xaaff5fb0, 0x87f85954,
  0x177c5dc0, 0xfbfbb491, 0xa1e5e03e, 0x5715875c,
  0xa02a0fa4, 0x1fde7abd };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_63[] =	/* primes 3 to 1451 */
{ 0x322123be, 0x40a1853c, 0xd02ea217, 0x363a368b,
  0xacb2117a, 0x342a5ee6, 0xa03a7fda, 0x4338eaac,
  0x9d9cc512, 0xffa944f1, 0x767e0a56, 0xc82c051f,
  0xe91415e0, 0x4cfddc19, 0x7f9539ee, 0x3801a5cc,
  0x3b68d593, 0xa5a8a3a9, 0x71ccc478, 0x938461f7,
  0xe804c928, 0xb3f42839, 0x97fa73a7, 0x09b9ebe5,
  0x7cbb88f1, 0xea9754c4, 0xbc0a20c1, 0xe0b7f585,
  0x6649a4b8, 0x88eec46b, 0xf86f7ccf, 0xfdecbfbd,
  0x46b40b23, 0xcf80aaef, 0xf810bf21, 0x8f793d2d,
  0x2722ddc8, 0xc8c87536, 0x66fc2278, 0xb5186905,
  0xe9f8220c, 0x0b454fa8, 0xc461c002, 0x80e6882a,
  0xb5e77c84, 0xde0b068e, 0xb34cdd5a, 0xa370bc8a,
  0x6e38121f, 0x2f3e9009, 0x82df957a, 0x585c307d,
  0x9b2b1f9d, 0x732df2a0, 0x1d9e6968, 0xbc23657f,
  0x4d152676, 0xe28268ad, 0xf7c026d3, 0x55a2a944,
  0xf41bc21f, 0x67b73894, 0x5828ad87 };

/**
 */
/*@observer@*/ /*@unchecked@*/
static uint32 spp_64[] =	/* primes 3 to 1471 */
{ 0x2465a7bd, 0x85011e1c, 0x9e052792, 0x9fff268c,
  0x82ef7efa, 0x416863ba, 0xa5acdb09, 0x71dba0cc,
  0xac3ee499, 0x9345029f, 0x2cf810b9, 0x9e406aac,
  0x5fce5dd6, 0x9d1c717d, 0xaea5d18a, 0xb913f456,
  0x505679bc, 0x91c57d46, 0xd9888857, 0x862b36e2,
  0xede2e473, 0xc1f0ab35, 0x9da25271, 0xaffe15ff,
  0x240e299d, 0x0b04f4cd, 0x0e4d7c0e, 0x47b1a7ba,
  0x007de89a, 0xae848fd5, 0xbdcd7f98, 0x15564eb0,
  0x60ae14f1, 0x9cb50c29, 0x1f0bbd8e, 0xd1c4c7f8,
  0xfc5fba51, 0x66200193, 0x9b532d92, 0xdac844a8,
  0x431d400c, 0x832d039f, 0x5f900b27, 0x8a75219c,
  0x2986140c, 0x79045d77, 0x59540854, 0xc31504dc,
  0x56f1df5e, 0xebe7bee4, 0x47658b91, 0x7bf696d6,
  0x927f2e24, 0x28fbeb34, 0x0e515cb9, 0x835d6387,
  0x1be8bbe0, 0x9cf13445, 0x799f2e67, 0x78815157,
  0x1a93b4c1, 0xeee55d1b, 0x9072e0b2, 0xf5c4607f };

uint32* mp32spprod[SMALL_PRIMES_PRODUCT_MAX] =
{
	spp_01,
	spp_02,
	spp_03,
	spp_04,
	spp_05,
	spp_06,
	spp_07,
	spp_08,
	spp_09,
	spp_10,
	spp_11,
	spp_12,
	spp_13,
	spp_14,
	spp_15,
	spp_16,
	spp_17,
	spp_18,
	spp_19,
	spp_20,
	spp_21,
	spp_22,
	spp_23,
	spp_24,
	spp_25,
	spp_26,
	spp_27,
	spp_28,
	spp_29,
	spp_30,
	spp_31,
	spp_32,
	spp_33,
	spp_34,
	spp_35,
	spp_36,
	spp_37,
	spp_38,
	spp_39,
	spp_40,
	spp_41,
	spp_42,
	spp_43,
	spp_44,
	spp_45,
	spp_46,
	spp_47,
	spp_48,
	spp_49,
	spp_50,
	spp_51,
	spp_52,
	spp_53,
	spp_54,
	spp_55,
	spp_56,
	spp_57,
	spp_58,
	spp_59,
	spp_60,
	spp_61,
	spp_62,
	spp_63,
	spp_64,
};

int mp32ptrials(uint32 bits)
{
	if (bits >= 1854)
		return 2;
	if (bits >= 1223)
		return 3;
	if (bits >= 927)
		return 4;
	if (bits >= 747)
		return 5;
	if (bits >= 627)
		return 6;
	if (bits >= 543)
		return 7;
	if (bits >= 480)
		return 8;
	if (bits >= 431)
		return 9;
	if (bits >= 393)
		return 10;
	if (bits >= 361)
		return 11;
	if (bits >= 335)
		return 12;
	if (bits >= 314)
		return 13;
	if (bits >= 295)
		return 14;
	if (bits >= 279)
		return 15;
	if (bits >= 265)
		return 16;
	if (bits >= 253)
		return 17;
	if (bits >= 242)
		return 18;
	if (bits >= 232)
		return 19;
	if (bits >= 223)
		return 20;
	if (bits >= 216)
		return 21;
	if (bits >= 209)
		return 22;
	if (bits >= 202)
		return 23;
	if (bits >= 196)
		return 24;
	if (bits >= 191)
		return 25;
	if (bits >= 186)
		return 26;
	if (bits >= 182)
		return 27;
	if (bits >= 178)
		return 28;
	if (bits >= 174)
		return 29;
	if (bits >= 170)
		return 30;
	if (bits >= 167)
		return 31;
	if (bits >= 164)
		return 32;
	if (bits >= 161)
		return 33;
	if (bits >= 160)
		return 34;
	return 35;
}

/**
 */
static void mp32prndbits(mp32barrett* p, uint8 msbclr, uint8 lsbset, randomGeneratorContext* rc)
	/*@modifies p @*/
{
	register uint32 size;

	if (p == (mp32barrett*) 0 || p->modl == (uint32*) 0)
		return;

	size = p->size;
	/*@-noeffectuncon@*/ /* LCL: ??? */
	(void) rc->rng->next(rc->param, p->modl, size);
	/*@=noeffectuncon@*/

	if (msbclr != 0)
		p->modl[0] &= (((uint32)0xffffffff) >> msbclr);

	p->modl[0] |= (((uint32)0x80000000) >> msbclr);

	/*@-shiftnegative@*/
	if (lsbset != 0)
		p->modl[size] |= (((uint32)0xffffffff) >> (32 - lsbset));
	/*@=shiftnegative@*/
}

/**
 * mp32psppdiv_w
 *  needs workspace of (3*size) words
 */
static int mp32psppdiv_w(const mp32barrett* p, /*@out@*/ uint32* wksp)
	/*@globals mp32spprod @*/
	/*@modifies wksp @*/
{
	/* small prime product trial division test */
	register uint32 size = p->size;

	if (size > SMALL_PRIMES_PRODUCT_MAX)
	{
		mp32setx(size, wksp+size, SMALL_PRIMES_PRODUCT_MAX, mp32spprod[SMALL_PRIMES_PRODUCT_MAX-1]);
		/*@-compdef@*/ /* LCL: wksp+size undef */
		mp32gcd_w(size, p->modl, wksp+size, wksp, wksp+2*size);
		/*@=compdef@*/
	}
	else
	{
		mp32gcd_w(size, p->modl, mp32spprod[size-1], wksp, wksp+2*size);
	}

	return mp32isone(size, wksp);
}

/**
 * mp32pmilrabtwo_w
 * needs workspace of (5*size+2)
 */
static int mp32pmilrabtwo_w(const mp32barrett* p, uint32 s, const uint32* rdata, const uint32* ndata, /*@out@*/ uint32* wksp)
	/*@modifies wksp @*/
{
	register uint32 size = p->size;
	register uint32 j = 0;

	mp32btwopowmod_w(p, size, rdata, wksp, wksp+size);

	while (1)
	{
		if (mp32isone(size, wksp))
			return (j == 0);

		if (mp32eq(size, wksp, ndata))
			return 1;

		if (++j < s)
			mp32bsqrmod_w(p, size, wksp, wksp, wksp+size);
		else
			return 0;
	}
}

/**
 * mp32pmilraba_w
 * needs workspace of (5*size+2) words
 */
static int mp32pmilraba_w(const mp32barrett* p, const uint32* adata, uint32 s, const uint32* rdata, const uint32* ndata, /*@out@*/ uint32* wksp)
	/*@modifies wksp @*/
{
	register uint32 size = p->size;
	register uint32 j = 0;

	mp32bpowmod_w(p, size, adata, size, rdata, wksp, wksp+size);

	while (1)
	{
		if (mp32isone(size, wksp))
			return (j == 0);

		if (mp32eq(size, wksp, ndata))
			return 1;

		if (++j < s)
			mp32bsqrmod_w(p, size, wksp, wksp, wksp+size);
		else
			return 0;
	}
}

/**
 * needs workspace of (8*size+2) words
 */
int mp32pmilrab_w(const mp32barrett* p, randomGeneratorContext* rc, int t, uint32* wksp)
{
	/*
	 * Miller-Rabin probabilistic primality test, with modification
	 *
	 * For more information, see:
	 * "Handbook of Applied Cryptography"
	 *  Chapter 4.24
	 *
	 * Modification to the standard algorithm:
	 *  The first value of a is not obtained randomly, but set to two
	 */

	/* this routine uses (size*3) storage, and calls mp32bpowmod, which needs (size*4+2) */
	/* (size) for a, (size) for r, (size) for n-1 */

	register uint32  size  = p->size;
	register uint32* ndata = wksp;
	register uint32* rdata = ndata+size;
	register uint32* adata = rdata+size;

	uint32 s;

	mp32copy(size, ndata, p->modl);
	(void) mp32subw(size, ndata, 1);
	mp32copy(size, rdata, ndata);

	s = mp32divpowtwo(size, rdata); /* we've split p-1 into (2^s)*r */

	/* should do an assert that s != 0 */

	/* do at least one test, with a = 2 */
	if (t == 0)
		t++;

	if (!mp32pmilrabtwo_w(p, s, rdata, ndata, wksp+3*size))
		return 0;

	while (t-- > 0)
	{
		/* generate a random 'a' into b->data */
		mp32brnd_w(p, rc, adata, wksp);

		if (!mp32pmilraba_w(p, adata, s, rdata, ndata, wksp+3*size))
			return 0;
	}

    return 1;
}

/**
 * needs workspace of (7*size+2) words
 */
void mp32prnd_w(mp32barrett* p, randomGeneratorContext* rc, uint32 size, int t, const mp32number* f, uint32* wksp)
{
	/*
	 * Generate a prime into p with (size*32) bits
	 *
	 * Conditions: size(f) <= size(p)
	 *
	 * Optional input f: if f is not null, then search p so that GCD(p-1,f) = 1
	 */

	mp32binit(p, size);

	if (p->modl != (uint32*) 0)
	{
		while (1)
		{
			/*
			 * Generate a random appropriate candidate prime, and test
			 * it with small prime divisor test BEFORE computing mu
			 */

			mp32prndbits(p, 0, 1, rc);

			/* do a small prime product trial division test on p */
			if (!mp32psppdiv_w(p, wksp))
				continue;

			/* if we have an f, do the congruence test */
			if (f != (mp32number*) 0)
			{
				mp32copy(size, wksp, p->modl);
				(void) mp32subw(size, wksp, 1);
				mp32setx(size, wksp+size, f->size, f->data);
				mp32gcd_w(size, wksp, wksp+size, wksp+2*size, wksp+3*size);

				if (!mp32isone(size, wksp+2*size))
					continue;
			}

			/* candidate has passed so far, now we do the probabilistic test */
			mp32bmu_w(p, wksp);

			if (mp32pmilrab_w(p, rc, t, wksp))
				return;
		}
	}
}

/**
 * needs workspace of (7*size+2) words
 */
void mp32prndconone_w(mp32barrett* p, randomGeneratorContext* rc, uint32 size, int t, const mp32barrett* q, const mp32number* f, mp32number* r, int cofactor, uint32* wksp)
{
	/*
	 * Generate a prime p with n bits such that p mod q = 1, and p = qr+1; r = 2s
	 *
	 * Conditions: q > 2 and size(q) < size(p) and size(f) <= size(p)
	 *
	 * Conditions: r must be chosen so that r is even, otherwise p will be even!
	 *
	 * if cofactor == 0, then s will be chosen randomly
	 * if cofactor == 1, then make sure that q does not divide r, i.e.:
	 *    q cannot be equal to r, since r is even, and q > 2; hence if q <= r make sure that GCD(q,r) == 1
	 * if cofactor == 2, then make sure that s is prime
	 * 
	 * Optional input f: if f is not null, then search p so that GCD(p-1,f) = 1
	 */

	mp32binit(p, size);

	if (p->modl != (uint32*) 0)
	{
		mp32barrett s;

		mp32bzero(&s);
		mp32binit(&s, p->size - q->size);

		while (1)
		{
			mp32prndbits(&s, 1, 0, rc);

			/*@-usedef@*/ /* s is set */
			if (cofactor == 1)
			{
				mp32setlsb(s.size, s.modl);

				/* if (q <= s) check if GCD(q,s) != 1 */
				if (mp32lex(q->size, q->modl, s.size, s.modl))
				{
					/* we can find adequate storage for computing the gcd in s->wksp */
					mp32setx(s.size, wksp, q->size, q->modl);
					mp32gcd_w(s.size, s.modl, wksp, wksp+s.size, wksp+2*s.size);

					if (!mp32isone(s.size, wksp+s.size))
						continue;
				}
			}
			else if (cofactor == 2)
			{
				mp32setlsb(s.size, s.modl);
			}
			else
				{};

			if (cofactor == 2)
			{
				/* do a small prime product trial division test on r */
				if (!mp32psppdiv_w(&s, wksp))
					continue;
			}

			/* multiply q*s into p, multiply by two, then add 1 */
			mp32mul(p->modl, s.size, s.modl, q->size, q->modl);
			(void) mp32multwo(p->size, p->modl);
			(void) mp32addw(p->size, p->modl, 1);

			/* do a small prime product trial division test on p */
			if (!mp32psppdiv_w(p, wksp))
				continue;

			/* if we have an f, do the congruence test */
			if (f != (mp32number*) 0)
			{
				mp32copy(size, wksp, p->modl);
				(void) mp32subw(size, wksp, 1);
				mp32setx(size, wksp, f->size, f->data);
				mp32gcd_w(size, wksp, wksp+size, wksp+2*size, wksp+3*size);
				if (!mp32isone(size, wksp+2*size))
					continue;
			}

			/* if cofactor is two, test if s is prime */
			if (cofactor == 2)
			{
				mp32bmu_w(&s, wksp);

				if (!mp32pmilrab_w(&s, rc, mp32ptrials(s.size << 5), wksp))
					continue;
			}

			/* candidate has passed so far, now we do the probabilistic test on p */
			mp32bmu_w(p, wksp);

			if (!mp32pmilrab_w(p, rc, t, wksp))
				continue;

			mp32nset(r, s.size, s.modl);
			(void) mp32multwo(r->size, r->data);
			mp32bfree(&s);

			return;
			/*@=usedef@*/
		}
	}
}

void mp32prndsafe_w(mp32barrett* p, randomGeneratorContext* rc, uint32 size, int t, uint32* wksp)
{
	/*
	 * Initialize with a probable safe prime of 'size' words, with probability factor t
	 *
	 * A safe prime p has the property that p = 2q+1, where q is also prime
	 * Use for ElGamal type schemes, where a generator of order (p-1) is required
	 */

	mp32binit(p, size);

	if (p->modl != (uint32*) 0)
	{
		mp32barrett q;

		mp32bzero(&q);
		mp32binit(&q, size);

		/*@-usedef@*/	/* q is set */
		while (1)
		{
			/*
			 * Generate a random appropriate candidate prime, and test
			 * it with small prime divisor test BEFORE computing mu
			 */

			mp32prndbits(p, 0, 2, rc);

			mp32copy(size, q.modl, p->modl);
			mp32divtwo(size, q.modl);

			/* do a small prime product trial division on q */
			if (!mp32psppdiv_w(&q, wksp))
				continue;

			/* do a small prime product trial division on p */
			if (!mp32psppdiv_w(p, wksp))
				continue;

			/* candidate prime has passed small prime division test for p and q */
			mp32bmu_w(&q, wksp);

			if (!mp32pmilrab_w(&q, rc, t, wksp))
				continue;

			mp32bmu_w(p, wksp);

			if (!mp32pmilrab_w(p, rc, t, wksp))
				continue;

			mp32bfree(&q);

			return;
		}
		/*@=usedef@*/
	}
}
