/*
                                   )
                                  (.)
                                  .|.
                                  | |
                              _.--| |--._
                           .-';  ;`-'& ; `&.
                          \   &  ;    &   &_/
                           |"""---...---"""|
                           \ | | | | | | | /
                            `---.|.|.|.---'

 * This file is generated by bake.lang.c for your convenience. Headers of
 * dependencies will automatically show up in this file. Include bake_config.h
 * in your main project file. Do not edit! */

#ifndef FEATURES_BAKE_CONFIG_H
#define FEATURES_BAKE_CONFIG_H

/* Headers of public dependencies */
#include <reflecs>

/* Headers of private dependencies */
#ifdef FEATURES_IMPL
/* No dependencies */
#endif

/* Convenience macro for exporting symbols */
#if FEATURES_IMPL && defined _MSC_VER
#define FEATURES_EXPORT __declspec(dllexport)
#elif FEATURES_IMPL
#define FEATURES_EXPORT __attribute__((__visibility__("default")))
#elif defined _MSC_VER
#define FEATURES_EXPORT __declspec(dllimport)
#else
#define FEATURES_EXPORT
#endif

#endif

