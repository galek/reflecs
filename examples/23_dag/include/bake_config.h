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

#ifndef DAG_BAKE_CONFIG_H
#define DAG_BAKE_CONFIG_H

/* Headers of public dependencies */
#include <reflecs>

/* Headers of private dependencies */
#ifdef DAG_IMPL
/* No dependencies */
#endif

/* Convenience macro for exporting symbols */
#if DAG_IMPL && defined _MSC_VER
#define DAG_EXPORT __declspec(dllexport)
#elif DAG_IMPL
#define DAG_EXPORT __attribute__((__visibility__("default")))
#elif defined _MSC_VER
#define DAG_EXPORT __declspec(dllimport)
#else
#define DAG_EXPORT
#endif

#endif

